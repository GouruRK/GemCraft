#include "user_event/gem_placement.h"

#include "game_engine/inventory.h"
#include "display/game_sectors.h"
#include "display/display_const.h"

int from_coord_to_index(const GameSectors* sectors, int x, int y) {
    x = (sectors->window.width - x) / CELL_SIZE;
    y = (sectors->window.height - y) / CELL_SIZE;

    return INVENTORY_SIZE - (y*2 + x) - 1;
}
