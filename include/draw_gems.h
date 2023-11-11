#ifndef DRAW_GEMS_H
#define DRAW_GEMS_H

#include <MLV/MLV_all.h>

#include "position.h"

void draw_hexa_gem(Position pos, MLV_Color color, int cell_width);

void draw_triangle_gem(Position pos, MLV_Color color, int cell_width);

void draw_square_gem(Position pos, MLV_Color color, int cell_width);

#endif
