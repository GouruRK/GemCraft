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
    PLACE_GEM,
    CANCEL_PLACING_TOWER,
    MOVE_GEM,
    QUIT
} Event;

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
