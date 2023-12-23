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

Error combine_gem(Player* player, Gem a, Gem b, Gem* res) {
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
    *res = init_gem(type, a.level + 1, color);
    player->mana -= 100;
    return OK;
}

Player init_player(void) {
    Player player;
    player.mana = 150;          // the mana pool store 150 mana by default
    player.mana_lvl = 0;        // mana pool's level is 0 by default
    player.max_quantity = 2000; // a mana pool of level 0 can store 2000 mana
    player.inventory = init_inventory();
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
    *res = init_random_gem(level);
    player->mana -= mana_require;
    return OK;
}
