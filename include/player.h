#ifndef PLAYER_H
#define PLAYER_H

#include "invetory.h"

typedef struct {
    int wave_lvl;
    int mana;
    int mana_lvl;
    Inventory inventory;
} Player;

#endif
