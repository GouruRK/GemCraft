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

static Sector gem_button_sector(int width, int height) {
    Position top_left = init_position(width*CELL_SIZE, GAUGE_HEIGHT);
    Position bottom_right = init_position(width*CELL_SIZE + PANEL_WIDTH, GAUGE_HEIGHT + BUTTON_HEIGHT);
    return init_sector(top_left, bottom_right);
}

static Sector inventory_sector(int width, int height) {
    Position top_left = init_position(width*CELL_SIZE, height*CELL_SIZE - INVENTORY_HEIGHT);
    Position bottom_right = init_position(width*CELL_SIZE + PANEL_WIDTH, height*CELL_SIZE);
    return init_sector(top_left, bottom_right);
}


GameSectors init_game_sectors(int width, int height) {
    GameSectors sectors;
    sectors.window = window_sector(width, height);
    sectors.field = field_sector(width, height);
    sectors.panel = panel_sector(width, height);
    sectors.gauge = gauge_sector(width, height);
    sectors.gem_button = gem_button_sector(width, height);
    sectors.inventory = inventory_sector(width, height);
    return sectors;
}
