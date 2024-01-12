#ifndef EFFECT_H
#define EFFECT_H

#include "utils/clock.h"

#define STACKABLE_STATUS 2  // Only  2 status max : main status + spraying

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
    Status status;
    Clock clock;
} Effect;

/**
 * @brief Initialize effect's clock and damage depending on the given effect
 * 
 * @param status
 * @param damage used only if status is PARASIT
 */
Effect init_effect(Status status, int damage);

#endif
