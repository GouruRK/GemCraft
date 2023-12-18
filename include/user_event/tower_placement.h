#ifndef TOWER_PLACEMENT_H
#define TOWER_PLACEMENT_H

#include "game_engine/tower.h"

Tower init_tower_at_mouse(void);

void update_tower_placement(Tower* tower);

#endif
