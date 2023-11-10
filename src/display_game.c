#include <MLV/MLV_all.h>

#include "../include/display_game.h"
#include "../include/field.h"
#include "../include/monster.h"

#define NB_VERTEXES 6
#define PADDING 1

const float gem_outline[NB_VERTEXES][2] = {
    {-0.2, -0.2}, /* A         B     */
    {0,    -0.4}, /* B        /  \   */
    {+0.2, -0.2}, /* C       A   C   */
    {+0.2, +0.2}, /* D       |   |   */
    {0,    +0.4}, /* E       F   D   */
    {-0.2, +0.2}  /* F       \  /    */
};                /*          E      */


const float gem_inline[NB_VERTEXES][2] = {
    {-0.1, -0.1},
    {0,    -0.2},
    {+0.1, -0.1},
    {+0.1, +0.1},
    {0,    +0.2},
    {-0.1, +0.1}
};     

// Prototype
void draw_board(Field field) {
    MLV_Color objects_color[6] = {
        MLV_COLOR_BROWN4,   // Tower
        MLV_COLOR_RED,      // Nest
        MLV_COLOR_GREEN,    // Camp
        MLV_COLOR_GREY,     // Empty
        MLV_COLOR_WHITE     // Path
    };
    MLV_Color color;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            color = objects_color[field.board[y][x]];
            MLV_draw_filled_rectangle(x * CELL_SIZE, y * CELL_SIZE, 
                                      CELL_SIZE, CELL_SIZE, color);
        }
    }

    // horizontal
    for (int y = 0; y < HEIGHT; y++) {
        MLV_draw_line(0, y * CELL_SIZE, WIDTH * CELL_SIZE, y * CELL_SIZE, MLV_COLOR_BLACK);
    }

    // vertical
    for (int x = 0; x < WIDTH; x++) {
        MLV_draw_line(x * CELL_SIZE, 0, x * CELL_SIZE, HEIGHT * CELL_SIZE, MLV_COLOR_BLACK);
    }
}

// Prototype
void draw_monster(const Monster m) {
    MLV_draw_filled_circle((int)(m.pos.x * CELL_SIZE), (int)(m.pos.y * CELL_SIZE), CELL_SIZE / 3, MLV_COLOR_BLUE);
}

// Prototype
void draw_gem(Position pos, MLV_Color color) {
    Position mid = cell_center(pos);
    
    // draw texture
    MLV_draw_filled_rectangle((mid.x + gem_outline[0][0]) * CELL_SIZE, // draw square ACDF
                              (mid.y + gem_outline[0][1]) * CELL_SIZE,
                              (0.4 * CELL_SIZE) + PADDING,
                              (0.4 * CELL_SIZE) + PADDING,
                              color);
    MLV_draw_filled_triangle((mid.x + gem_outline[0][0]) * CELL_SIZE, // draw triangle ABC
                             (mid.y + gem_outline[0][1]) * CELL_SIZE,
                             (mid.x + gem_outline[1][0]) * CELL_SIZE,
                             (mid.y + gem_outline[1][1]) * CELL_SIZE,
                             (mid.x + gem_outline[2][0]) * CELL_SIZE,
                             (mid.y + gem_outline[2][1]) * CELL_SIZE,
                             color);
    MLV_draw_filled_triangle((mid.x + gem_outline[NB_VERTEXES - 1][0]) * CELL_SIZE, // draw triangle DFE
                             (mid.y + gem_outline[NB_VERTEXES - 1][1]) * CELL_SIZE,
                             (mid.x + gem_outline[NB_VERTEXES - 2][0]) * CELL_SIZE,
                             (mid.y + gem_outline[NB_VERTEXES - 2][1]) * CELL_SIZE,
                             (mid.x + gem_outline[NB_VERTEXES - 3][0]) * CELL_SIZE,
                             (mid.y + gem_outline[NB_VERTEXES - 3][1]) * CELL_SIZE,
                             color);

    // draw_inner_gem
    for (int i = 0; i < NB_VERTEXES - 1; i++) {
        MLV_draw_line((mid.x + gem_inline[i][0]) * CELL_SIZE,
                      (mid.y + gem_inline[i][1]) * CELL_SIZE, 
                      (mid.x + gem_inline[i + 1][0]) * CELL_SIZE,
                      (mid.y + gem_inline[i + 1][1]) * CELL_SIZE, 
                      MLV_COLOR_BLACK);
    }
    MLV_draw_line((mid.x + gem_inline[0][0]) * CELL_SIZE,
                  (mid.y + gem_inline[0][1]) * CELL_SIZE, 
                  (mid.x + gem_inline[NB_VERTEXES - 1][0]) * CELL_SIZE,
                  (mid.y + gem_inline[NB_VERTEXES - 1][1]) * CELL_SIZE, 
                  MLV_COLOR_BLACK);

    // draw outline
    for (int i = 0; i < NB_VERTEXES - 1; i++) {
        MLV_draw_line((mid.x + gem_outline[i][0]) * CELL_SIZE,
                      (mid.y + gem_outline[i][1]) * CELL_SIZE, 
                      (mid.x + gem_outline[i + 1][0]) * CELL_SIZE,
                      (mid.y + gem_outline[i + 1][1]) * CELL_SIZE, 
                      MLV_COLOR_BLACK);
    }
    MLV_draw_line((mid.x + gem_outline[0][0]) * CELL_SIZE,
                  (mid.y + gem_outline[0][1]) * CELL_SIZE, 
                  (mid.x + gem_outline[NB_VERTEXES - 1][0]) * CELL_SIZE,
                  (mid.y + gem_outline[NB_VERTEXES - 1][1]) * CELL_SIZE, 
                  MLV_COLOR_BLACK);

    // draw_vertex_connection
    for (int i = 0; i < NB_VERTEXES; i++) {
        MLV_draw_line((mid.x + gem_outline[i][0]) * CELL_SIZE,
                      (mid.y + gem_outline[i][1]) * CELL_SIZE, 
                      (mid.x + gem_inline[i][0]) * CELL_SIZE,
                      (mid.y + gem_inline[i][1]) * CELL_SIZE, 
                      MLV_COLOR_BLACK);
    }
}
