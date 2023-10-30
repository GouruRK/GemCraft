#include "../include/position.h"

PositionInt create_int_position(int x, int y) {
    PositionInt pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

PositionFloat create_float_position(float x, float y) {
    PositionFloat pos;
    pos.x = x;
    pos.y = y;
    return pos;
}
