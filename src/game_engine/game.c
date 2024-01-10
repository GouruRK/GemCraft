#include "game_engine/game.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "display/game_sectors.h"
#include "game_engine/score.h"
#include "game_engine/field.h"
#include "game_engine/generation.h"
#include "game_engine/player.h"
#include "game_engine/projectile.h"
#include "game_engine/tower.h"
#include "user_event/interact.h"
#include "user_event/tower_placement.h"
#include "utils/clock.h"
#include "utils/errors.h"

Error init_game(Game* game) {
    game->wave = 0;

    game->time.tv_sec = 0;
    game->time.tv_nsec = 0;

    game->game_status = ONGOING;
    game->field = generate_field();
    if (init_projectile_array(&(game->field.projectiles)) == ALLOCATION_ERROR) {
        return ALLOCATION_ERROR;
    }
    game->field.towers = init_tower_array();

    game->player = init_player();
    game->cur_interact = init_interact();
    game->sectors = init_game_sectors();
    game->score = init_score();
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
static Error update_monster(Monster* monster, Score* score, Field* field, Player* player) {
    update_effect_monster(monster, score);

    move_monster(monster);

    if (has_reach_dest(monster)) {
        update_monster_dest(monster, field, player);
    }

    return OK;
}

/**
 * @brief Spawn monsters
 *
 * @param game
 */
static void update_nest(Game* game) {
    if (game->field.nest.monster_remaining > 0 &&
        game->field.nest.spawn_clock.next_interval == 0) {
        spawn_monster_field(&(game->field), game->wave,
                            game->field.nest.type_wave);
        if (game->field.nest.monster_remaining == 1) {
            game->field.nest.spawn_clock = init_clock(TIMER_WAVE, -1);
        }
        game->field.nest.monster_remaining--;
        game->field.nest.spawn_clock.next_interval =
            game->field.nest.spawn_clock.interval;
    } else if (game->wave >= 1 &&
               game->field.nest.spawn_clock.next_interval == 0) {
        init_new_wave(&(game->field.nest), &(game->score), game->wave);
        game->wave++;
    }
}

/**
 * @brief Update all clocks in the game
 *
 * @param game
 */
static void update_clocks(Game* game) {
    decrease_clock(&game->field.nest.spawn_clock);
}

static void update_projectiles(ProjectileArray* array, Score* score,
                               MonsterArray* monster_array, Player* player) {
    for (int i = 0; i < array->nb_elt; i++) {
        if (!is_alive(array->array[i].target)) {
            suppress_proj_index(array, i);
        } else if (has_reach_target(&(array->array[i]))) {
            hit_target(&(array->array[i]), score, monster_array);
            // if the projectile kill his target
            if (!is_alive(array->array[i].target)) {
                int mana_drop = array->array[i].target->max_health * 0.1 *
                                pow(1.3, player->mana_lvl);
                player->mana =
                    min(player->max_quantity, mana_drop + player->mana);
            }

            suppress_proj_index(array, i);
        } else {
            move_projectile(&(array->array[i]));
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

    if (tower->shoot_interval.next_interval == 0) {
        Monster* target = NULL;
        // Find the monster with the most health within range of dist tiles
        float dist = 3 + tower->gem.level / 10.0;
        for (int i = 0; i < monsters->array_size; i++) {
            if (is_alive(&monsters->array[i]) &&
                calc_distance(cell_center(tower->pos), monsters->array[i].pos) <= dist) {
                if (target == NULL ||
                    target->health < monsters->array[i].health) {
                    target = &monsters->array[i];
                }
            }
        }
        if (target) {
            Projectile proj = init_projectile(cell_center(tower->pos), target,
            tower->gem);
            add_projectile_array(projectiles, proj);
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
            update_monster(&(game->field.monsters.array[i]), &(game->score), &(game->field),
                           &(game->player));
        }
    }

    update_nest(game);

    update_towers(&game->field.towers, &game->field.monsters,
                    &game->field.projectiles);

    update_projectiles(&(game->field.projectiles), &(game->score),
                       &(game->field.monsters), &(game->player));

    update_clocks(game);

    return OK;
}

bool is_game_over(Game* game) {
    if (game->player.mana <= 0) {
        game->game_status = OVER;
        return true;
    }
    return false;
}
