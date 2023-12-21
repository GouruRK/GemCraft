#include "user_event/gem_placement.h"

#include <MLV/MLV_all.h>

#include "game_engine/inventory.h"
#include "display/game_sectors.h"
#include "display/display_const.h"
#include "user_event/interact.h"

int from_coord_to_index(const GameSectors* sectors, int x, int y) {
    x = (sectors->window.width - x) / CELL_SIZE;
    y = (sectors->window.height - y) / CELL_SIZE;

    return INVENTORY_SIZE - (y*2 + x) - 1;
}

void update_gem_movement(Interaction* interact) {
    if (interact->current_action != MOVING_GEM) {
        return;
    }

    int x, y;
    MLV_get_mouse_position(&x, &y);

    interact->object_pos = init_position(x / CELL_SIZE, y / CELL_SIZE);
}
