#include "../include/player.h"

#include "../include/gem.h"
#include "../include/util.h"
#include "../include/errors.h"

Player init_player() {
    Player p;

    p.mana = 150;
    p.mana_lvl = 0;
    p.max_quantity = 150;
    p.max_lvl = 2000;
    
    return p;
}

int mana_require_for_level(int level) {
    return 100 * (1 << level);  // 100 * 2^n
}

Error generate_gem(Player* player, int level, Gem* res) {
    int mana_require = mana_require_for_level(level);
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
