#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_engine/gem.h"
#include "game_engine/monster.h"
#include "game_engine/score.h"
#include "utils/position.h"
#include "utils/errors.h"

#define BASE_PROJ_ARRAY_SIZE 100

typedef struct {
    Position pos;
    float speed;
    Monster* target;
    Gem source;
} Projectile;

typedef struct {
    int max_size;
    int nb_elt;
    Projectile* array;
} ProjectileArray;

/*-----------------------------Projectile related-----------------------------*/

/**
 * @brief Creates a projectile object.
 *
 * @param pos current position
 * @param target
 * @param source
 * @return created projectile
 */
Projectile init_projectile(Position pos, Monster* target, Gem source);

/**
 * @brief Check if a projectile has reach his target
 *
 * @param proj
 * @return int
 */
int has_reach_target(Projectile* proj);

/**
 * @brief Deald damage to the target and apply effect
 *
 * @param proj
 * @param score
 * @param array
 */
void hit_target(Projectile* proj, Score* score, MonsterArray* array);

/**
 * @brief Move a projectile toward his target
 *
 * @param proj
 */
void move_projectile(Projectile* proj);

/*-------------------------------Array Related--------------------------------*/

/**
 * @brief Initialize given projectile array
 * 
 * @param array Array to initialize
 * @return Error allocation error
 */
Error init_projectile_array(ProjectileArray* array);

/**
 * @brief Copy proj into the last position of the array
 * Can double the amount of projectile if the max size is reached
 * 
 * @param array 
 * @param proj 
 * @return Error ALLOCATION_ERROR
 */
Error add_projectile_array(ProjectileArray* array, Projectile proj);

/**
 * @brief Overwrite the last element of the array into the element at the given 
 * index
 * 
 * @param array 
 * @param index 
 */
void suppress_proj_index(ProjectileArray* array, int index);

#endif
