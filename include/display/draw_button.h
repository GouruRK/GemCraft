#ifndef DRAW_BUTTONS_H
#define DRAW_BUTTONS_H

#include "display/game_sectors.h"

#define BUTTON_BACKGROUND_COLOR MLV_COLOR_DARKSLATEGREY
#define BUTTON_HOVER_COLOR MLV_rgba(32, 56, 56, 255)
#define BUTTON_TEXT_COLOR MLV_COLOR_WHITE

/**
 * @brief Draw all buttons on the control panel
 * 
 * @param sectors 
 */
void draw_buttons(const GameSectors* sectors);

/**
 * @brief Draw the remaining time of the next wave on wave button
 * 
 * @param remaining_time 
 * @param nb_wave 
 * @param wave 
 */
void draw_wave_progression(int remaining_time, int nb_wave, Sector wave);

#endif
