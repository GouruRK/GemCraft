#ifndef DRAW_MANA_GAUGE_H
#define DRAW_MANA_GAUGE_H

#include "game_engine/player.h"
#include "utils/sector.h"

/**
 * @brief Draw mana reserve
 * 
 * @param player Mana data of the player
 * @param info sector where to draw the gauge
 */
void draw_gauge(Player player, Sector info);

#endif

