#ifndef SECTOR_H
#define SECTOR_H

#include <stdbool.h>

#include "utils/position.h"

typedef struct {
    int width;
    int height;
    Position top_left;
    Position bottom_right;
} Sector;

/**
 * @brief Create a sector structure
 * 
 * @param top_left 
 * @param bottom_right 
 * @return
 */
Sector init_sector(Position top_left, Position bottom_right);

/**
 * @brief Check if a position is inside a sector
 * 
 * @param sec 
 * @param pos 
 * @return
 */
bool is_pos_in_sector(Sector sec, Position pos);

/**
 * @brief Check if coordinates are inside a sector
 * 
 * @param sec 
 * @param x 
 * @param y 
 * @return
 */
bool is_coord_in_sector(Sector sec, int x, int y);

#endif
