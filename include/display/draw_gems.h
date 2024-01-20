/**
 * @file draw_gems.h
 * @author Coserariu Alain & Kies Remy
 * @brief Draw representation for gems
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DRAW_GEMS_H

#define DRAW_GEMS_H

#include <MLV/MLV_all.h>

#include "game_engine/gem.h"
#include "utils/position.h"

#define TRIANGLE_LEVEL 0
#define SQUARE_LEVEL 2
#define PENTA_LEVEL 4
#define HEXA_LEVEL 6

/**
 * @brief Draw a gem at given position
 * 
 * @param pos position to draw the gem
 * @param gem gem to draw. Gem's level defines its shape
 */
void draw_gem(Position pos, Gem gem);

#endif
