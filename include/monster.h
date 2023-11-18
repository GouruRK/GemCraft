#ifndef MONSTER_H
#define MONSTER_H

#include <time.h>

#include "errors.h"
#include "position.h"
#include "util.h"
#include "effect.h"

#define MAX_WAVE_SIZE 24

typedef enum {
    NORMAL,
    CROWD,
    FAST,
    BOSS,
} TypeWave;

typedef struct {
    int health;
    int max_health;
    int index_path;   // Position in the path array in a field
    Effect status[STACKABLE_STATUS];  // The second status is spraying residue
    color color;
    float default_speed;
    float speed;  // Number of cases per seconde traveled
    Position pos;
    Position dest;
} Monster;

typedef struct {
    int curr_size;
    int max_size;
    Monster* lst;  // List of monster
} MonsterArray;

/**
 * @brief Initialize a monster
 *
 * @param pos_init Initial position on the field
 * @param type_wave
 * @param wave_number
 * @param dest
 * @return Monster
 */
Monster init_monster(Position pos_init, TypeWave type_wave, int wave_number,
                     Position dest);

/**
 * @brief Move a monster in toward his destination
 *
 * @param monster
 * @param destination a position on the field
 */
void move_monster(Monster* monster);

/**
 * @brief Tell if a monster is near enough his destination
 *
 * @param monster
 * @return int
 */
int has_reach_dest(const Monster* monster);

/**
 * @brief Tell if monster health is > 0
 *
 * @param monster
 * @return int
 */
int is_alive(const Monster* monster);

/**
 * @brief Add an effect to a monster
 * 
 * @param monster 
 * @param effect 
 */
void add_effect_monster(Monster* monster, Effect effect);

/**
 * @brief Update the effect on the monster
 * 
 * @param monster 
 */
void update_effect_monster(Monster* monster);

/*---------------------------Monster array related---------------------------*/

/**
 * @brief Initialize a monster array
 *
 * @param array
 * @return Error
 */
Error init_monster_array(MonsterArray* array);

/**
 * @brief Realloc the monster array :
 *    -If the curr_size == max_size, increase the array size by
 * MAX_WAVE_SIZE
 *    -If the curr_size < max_size - MAX_WAVE_SIZE
 * reduce the array size by MAX_WAVE_SIZE
 *
 * curr_size > max_size should never happen, return INCOHERENT_TAB_DATA
 *
 * @param array
 * @return Error
 */
Error realloc_monster_array(MonsterArray* array);

/**
 * @brief Add a monster to a monster array, can realloc the array
 *
 * @param array
 * @param monster
 * @return Error
 */
Error add_monster_array(MonsterArray* array, Monster monster);

#endif
