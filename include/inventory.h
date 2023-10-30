#ifndef INVETORY_H
#define INVETORY_H

#include <stdbool.h>

#include "list_gem.h"

typedef struct {
    bool free;
    Gem* gem;
} Indexes;

typedef struct  {
    int max_gem;                // TODO: static array ?
    Indexes* inventory_place;
    ListGems* list;
} Inventory;

int add_inventory(Inventory* inv, Gem gem);

#endif
