#ifndef TOWERS_H
#define TOWERS_H

#include <stdbool.h>

#include "gem.h"
#include "position.h"
#include "errors.h"

#define MAX_TOWER 616  // 22 * 28 = number of tiles on the field

typedef struct {
    Gem gem;
    bool hold_gem;
    Position pos;
} Tower;

typedef struct {
    Tower lst[MAX_TOWER];
    int cur_len;
    int next_tower_cost;
} TowerArray;

//-------------------------------Tower manipulation-------------------------------

/**
 * @brief Create a tower object from a given position
 * 
 * @param pos positin of the tower
 * @return created tower
 */
Tower init_tower(Position pos);

/**
 * @brief Add a gem to a tower
 * 
 * @param tower tower to add the gem
 * @param gem gem to be added
 * @return NON_EMPTY_TOWER if the tower already contains a gem
 *         else OK
 */
Error add_gem_to_tower(Tower* tower, Gem gem);

/**
 * @brief Remove the gem from a tower and store it in `gem`
 * 
 * @param tower tower to remove the gem
 * @param gem removed gem
 * @return EMPTY_TOWER if the tower does not contains a gem
 *         else OK
 */
Error remove_gem_to_tower(Tower* tower, Gem* gem);

//-------------------------------Tower Array related-------------------------------

/**
 * @brief Create a tower array object
 * 
 * @return tower array 
 */
TowerArray create_tower_array(void);

/**
 * @brief Add a tower to a towerArray
 * 
 * @param array array to add the tower
 * @param tower tower to be added
 * @return TOWER_ARRAY_FULL if the array can no longer add towers
 *         else OK
 */
Error add_tower_array(TowerArray* array, Tower tower);

#endif
