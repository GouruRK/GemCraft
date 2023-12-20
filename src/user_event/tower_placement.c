#include <MLV/MLV_all.h>

#include "utils/position.h"
#include "game_engine/tower.h"
#include "display/game_sectors.h"
#include "display/display_const.h"

Tower init_tower_at_mouse(Sector panel) {
    int x, y;
    MLV_get_mouse_position(&x, &y);

    if (is_coord_in_sector(panel, x, y)) {
        x = panel.top_left.x - 1;
    }

    printf("x: %d, y: %d\n", x, y);
    return init_tower(init_position(x / CELL_SIZE, y / CELL_SIZE));
}

void update_tower_placement(Sector panel, Tower* tower) {
    int x, y;
    MLV_get_mouse_position(&x, &y);

    if (is_coord_in_sector(panel, x, y)) {
        return;
    }
    
    tower->pos = init_position(x / CELL_SIZE, y / CELL_SIZE);
}
