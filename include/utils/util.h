#ifndef UTIL_H
#define UTIL_H

#include <time.h>

#define FLOAT_COMPARISON_MARGIN 0.05

typedef unsigned int color;  // Color represented with an angle in degrees (0-359)
typedef int frame;  // Count frame

/**
 * @brief Generate a random float between '0' and '1'.
 * 
 * @return float generated float
 */
double uniform(void);

/**
 * @brief Generate a random inclusive int bounded by `min` and `max`.
 * 
 * @param min minimum bound
 * @param max maximum bound
 * @return int generated int
 */
int random_int(int min, int max);

/**
 * @brief Return the difference between two time
 * 
 * @param start 
 * @param end 
 * @return struct timespec 
 */
struct timespec diff_time(struct timespec start, struct timespec end);

/**
 * @brief Generate a random color
 * 
 * @return color 
 */
color random_color();

/**
 * @brief Return the max value between a and b
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int max(int a, int b);

/**
 * @brief Return the min value between a and b
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int min(int a, int b);

#endif
