#ifndef GAME_H
#define GAME_H

#include "field.h"
#include "monster.h"
#include "player.h"
#include "tower.h"

typedef struct {
    int wave;               // number of waves
    int time;               // time before next wave
    int game_status;        // pause, ...
    TowerArray towers;      // list of towers
    MonsterArray monsters;  // list of monsters
    Field field;            // game board
    Player player;          // player info
} Game;

#endif
