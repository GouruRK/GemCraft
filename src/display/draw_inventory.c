#include <MLV/MLV_all.h>
#include <stdio.h>

#include "game_engine/inventory.h"
#include "utils/sector.h"
#include "display/display_game.h"

void draw_inventory_layout(Sector info) {
    int height = INVENTORY_SIZE / 2 * CELL_SIZE;
    int top_y = info.bottom_right.y - height;
    MLV_draw_filled_rectangle(info.top_left.x, 
                              top_y,
                              info.width,
                              height,
                              MLV_COLOR_DARKSLATEGREY);
    
    // horizontal
    for (int y = 0; y < INVENTORY_SIZE / 2; y++) {
        MLV_draw_line(info.top_left.x, top_y + y*CELL_SIZE, info.bottom_right.x, top_y + y*CELL_SIZE, MLV_COLOR_BLACK);
    }

    // vertical
    for (int x = 0; x < 2; x++) {
        MLV_draw_line(info.top_left.x + x*CELL_SIZE, top_y, info.top_left.x + x*CELL_SIZE, info.bottom_right.y, MLV_COLOR_BLACK);
    }

}


