/**
 * @file tower_placement.h
 * @author Coserariu Alain & Kies Remy
 * @brief Contains function interact with towers
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TOWER_PLACEMENT_H
#define TOWER_PLACEMENT_H

#include "game_engine/tower.h"
#include "utils/sector.h"

/**
 * @brief Create a tower object at the player's mouse
 * 
 * @param panel 
 * @return
 */
Tower init_tower_at_mouse(Sector panel);

/**
 * @brief Update a tower's position at the player's mouse
 * 
 * @param panel 
 * @param tower 
 */
void update_tower_placement(Sector panel, Tower* tower);

#endif
