#define _POSIX_C_SOURCE 199309L

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display_game.h"
#include "field.h"
#include "game.h"
#include "generation.h"
#include "monster.h"
#include "player.h"
#include "position.h"
#include "util.h"
#include "projectile.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    struct timespec start_time, end_time, time_difference;
    double extra_time;

    // PROTOTYPE events

    // intel on keyboard
    MLV_Keyboard_modifier mod;
    MLV_Keyboard_button sym;
    MLV_Button_state state;

    // event code
    MLV_Event event;

    MLV_create_window("Tower Defense", NULL, WIDTH * CELL_SIZE,
                      HEIGHT * CELL_SIZE);

    Game game;
    init_game(&game);

    // PROTOTYPE Adding a projectile
    Position proj_pos = {0.5, 0.5};
    Projectile proj;
    proj.target = NULL;
    Position pos_proj2 = {1.5, 1.5};
    Projectile proj_2;
    proj_2.target = NULL;

    int terminated = 0;
    int count_frame = 0;
    while (!terminated) {
        // PROTOTYPE Reading event
        event = MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL, NULL, NULL,
                              &state);

        if (event == MLV_KEY) {
            switch (sym) {
                case 'q':  // Quit the game
                    terminated = 1;
                    break;

                case 'w': // Summon a wave
                    if (game.field.nest.monster_remaining == 0) {
                        fprintf(stderr, "%c\n", sym);
                        init_new_wave(&(game.field.nest), game.wave);
                        game.wave++;
                    }
                    break;
                default:
                    break;
            }
        }

        // End reading event

        clock_gettime(CLOCK_MONOTONIC, &start_time);

        update_game(&game);

        if (game.field.monsters.curr_size == 1) {
            proj = init_projectile(proj_pos, &game.field.monsters.lst[0], create_gem(HYDRO, 1, 240));
            proj_2 = init_projectile(pos_proj2, &game.field.monsters.lst[0], create_gem(PYRO, 1, 0));
        }

        // PROTOTYPE update one projectile
        if (proj.target) {update_projectile(&proj, &(game.field.monsters)); };
        if (proj_2.target) {update_projectile(&proj_2, &(game.field.monsters));};

        // Drawing
        draw_board(game.field);

        for (int i = 0; i < game.field.monsters.curr_size; i++) {
            draw_monster(&game.field.monsters.lst[i]);
        }

        // PROTOTYPE draw one projectile
        if (proj.target) {draw_projectile(&proj);};
        if (proj_2.target) {draw_projectile(&proj_2);};

        MLV_update_window();
        // End drawing

        clock_gettime(CLOCK_MONOTONIC, &end_time);

        time_difference = diff_time(start_time, end_time);

        extra_time = 1.0 / FRAMERATE - (time_difference.tv_nsec / 1000000000.0);
        if (extra_time > 0) {
            MLV_wait_milliseconds((int)(extra_time * 1000));
        }

        // PROTOTYPE just to count some frame for debugging
        count_frame++;
        if (count_frame % FRAMERATE == 0) {
            fprintf(stderr, "frame : %d\n", count_frame / FRAMERATE);
        }
    }

    MLV_free_window();
    free(game.field.monsters.lst);

    return 0;
}
