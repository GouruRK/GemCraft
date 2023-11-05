#ifndef FIELD_H
#define FIELD_H

#include <stdbool.h>

#include "errors.h"
#include "monster.h"
#include "player.h"
#include "position.h"
#include "tower.h"

#define WIDTH 28
#define HEIGHT 22

#define MAX_LEN WIDTH* HEIGHT

typedef enum {
    TOWER,
    NEST,
    CAMP,
    EMPTY,
    PATH,
} Objects;

typedef struct {
    int cur_len;
    Position path[MAX_LEN];
} MonsterPath;

typedef struct {
    int monster_remaining;
    int nb_frame_before_next_spawn;
    int nb_frame_between_spawn;
    TypeWave type_wave;
    Position pos;
} Nest;

typedef struct {
    Position camp;
    Nest nest;
    TowerArray towers;      // list of towers
    MonsterArray monsters;  // list of monsters
    Objects board[HEIGHT][WIDTH];
    MonsterPath monster_path;
} Field;

Objects get_field(Field field, Position pos);

void add_to_field(Field* field, Position pos, Objects object);

//-------------------------------Tower related-------------------------------

Error place_tower(Field* field, Player* player, Tower tower);

//-------------------------------Monster related-------------------------------

/**
 * @brief Add a monster on the field spawning on the nest
 *
 * @param field
 * @param wave_nb
 * @param type_wave
 * @return Error
 */
Error spawn_monster_field(Field* field, int wave_nb, TypeWave type_wave);

/**
 * @brief Find the next destination for a monster. If he step on the camp the
 * ban process will occurs
 *
 * @param monster
 * @param field
 * @param player
 */
void update_monster_dest(Monster* monster, const Field* field, Player* player);

/**
 * @brief Load a new wave in a nest
 *
 * @param nest
 */
void init_new_wave(Nest* nest, int nb_wave);

#endif