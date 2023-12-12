#ifndef EFFECT_H
#define EFFECT_H

#include "utils/clock.h"

#define STACKABLE_STATUS 2  // Number of status that can be stack on a monster

typedef enum {
    NONE,
    PYRO_RESIDUE,
    DENDRO_RESIDUE,
    HYDRO_RESIDUE,
    SPLASH,      // Pyro
    PARASIT,     // Dendro
    SLOW,        // Hydro
    SPRAYING,    // Pyro + Hydro
    BURN,        // Pyro + Dendro
    PETRIFICUS,  // Dendro + Hydro
} Status;

typedef struct {
    int next_damage;  // Amount of damage taken by the effect
    Status status;  // Applied status
    Clock clock;
} Effect;

/**
 * @brief Initialize an effect to NONE and set timers to 0
 * 
 */
Effect init_effect();

#endif
