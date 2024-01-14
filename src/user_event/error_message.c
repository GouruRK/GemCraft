#include "user_event/error_message.h"

#include <stdio.h>
#include <stdbool.h>

#include "user_event/event.h"
#include "utils/errors.h"
#include "utils/clock.h"

// kind of errors when player is missing mana
static char* mana_error[] = {
    [SUMMON_TOWER] = "create a tower",
    [SUMMON_GEM] = "create a gem at its selected level",
    [UPGRADE_MANA_POOL] = "upgrade the mana pool",
    [DROP_GEM_IN_INVENTORY] = "combine two gems",
    [ADD_GEM_LEVEL] = "not enough mana to create gem of superior level"
};

// kind of errors with inventory
static char* inventory_error[] = {
    [CANCEL_PLACING_GEM] = "drop gem",
    [SUMMON_GEM] = "create gem"
};

/**
 * @brief Create a error message object according to the event 
 *        and the error code
 * 
 * @param message 
 * @param event 
 * @param code 
 */
static void create_error_message(char* message, Event event, Error code) {
    switch (code) {
        case NOT_ENOUGHT_MANA:
            sprintf(message, "Not enough mana to %s", mana_error[event]);
            break;
        case MAXIMUM_LEVEL_REACH:
            sprintf(message, "You've reach the maximum level of the mana pool");
            break;
        case INVENTORY_FULL:
            sprintf(message, "Cannot %s because inventory's full", 
                    inventory_error[event]);
            break;
        case DIFFERENT_GEM_LVL:
            sprintf(message, "Selected gems dont have the same level and "
                             "can't be combined");
            break;
        case WAVE_IS_ALREADY_SPAWNING:
            sprintf(message, "You have already reach the maximum of "
                             "simultaneous spawning waves");
            break;
        case NO_TOWER_FOUND:
        case NON_EMPTY_TOWER:
            sprintf(message, "You can only place gems on empty towers");
            break;
        case NON_EMPTY_PLACE:
            sprintf(message, "Towers can only be placed on empty tiles");
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
    err.clock = init_clock(-1, 4);
    create_error_message(err.message, event, code);
    return err;
}


