#include "display/draw_gems.h"

#include <MLV/MLV_all.h>

#include "utils/position.h"
#include "display/color.h"
#include "display/display_const.h"

#define NB_HEXA_VRTX 6
#define NB_SQ_VRTX   4
#define NB_TRIG_VRTX 3
#define PADDING 1

/**
 * @brief Draw outlines of a gem
 * 
 * @param pos middle of the gem to draw
 * @param points array of points that forms the outline
 * @param length length of the array
 */
static void draw_outline(Position pos, float points[][2], int length) {
    for (int i = 0; i < length - 1; i++) {
        MLV_draw_line((pos.x + points[i][0])*CELL_SIZE,
                      (pos.y + points[i][1])*CELL_SIZE, 
                      (pos.x + points[i + 1][0])*CELL_SIZE,
                      (pos.y + points[i + 1][1])*CELL_SIZE, 
                      MLV_COLOR_BLACK);
    }
    MLV_draw_line((pos.x + points[0][0])*CELL_SIZE,
                  (pos.y + points[0][1])*CELL_SIZE, 
                  (pos.x + points[length - 1][0])*CELL_SIZE,
                  (pos.y + points[length - 1][1])*CELL_SIZE, 
                  MLV_COLOR_BLACK);
}

/**
 * @brief Draw connections between outer and inner line of a gem
 * 
 * @param pos middle of the gem to draw
 * @param inline_p array of points that forms the inline
 * @param outline_p array of points that forms the outline
 * @param length length of both inner and outer points array
 */
static void draw_connections(Position pos, float inline_p[][2], float outline_p[][2], int length) {
    for (int i = 0; i < length; i++) {
        MLV_draw_line((pos.x + outline_p[i][0])*CELL_SIZE,
                      (pos.y + outline_p[i][1])*CELL_SIZE, 
                      (pos.x + inline_p[i][0])*CELL_SIZE,
                      (pos.y + inline_p[i][1])*CELL_SIZE, 
                      MLV_COLOR_BLACK);
    }
}

/**
 * @brief Draw triangular representation of gems
 * 
 * @param pos position of the gem
 * @param color color of the texture
 */
static void draw_triangle_gem(Position pos, MLV_Color color) {
    Position mid = cell_center(pos);

    static float outline_tri[NB_TRIG_VRTX][2] = {
        {-0.4, +0.4},
        {0,    -0.4},
        {+0.4, +0.4}
    };

    static float inline_tri[NB_TRIG_VRTX][2] = {
        {-0.2, +0.2},
        {0,    -0.1},
        {+0.2, +0.2}
    };

    // draw textures
    MLV_draw_filled_triangle((mid.x + outline_tri[0][0])*CELL_SIZE, // draw triangle ABC
                             (mid.y + outline_tri[0][1])*CELL_SIZE,
                             (mid.x + outline_tri[1][0])*CELL_SIZE,
                             (mid.y + outline_tri[1][1])*CELL_SIZE,
                             (mid.x + outline_tri[2][0])*CELL_SIZE,
                             (mid.y + outline_tri[2][1])*CELL_SIZE,
                             color);
                
    // draw outlines
    draw_outline(mid, outline_tri, NB_TRIG_VRTX);
    draw_outline(mid, inline_tri, NB_TRIG_VRTX);


    // draw connection between outlines
    draw_connections(mid, inline_tri, outline_tri, NB_TRIG_VRTX);
}

/**
 * @brief Draw hexagonal representation of gems
 * 
 * @param pos position of the gem
 * @param color color of the texture
 */
