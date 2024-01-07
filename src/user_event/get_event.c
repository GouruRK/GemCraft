#include "user_event/get_event.h"

#include <MLV/MLV_all.h>

#include "user_event/interact.h"
#include "display/game_sectors.h"

// link between keys and events
Event key_events[] = {
    ['q'] = QUIT,
    ['w'] = SUMMON_WAVE,
    ['t'] = SUMMON_TOWER
};

/**
 * @brief Get events triggered with the mouse
 * 
 * @param interaction 
 * @param sectors 
 * @param button 
 * @return
 */
static Event get_mouse_event(Interaction interaction, const GameSectors* sectors, MLV_Mouse_button button) {
    int x, y;
    MLV_get_mouse_position(&x, &y);
    if (button == MLV_BUTTON_LEFT) {
        if (interaction.current_action == PLACING_TOWER && is_coord_in_sector(sectors->field, x, y)) {
            return PLACE_TOWER;
        }
        if (interaction.current_action == MOVING_GEM) {
            if (is_coord_in_sector(sectors->inventory, x, y)) return DROP_GEM_IN_INVENTORY;
            if (is_coord_in_sector(sectors->field, x, y)) return DROP_GEM_IN_FIELD;
        }
        if (is_coord_in_sector(sectors->upgrade_button, x, y)) return UPGRADE_MANA_POOL;
        if (is_coord_in_sector(sectors->pause_button, x, y)) return CHANGE_GAME_STATUS;
        if (is_coord_in_sector(sectors->wave_button, x, y)) return SUMMON_WAVE;
        if (is_coord_in_sector(sectors->gem_button, x, y)) return SUMMON_GEM;
        if (is_coord_in_sector(sectors->add_button, x, y)) return ADD_GEM_LEVEL;
        if (is_coord_in_sector(sectors->sub_button, x, y)) return SUB_GEM_LEVEL;
        if (is_coord_in_sector(sectors->tower_button, x, y)) return SUMMON_TOWER;
        if (interaction.current_action == NO_ACTION) {
            if (is_coord_in_sector(sectors->field, x, y)) return PICK_GEM_FROM_FIELD;
            if (is_coord_in_sector(sectors->inventory, x, y)) return PICK_GEM_FROM_INVENTORY;
        }
        return HIDE_TOOLTIP;
    } else if (button == MLV_BUTTON_RIGHT) {
        if (interaction.current_action == PLACING_TOWER) {
            return CANCEL_PLACING_TOWER;
        } 
        if (interaction.current_action == NO_ACTION) {
            return SHOW_TOOLTIP;
        }
        return HIDE_TOOLTIP;
    }
    
    if (is_coord_in_sector(sectors->upgrade_button, x, y)) return SHOW_UPGRADE_COST;
    if (is_coord_in_sector(sectors->gem_button, x, y)) return SHOW_GEM_COST;
    if (is_coord_in_sector(sectors->tower_button, x, y)) return SHOW_TOWER_COST;

    return NO_EVENT;
}

Event get_event(Interaction interaction, const GameSectors* sectors) {
    // intel on keyboard
    MLV_Keyboard_modifier mod;
    MLV_Keyboard_button sym;
    MLV_Button_state state;

    // intel on mouse
    MLV_Mouse_button mouse_but;

    MLV_Event event = MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL, NULL, &mouse_but,
                              &state);

    if (state == MLV_RELEASED) {
        return NO_EVENT;
    }

    if (event == MLV_KEY) {
        return key_events[sym];
    }
    return get_mouse_event(interaction, sectors, mouse_but);
}
