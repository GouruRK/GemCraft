#ifndef PLAYER_H
#define PLAYER_H

#include "gem.h"
#include "inventory.h"

typedef struct {
    int mana;               // Current quantity of mana
    int mana_lvl;           // Level of the mana pool
    int max_quantity;       // Maximum of mana that can be stored in the pool
    int max_lvl;            // Maximum reachable (2000 by default)
    Inventory inventory;
} Player;

/**
 * @brief Gives the amout of mana require to create a pure gem of 
 *        a given level 
 * 
 * @param level wanted level
 * @return amout of mana
 */
int mana_require_for_level(int level);

/**
 * @brief Sets a randomly generated pure gem of `level` at `res`, and 
 *        remove the mana require to create it.
 * 
 * @param player player information of mana
 * @param level wanted level
 * @param res set the created gem
 * @return 1 in case of success, else 0
 */
int generate_gem(Player* player, int level, Gem* res);

/**
 * @brief Combines two gems of same level and create a gem with a level + 1.
 *        Remove the mana require to combine them.
 *        Set the new gem in `res`.
 * 
 * @param player player information of mana
 * @param a first gem to combine
 * @param b second gem to combine
 * @param res set the created gem
 * @return 1 in case of success, else 0
 */
int combine_gem(Player* player, Gem a, Gem b, Gem* res);

#endif
