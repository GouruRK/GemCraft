#ifndef INVETORY_H
#define INVETORY_H

#include "arrayGem.h"
#include "player.h"

typedef struct  {
    int maxGem;
    ArrayGem gems;
} Inventory;

int add_inventory(Player player, Gem gem);

#endif
