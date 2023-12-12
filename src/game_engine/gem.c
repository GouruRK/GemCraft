#include "game_engine/gem.h"
#include "game_engine/player.h"
#include "utils/util.h"
#include "game_engine/inventory.h"

Gem create_gem(TypeGems type, int level, int color) {
    Gem gem;
    gem.type = type;
    gem.level = level;
    gem.color = color;
    gem.reload_time = 2; // by default, reload time of 2s
    return gem;
}

Gem create_random_gem(int level) {
    int color;
    TypeGems type = random_int(0, 2);
    switch (type) {
        case PYRO:
            // chose between 0-30 or 330-359
            if (uniform() < 0.5) {
                color = random_color();
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
        default:
            break;
    }
    return create_gem(type, level, color);
}
