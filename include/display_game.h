#ifndef DISPLAY_GAME_H
#define DISPLAY_GAME_H

#include "field.h"
#include "monster.h"
#include "projectile.h"

#define CELL_SIZE 32

// PROTOTYPE
void draw_board(Field field);
void draw_monster(const Monster* m);
void draw_projectile(const Projectile* proj);
void draw_tower(const Tower tower);
#endif
