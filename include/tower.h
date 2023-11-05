#ifndef TOWERS_H
#define TOWERS_H

#include "gem.h"
#include "position.h"

#define MAX_TOWER 28*22

typedef struct {
    Gem gem;
    Position pos;
} Tower;

typedef struct {
    Tower lst[MAX_TOWER];
    int cur_len;
    int next_tower_coast;
} TowerArray;

#endif
