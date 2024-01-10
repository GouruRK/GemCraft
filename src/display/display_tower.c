#include "display/display_tower.h"

#include <MLV/MLV_all.h>
#include <math.h>

#include "display/display_const.h"
#include "display/draw_gems.h"
#include "utils/util.h"
#include "game_engine/game.h"
#include "game_engine/tower.h"

#define NB_POINT_CIRCLE 100

// Top left coordinates of blocks of tower corners
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

/**
 * @brief Draw regular polygon to simulate part of a circle
 * 
 * @param x // Center of the
 * @param y 
 * @param radius 
 * @param start_angle 
 * @param end_angle 
 * @param color 
 */
static void draw_filled_partial_circle(int x, int y, int radius, 
                                       double start_angle, double end_angle, 
                                       MLV_Color color) {
    int ax[NB_POINT_CIRCLE];
    int ay[NB_POINT_CIRCLE];

    ax[0] = x;
    ay[0] = y;

    float step = (end_angle - start_angle) / NB_POINT_CIRCLE;
    for (int i = 1; i < NB_POINT_CIRCLE; i++) {
        ax[i] = x + radius * cos(start_angle + (i - 1) * step);
        ay[i] = y + radius * sin(start_angle + (i - 1) * step);
    }

    MLV_draw_filled_polygon(ax, ay, NB_POINT_CIRCLE, color);
}

static void draw_reload_time (Tower tower) {
    Position tower_pos = cell_center(tower.pos);
    int x = tower_pos.x * CELL_SIZE;
    int y = tower_pos.y * CELL_SIZE;

    MLV_Color grey = MLV_rgba(0, 0, 0, 100);
    MLV_Color light_grey = MLV_rgba(200, 200, 200, 200);
    int radius = CELL_SIZE / 2.3;
    MLV_draw_filled_circle(x, y, radius, grey);
    
    double start_angle = 7 * M_PI / 2;
    double end_angle = 3 * M_PI / 2;
    double step = (start_angle - end_angle) / (TOWER_DEPLOY_TIME * FRAMERATE);
    end_angle -= step * tower.deploy_timer.remaining_time;
    draw_filled_partial_circle(x, y, radius, start_angle, end_angle, 
                               light_grey);
}

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
        if (tower.deploy_timer.remaining_time > 0) {
            draw_reload_time(tower);
        }
    }
}

