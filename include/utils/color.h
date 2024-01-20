/**
 * @file color.h
 * @author Coserariu Alain & Kies Remy
 * @brief Contains colors manipulations as transformation to MLV_Color and 
 * random generator
 * @date 20-01-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COLOR_H
#define COLOR_H

#include <MLV/MLV_all.h>

typedef unsigned int color;  // Color represented with an angle in degrees
                             // (0-359)

/**
 * @brief Return an RGB color based on a HSV angle
 * 
 * @param angle 
 * @return RGB color
 */
MLV_Color transform_color(int angle);

/**
 * @brief Generate a random color
 * 
 * @return color 
 */
color random_color();

#endif
