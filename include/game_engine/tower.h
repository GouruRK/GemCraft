#ifndef TOWERS_H
#define TOWERS_H

#include <stdbool.h>

#include "game_engine/gem.h"
#include "utils/position.h"
#include "utils/errors.h"
#include "utils/clock.h"

#define MAX_TOWER 616  // 22 * 28 = number of tiles on the field
#define TOWER_DEPLOY_TIME 2

typedef struct {
    Gem gem;
    bool hold_gem;
    Position pos;
    Clock deploy_timer;  // Timer to load the gem
    Clock shoot_interval;  // Metronom to shoot projectile
} Tower;

typedef struct {
    Tower lst[MAX_TOWER];
    int cur_len;
    int next_tower_cost;
    int free_towers;
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
Error remove_gem_from_tower(Tower* tower, Gem* gem);

/**
 * @brief Decrease clocks of the tower
 *
 * @param tower
 */
void update_clock_tower(Tower* tower);

//-------------------------------Tower Array related-------------------------------

/**
 * @brief Get cost for the next tower 
 * 
 * @param array 
 * @return
 */
int get_tower_cost(const TowerArray* array);

/**
 * @brief Add free towers
 * 
 * @param array 
 * @param nb_towers 
 */
void add_free_towers(TowerArray* array, int nb_towers);

/**
 * @brief Create a tower array object
 * 
 * @return tower array 
 */
TowerArray init_tower_array(void);

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
