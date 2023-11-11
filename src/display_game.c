#include <MLV/MLV_all.h>

#include "../include/display_game.h"
#include "../include/field.h"
#include "../include/monster.h"

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

