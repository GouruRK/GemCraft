#ifndef POSITION_H
#define POSITION_H

typedef struct {
    float x;
    float y;
} PositionFloat;

typedef struct {
    int x;
    int y;
} PositionInt;

/**
 * @brief Create a position object of int coordinates
 * 
 * @param x abscissa
 * @param y ordinate
 * @return new position
 */
PositionInt create_int_position(int x, int y);

/**
 * @brief Create a position object of float coordinates
 * 
 * @param x abscissa
 * @param y ordinate
 * @return new position
 */
PositionFloat create_float_position(float x, float y);

#endif