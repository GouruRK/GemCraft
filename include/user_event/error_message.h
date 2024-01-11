#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include <stdbool.h>

#include "user_event/events.h"
#include "utils/errors.h"
#include "utils/clock.h"

typedef struct {
    bool contains_message;
    Event event;
    Error code;
    Clock clock;
    char message[512];
} ErrorMessage;

/**
 * @brief Create an error message structure according to the given event
 *        and the error code
 * 
 * @param event 
 * @param code 
 * @return
 */
ErrorMessage init_error_message(Event event, Error code);

#endif
