#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>

#include "interact.h"
#include "game_engine/game.h"

typedef enum {
    NO_EVENT,
    SUMMON_WAVE,
    SUMMON_TOWER,
    PLACE_TOWER,
    CANCEL_PLACING_TOWER,
    QUIT
} Event;

void exit_function(void* data);

/**
 * @brief Get the current event
 * 
 * @param interaction current player interaction
 * @return current event
 */
Event get_event(Interaction interaction);

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
