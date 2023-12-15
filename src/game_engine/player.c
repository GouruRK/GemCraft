#include <math.h>

#include "game_engine/gem.h"
#include "game_engine/player.h"
#include "utils/util.h"
#include "utils/errors.h"

static int mana_require_for_pool(int level) {
    return pow(500, 1.4 * level);
} 

static int max_mana(int level) {
    return pow(2000, 1.4 * level);
}

/**
 * @brief Gives the amout of mana require to create a pure gem of 
 *        a given level 
 * 
 * @param level wanted level
 * @return amout of mana
 */
static int mana_require_for_gem(int level) {
    return 100 * (1 << level);  // 100 * 2^n
}

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
static Error combine_gem(Player* player, Gem a, Gem b, Gem* res) {
    if ((player->mana < 100)) {
        return NOT_ENOUGHT_MANA;
    }
    if (a.level != b.level) {
        return DIFFERENT_GEM_LVL;
    }

    TypeGems type = MIXTE;
    if (a.type == b.type && a.type != MIXTE) {
        type = a.type;
    }
    
    int color = (a.color + b.color) / 2;
    *res = create_gem(type, a.level + 1, color);
    player->mana -= 100;
    return OK;
}

Player init_player(void) {
    Player player;
    player.mana = 150;          // the mana pool store 150 mana by default
    player.mana_lvl = 0;        // mana pool's level is 0 by default
    player.max_quantity = 2000; // a mana pool of level 0 can store 2000 mana
    return player;
}

Error upgrade_mana_pool(Player* player) {
    int cost = mana_require_for_pool(player->mana_lvl);

    if (player->mana < cost) {
        return NOT_ENOUGHT_MANA;
    }

    player->mana -= cost;
    player->mana_lvl++;
    player->max_quantity = max_mana(player->mana_lvl);
    return OK;
}

Error generate_gem(Player* player, int level, Gem* res) {
    int mana_require = mana_require_for_gem(level);
    if (player->mana < mana_require) {
        return NOT_ENOUGHT_MANA;
    }
    *res = create_random_gem(level);
    player->mana -= mana_require;
    return OK;
}

Error mix_gem_at(Player* player, int index_a, int index_b) {
    Gem a, b, res;
    Error err;
    Inventory* inv = &(player->inventory);

    if ((err = remove_gem_at(inv, &a, index_a)) != OK) {
        return err;
    }
    if ((err = remove_gem_at(inv, &b, index_b)) != OK) {
        store_gem_at(inv, a, index_a);
        return err;
    }

    if ((err = combine_gem(player, a, b, &res)) != OK) {
        store_gem_at(inv, a, index_a);
        store_gem_at(inv, b, index_b);
        return err;
    }

    store_gem_at(inv, res, index_a);
    return OK;
}