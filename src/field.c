#include "../include/field.h"

// Prototype
Field create_empty_field(void) {
    Field field;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            field.board[y][x] = EMPTY;
        }
    }
    return field;
}

Objects get_field(Field field, PositionInt pos) {
    return field.board[pos.y][pos.x];
}
