#include "game.h"

#include <stdbool.h>
#include <stdio.h>

#include "clock.h"
#include "error.h"
#include "field.h"  // needed to test towers
#include "generation.h"
#include "player.h"
#include "projectile.h"
#include "tower.h"  // needed to test towers

Error init_game(Game* game) {
    game->wave = 0;

    game->time.tv_sec = 0;
    game->time.tv_nsec = 0;

    game->game_status = ONGOING;
    game->field = generate_field();

    game->player = init_player();

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
static Error update_monster(Monster* monster, Field* field, Player* player) {
    update_effect_monster(monster);

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
        init_new_wave(&(game->field.nest), game->wave);
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

Error update_game(Game* game) {
    // Update the monsters
    for (int i = 0; i < game->field.monsters.curr_size; i++) {
        if (is_alive(&(game->field.monsters.lst[i]))) {
            update_monster(&(game->field.monsters.lst[i]), &(game->field),
                           &(game->player));
        }
    }

    update_nest(game);

    // Update timer of objects
    update_clocks(game);

    return OK;
}

Error update_projectile(Projectile* proj, MonsterArray* array) {
    if (has_reach_target(proj)) {
        hit_target(proj, array);
        // PROTOTYPE should suppress the proj
        proj->target = NULL;
        return OK;
    }
    move_projectile(proj);
    return OK;
}
