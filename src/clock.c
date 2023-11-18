#include "clock.h"

#include "game.h"

Clock init_clock(int interval, int remaining_time) {
    Clock res;
    res.interval = interval * FRAMERATE;
    res.next_interval = 0;
    res.remaining_time = remaining_time * FRAMERATE;

    return res;
}

void decrease_clock(Clock* clock) {
    if (clock->remaining_time == 0) {
        return;
    }

    if (clock->next_interval > 0) {
        clock->next_interval--;
    } else {
        clock->next_interval = clock->interval;
    }

    clock->remaining_time--;
}
