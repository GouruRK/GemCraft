#ifndef DISPLAY_GAME_H
#define DISPLAY_GAME_H

#include "field.h"
#include "monster.h"

#define CELL_SIZE 32

void draw_board(Field field);
void draw_monster(const Monster m);

#endif
