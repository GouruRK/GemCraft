#ifndef GAME_H
#define GAME_H

#include <time.h>

#include "errors.h"
#include "field.h"
#include "player.h"

#define FRAMERATE 60
#define TIMER_WAVE 35  // Max time between each wave

typedef enum {
    ONGOING,
    PAUSE,
} GameState;

typedef struct {
    int wave;                        // number of waves
    struct timespec time_next_wave;  // time before next wave
    struct timespec time;            // Time since the befinning of the game
    GameState game_status;
    Field field;    // game board
    Player player;  // player info
} Game;

/**
 * @brief Initialize all elements for a game
 *
 * @param game
 * @return Error
 */
Error init_game(Game* game);

/**
 * @brief Calculate everything to do in one frame
 * 
 * @param game 
 * @return Error 
 */
Error update_game(Game* game);

#endif
