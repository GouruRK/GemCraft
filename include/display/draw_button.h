#ifndef DRAW_BUTTONS_H
#define DRAW_BUTTONS_H

#include "display/game_sectors.h"
#include "game_engine/game.h"

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
 * @param game
 * @param wave
 * @param gauge 
 */
void draw_wave_progression(const Game* game, Sector wave, Sector gauge);

/**
 * @brief Draw buttons outline
 * 
 * @param sectors 
 */
void draw_button_outline(const GameSectors* sectors);

#endif
