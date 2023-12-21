#ifndef INTERACT_H
#define INTERACT_H

#include "game_engine/tower.h"
#include "game_engine/gem.h"
#include "game_engine/field.h"
#include "game_engine/player.h"
#include "utils/position.h"

typedef enum {
    NO_ACTION,
    PLACING_TOWER,
    MOVING_GEM
} Action;

typedef struct {
    Action current_action;
    union {
        Tower selected_tower;
        Gem selected_gem;
    };
    Position object_pos;
} Interaction;

/**
 * @brief Init interactoin object with no current action
 * 
 * @return
 */
Interaction init_interact(void);

/**
 * @brief Set the current interaction to `PLACING_TOWER` and set the tower
 * 
 * @param interact 
 * @param tower 
 * @return
 */
Error set_interact_tower_placement(Interaction* interact, Tower tower);

Error set_interact_gem_movement(Interaction* interact, Gem gem);

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

void reset_interaction(Interaction* interact);

#endif
