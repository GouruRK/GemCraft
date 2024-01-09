#ifndef NEST_H
#define NEST_H

#include "game_engine/monster.h"
#include "utils/position.h"
#include "utils/clock.h"

#define MAX_WAVE_NUMBER 3

typedef struct {
    int monster_remaining;
    Clock spawn_clock;
    TypeWave type;
} Wave;

typedef struct {
    Wave wave[MAX_WAVE_NUMBER];
    int nb_waves;
    Position pos;
} Nest;

/**
 * @brief Initialize a nest
 * 
 * @param pos Position of the nest
 * @return Nest 
 */
Nest init_nest(Position pos);

/**
 * @brief Generate one new wave inside the nest
 * 
 * @param nest
 * @param nb_wave
 */
void add_wave_nest(Nest* nest, int nb_wave);

#endif
