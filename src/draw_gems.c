#include "../include/draw_gems.h"

#include <MLV/MLV_all.h>

#include "../include/position.h"


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
 * @param cell_width cell size (graphic)
 */
static void draw_outline(Position pos, float points[][2], int length, int cell_width) {
    for (int i = 0; i < length - 1; i++) {
        MLV_draw_line((pos.x + points[i][0]) * cell_width,
                      (pos.y + points[i][1]) * cell_width, 
                      (pos.x + points[i + 1][0]) * cell_width,
                      (pos.y + points[i + 1][1]) * cell_width, 
                      MLV_COLOR_BLACK);
    }
    MLV_draw_line((pos.x + points[0][0]) * cell_width,
                  (pos.y + points[0][1]) * cell_width, 
                  (pos.x + points[length - 1][0]) * cell_width,
                  (pos.y + points[length - 1][1]) * cell_width, 
                  MLV_COLOR_BLACK);
}

/**
 * @brief Draw connections between outer and inner line of a gem
 * 
 * @param pos middle of the gem to draw
 * @param inline_p array of points that forms the inline
 * @param outline_p array of points that forms the outline
 * @param length length of both inner and outer points array
 * @param cell_width cell size (graphic)
 */
static void draw_connections(Position pos, float inline_p[][2], float outline_p[][2], int length, int cell_width) {
    for (int i = 0; i < length; i++) {
        MLV_draw_line((pos.x + outline_p[i][0]) * cell_width,
                      (pos.y + outline_p[i][1]) * cell_width, 
                      (pos.x + inline_p[i][0]) * cell_width,
                      (pos.y + inline_p[i][1]) * cell_width, 
                      MLV_COLOR_BLACK);
    }
}

void draw_triangle_gem(Position pos, MLV_Color color, int cell_width) {
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
    MLV_draw_filled_triangle((mid.x + outline_tri[0][0]) * cell_width, // draw triangle ABC
                             (mid.y + outline_tri[0][1]) * cell_width,
                             (mid.x + outline_tri[1][0]) * cell_width,
                             (mid.y + outline_tri[1][1]) * cell_width,
                             (mid.x + outline_tri[2][0]) * cell_width,
                             (mid.y + outline_tri[2][1]) * cell_width,
                             color);
                
    // draw outlines
    draw_outline(mid, outline_tri, NB_TRIG_VRTX, cell_width);
    draw_outline(mid, inline_tri, NB_TRIG_VRTX, cell_width);


    // draw connection between outlines
    draw_connections(mid, inline_tri, outline_tri, NB_TRIG_VRTX, cell_width);
}

void draw_square_gem(Position pos, MLV_Color color, int cell_width) {
    Position mid = cell_center(pos);

    static float outline_sq[NB_SQ_VRTX][2] = {
        {-0.4, 0},
        {0,    -0.4},
        {+0.4, 0},
        {0, +0.4}
    };

    static float inline_sq[NB_SQ_VRTX][2] = {
        {-0.2, 0},
        {0,    -0.2},
        {+0.2, 0},
        {0,    +0.2}
    };

    MLV_draw_filled_triangle((mid.x + outline_sq[0][0]) * cell_width, // draw triangle ABC
                             (mid.y + outline_sq[0][1]) * cell_width,
                             (mid.x + outline_sq[1][0]) * cell_width,
                             (mid.y + outline_sq[1][1]) * cell_width,
                             (mid.x + outline_sq[2][0]) * cell_width,
                             (mid.y + outline_sq[2][1]) * cell_width,
                             color);
    MLV_draw_filled_triangle((mid.x + outline_sq[0][0]) * cell_width, // draw triangle ABC
                             (mid.y + outline_sq[0][1]) * cell_width,
                             (mid.x + outline_sq[2][0]) * cell_width,
                             (mid.y + outline_sq[2][1]) * cell_width,
                             (mid.x + outline_sq[3][0]) * cell_width,
                             (mid.y + outline_sq[3][1]) * cell_width,
                             color);
    
    // draw outlines
    draw_outline(mid, outline_sq, NB_SQ_VRTX, cell_width);
    draw_outline(mid, inline_sq, NB_SQ_VRTX, cell_width);


    // draw connection between outlines
    draw_connections(mid, inline_sq, outline_sq, NB_SQ_VRTX, cell_width);
}

void draw_hexa_gem(Position pos, MLV_Color color, int cell_width) {
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
    MLV_draw_filled_rectangle((mid.x + outline_hexa[0][0]) * cell_width, // draw square ACDF
                              (mid.y + outline_hexa[0][1]) * cell_width,
                              (0.4 * cell_width) + PADDING,
                              (0.4 * cell_width) + PADDING,
                              color);
    MLV_draw_filled_triangle((mid.x + outline_hexa[0][0]) * cell_width, // draw triangle ABC
                             (mid.y + outline_hexa[0][1]) * cell_width,
                             (mid.x + outline_hexa[1][0]) * cell_width,
                             (mid.y + outline_hexa[1][1]) * cell_width,
                             (mid.x + outline_hexa[2][0]) * cell_width,
                             (mid.y + outline_hexa[2][1]) * cell_width,
                             color);
    MLV_draw_filled_triangle((mid.x + outline_hexa[NB_HEXA_VRTX - 1][0]) * cell_width, // draw triangle DFE
                             (mid.y + outline_hexa[NB_HEXA_VRTX - 1][1]) * cell_width,
                             (mid.x + outline_hexa[NB_HEXA_VRTX - 2][0]) * cell_width,
                             (mid.y + outline_hexa[NB_HEXA_VRTX - 2][1]) * cell_width,
                             (mid.x + outline_hexa[NB_HEXA_VRTX - 3][0]) * cell_width,
                             (mid.y + outline_hexa[NB_HEXA_VRTX - 3][1]) * cell_width,
                             color);

    // draw outlines
    draw_outline(mid, outline_hexa, NB_HEXA_VRTX, cell_width);
    draw_outline(mid, inline_hexa, NB_HEXA_VRTX, cell_width);


    // draw connection between outlines
    draw_connections(mid, inline_hexa, outline_hexa, NB_HEXA_VRTX, cell_width);
    
}
