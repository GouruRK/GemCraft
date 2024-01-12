#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>

#include "game_engine/game.h"
#include "user_event/interact.h"
#include "display/game_sectors.h"
#include "utils/errors.h"

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
