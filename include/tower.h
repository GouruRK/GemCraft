#ifndef TOWERS_H
#define TOWERS_H

#include "gem.h"
#include "position.h"

typedef struct {
    Gem gem;
    Position pos;
} Tower;

typedef struct {
    Tower* lst;
    int max_size;
    int cur_len;
} TowerList;

#endif
