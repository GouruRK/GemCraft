#ifndef CLOCK_H
#define CLOCK_H

#include "util.h"

typedef struct {
    frame interval;
    frame next_interval;
    frame remaining_time;  // Negative value mean infinite clock
} Clock;

/**
 * @brief Initialize a clock. Convert seconds to frame
 * 
 * @param interval Seconds between two actions
 * @param remaining_time Seconds before the timer end
 * @return Clock 
 */
Clock init_clock(int interval, int remaining_time);

/**
 * @brief Update the clock's timers.
 * 
 * @param clock 
 */
void decrease_clock(Clock* clock);

#endif