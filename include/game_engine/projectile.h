#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_engine/gem.h"
#include "game_engine/monster.h"
#include "utils/position.h"
#include "utils/errors.h"

#define BASE_PROJ_ARRAY_SIZE 1000

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
 * @param array
 */
void hit_target(Projectile* proj, MonsterArray* array);

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

// /**
//  * @brief Creates an empty node object.
//  *
//  * @return Node* if success, else NULL
//  */
// Node* init_node(void);

// /**
//  * @brief Creates a node object with given projectile.
//  *
//  * @param proj projectile
//  * @return Node* if success, else NULL
//  */
// Node* init_filled_node(Projectile proj);

// /**
//  * @brief Creates a array object.
//  *
//  * @return Array (NULL by default)
//  */
// ProjectileArray create_array(void);

// /**
//  * @brief Adds a node at the array's head.
//  *        Node must not be NULL.
//  *
//  * @param array array to add
//  * @param node node to be added
//  * @return 1 in case of success, else 0
//  */
// int add_node(ProjectileArray* array, Node* node);

// /**
//  * @brief Creates a node that contains the given projectile and add them
//  *        at the array's head.
//  *
//  * @param array array to add the projectile
//  * @param proj projectile to be added
//  * @return 1 in case of sucess else 0
//  */
// int add_projectile(ProjectileArray* array, Projectile proj);

// /**
//  * @brief Pops and return the array's head node.
//  *
//  * @param array array pop the node
//  * @return popped node
//  */
// Node* pop_node(ProjectileArray* array);

// /**
//  * @brief Frees allocated memory of the array.
//  *
//  * @param array array to free
//  */
// void free_array(ProjectileArray* array);

#endif
