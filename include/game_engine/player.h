#ifndef PLAYER_H
#define PLAYER_H

#include "game_engine/gem.h"
#include "game_engine/inventory.h"

typedef struct {
    int mana;               // Current quantity of mana
    int mana_lvl;           // Level of the mana pool
    int max_quantity;       // Maximum of mana that can be stored in the pool
    Inventory inventory;
} Player;

/**
 * @brief PROTOTYPE
 * Initialize a player with an empty inventory
 * 
 * @return Player 
 */
Player init_player(void);

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
Error combine_gem(Player* player, Gem a, Gem b, Gem* res);

#endif
