#include <math.h>

#include "game_engine/gem.h"
#include "game_engine/player.h"
#include "utils/util.h"
#include "utils/errors.h"
#include <stdio.h>

/**
 * @brief Retrurn the maximum amout of mana the gauge can store at its level
 * 
 * @param level 
 * @return
 */
static int max_mana(int level) {
    return 2000*pow(1.4, level);
}

int mana_require_for_pool(int level) {
    return 500*pow(1.4, level);
} 

int mana_require_for_gem(int level) {
    return 100*(1 << level);  // 100 * 2^n
}

/**
 * @brief Combine colors of two gems of same type
 * 
 * @param a 
 * @param b 
 * @param type 
 * @return
 */
static int combine_color(int a, int b, TypeGems type) {
    int color = (a + b) / 2;
    if (type != PYRO) {
        return color;
    }

    if (((0 <= a && a <= 30) && (0 <= b && b <= 30)) || 
        ((330 <= a && a <= 359) && (330 <= b && b <= 359))) {
            return color;
    }

    return max(a, b);
}

void add_mana(Player* player, int mana) {
    player->mana = min(player->max_quantity, player->mana + mana);
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
    
    // int color = (a.color + b.color) / 2;
    int color = combine_color(a.color, b.color, type);
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

void upgrade_mana_pool_level(Player* player) {
    if (player->mana_lvl == 40) {
        return;
    }

    player->mana_lvl++;
    player->max_quantity = max_mana(player->mana_lvl);
}

Error upgrade_mana_pool(Player* player) {
    if (player->mana_lvl == 40) {
        return MAXIMUM_LEVEL_REACH; // limit the mana level to 40 to avoid int overflow
    }

    int cost = mana_require_for_pool(player->mana_lvl + 1);
    
    if (player->mana < cost) {
        return NOT_ENOUGHT_MANA;
    }

    player->mana -= cost;
    upgrade_mana_pool_level(player);
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
