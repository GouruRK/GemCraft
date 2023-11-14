#ifndef NEST_H
#define NEST_H

#include "monster.h"
#include "position.h"
#include "clock.h"

typedef struct {
    int monster_remaining;  // Number of monster to spawn
    Clock spawn_clock;
    // int nb_frame_before_next_spawn;
    // int nb_frame_between_spawn;
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
