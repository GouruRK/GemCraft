#include <math.h>

#include "../include/gem.h"
#include "../include/player.h"

#include "../include/gem.h"
#include "../include/util.h"
#include "../include/errors.h"

Player init_player(void) {
    Player player;
    player.mana = 150;          // the mana pool store 150 mana by default
    player.mana_lvl = 0;        // mana pool's level is 0 by default
    player.max_quantity = 2000; // a mana pool of level 0 can store 2000 mana
    return player;
}

int mana_require_for_pool(int level) {
    return pow(500, 1.4 * level);
} 

int max_mana(int level) {
    return pow(2000, 1.4 * level);
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

int mana_require_for_gem(int level) {
    return 100 * (1 << level);  // 100 * 2^n
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
    *res = create_gem(type, a.level + 1, color);
    player->mana -= 100;
    return OK;
}

// int main(void) {
//     #include <stdio.h>
//     printf("Test de mana_require_for_gem : \n");
//     for (int i = 0; i < 5; i++) {
//         printf("level %d : %d\n", mana_require_for_gem(i));
//     }
// }
