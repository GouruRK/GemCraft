#ifndef DRAW_MANA_GAUGE_H
#define DRAW_MANA_GAUGE_H

#include "game_engine/player.h"
#include "utils/sector.h"

/**
 * @brief Get onscreen heigh for the given mana quantity 
 * 
 * @param max_quantity 
 * @param mana 
 * @return
 */
int get_height(int max_quantity, int mana);

/**
 * @brief Draw mana reserve
 * 
 * @param player Mana data of the player
 * @param info sector where to draw the gauge
 */
void draw_gauge(Player player, Sector info);

/**
 * @brief Display on gauge the max quantity and the current stored quantity
 *        of mana of the gauge
 * 
 * @param player 
 * @param info 
 */
void draw_gauge_numbers(Player player, Sector info);

#endif

