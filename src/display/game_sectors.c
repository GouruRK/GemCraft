#include "display/game_sectors.h"

#include "display/display_const.h"
#include "utils/position.h"
#include "utils/sector.h"

static Sector window_sector(int width, int height) {
    Position top_left = init_position(0, 0);
    Position bottom_right = init_position(width*CELL_SIZE + PANEL_WIDTH, height*CELL_SIZE);
    return init_sector(top_left, bottom_right);
}

static Sector field_sector(int width, int height) {
    Position top_left = init_position(0, 0);
    Position bottom_right = init_position(width*CELL_SIZE, height*CELL_SIZE);
    return init_sector(top_left, bottom_right);
}

static Sector panel_sector(int width, int height) {
    Position top_left = init_position(width*CELL_SIZE, 0);
    Position bottom_right = init_position(width*CELL_SIZE + PANEL_WIDTH, height*CELL_SIZE);
    return init_sector(top_left, bottom_right);
}

static Sector gauge_sector(int width, int height) {
    Position top_left = init_position(width*CELL_SIZE, 0);
    Position bottom_right = init_position(width*CELL_SIZE + PANEL_WIDTH, GAUGE_HEIGHT);
    return init_sector(top_left, bottom_right);
}

static Sector create_panel_button_sector(int width, int height, int y) {
    Position top_left = init_position(width*CELL_SIZE, y);
    Position bottom_right = init_position(width*CELL_SIZE + PANEL_WIDTH, y + BUTTON_HEIGHT);
    return init_sector(top_left, bottom_right);
}

static Sector inventory_sector(int width, int height) {
    Position top_left = init_position(width*CELL_SIZE, height*CELL_SIZE - INVENTORY_HEIGHT);
    Position bottom_right = init_position(width*CELL_SIZE + PANEL_WIDTH, height*CELL_SIZE);
    return init_sector(top_left, bottom_right);
}

GameSectors init_game_sectors(int width, int height) {
    GameSectors sectors;

    // no need to use static here because this function is only called once
    Sector* buttons_sector[NB_BUTTONS] = {
        &sectors.upgrade_button,
        &sectors.gem_button,
        &sectors.tower_button,
        &sectors.add_button,
        &sectors.gem_lvl,
        &sectors.sub_button,
        &sectors.wave_button,
        &sectors.pause_button
    };

    sectors.window = window_sector(width, height);
    sectors.field = field_sector(width, height);
    sectors.panel = panel_sector(width, height);
    sectors.gauge = gauge_sector(width, height);
    
    for (int i = 0; i < NB_BUTTONS; i++) {
        *(buttons_sector[i]) = create_panel_button_sector(width, height, GAUGE_HEIGHT + i*BUTTON_HEIGHT);
    }

    sectors.inventory = inventory_sector(width, height);
    return sectors;
}
