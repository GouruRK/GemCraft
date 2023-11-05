#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "position.h"
#include "monster.h"
#include "gem.h"

typedef struct {
    float speed;
    Position pos;
    Monster* target;
    Gem source;
} Projectile;

typedef struct _node {
    struct _node* next;
    Projectile proj;
} Node, *ProjectileArray;

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
 * @brief Creates an empty node object.
 * 
 * @return Node* if success, else NULL
 */
Node* init_node(void);

/**
 * @brief Creates a node object with given projectile.
 * 
 * @param proj projectile
 * @return Node* if success, else NULL
 */
Node* init_filled_node(Projectile proj);

/**
 * @brief Creates a array object.
 * 
 * @return Array (NULL by default)
 */
ProjectileArray create_array(void);

/**
 * @brief Adds a node at the array's head.
 *        Node must not be NULL.
 * 
 * @param array array to add
 * @param node node to be added
 * @return 1 in case of success, else 0
 */
int add_node(ProjectileArray* array, Node* node);

/**
 * @brief Creates a node that contains the given projectile and add them 
 *        at the array's head.
 * 
 * @param array array to add the projectile 
 * @param proj projectile to be added
 * @return 1 in case of sucess else 0
 */
int add_projectile(ProjectileArray* array, Projectile proj);

/**
 * @brief Pops and return the array's head node. 
 * 
 * @param array array pop the node
 * @return popped node
 */
Node* pop_node(ProjectileArray* array);

/**
 * @brief Frees allocated memory of the array.
 * 
 * @param array array to free 
 */
void free_array(ProjectileArray* array);

#endif
