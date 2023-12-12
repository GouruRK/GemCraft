#ifndef NEST_H
#define NEST_H

#include "game_engine/monster.h"
#include "utils/position.h"
#include "utils/clock.h"

typedef struct {
    int monster_remaining;  // Number of monster to spawn
    Clock spawn_clock;
    TypeWave type_wave;
    Position pos;
} Nest;

/**
 * @brief Initialize a nest
 * 
 * @param pos Position of the nest
 * @return Nest 
 */
Nest init_nest(Position pos);

#endif
