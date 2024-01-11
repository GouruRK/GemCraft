#include "user_event/error_message.h"

#include <stdio.h>
#include <stdbool.h>

#include "user_event/event.h"
#include "utils/errors.h"
#include "utils/clock.h"

static char* mana_error[] = {
    [SUMMON_TOWER] = "create a tower",
    [SUMMON_GEM] = "create a gem at its selected level",
    [UPGRADE_MANA_POOL] = "upgrade the mana pool",
    [DROP_GEM_IN_INVENTORY] = "combine two gems",
    [ADD_GEM_LEVEL] = "not enough mana to create gem of superior level"
};

static char* inventory_error[] = {
    [CANCEL_PLACING_GEM] = "drop gem",
    [SUMMON_GEM] = "create gem"
};

static void create_error_message(char* message, Event event, Error code) {
    switch (code) {
        case NOT_ENOUGHT_MANA:
            sprintf(message, "Not enough mana to %s", mana_error[event]);
            break;
        case INVENTORY_FULL:
            sprintf(message, "Cannot %s because inventory's full", 
                    inventory_error[event]);
            break;
        case NON_EMPTY_TOWER:
            sprintf(message, "Cannot place gem in  the tower because its "
                             "not an empty tower");
            break;
        case DIFFERENT_GEM_LVL:
            sprintf(message, "Selected gems dont have the same level and "
                             "can't be combined");
            break;
        case WAVE_IS_ALREADY_SPAWNING:
            sprintf(message, "You have already reach the maximum of "
                             "simultaneous spawning waves");
            break;
        default:
            sprintf(message, "Unhandle code %d of event %d", 
                    code, event);
            break;
    }
}

ErrorMessage init_error_message(Event event, Error code) {
    ErrorMessage err;
    err.contains_message = true;
    err.event = event;
    err.code = code;
    err.clock = init_clock(-1, 5);
    create_error_message(err.message, event, code);
    return err;
}


