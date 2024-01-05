#include "display/game_sectors.h"

#include "display/display_const.h"
#include "utils/position.h"
#include "utils/sector.h"
#include "game_engine/field.h"

/**
 * @brief Create full window sector
 * 
 * @return
 */
static Sector window_sector(void) {
    Position top_left = init_position(0, 0);
    Position bottom_right = init_position(FIELD_WIDTH + PANEL_WIDTH, FIELD_HEIGHT);
    return init_sector(top_left, bottom_right);
}

/**
 * @brief Create the field sector
 * 
 * @return
 */
static Sector field_sector(void) {
    Position top_left = init_position(0, 0);
    Position bottom_right = init_position(FIELD_WIDTH, FIELD_HEIGHT);
    return init_sector(top_left, bottom_right);
}

/**
 * @brief Create the rigth-panel sector, with all the controls buttons 
 * 
 * @return
 */
static Sector panel_sector(void) {
    Position top_left = init_position(FIELD_WIDTH, 0);
    Position bottom_right = init_position(FIELD_WIDTH + PANEL_WIDTH, FIELD_HEIGHT);
    return init_sector(top_left, bottom_right);
}

/**
 * @brief Create the gauge sector to draw mana
 * 
 * @return
 */
static Sector gauge_sector(void) {
    Position top_left = init_position(FIELD_WIDTH, 0);
    Position bottom_right = init_position(FIELD_WIDTH + PANEL_WIDTH, GAUGE_HEIGHT);
    return init_sector(top_left, bottom_right);
}

/**
 * @brief Create a button with a given ordinate
 * 
 * @param y 
 * @return
 */
static Sector create_panel_button_sector(int y) {
    Position top_left = init_position(FIELD_WIDTH, y);
    Position bottom_right = init_position(FIELD_WIDTH + PANEL_WIDTH, y + BUTTON_HEIGHT);
    return init_sector(top_left, bottom_right);
}

/**
 * @brief Create the inventory sector to save gems
 * 
 * @return
 */
static Sector inventory_sector(void) {
    Position top_left = init_position(FIELD_WIDTH, FIELD_HEIGHT - INVENTORY_HEIGHT);
    Position bottom_right = init_position(FIELD_WIDTH + PANEL_WIDTH, FIELD_HEIGHT);
    return init_sector(top_left, bottom_right);
}

GameSectors init_game_sectors(void) {
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

    sectors.window = window_sector();
    sectors.field = field_sector();
    sectors.panel = panel_sector();
    sectors.gauge = gauge_sector();
    
    for (int i = 0; i < NB_BUTTONS; i++) {
        *(buttons_sector[i]) = create_panel_button_sector(GAUGE_HEIGHT + i*BUTTON_HEIGHT);
    }

    sectors.inventory = inventory_sector();
    return sectors;
}