static void draw_square_gem(Position pos, MLV_Color color) {
    Position mid = cell_center(pos);

    static float outline_sq[NB_SQ_VRTX][2] = {
        {-0.4, 0},
        {0, -0.4},
        {+0.4, 0},
        {0, +0.4}
    };

    static float inline_sq[NB_SQ_VRTX][2] = {
        {-0.2, 0},
        {0, -0.2},
        {+0.2, 0},
        {0, +0.2}
    };

    MLV_draw_filled_triangle((mid.x + outline_sq[0][0])*CELL_SIZE, // draw triangle ABC
                             (mid.y + outline_sq[0][1])*CELL_SIZE,
                             (mid.x + outline_sq[1][0])*CELL_SIZE,
                             (mid.y + outline_sq[1][1])*CELL_SIZE,
                             (mid.x + outline_sq[2][0])*CELL_SIZE,
                             (mid.y + outline_sq[2][1])*CELL_SIZE,
                             color);
    MLV_draw_filled_triangle((mid.x + outline_sq[0][0])*CELL_SIZE, // draw triangle ABC
                             (mid.y + outline_sq[0][1])*CELL_SIZE,
                             (mid.x + outline_sq[2][0])*CELL_SIZE,
                             (mid.y + outline_sq[2][1])*CELL_SIZE,
                             (mid.x + outline_sq[3][0])*CELL_SIZE,
                             (mid.y + outline_sq[3][1])*CELL_SIZE,
                             color);
    
    // draw outlines
    draw_outline(mid, outline_sq, NB_SQ_VRTX);
    draw_outline(mid, inline_sq, NB_SQ_VRTX);


    // draw connection between outlines
    draw_connections(mid, inline_sq, outline_sq, NB_SQ_VRTX);
}

/**
 * @brief Draw hexagonal representation of gems
 * 
 * @param pos position of the gem
 * @param color color of the texture
 */
static void draw_hexa_gem(Position pos, MLV_Color color) {
    Position mid = cell_center(pos);
    
    static float outline_hexa[NB_HEXA_VRTX][2] = {
        {-0.2, -0.2}, /* A         B     */
        {0,    -0.4}, /* B        /  \   */
        {+0.2, -0.2}, /* C       A   C   */
        {+0.2, +0.2}, /* D       |   |   */
        {0,    +0.4}, /* E       F   D   */
        {-0.2, +0.2}  /* F       \  /    */
    };                /*          E      */


    static float inline_hexa[NB_HEXA_VRTX][2] = {
        {-0.1, -0.1},
        {0,    -0.2},
        {+0.1, -0.1},
        {+0.1, +0.1},
        {0,    +0.2},
        {-0.1, +0.1}
    };

    // draw texture
    MLV_draw_filled_rectangle((mid.x + outline_hexa[0][0])*CELL_SIZE, // draw square ACDF
                              (mid.y + outline_hexa[0][1])*CELL_SIZE,
                              (0.4*CELL_SIZE) + PADDING,
                              (0.4*CELL_SIZE) + PADDING,
                              color);
    MLV_draw_filled_triangle((mid.x + outline_hexa[0][0])*CELL_SIZE, // draw triangle ABC
                             (mid.y + outline_hexa[0][1])*CELL_SIZE,
                             (mid.x + outline_hexa[1][0])*CELL_SIZE,
                             (mid.y + outline_hexa[1][1])*CELL_SIZE,
                             (mid.x + outline_hexa[2][0])*CELL_SIZE,
                             (mid.y + outline_hexa[2][1])*CELL_SIZE,
                             color);
    MLV_draw_filled_triangle((mid.x + outline_hexa[NB_HEXA_VRTX - 1][0])*CELL_SIZE, // draw triangle DFE
                             (mid.y + outline_hexa[NB_HEXA_VRTX - 1][1])*CELL_SIZE,
                             (mid.x + outline_hexa[NB_HEXA_VRTX - 2][0])*CELL_SIZE,
                             (mid.y + outline_hexa[NB_HEXA_VRTX - 2][1])*CELL_SIZE,
                             (mid.x + outline_hexa[NB_HEXA_VRTX - 3][0])*CELL_SIZE,
                             (mid.y + outline_hexa[NB_HEXA_VRTX - 3][1])*CELL_SIZE,
                             color);

    // draw outlines
    draw_outline(mid, outline_hexa, NB_HEXA_VRTX);
    draw_outline(mid, inline_hexa, NB_HEXA_VRTX);


    // draw connection between outlines
    draw_connections(mid, inline_hexa, outline_hexa, NB_HEXA_VRTX);
}

void draw_gem(Position pos, Gem gem) {
    MLV_Color color = transform_color(gem.color);
    if (TRIANGLE_LEVEL <= gem.level && gem.level < SQUARE_LEVEL) {
        draw_triangle_gem(pos, color); 
    } else if (SQUARE_LEVEL <= gem.level && gem.level < HEXA_LEVEL) {
        draw_square_gem(pos, color);
    } else {
        draw_hexa_gem(pos, color);
    }
}
