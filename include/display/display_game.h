#ifndef DISPLAY_GAME_H
#define DISPLAY_GAME_H

#include "game_engine/game.h"
#include "game_engine/field.h"
#include "game_engine/monster.h"
#include "game_engine/projectile.h"

#define BLOCK_SIZE 4
#define NB_BLOCKS 12

// PROTOTYPE
void draw_game(const Game* game);

#endif
