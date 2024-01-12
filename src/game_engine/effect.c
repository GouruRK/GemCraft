#include "game_engine/effect.h"

Effect init_effect(Status status, int damage) {
    Effect effect;

    effect.status = status;

    switch (status) {
        case PARASIT:
            effect.clock = init_clock(0.5, 10);
            effect.next_damage = min(damage, 1);
            break;
        case SLOW:
            effect.clock = init_clock(-1, 10);
            effect.next_damage = 0;
        case SPRAYING:
            effect.clock = init_clock(-1, 5);
            effect.next_damage = 0;
            break;
        case PETRIFICUS:
            effect.clock = init_clock(-1, 3);
            effect.next_damage = 0;
            break;
        default:
            effect.clock = init_clock(-1, -1);
            effect.next_damage = 0;
            break;
    }

    return effect;
}