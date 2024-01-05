#include "user_event/get_event.h"

#include <MLV/MLV_all.h>

#include "user_event/interact.h"
#include "display/game_sectors.h"

Event key_events[] = {
    ['q'] = QUIT,
    ['w'] = SUMMON_WAVE,
    ['t'] = SUMMON_TOWER
};

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
        if (is_coord_in_sector(sectors->gem_button, x, y)) return SUMMON_GEM;
        if (is_coord_in_sector(sectors->add_button, x, y)) return ADD_GEM_LEVEL;
        if (is_coord_in_sector(sectors->sub_button, x, y)) return SUB_GEM_LEVEL;
        if (is_coord_in_sector(sectors->tower_button, x, y)) return SUMMON_TOWER;
        if (interaction.current_action == NO_ACTION) {
            if (is_coord_in_sector(sectors->field, x, y)) return PICK_GEM_FROM_FIELD;
            if (is_coord_in_sector(sectors->inventory, x, y)) return PICK_GEM_FROM_INVENTORY;
        }
    } else if (button == MLV_BUTTON_RIGHT) {
        if (interaction.current_action == PLACING_TOWER) {
            return CANCEL_PLACING_TOWER;
        }
    }
    return NO_EVENT;
}

Event get_event(Interaction interaction, const GameSectors* sectors) {
    // intel on keyboard
    MLV_Keyboard_modifier mod;
    MLV_Keyboard_button sym;
    MLV_Button_state state;
    static MLV_Button_state prev_state;

    // intel on mouse
    MLV_Mouse_button mouse_but;

    MLV_Event event = MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL, NULL, &mouse_but,
                              &state);

    if (state == prev_state) { // to prevent placing a gem right after picking it
        return NO_EVENT;
    } 
    prev_state = state;

    if (state == MLV_RELEASED) {
        return NO_EVENT;
    }

    if (event == MLV_KEY) {
        return key_events[sym];
    }
    return get_mouse_event(interaction, sectors, mouse_but);
}
