/**
 * @file command_line.h
 * @author Coserariu Alain & Kies Remy
 * @brief Handle command lines
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <stdbool.h>

#include "utils/errors.h"

Error command_line(bool* help, int argc, char* argv[]);

#endif
