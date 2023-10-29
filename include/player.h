#ifndef PLAYER_H
#define PLAYER_H

#include "invetory.h"

typedef struct {
    int mana;               // Current quantity of mana
    int mana_lvl;           // Level of the mana pool
    int max_quantity;       // Maximum of mana that can be stored in the pool
    int max_lvl;            // Maximum reachable (2000 by default)
    Inventory inventory;
} Player;

#endif
