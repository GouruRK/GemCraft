#ifndef POSITION_H
#define POSITION_H

typedef struct {
    float x;
    float y;
} Position_float;

typedef struct {
    int x;
    int y;
} Position_int;

/**
 * @brief Create a position object
 * 
 * @param x abscissa
 * @param y ordinate
 * @return new position
 */
Position create_position(int x, int y);

#endif