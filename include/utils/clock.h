#ifndef CLOCK_H
#define CLOCK_H

#include "utils/util.h"

/**
 * @brief Act as a metronome during a defined time.
 * Negative interval means the metronome doesn't count interval
 * Negative remainint_time means the metronome should never stop
 * 
 */
typedef struct {
    frame interval;
    frame next_interval;
    frame remaining_time;
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