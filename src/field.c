#include "../include/field.h"

// Prototype
Field create_empty_field(void) {
    Field field;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            field.board[y][x] = EMPTY;
        }
    }
    field.camp = (Cell){
        .pos = (Position){.x = 0, .y = 0},
        .type = CAMP
    };
    field.board[0][0] = CAMP;

    field.nest = (Cell){
        .pos = (Position){.x = WIDTH - 1, .y = HEIGHT - 1},
        .type = NEST
    };
    field.board[HEIGHT - 1][WIDTH - 1] = NEST;
    return field;
}
