#ifndef GEM_PLACEMENT_H
#define GEM_PLACEMENT_H

#include "display/game_sectors.h"
#include "user_event/interact.h"

int from_coord_to_index(const GameSectors* sectors, int x, int y);

void update_gem_movement(Interaction* interact);

#endif
