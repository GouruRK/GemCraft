#include "user_event/interact.h"

#include <stdbool.h>

#include "game_engine/tower.h"
#include "game_engine/field.h"
#include "game_engine/player.h"
#include "game_engine/gem.h"
#include "utils/errors.h"

/**
 * @brief Check if an interaction can be overwritten
 * 
 * @param action 
 * @return
 * @return
 */
static bool is_action_can_be_overwritten(Action action) {
   return action == NO_ACTION
            || action == SHOWING_GEM_COST 
            || action == SHOWING_TOWER_COST
            || action == SHOWING_UPGRADE_COST
            || action == SHOWING_GEM_COST_ADD
            || action == SHOWING_GEM_COST_SUB;
}

Interaction init_interact(void) {
    Interaction interact;
    interact.current_action = NO_ACTION;
    interact.gem_level = 0;
    interact.show_combine_cost = false;
    return interact;
} 

Error set_interact_tower_placement(Interaction* interact, Tower tower) {
    if (!is_action_can_be_overwritten(interact->current_action)) {
        return ACTION_ALREADY_IN_PROGRESS;
    }
    interact->current_action = PLACING_TOWER;
    interact->selected_tower = tower;
    return OK;
}

Error set_interact_gem_movement(Interaction* interact, Gem gem) {
    if (!is_action_can_be_overwritten(interact->current_action)) {
        return ACTION_ALREADY_IN_PROGRESS;
    }
    interact->current_action = MOVING_GEM;
    interact->selected_gem = gem;
    return OK;
}

Error set_interact_tooltip(Interaction* interact, ToolTip tip) {
    if (!is_action_can_be_overwritten(interact->current_action)) {
        return ACTION_ALREADY_IN_PROGRESS;
    }
    interact->current_action = SHOWING_TOOLTIP;
    interact->tooltip = tip;
    return OK;
}

/**
 * @brief Set given action to the current interaction if the current interaction
 *        can be overwritten
 * 
 * @param interact 
 * @param action 
 * @return
 */
static Error change_mouseover(Interaction* interact, Action action) {
    if (is_action_can_be_overwritten(interact->current_action)) {
        interact->current_action = action;
        return OK;
    }
    return ACTION_ALREADY_IN_PROGRESS;
}

Error set_interact_show_upgrade_cost(Interaction* interact) {
    return change_mouseover(interact, SHOWING_UPGRADE_COST);
}

Error set_interact_show_tower_cost(Interaction* interact) {
    return change_mouseover(interact, SHOWING_TOWER_COST);
}

Error set_interact_show_gem_cost(Interaction* interact) {
    return change_mouseover(interact, SHOWING_GEM_COST);
}

Error set_interact_show_gem_cost_add(Interaction* interact) {
    return change_mouseover(interact, SHOWING_GEM_COST_ADD);
}

Error set_interact_show_gem_cost_sub(Interaction* interact) {
    return change_mouseover(interact, SHOWING_GEM_COST_SUB);
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

void reset_overwritable_interaction(Interaction* interact) {
    if (is_action_can_be_overwritten(interact->current_action)) {
        interact->current_action = NO_ACTION;
    }
}
