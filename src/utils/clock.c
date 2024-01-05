#include "utils/clock.h"

#include <stdio.h>

#include "game_engine/game.h"

Clock init_clock(float interval, float remaining_time) {
    Clock res;

    if (interval < 0) {
        res.interval = -1;
        res.next_interval = -1;
    } else {
        res.interval = interval * FRAMERATE;
        res.next_interval = 0;
    }

    if (remaining_time < 0) {
        res.remaining_time = -1;
    } else {
        res.remaining_time = remaining_time * FRAMERATE;
    }

    return res;
}

void decrease_clock(Clock* clock) {
    if (clock->remaining_time > 0) {
        clock->remaining_time--;
    }

    if (clock->next_interval > 0) {
        clock->next_interval--;
    } else {
        clock->next_interval = clock->interval;
    }
}
