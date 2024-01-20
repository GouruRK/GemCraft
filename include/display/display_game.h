/**
 * @file display_game.h
 * @author Coserariu Alain & Kies Remy
 * @brief Main function to draw game on screen
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DISPLAY_GAME_H
#define DISPLAY_GAME_H

#include "game_engine/game.h"
#include "game_engine/field.h"
#include "game_engine/monster.h"
#include "game_engine/projectile.h"

void draw_game(const Game* game);

#endif
