#ifndef FIELD_H
#define FIELD_H

#include "monster.h"
#include "position.h"
#include "tower.h"
#include "player.h"

#define WIDTH 28
#define HEIGHT 22

#define MAX_LEN WIDTH* HEIGHT

typedef enum { TOWER, NEST, CAMP, EMPTY, PATH } Objects;

typedef struct {
    int cur_len;
    Position path[MAX_LEN];
} MonsterPath;

typedef struct {
    Position nest;
    Position camp;
    TowerArray towers;      // list of towers
    MonsterArray monsters;  // list of monsters
    Objects board[HEIGHT][WIDTH];
    MonsterPath monster_path;
} Field;

/**
 * @brief Decrease the mana amount of the player and tp the monster to the nest
 *
 * @param monster
 * @param player
 * @param field
 */
void ban_monster(Monster* monster, Player* player, const Field* field);

#endif
