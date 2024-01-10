#include "game_engine/nest.h"

#include <stdio.h>

#include "game_engine/game.h"

Nest init_nest(Position pos) {
    Nest res;
    res.pos = pos;
    res.nb_waves = 0;

    return res;
}

/**
 * @brief Generate a random wave type
 *
 * @param nb_wave
 * @return TypeWave
 */
static TypeWave generate_random_wave(int nb_wave) {
    int proba_waves[4];
    if (nb_wave < 5) {
        proba_waves[NORMAL] = 60;
        proba_waves[CROWD] = 20;
        proba_waves[FAST] = 20;
        proba_waves[BOSS] = 0;
    } else {
        proba_waves[NORMAL] = 50;
        proba_waves[CROWD] = 20;
        proba_waves[FAST] = 20;
        proba_waves[BOSS] = 10;
    }

    int rand_val = random_int(0, 100);

    for (int i = 0; i < 4; i++) {
        if (rand_val < proba_waves[i]) {
            return i;
        }
        rand_val -= proba_waves[i];
    }

    return -1;  // Should never happend
}

/**
 * @brief Generate wave with random type (crowd fast normal or boss)
 * 
 * @param nb_wave 
 * @return Wave 
 */
static Wave init_wave(int nb_wave) {
    Wave res;

    res.type = generate_random_wave(nb_wave);
    res.monster_remaining = 12;
    res.spawn_clock = init_clock(1, -1);

    switch (res.type) {
        case CROWD:
            res.monster_remaining = 24;
            res.spawn_clock.interval = FRAMERATE / 2;
            break;

        case FAST:
            res.spawn_clock.interval = FRAMERATE / 2;
            break;

        case BOSS:
            res.monster_remaining = 2;
            break;

        default:
            break;
    }

    return res;
}

int add_wave_nest(Nest* nest, int nb_wave) {
    for (int i = 0; i < nest->nb_waves; i++) {
        if (nest->wave[i].monster_remaining == 0) {
            nest->wave[i] = init_wave(nb_wave);
            return 1;
        }
    }

    if (nest->nb_waves == MAX_WAVE_NUMBER) {
        return 0;
    }

    nest->wave[nest->nb_waves] = init_wave(nb_wave);
    nest->nb_waves++;
    return 1;
}
