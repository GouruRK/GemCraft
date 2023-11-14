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
#include "interact.h"
#include "tower_placement.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    struct timespec start_time, end_time, time_difference;
    double extra_time;

    // PROTOTYPE events

    // intel on keyboard
    MLV_Keyboard_modifier mod;
    MLV_Keyboard_button sym;
    MLV_Button_state state;

    // intel on mouse
    MLV_Mouse_button mouse_but;

    // event code
    MLV_Event event;

    MLV_create_window("Tower Defense", NULL, WIDTH * CELL_SIZE,
                      HEIGHT * CELL_SIZE);

    Game game;
    init_game(&game);

    int terminated = 0;
    int count_frame = 0;
    while (!terminated) {
        // PROTOTYPE Reading event
        event = MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL, NULL, &mouse_but,
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
                case 't': // place a tower
                    if (game.player.mana > game.field.towers.next_tower_cost) {
                        set_interact_tower_placement(&(game.cur_interact), init_tower_at_mouse(CELL_SIZE));
                    }
                    break;
                default:
                    break;
            }
        } else if(event == MLV_MOUSE_BUTTON) {
            switch (mouse_but) {
                case MLV_BUTTON_LEFT:
                    if (game.cur_interact.current_action == PLACING_TOWER) {
                        drop_tower(&(game.cur_interact), &(game.field), &(game.player));
                    }
                    break;
                case MLV_BUTTON_RIGHT:
                    cancel_interaction(&(game.cur_interact));
                    break;
                default:
                    break;
            }
        }

        // End reading event

        clock_gettime(CLOCK_MONOTONIC, &start_time);

        update_game(&game);

        // Drawing
        draw_board(game.field);

        for (int i = 0; i < game.field.monsters.curr_size; i++) {
            draw_monster(&game.field.monsters.lst[i]);
        }

        // Prototype
        if (game.cur_interact.current_action == PLACING_TOWER) {
            update_tower_placement(&(game.cur_interact.selected_tower), CELL_SIZE);
            draw_tower(game.cur_interact.selected_tower);
        }


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
