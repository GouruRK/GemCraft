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
 * @param interval Seconds between two actions.
 * Negative value mean it is only a chronometer
 * @param remaining_time Seconds before the timer end.
 * Negative value for remaining_time mean infinite clock
 * @return Clock
 */
Clock init_clock(float interval, float remaining_time);

/**
 * @brief Update the clock's timers.
 *
 * @param clock
 */
void decrease_clock(Clock* clock);

#endif