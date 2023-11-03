#include "../include/game.h"

#include <stdio.h>

#include "../include/error.h"
#include "../include/generation.h"
#include "../include/player.h"

Error init_game(Game* game) {
    game->wave = 0;

    game->time_next_wave.tv_sec = TIMER_WAVE;
    game->time_next_wave.tv_nsec = 0;

    game->time.tv_sec = 0;
    game->time.tv_nsec = 0;

    game->game_status = ONGOING;
    game->field = generate_field();

    game->player = init_player();

    // PROTOTYPE adding a single monster
    spawn_monster_field(&game->field, 0, NORMAL);

    return OK;
}

Error update_game(Game* game) {
    // Update the monsters
    for (int i = 0; i < game->field.monsters.curr_size; i++) {
        move_monster(&(game->field.monsters.lst[i]));

        if (has_reach_dest(&(game->field.monsters.lst[i]))) {
            update_monster_dest(&(game->field.monsters.lst[i]), &(game->field), &(game->player));
        }
    }

    return OK;
}
