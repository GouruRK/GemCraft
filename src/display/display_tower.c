#include "display/display_tower.h"

#include <MLV/MLV_all.h>

#include "display/display_const.h"
#include "display/draw_gems.h"

int corners[NB_BLOCKS][2] = {
    // top left corner
    {0, 0},
    {0, BLOCK_SIZE},
    {BLOCK_SIZE, 0},
    // top right corner
    {CELL_SIZE - BLOCK_SIZE, 0},
    {CELL_SIZE - BLOCK_SIZE*2, 0},
    {CELL_SIZE - BLOCK_SIZE, BLOCK_SIZE},
    // bottom left corner
    {0, CELL_SIZE - BLOCK_SIZE},
    {0, CELL_SIZE - BLOCK_SIZE*2},
    {BLOCK_SIZE, CELL_SIZE - BLOCK_SIZE},
    // bottom right corner
    {CELL_SIZE - BLOCK_SIZE, CELL_SIZE - BLOCK_SIZE},
    {CELL_SIZE - BLOCK_SIZE*2, CELL_SIZE - BLOCK_SIZE},
    {CELL_SIZE - BLOCK_SIZE, CELL_SIZE - BLOCK_SIZE*2},
};

void draw_tower(Tower tower) {
    MLV_draw_filled_rectangle(tower.pos.x*CELL_SIZE,
                              tower.pos.y*CELL_SIZE,
                              CELL_SIZE, CELL_SIZE,
                              MLV_rgba(85, 85, 85, 140));
    
    for (int i = 0; i < NB_BLOCKS; i++) {
        MLV_draw_filled_rectangle(tower.pos.x*CELL_SIZE + corners[i][0],
                                  tower.pos.y*CELL_SIZE + corners[i][1],
                                  BLOCK_SIZE, BLOCK_SIZE, MLV_COLOR_BLACK);
    }
    if (tower.hold_gem) {
        draw_gem(tower.pos, tower.gem);
    }
}

