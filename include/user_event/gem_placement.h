#ifndef GEM_PLACEMENT_H
#define GEM_PLACEMENT_H

#include "display/game_sectors.h"
#include "user_event/interact.h"

/**
 * @brief Transform on screen coordinates to an index of the inventory
 * 
 * @param sectors
 * @param x 
 * @param y 
 * @return
 */
int from_coord_to_index(const GameSectors* sectors, int x, int y);

/**
 * @brief Update interact position when moving a gem
 * 
 * @param interact 
 */
void update_gem_movement(const GameSectors* sectors, Interaction* interact);

#endif
