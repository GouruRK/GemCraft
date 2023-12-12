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
 * @brief Combines two gems store at indexes `index_a` and `index_b` of the inventory.
 * 
 * @param player 
 * @param index_a 
 * @param index_b 
 * @return
 */
Error mix_gem_at(Player* player, int index_a, int index_b);

#endif
