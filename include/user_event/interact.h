/**
 * @file interact.h
 * @author Coserariu Alain & Kies Remy
 * @brief Contains all possible interaction with the mouse, such as tower in 
 * the hand, gem in the hand...
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef INTERACT_H
#define INTERACT_H

#include <stdbool.h>

#include "game_engine/tower.h"
#include "game_engine/gem.h"
#include "game_engine/field.h"
#include "game_engine/player.h"
#include "utils/position.h"
#include "display/tooltip.h"
#include "user_event/error_message.h"

typedef enum {
    NO_ACTION,
    PLACING_TOWER,
    MOVING_GEM,
    SHOWING_TOOLTIP,
    SHOWING_UPGRADE_COST,
    SHOWING_GEM_COST,
    SHOWING_TOWER_COST,
    SHOWING_GEM_COST_ADD,
    SHOWING_GEM_COST_SUB,
    SHOWING_COMBINE_COST,
} Action;

typedef struct {
    Action current_action;
    union {
        Tower selected_tower;
        Gem selected_gem;
        ToolTip tooltip;
    };
    Position object_pos;
    unsigned int gem_level;
    bool show_combine_cost;
    ErrorMessage err;
} Interaction;

/**
 * @brief Init interactoin object with no current action
 * 
 * @return
 */
Interaction init_interact(void);

/**
 * @brief Set current interaction to `PLACING_TOWER` and set the tower
 * 
 * @param interact 
 * @param tower 
 * @return
 */
Error set_interact_tower_placement(Interaction* interact, Tower tower);

/**
 * @brief Set current interaction to `MOVING_GEM` and set the given gem
 * 
 * @param interact 
 * @param gem 
 * @return
 */
Error set_interact_gem_movement(Interaction* interact, Gem gem);

/**
 * @brief Set current interaction to `SHOWING_TOOLTIP` and set the given tooltip
 * 
 * @param interact 
 * @param tip 
 * @return
 */
Error set_interact_tooltip(Interaction* interact, ToolTip tip);

/**
 * @brief Set current interaction to `SHOWING_UPGRADE_COST`
 * 
 * @param interact 
 * @return
 */
Error set_interact_show_upgrade_cost(Interaction* interact);

/**
 * @brief Set current interaction to `SHOWING_TOWER_COST`
 * 
 * @param interact 
 * @return
 */
Error set_interact_show_tower_cost(Interaction* interact);

/**
 * @brief Set current interaction to `SHOWING_GEM_COST`
 * 
 * @param interact 
 * @return
 */
Error set_interact_show_gem_cost(Interaction* interact);

/**
 * @brief Set current interaction to `SHOWING_GEM_COST_ADD`
 * 
 * @param interact 
 * @return
 */
Error set_interact_show_gem_cost_add(Interaction* interact);

/**
 * @brief Set current interaction to `SHOWING_GEM_COST_SUB`
 * 
 * @param interact 
 * @return
 */
Error set_interact_show_gem_cost_sub(Interaction* interact);

/**
 * @brief Place a tower on the current square of the field
 * 
 * @param interact 
 * @param field 
 * @param player 
 * @return
 */
Error drop_tower(Interaction* interact, Field* field, Player* player);

/**
 * @brief Cancel current user interaction
 * 
 * @param interact 
 */
void cancel_interaction(Interaction* interact);

/**
 * @brief Set current interaction to no interaction
 * 
 * @param interact 
 */
void reset_interaction(Interaction* interact);

/**
 * @brief Reset current interaction if possible
 * 
 * @param interact 
 */
void reset_overwritable_interaction(Interaction* interact);

#endif
