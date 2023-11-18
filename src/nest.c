#include "nest.h"

#include <stdio.h>

#include "game.h"

Nest init_nest(Position pos) {
    Nest res;

    res.pos = pos;
    
    res.monster_remaining = 0;
    res.spawn_clock = init_clock(1, -1);
    res.spawn_clock.next_interval = res.spawn_clock.interval;
    res.type_wave = NORMAL;

    return res;
}
