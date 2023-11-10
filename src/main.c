#define _POSIX_C_SOURCE 199309L

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/display_game.h"
#include "../include/field.h"
#include "../include/game.h"
#include "../include/generation.h"
#include "../include/monster.h"
#include "../include/player.h"
#include "../include/position.h"

struct timespec diff_time(struct timespec start, struct timespec end) {
    struct timespec diff;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        diff.tv_sec = end.tv_sec - start.tv_sec - 1;
        diff.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        diff.tv_sec = end.tv_sec - start.tv_sec;
        diff.tv_nsec = end.tv_nsec - start.tv_nsec;
    }

    return diff;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    struct timespec start_time, end_time, time_difference;
    double extra_time;

    MLV_create_window("Tower Defense", NULL, WIDTH * CELL_SIZE,
                      HEIGHT * CELL_SIZE);

    Game game;
    init_game(&game);

    int terminated = 0;
    int count_frame = 0;
    while (!terminated) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        update_game(&game);

        // Drawing
        draw_board(game.field);
        
        draw_gem(init_position(20, 20), MLV_COLOR_GREEN1);
        draw_gem(init_position(19, 20), MLV_COLOR_BLUE);
        draw_gem(init_position(18, 20), MLV_COLOR_RED);

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

    MLV_wait_seconds(5);
    MLV_free_window();
    return 0;
}
