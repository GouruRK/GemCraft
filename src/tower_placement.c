#include <MLV/MLV_all.h>

#include "../include/position.h"
#include "../include/tower.h"


void update_tower_placement(Tower* tower, int cell_width) {
    int x, y;
    MLV_get_mouse_position(&x, &y);

    tower->pos = init_position(x / cell_width, y / cell_width);
}


