#ifndef GEM_H
#define GEM_H

#include "player.h"

typedef enum {  
    PYRO,
    DENDRO,
    HYDRO,
    MIXTE
} TypeGems;

typedef struct {
    int level;
    int color;
    int reload_time;
    TypeGems type;
} Gem;

/**
 * @brief Creates a gem object.
 * 
 * @param type gem type
 * @param level gem level
 * @param color gem color
 * @return created gem
 */
Gem create_gem(TypeGems type, int level, int color);

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
