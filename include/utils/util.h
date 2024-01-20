/**
 * @file util.h
 * @author Coserariu Alain & Kies Remy
 * @brief Contains all the utility as random number generator, conversion, math
 * functions..
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef UTIL_H
#define UTIL_H

#include <time.h>

#define M_PI 3.14159265358979323846
#define FLOAT_COMPARISON_MARGIN 0.05

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
 * @brief Return the max value between a and b
 * 
 * @param a 
 * @param b 
 * @return unsigned long long
 */
long long max(long long a, long long b);

/**
 * @brief Return the min value between a and b
 * 
 * @param a 
 * @param b 
 * @return unsigned long long
 */
long long min(long long a, long long b);

/**
 * @brief Convert degree to radiant
 * 
 * @param angle 
 * @return double 
 */
double degree_to_rad(int angle);

#endif
