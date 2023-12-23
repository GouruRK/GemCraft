#include "utils/position.h"

#include <math.h>
#include <stdbool.h>

#include "display/display_const.h"

Position init_position(float x, float y) {
    Position pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

Position init_scaled_position(float x, float y) {
    Position pos;
    pos.x = x / CELL_SIZE;
    pos.y = y / CELL_SIZE;
    return pos;
}

float calc_direction(Position a, Position b) {
    float opposite = b.y - a.y;
    float adjacent = b.x - a.x;

    return atan2f(opposite, adjacent);
}

float calc_distance(Position a, Position b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Position cell_center(Position cell) {
    cell.x = (int)cell.x + 0.5;
    cell.y = (int)cell.y + 0.5;
    return cell;
}

bool compare_pos(Position a, Position b) {
    return (((int)a.x) == ((int)b.x)) && (((int)a.y) == ((int)b.y));
}
