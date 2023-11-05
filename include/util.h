#ifndef UTIL_H
#define UTIL_H

#include <time.h>

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

#endif
