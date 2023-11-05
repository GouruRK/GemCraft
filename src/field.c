#include "../include/field.h"

#include <math.h>

#include "../include/monster.h"
#include "../include/player.h"
#include "../include/position.h"

//-------------------------------Monster related-------------------------------

Error spawn_monster_field(Field* field, int wave_nb, TypeWave type_wave) {
    Monster m = init_monster(cell_center(field->nest), type_wave, wave_nb,
                             cell_center(field->monster_path.path[0]));

    Error err = add_monster_array(&(field->monsters), m);

    return err;
}

/**
 * @brief Decrease the mana amount of the player and tp the monster to the nest
 *
 * @param monster
 * @param player
 * @param field
 */
static void ban_monster(Monster* monster, Player* player, const Field* field) {
    player->mana -=
        (monster->max_health * 15.0 / 100) * pow(1.3, player->mana_lvl);

    monster->index_path = 0;
    monster->dest = cell_center(field->monster_path.path[0]);
    monster->pos = cell_center(field->nest);
}

void update_monster_dest(Monster* monster, const Field* field, Player* player) {
    if (monster->index_path == field->monster_path.cur_len - 1) {
        // If monster step on the camp
        ban_monster(monster, player, field);
    } else {
        monster->index_path++;
        monster->dest = cell_center(field->monster_path.path[monster->index_path]);
    }
}
