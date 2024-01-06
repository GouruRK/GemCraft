#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>

#include "interact.h"
#include "game_engine/game.h"
#include "display/game_sectors.h"

typedef enum {
    NO_EVENT,
    SUMMON_WAVE,
    SUMMON_TOWER,
    SUMMON_GEM,
    PLACE_TOWER,
    CANCEL_PLACING_TOWER,
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
    HIDE_TOOLTIP
} Event;

typedef void (*event_function)(Game*);

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

#endif
