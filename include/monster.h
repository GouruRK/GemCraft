#ifndef MONSTER_H
#define MONSTER_H

#include "position.h"

#define MAX_WAVE_SIZE 24

typedef enum {
    NONE,
    SPLASH,         // Pyro
    PARASIT,        // Dendro
    SLOW,           // Hydro
    SPRAYING,       // Pyro + Hydro
    BURN,           // Pyro + Dendro
    PETRIFICUS,     // Dendro + Hydro
} Status;

typedef enum {
    NORMAL,
    CROWD,
    FAST,
    BOSS
} TypeWave;

typedef struct {
    int health;
    float speed;
    int color;
    Position pos;
    Status status;
    float effect_duration;
} Monster;

typedef struct {
    int cur_size;
    TypeWave type;
    Monster lst[MAX_WAVE_SIZE];
} MonsterArray;

#endif
