#include "utils/sector.h"

#include <stdbool.h>

#include "utils/position.h"

Sector init_sector(Position top_left, Position bottom_right) {
    Sector sector;
    sector.top_left = top_left;
    sector.bottom_right = bottom_right;
    sector.width = bottom_right.x - top_left.x;
    sector.height = bottom_right.y - top_left.y;
    return sector;
}

bool is_pos_in_sector(Sector sec, Position pos) {
    return (sec.top_left.x <= pos.x && pos.x < sec.bottom_right.x)
           && (sec.top_left.y <= pos.y && pos.y < sec.bottom_right.y);
}

bool is_coord_in_sector(Sector sec, int x, int y) {
    return (sec.top_left.x <= x && x < sec.bottom_right.x)
           && (sec.top_left.y <= y && y < sec.bottom_right.y);
}
