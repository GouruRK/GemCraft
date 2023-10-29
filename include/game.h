#ifndef GAME_H
#define GAME_H

#include "tower.h"
#include "monster.h"
#include "field.h"
#include "player.h"

typedef struct {
    int wave;               // number of waves
    int time;               // time before next wave
    TowerArray towers;       // list of towers
    MonsterArray monsters;   // list of monsters
    Field field;            // game board
    Player player;          // player info
    int game_status;        // pause, ...
} Game;

#endif
