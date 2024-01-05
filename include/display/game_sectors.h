#ifndef GAME_SECTION_H
#define GAME_SECTION_H

#include "utils/sector.h"

typedef struct {
    Sector window;
    Sector field;
    Sector panel;
    Sector gauge;
    Sector upgrade_button;
    Sector gem_button;
    Sector tower_button;
    Sector add_button;
    Sector gem_lvl;
    Sector sub_button;
    Sector pause_button;
    Sector wave_button;
    Sector inventory;
} GameSectors;

/**
 * @brief Creates sectors of buttons, field, inventory, ... for the window 
 * 
 * @return
 */
GameSectors init_game_sectors(void);

#endif