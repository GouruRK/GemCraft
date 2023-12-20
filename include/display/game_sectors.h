#ifndef GAME_SECTION_H
#define GAME_SECTION_H

#include "utils/sector.h"

typedef struct {
    Sector field;
    Sector panel;
    Sector gauge;
    Sector window;
    Sector inventory;
} GameSectors;

GameSectors init_game_sectors(int width, int height);

#endif