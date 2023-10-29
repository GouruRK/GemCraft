#ifndef MONSTER_H
#define MONSTER_H

#include "position.h"
#include "gem.h"

typedef struct {
    int health;
    float speed;
    int color;
    Position pos;
    Effect effect;
    float effect_duration;
} Monster;

typedef struct {
    Monster* lst;
    int max_len;
    int cur_size;
} MonsterList;

#endif
