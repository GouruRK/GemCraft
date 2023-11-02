#ifndef MONSTER_H
#define MONSTER_H

#include <time.h>

#include "position.h"

#define MAX_WAVE_SIZE 24

typedef enum {
    NONE,
    SPLASH,      // Pyro
    PARASIT,     // Dendro
    SLOW,        // Hydro
    SPRAYING,    // Pyro + Hydro
    BURN,        // Pyro + Dendro
    PETRIFICUS,  // Dendro + Hydro
} Status;

typedef enum { NORMAL, CROWD, FAST, BOSS } TypeWave;

typedef struct {
    int health;
    int max_health;
    int color;
    float speed;  // Number of cases per seconde traveled
    struct timespec effect_duration;
    Position pos;
    Position dest;
    Status status;
} Monster;

typedef struct {
    int cur_size;
    TypeWave type;
    Monster lst[MAX_WAVE_SIZE];
} MonsterArray;

/**
 * @brief Initialize a monster
 *
 * @param pos_init Initial position on the field
 * @param type_wave
 * @param wave_number
 * @param dest
 * @return Monster
 */
Monster init_monster(Position pos_init, TypeWave type_wave, int wave_number,
                     Position dest);

/**
 * @brief Move a monster in toward his destination
 *
 * @param monster
 * @param destination a position on the field
 */
void move_monster(Monster* monster);

#endif
