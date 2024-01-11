#ifndef DISPLAY_ERROR_H
#define DISPLAY_ERROR_H

#include "user_event/error_message.h"
#include "utils/sector.h"

void display_error(const ErrorMessage* err, Sector window);

#endif
