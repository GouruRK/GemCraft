#include <MLV/MLV_all.h>

#include "utils/position.h"
#include "game_engine/tower.h"
#include "display/display_const.h"

Tower init_tower_at_mouse(void) {
    int x, y;
    MLV_get_mouse_position(&x, &y);

    return init_tower(init_position(x / CELL_SIZE, y / CELL_SIZE));
}

void update_tower_placement(Tower* tower) {
    int x, y;
    MLV_get_mouse_position(&x, &y);

    tower->pos = init_position(x / CELL_SIZE, y / CELL_SIZE);
}
