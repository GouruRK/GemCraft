#include "display/draw_inventory.h"

#include <MLV/MLV_all.h>
#include <stdio.h>

#include "game_engine/inventory.h"
#include "game_engine/gem.h"
#include "display/draw_gems.h"
#include "display/color.h"
#include "display/display_const.h"
#include "utils/sector.h"
#include "utils/position.h"

static void transform_coords(int index, int* x, int* y) {
    *x = index % 2; // 2 because inventory contains to columns
    *y = index / 2;
}

/**
 * @brief Draw inventory layout
 * 
 * @param inventory sector where inventory is placed
 */
static void draw_inventory_layout(Sector info) {
    int top_y = info.bottom_right.y - INVENTORY_HEIGHT;
    MLV_draw_filled_rectangle(info.top_left.x, 
                              top_y,
                              info.width,
                              INVENTORY_HEIGHT,
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

void draw_inventory(Inventory inventory, Sector info) {
    draw_inventory_layout(info);
    int x, y;
    Gem gem;
    
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (!inventory.array[i].empty) {
            gem = inventory.array[i].gem;
            transform_coords(i, &x, &y);

            draw_gem(init_position(WIDTH + x, HEIGHT - INVENTORY_SIZE/2 + y), gem);
        }
    }
}
