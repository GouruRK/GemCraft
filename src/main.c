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
    Field field = generate_field();

    Monster wenjieFang = init_monster(field.nest, NORMAL, 1, field.camp);
    Player player = init_player();

    int terminated = 0;
    int count_frame = 0;
    while (!terminated) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        move_monster(&wenjieFang);
        if (field.camp.x + 0.4 < wenjieFang.pos.x &&
            wenjieFang.pos.x < field.camp.x + 0.6 &&
            field.camp.y - 0.4 < wenjieFang.pos.y &&
            wenjieFang.pos.y < field.camp.y + 0.6) {
            ban_monster(&wenjieFang, &player, &field);
        }

        draw_board(field);
        draw_monster(wenjieFang);
        MLV_update_window();

        clock_gettime(CLOCK_MONOTONIC, &end_time);

        time_difference = diff_time(start_time, end_time);

        extra_time = 1.0 / FRAMERATE - (time_difference.tv_nsec / 1000000000.0);
        if (extra_time > 0) {
            MLV_wait_milliseconds((int)(extra_time * 1000));
        }

        count_frame++;
        if (count_frame % 60 == 0) {
            fprintf(stderr, "frame : %d\n", count_frame / 60);
        }
    }

    MLV_wait_seconds(5);
    MLV_free_window();
    return 0;
}
