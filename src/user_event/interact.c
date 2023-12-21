#include "user_event/interact.h"
#include "game_engine/tower.h"
#include "game_engine/field.h"
#include "game_engine/player.h"
#include "game_engine/gem.h"
#include "utils/errors.h"

Interaction init_interact(void) {
    Interaction interact;
    interact.current_action = NO_ACTION;
    return interact;
} 

Error set_interact_tower_placement(Interaction* interact, Tower tower) {
    if (interact->current_action != NO_ACTION) {
        return ACTION_ALREADY_IN_PROGRESS;
    }
    interact->current_action = PLACING_TOWER;
    interact->selected_tower = tower;
    return OK;
}

Error set_interact_gem_movement(Interaction* interact, Gem gem) {
    if (interact->current_action != NO_ACTION) {
        return ACTION_ALREADY_IN_PROGRESS;
    }
    interact->current_action = MOVING_GEM;
    interact->selected_gem = gem;
    return OK;
}

Error drop_tower(Interaction* interact, Field* field, Player* player) {
    if (interact->current_action != PLACING_TOWER) {
        return INVALID_ACTION;
    }
    Error err = place_tower(field, player, interact->selected_tower);
    if (err != OK) {
        return err;
    }
    interact->current_action = NO_ACTION;
    return OK;
}

void cancel_interaction(Interaction* interact) {
    if (interact->current_action == PLACING_TOWER) {
        interact->current_action = NO_ACTION;
    }
}

void reset_interaction(Interaction* interact) {
    interact->current_action = NO_ACTION;
}
