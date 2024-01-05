#ifndef GET_EVENT_H
#define GET_EVENT_H

#include "event.h"
#include "interact.h"
#include "display/game_sectors.h"

/**
 * @brief Get the current event
 * 
 * @param interaction current player interaction
 * @return current event
 */
Event get_event(Interaction interaction, const GameSectors* sectors);

#endif
