#ifndef TOWERS_H
#define TOWERS_H

#include <stdbool.h>

#include "gem.h"
#include "position.h"
#include "errors.h"

#define MAX_TOWER 616

typedef struct {
    Gem gem;
    bool hold_gem;
    Position pos;
} Tower;

typedef struct {
    Tower lst[MAX_TOWER];
    int cur_len;
    int next_tower_cost;
} TowerArray;

Tower init_tower(Position pos);

Error add_gem_to_tower(Tower* tower, Gem gem);

Error remove_gem_to_tower(Tower* tower, Gem* gem);

TowerArray create_tower_array(void);

Error add_tower_array(TowerArray* array, Tower tower);

#endif
