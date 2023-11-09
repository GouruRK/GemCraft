#include "../include/inventory.h"

#include <stdbool.h>

#include "../include/gem.h"
#include "../include/errors.h"

GemNode init_gem_node(void) {
    GemNode node;
    node.empty = true;
    return node;
}

GemNode init_filled_gem_node(Gem gem) {
    GemNode node;
    node.empty = false;
    node.gem = gem;
    return node;
}

Inventory init_inventory(void) {
    Inventory inv;
    inv.nb_gems = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        inv.array[i] = init_gem_node();
    }
    return inv;
}

Error store_gem_at(Inventory* inv, Gem gem, int index) {
    if (!inv->array[index].empty) {
        return NON_EMPTY_INVENTORY_PLACE;
    }
    inv->array[index] = init_filled_gem_node(gem);
    inv->nb_gems++;
    return OK;
}

Error remove_gem_at(Inventory* inv, Gem* gem, int index) {
    if (!inv->array[index].empty) {
        return EMPTY_INVENTORY_PLACE;
    }
    *gem = inv->array[index].gem;
    inv->array[index].empty = true;
    inv->nb_gems--;
    return OK;
}

Error next_free_index(Inventory* inv, int* index) {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (inv->array[i].empty) {
            *index = i;
            return OK;
        }
    }
    *index = -1;
    return INVENTORY_FULL;
}

Error get_gem(Inventory* inv, Gem* gem, int index) {
    if (inv->array[index].empty) {
        return EMPTY_INVENTORY_PLACE;
    }
    *gem = inv->array[index].gem;
    return OK;
}

Error add_inventory(Inventory* inv, Gem gem) {
    int* index;
    Error err;
    if ((err = next_free_index(inv, &index)) != OK) {
        return err;
    }
    return store_gem_at(inv, gem, index);
}
