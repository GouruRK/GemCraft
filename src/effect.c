#include "effect.h"

Effect init_effect() {
    Effect effect;

    effect.status = NONE;
    effect.clock = init_clock(-1, -1);
    effect.next_damage = 0;

    return effect;
}