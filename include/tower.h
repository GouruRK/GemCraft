#ifndef TOWERS_H
#define TOWERS_H

#include "gem.h"
#include "position.h"
#include "field.h"

#define MAX_TOWER WIDTH*HEIGHT

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
