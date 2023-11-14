#include "game.h"

#include <stdbool.h>
#include <stdio.h>

#include "error.h"
#include "field.h"  // needed to test towers
#include "generation.h"
#include "player.h"
#include "projectile.h"
#include "interact.h"
#include "tower.h"  // needed to test towers"
#include "interact.h"
#include "tower_placement.h"

Error init_game(Game* game) {
    game->wave = 0;

    game->time_next_wave = TIMER_WAVE * FRAMERATE;

    game->time.tv_sec = 0;
    game->time.tv_nsec = 0;

    game->game_status = ONGOING;
    game->field = generate_field();

    game->player = init_player();
    game->cur_interact = init_interact();

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

Error update_game(Game* game) {
    // Update the monsters
    for (int i = 0; i < game->field.monsters.curr_size; i++) {
        if (is_alive(&(game->field.monsters.lst[i]))) {
            update_monster(&(game->field.monsters.lst[i]), &(game->field),
                           &(game->player));
        }
    }

    if (game->field.nest.monster_remaining > 0 &&
        game->field.nest.nb_frame_before_next_spawn == 0) {
        spawn_monster_field(&(game->field), game->wave,
                            game->field.nest.type_wave);
        game->field.nest.monster_remaining--;
        game->field.nest.nb_frame_before_next_spawn =
            game->field.nest.nb_frame_between_spawn;
    }

    // Update timer of objects
    if (game->field.nest.nb_frame_before_next_spawn > 0) {
        game->field.nest.nb_frame_before_next_spawn--;
    }
    if (game->time_next_wave > 0) {
        game->time_next_wave--;
    }

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
