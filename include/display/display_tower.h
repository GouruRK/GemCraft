/**
 * @file display_tower.h
 * @author Coserariu Alain & Kies Remy
 * @brief Contains tower representation
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DISPLAY_TOWER_H
#define DISPLAY_TOWER_H

#define BLOCK_SIZE 4
#define NB_BLOCKS 12

#include "game_engine/tower.h"

/**
 * @brief Display tower representation
 * 
 * @param tower 
 */
void draw_tower(Tower tower);

#endif
