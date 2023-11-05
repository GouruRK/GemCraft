#include "../include/field.h"

#include <math.h>
#include <stdbool.h>

#include "../include/monster.h"
#include "../include/player.h"
#include "../include/position.h"
#include "../include/util.h"
#include "../include/game.h"

Objects get_field(Field field, Position pos) {
    return field.board[(int)pos.y][(int)pos.x];
}

void add_to_field(Field* field, Position pos, Objects object) {
    field->board[(int)(pos.y)][(int)(pos.x)] = object;
}

//-------------------------------Monster related-------------------------------

Error place_tower(Field* field, Player* player, Tower tower) {
    int cost = field->towers.next_tower_cost;
    Error err;

    if (player->mana < cost) {
        return NOT_ENOUGHT_MANA;
    }

    if (get_field(*field, tower.pos) != EMPTY) {
        return NON_EMPTY_PLACE;
    }

    err = add_tower_array(&(field->towers), tower);
    if (err != OK) {
        return err;
    }

    add_to_field(field, tower.pos, TOWER);
    player->mana -= cost;
    return OK;
}

//-------------------------------Monster related-------------------------------

Error spawn_monster_field(Field* field, int wave_nb, TypeWave type_wave) {
    Monster m = init_monster(cell_center(field->nest.pos), type_wave, wave_nb,
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
    monster->pos = cell_center(field->nest.pos);
}

void update_monster_dest(Monster* monster, const Field* field, Player* player) {
    if (monster->index_path == field->monster_path.cur_len - 1) {
        // If monster step on the camp
        ban_monster(monster, player, field);
    } else {
        monster->index_path++;
        monster->dest =
            cell_center(field->monster_path.path[monster->index_path]);
    }
}

/**
 * @brief Generate a random wave type
 *
 * @param nb_wave
 * @return TypeWave
 */
static TypeWave generate_random_wave(int nb_wave) {
    int proba_waves[4];
    if (nb_wave <= 5) {
        proba_waves[NORMAL] = 60;
        proba_waves[CROWD] = 20;
        proba_waves[FAST] = 20;
        proba_waves[BOSS] = 0;
    } else {
        proba_waves[NORMAL] = 50;
        proba_waves[CROWD] = 20;
        proba_waves[FAST] = 20;
        proba_waves[BOSS] = 10;
    }

    int rand_val = random_int(0, 100);

    for (int i = 0; i < 4; i++) {
        if (rand_val < proba_waves[i]) {
            return i;
        }
        rand_val -= proba_waves[i];
    }

    return -1;  // Should never happend
}

void init_new_wave(Nest* nest, int nb_wave) {
    nest->type_wave = generate_random_wave(nb_wave);

    nest->monster_remaining = 12;
    nest->nb_frame_between_spawn = FRAMERATE;
    nest->nb_frame_before_next_spawn = 0;

    switch (nest->type_wave) {
        case CROWD:
            nest->monster_remaining = 24;
            break;

        case FAST:
            nest->nb_frame_between_spawn = FRAMERATE / 2;
            break;

        case BOSS:
            nest->monster_remaining = 2;
            break;
        
        default:
            break;
    }
}