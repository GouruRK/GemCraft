#ifndef INVETORY_H
#define INVETORY_H

#include <stdbool.h>

#include "gem.h"
#include "errors.h"

#define INVENTORY_SIZE 32

typedef struct {
    Gem gem;
    bool empty;
} GemNode;

typedef struct {
    int nb_gems;
    GemNode array[INVENTORY_SIZE];
} Inventory;

GemNode init_gem_node(void);

GemNode init_filled_gem_node(Gem gem);

Inventory init_inventory(void);

Error store_gem_at(Inventory* inv, Gem gem, int index);

Error remove_gem_at(Inventory* inv, Gem* gem, int index);

Error next_free_index(Inventory* inv, int* index);

Error get_gem(Inventory* inv, Gem* gem, int index);

Error add_inventory(Inventory* inv, Gem gem);

#endif
