#ifndef INVETORY_H
#define INVETORY_H

#include <stdbool.h>

#include "game_engine/gem.h"
#include "utils/errors.h"

#define INVENTORY_SIZE 20

typedef struct {
    Gem gem;
    bool empty;
} GemNode;

typedef struct {
    int nb_gems;
    GemNode array[INVENTORY_SIZE];
} Inventory;

/**
 * @brief Create a GemNode object that doesn't contains a gem.
 * 
 * @return created GemNode
 */
GemNode init_gem_node(void);

/**
 * @brief Create a GemNode that contains a gem.
 * 
 * @return created GemNode
 */
GemNode init_filled_gem_node(Gem gem);

/**
 * @brief Create the Inventory object with its initials values.
 * 
 * @return created Inventory
 */
Inventory init_inventory(void);

/**
 * @brief Store a gem in the inventory at given index
 * 
 * @param inv
 * @param gem 
 * @param index 
 * @return NON_EMPTY_INVENTORY_PLACE if a gem is already stored at index
 *         else OK
 */
Error store_gem_at(Inventory* inv, Gem gem, int index);

/**
 * @brief Remove a gem from the inventory at given index.
 *        Set `gem` with the new gem. 
 * 
 * @param inv 
 * @param gem
 * @param index 
 * @return EMPTY_INVENTORY_PLACE if there is no gem stored at index
 *         else OK
 */
Error remove_gem_at(Inventory* inv, Gem* gem, int index);

/**
 * @brief Find the next index where there is no gem stored.
 *        Set `index` with the found index. `index` is '-1'
 *        if there is no empty place.
 * 
 * @param inv 
 * @param index 
 * @return INVENTORY_FULL if there is no empty place
 *         else OK
 */
Error next_free_index(Inventory* inv, int* index);

/**
 * @brief Add a gem to the inventory
 * 
 * @param inv 
 * @param gem 
 * @return OK if no errors
 */
Error add_inventory(Inventory* inv, Gem gem);

bool is_inventory_full(Inventory* inv);

#endif
