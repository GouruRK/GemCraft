#ifndef DRAW_GEMS_H

#define DRAW_GEMS_H

#include <MLV/MLV_all.h>

#include "utils/position.h"
#include "game_engine/gem.h"

#define TRIANGLE_LEVEL 0
#define SQUARE_LEVEL 5
#define HEXA_LEVEL 10

/**
 * @brief Draw hexagonal representation of gems
 * 
 * @param pos position of the gem
 * @param color color of the texture
 * @param cell_width cell size in the window view
 */
void draw_hexa_gem(Position pos, MLV_Color color, int cell_width);

/**
 * @brief Draw hexagonal representation of gems
 * 
 * @param pos position of the gem
 * @param color color of the texture
 * @param cell_width cell size in the window view
 */
void draw_square_gem(Position pos, MLV_Color color, int cell_width);

/**
 * @brief Draw triangular representation of gems
 * 
 * @param pos position of the gem
 * @param color color of the texture
 * @param cell_width cell size in the window view
 */
void draw_triangle_gem(Position pos, MLV_Color color, int cell_width);

void draw_gem(Position pos, Gem gem, int cell_width);

#endif
