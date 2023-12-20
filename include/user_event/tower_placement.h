#ifndef TOWER_PLACEMENT_H
#define TOWER_PLACEMENT_H

#include "game_engine/tower.h"
#include "utils/sector.h"

Tower init_tower_at_mouse(Sector panel);

void update_tower_placement(Sector panel, Tower* tower);

#endif
