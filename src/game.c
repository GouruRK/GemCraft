#include "../include/game.h"

#include <stdbool.h>
#include <stdio.h>

#include "../include/error.h"
#include "../include/field.h"  // needed to test towers
#include "../include/generation.h"
#include "../include/player.h"
#include "../include/tower.h"  // needed to test towers

Error init_game(Game* game) {
    game->wave = 0;

    game->time_next_wave = TIMER_WAVE * FRAMERATE;

    game->time.tv_sec = 0;
    game->time.tv_nsec = 0;

    game->game_status = ONGOING;
    game->field = generate_field();

    game->player = init_player();

    // PROTOTYEP adding a tower (first tower, free cost)
    place_tower(&(game->field), &(game->player),
                init_tower(init_position(27, 21)));
    place_tower(&(game->field), &(game->player),
                init_tower(init_position(27, 20)));
    place_tower(&(game->field), &(game->player),
                init_tower(init_position(27, 19)));
    place_tower(&(game->field), &(game->player),
                init_tower(init_position(27, 18)));
    place_tower(&(game->field), &(game->player),
                init_tower(init_position(27, 17)));

    return OK;
}

Error update_game(Game* game) {
    // Update the monsters
    for (int i = 0; i < game->field.monsters.curr_size; i++) {
        move_monster(&(game->field.monsters.lst[i]));

        if (has_reach_dest(&(game->field.monsters.lst[i]))) {
            update_monster_dest(&(game->field.monsters.lst[i]), &(game->field),
                                &(game->player));
        }
    }

    if (game->field.nest.monster_remaining > 0 &&
        game->field.nest.nb_frame_before_next_spawn == 0) {
        spawn_monster_field(&(game->field), game->wave,
                            game->field.nest.type_wave);
        game->field.nest.monster_remaining--;
        game->field.nest.nb_frame_before_next_spawn = game->field.nest.nb_frame_between_spawn;
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
