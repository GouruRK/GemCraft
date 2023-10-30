#include "../include/gem.h"
#include "../include/player.h"
#include "../include/util.h"
#include "../include/inventory.h"

Gem create_gem(TypeGems type, int level, int color) {
    Gem gem;
    gem.type = type;
    gem.level = level;
    gem.color = color;
    gem.reload_time = 2; // by default, reload time of 2s
    return gem;
}

int mana_require_for_level(int level) {
    return 100 * (1 << level);  // 100 * 2^n
}

Gem _generate_gem(int level) {
    int color;
    TypeGems type = random_int(0, 2);
    switch (type) {
        case PYRO:
            // chose between 0-30 or 330-359
            if (uniform() < 0.5) {
                color = random_int(0, 30);
            } else {
                color = random_int(330, 359);
            }
            break;
        case DENDRO:
            color = random_int(90, 150);
            break;
        case HYDRO:
            color = random_int(210, 270);
            break;
    }
    return create_gem(type, level, color);
}

int generate_gem(Player* player, int level, Gem* res) {
    int mana_require = mana_require_for_level(level);
    if (player->mana < mana_require) {
        return 1;
    }
    *res = _generate_gem(level);
    player->mana -= mana_require;
    return 1;
}

int combine_gem(Player* player, Gem a, Gem b, Gem* res) {
    if ((player->mana < 100) || (a.level != b.level)) {
        return 0;
    }
    TypeGems type = MIXTE;
    if (a.type == b.type && a.type != MIXTE) {
        type = a.type;
    }
    int color = (a.color + b.color) / 2;
    *res = create_gem(type, a.level + 1, color);
    player->mana -= 100;
    return 1;
}
