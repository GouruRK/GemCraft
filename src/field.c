#include "../include/field.h"

#include <math.h>

void ban_monster(Monster* monster, Player* player, const Field* field) {
    player->mana -= (monster->max_health * 15.0 / 100) * pow(1.3, player->mana_lvl);
    
    monster->dest.x = field->monster_path.path[0].x + 0.5;
    monster->dest.y = field->monster_path.path[0].y + 0.5;
    
    monster->pos.x = field->nest.x + 0.5;
    monster->pos.y = field->nest.y + 0.5;
}
