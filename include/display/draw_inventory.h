#ifndef DRAW_INVENTORY_H
#define DRAW_INVENTORY_H

#include "game_engine/field.h"
#include "display/display_game.h"
#include "utils/sector.h"

/**
 * @brief Draw inventory layout and its content
 * 
 * @param inventory inventory to draw
 * @param info sector where inventory is placed
 */
void draw_inventory(Inventory inventory, Sector sector);

#endif
