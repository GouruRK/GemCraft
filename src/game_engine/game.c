#include "game_engine/game.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "display/game_sectors.h"
#include "display/display_skill_tree.h"
#include "game_engine/field.h"
#include "game_engine/generation.h"
#include "game_engine/monster.h"
#include "game_engine/nest.h"
#include "game_engine/player.h"
#include "game_engine/projectile.h"
#include "game_engine/score.h"
#include "game_engine/tower.h"
#include "user_event/interact.h"
#include "user_event/tower_placement.h"
#include "user_event/error_message.h"
#include "user_event/skill_tree.h"
#include "utils/clock.h"
#include "utils/errors.h"

Error init_game(Game* game) {
    game->wave = 0;

    game->time_until_next_wave = init_clock(-1, -1);

    game->game_status = ONGOING;
    game->field = generate_field();
    if (init_projectile_array(&(game->field.projectiles)) == ALLOCATION_ERROR) {
        return ALLOCATION_ERROR;
    }
    game->field.towers = init_tower_array();
    init_monster_array(&(game->field.monsters));

    game->player = init_player();
    game->cur_interact = init_interact();
    game->sectors = init_game_sectors();
    game->score = init_score();
    game->tree = init_skill_tree(&(game->player), 1);
    return OK;
}

/**
 * @brief Calculate monster state for the current frame
 *
 * @param monster
 * @param field
 * @param player
 * @return Error
 */
static Error update_monster(Monster* monster, Score* score, Field* field,
                            Player* player) {
    update_effect_monster(monster, score);

    if (!is_alive(monster)) {  // If the monster dies of effect
        long long mana_drop =
            monster->max_health * 0.1 * pow(1.3, player->mana_lvl);
        player->mana = min(player->max_quantity, mana_drop + player->mana);
        return OK;
    }

    move_monster(monster);

    if (has_reach_dest(monster)) {
        update_monster_dest(monster, field, player);
    }

    return OK;
}

static void update_wave(Wave* w, Game* game) {
    if (w->monster_remaining > 0 && w->spawn_clock.next_interval == 0) {
        spawn_monster_field(&(game->field), game->wave, w->type);
        w->monster_remaining--;
    }

    decrease_clock(&w->spawn_clock);
}

/**
 * @brief Spawn monsters from the nest
 *
 * @param game
 */
static void update_nest(Game* game) {
    for (int i = 0; i < game->field.nest.nb_waves; i++) {
        if (game->field.nest.wave[i].monster_remaining > 0) {
            update_wave(&game->field.nest.wave[i], game);
        }
    }

    if (game->wave >= 1 && game->time_until_next_wave.next_interval == 0) {
        add_wave_nest(&(game->field.nest), &(game->score), game->wave);
        game->wave++;
        if (!(game->wave % WAVE_OFFSET)) {
            game->game_status = SKILL;
            replace_skill(&(game->tree), &(game->player), game->wave);
        }
    }

    decrease_clock(&game->time_until_next_wave);
}

static void update_projectiles(ProjectileArray* array, Score* score,
                               MonsterArray* monster_array, Player* player) {
    for (int i = 0; i < array->nb_elt; i++) {
        int suppress_proj = 0;
        if (!is_alive(array->array[i].target)) {
            suppress_proj = 1;
        } else if (has_reach_target(&(array->array[i]))) {
            hit_target(&(array->array[i]), score, monster_array, player);
            // if the projectile kill his target
            if (!is_alive(array->array[i].target)) {
                long long mana_drop =
                    array->array[i].target->max_health * 0.1 *
                    pow(1.3, player->mana_lvl);
                player->mana =
                    min(player->max_quantity, mana_drop + player->mana);
            }

            suppress_proj = 1;
        } else {
            move_projectile(&(array->array[i]));
        }

        if (suppress_proj) {
            suppress_proj_index(array, i);
            i--;
        }
    }
}

static void update_tower(Tower* tower, MonsterArray* monsters,
                         ProjectileArray* projectiles) {
    if (!tower->hold_gem) return;

    if (tower->deploy_timer.remaining_time > 0) {
        decrease_clock(&tower->deploy_timer);
        return;
    }

    if (tower->shoot_interval.remaining_time == 0) {
        Monster* target = NULL;
        // Find the monster with the most health within range of dist tiles
        float dist = calc_radius_shoot_range(&tower->gem);
        for (int i = 0; i < monsters->array_size; i++) {
            if (is_alive(&monsters->array[i]) &&
                calc_distance(cell_center(tower->pos),
                              monsters->array[i].pos) <= dist) {
                if (target == NULL ||
                    target->health < monsters->array[i].health) {
                    target = &monsters->array[i];
                }
            }
        }
        if (target) {
            Projectile proj =
                init_projectile(cell_center(tower->pos), target, tower->gem);
            add_projectile_array(projectiles, proj);
            tower->shoot_interval =
                init_clock(-1, 0.5 - tower->gem.level / 100.0);
        }
    }

    decrease_clock(&tower->shoot_interval);
}

static void update_towers(TowerArray* towers, MonsterArray* monsters,
                          ProjectileArray* projectiles) {
    for (int i = 0; i < towers->cur_len; i++) {
        update_tower(&towers->lst[i], monsters, projectiles);
    }
}

Error update_game(Game* game) {
    // Update the monsters
    for (int i = 0; i < game->field.monsters.array_size; i++) {
        if (is_alive(&(game->field.monsters.array[i]))) {
            update_monster(&(game->field.monsters.array[i]), &(game->score),
                           &(game->field), &(game->player));
        }
    }

    update_nest(game);

    update_towers(&game->field.towers, &game->field.monsters,
                  &game->field.projectiles);

    update_projectiles(&(game->field.projectiles), &(game->score),
                       &(game->field.monsters), &(game->player));

    if (game->cur_interact.err.contains_message) {
        decrease_clock(&(game->cur_interact.err.clock));
        if (!game->cur_interact.err.clock.remaining_time) {
            game->cur_interact.err.contains_message = false;
        }
    }
    
    int max_level = search_max_gem_level_with_mana(&(game->player));
    game->cur_interact.gem_level = min(max_level, game->cur_interact.gem_level);

    if (game->game_status == SKILL && !game->tree.has_sectors) {
        init_sectors(&(game->tree), game->sectors.window);
    }

    return OK;
}

bool is_game_over(Game* game) {
    if (game->player.mana <= 0) {
        game->game_status = OVER;
        return true;
    }
    return false;
}
