#ifndef DRAW_GEMS_H

#define DRAW_GEMS_H

#include <MLV/MLV_all.h>

#include "game_engine/gem.h"
#include "utils/position.h"

#define TRIANGLE_LEVEL 0
#define SQUARE_LEVEL 5
#define HEXA_LEVEL 10

/**
 * @brief Draw a gem at given position
 * 
 * @param pos position to draw the gem
 * @param gem gem to draw. Gem's level defines its shape
 */
void draw_gem(Position pos, Gem gem);

#endif
