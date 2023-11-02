#include "../include/position.h"

#include <math.h>

Position create_position(float x, float y) {
    Position pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

float calc_direction(Position a, Position b) {
    float opposite = b.y - a.y;
    float adjacent = b.x - a.x;

    return atan2f(opposite, adjacent);
}
