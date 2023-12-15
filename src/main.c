#define _POSIX_C_SOURCE 199309L

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display/display_game.h"
#include "game_engine/field.h"
#include "game_engine/game.h"
#include "game_engine/generation.h"
#include "game_engine/monster.h"
#include "game_engine/player.h"
#include "utils/position.h"
#include "utils/util.h"
#include "game_engine/projectile.h"
#include "user_event/interact.h"
#include "user_event/tower_placement.h"
#include "user_event/event.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    struct timespec start_time, end_time, time_difference;
    double extra_time;
    Game game;
    init_game(&game);

    MLV_create_window("Tower Defense", NULL, 
        game.sections.field_section.width + game.sections.inventory_section.width,
        game.sections.field_section.height);


    int terminated = 0;
    int count_frame = 0;
    while (!terminated) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        if (process_event(&game)) {
            break;
        }

        update_game(&game);

        // Drawing
        draw_game(&game);
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
            fprintf(stderr, "Frame : %d  Time to compute the frame : %ld\n", count_frame / FRAMERATE, time_difference.tv_nsec);
        }
    }

    MLV_free_window();

    return 0;
}
