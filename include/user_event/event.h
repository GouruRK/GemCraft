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

Event get_event(Interaction interaction);
bool process_event(Game* game);

#endif
