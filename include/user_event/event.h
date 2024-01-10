#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>

#include "user_event/interact.h"
#include "game_engine/game.h"
#include "display/game_sectors.h"
#include "utils/errors.h"

typedef enum {
    NO_EVENT,
    SUMMON_WAVE,
    SUMMON_TOWER,
    SUMMON_GEM,
    PLACE_TOWER,
    CANCEL_PLACING_TOWER,
    CANCEL_PLACING_GEM,
    PICK_GEM_FROM_FIELD,
    PICK_GEM_FROM_INVENTORY,
    ADD_GEM_LEVEL,
    SUB_GEM_LEVEL,
    QUIT,
    DROP_GEM_IN_INVENTORY,
    DROP_GEM_IN_FIELD,
    CHANGE_GAME_STATUS,
    UPGRADE_MANA_POOL,
    SHOW_TOOLTIP,
    HIDE_TOOLTIP,
    SHOW_UPGRADE_COST,
    SHOW_GEM_COST,
    SHOW_TOWER_COST,
    SHOW_GEM_COST_ADD,
    SHOW_GEM_COST_SUB,
    SHOW_COMBINE_COST
} Event;

typedef Error (*event_function)(Game*);

/**
 * @brief Set 'data' to 1 whenever the player close the window
 * 
 * @param data 
 */
void exit_function(void* data);

/**
 * @brief Get the current event and process it by updating the current 
 *        player interaction
 * 
 * @param game  
 * @return 'true' if the player wants to quit,
 *         else 'false'
 */
bool process_event(Game* game);

/**
 * @brief Wait for the very next event
 * 
 * @param stop 
 */
void wait_event(int* stop);

#endif
