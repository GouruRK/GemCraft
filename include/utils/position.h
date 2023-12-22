#ifndef POSITION_H
#define POSITION_H

#include <stdbool.h>

typedef struct {
    float x;
    float y;
} Position;

/**
 * @brief Create a position object of float coordinates
 * 
 * @param x abscissa
 * @param y ordinate
 * @return new position
 */
Position init_position(float x, float y);

/**
 * @brief Calculate the direction in radians between two point a and b
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float calc_direction(Position a, Position b);

/**
 * @brief Calculate the distance between two point
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float calc_distance(Position a, Position b);

/**
 * @brief Find the center of a cell
 * 
 * @param cell 
 * @return Position
 */
Position cell_center(Position cell);

bool compare_pos(Position a, Position b);

#endif
