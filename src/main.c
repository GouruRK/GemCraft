#define _POSIX_C_SOURCE 199309L

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "display/display_game.h"
#include "display/display_score.h"
#include "game_engine/field.h"
#include "game_engine/game.h"
#include "game_engine/generation.h"
#include "game_engine/monster.h"
#include "game_engine/player.h"
#include "utils/position.h"
#include "utils/util.h"
#include "utils/command_line.h"
#include "game_engine/projectile.h"
#include "user_event/interact.h"
#include "user_event/tower_placement.h"
#include "user_event/event.h"

/**
 * @brief Free allocated memory for the game
 * 
 * @param game 
 */
static void free_memory(Game* game) {
    free(game->field.projectiles.array);
}

static void print_help(void) {
    printf("Usage: GemCraft [OPTION...] \n"
           "Play a Tower Defense game !\n\n"
           "  -h, --help\t\tdisplay this help message and exit\n"
           );
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    bool help = false;
    if (command_line(&help, argc, argv) != OK) {
        return 1;
    }
    if (help) {
        print_help();
        return 0;
    }

    struct timespec start_time, end_time, time_difference;
    double extra_time;
    Game game;
    int terminated = 0;
    init_game(&game);

    // set terminated to '1' whenever the exit button of MLV is trigger
    // Allows to properly exit the main loop for memory liberation
    // Without this instruction, exit button exit the program 
    MLV_execute_at_exit(exit_function, &terminated);

    MLV_create_window("Tower Defense", "Tower Defense",
                      game.sectors.window.width, game.sectors.window.height);

    while (!terminated && !is_game_over(&game)) {
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        if (process_event(&game)) {
            break;
        }

        if (game.game_status == ONGOING) {
            update_game(&game);
            draw_game(&game);
        } else if (game.game_status == SKILL) {
            draw_game(&game);
        }

        clock_gettime(CLOCK_MONOTONIC, &end_time);

        time_difference = diff_time(start_time, end_time);

        extra_time = 1.0 / FRAMERATE - (time_difference.tv_nsec / 1000000000.0);
        if (extra_time > 0) {
            MLV_wait_milliseconds((int)(extra_time * 1000));
        }
    }

    free_memory(&game);

    if (is_game_over(&game)) {
        display_score(&(game.score), &(game.sectors));
        wait_event(&terminated);
    }

    MLV_free_window();
    return 0;
}
