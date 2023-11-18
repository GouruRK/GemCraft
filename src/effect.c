#include "effect.h"

Effect init_effect(Status status) {
    Effect effect;

    effect.status = NONE;
    effect.clock = init_clock(0, 0);
    effect.next_damage = 0;

    return effect;
}