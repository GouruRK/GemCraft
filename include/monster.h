#ifndef MONSTER_H
#define MONSTER_H

#include <time.h>

#include "errors.h"
#include "position.h"

#define MAX_WAVE_SIZE 24

typedef enum {
    NONE,
    SPLASH,      // Pyro
    PARASIT,     // Dendro
    SLOW,        // Hydro
    SPRAYING,    // Pyro + Hydro
    BURN,        // Pyro + Dendro
    PETRIFICUS,  // Dendro + Hydro
} Status;

typedef enum {
    NORMAL,
    CROWD,
    FAST,
    BOSS,
} TypeWave;

typedef struct {
    int health;
    int max_health;
    int color;
    int index_path; // Position in the path array in a field
    float speed;  // Number of cases per seconde traveled
    struct timespec effect_duration;
    Position pos;
    Position dest;
    Status status;
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
int has_reach_dest(Monster* monster);

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
