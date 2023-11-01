#ifndef TOWERS_H
#define TOWERS_H

#include "gem.h"
#include "position.h"
#include "errors.h"

#define MAX_TOWER 616

typedef struct {
    Gem gem;
    PositionInt pos;
} Tower;

typedef struct {
    Tower lst[MAX_TOWER];
    int cur_len;
    int next_tower_cost;
} TowerArray;

Tower crate_tower(Gem gem, PositionInt pos);

TowerArray create_tower_array(void);

Error add_tower_array(TowerArray* array, Tower tower);

#endif
