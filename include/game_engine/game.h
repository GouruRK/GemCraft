#ifndef GAME_H
#define GAME_H

#include <time.h>

#include "utils/errors.h"
#include "game_engine/field.h"
#include "game_engine/player.h"
#include "game_engine/projectile.h"
#include "user_event/interact.h"
#include "display/game_sectors.h"

#define FRAMERATE 60
#define TIMER_WAVE 35  // Max time between each wave in seconds

typedef enum {
    ONGOING,
    PAUSE,
} GameState;

typedef struct {
    int wave;                   // number of waves
    int time_next_wave;         // number of frame before the next wave
    struct timespec time;       // Time since the befinning of the game
    GameState game_status;
    Field field;                // game board
    Player player;              // player info
    Interaction cur_interact;   // current player interaction
    GameSectors sectors;       // differencies window's section for inventory and field
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

/**
 * @brief PROTOTYPE updating one projectile
 * 
 * @param proj 
 * @return Error 
 */
Error update_projectile(Projectile* proj, MonsterArray* array);

#endif
