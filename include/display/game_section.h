#ifndef GAME_SECTION_H
#define GAME_SECTION_H

#include "utils/sector.h"

#define INVENTORY_WIDTH 64

typedef struct {
    Sector field_section;
    Sector inventory_section;
} GameSection;

GameSection init_custom_game_section(Sector field, Sector inventory);
GameSection init_game_section(int width, int height);

#endif