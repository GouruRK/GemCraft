/**
 * @file display_const.h
 * @author Coserariu Alain & Kies Remy
 * @brief Defines constants for graphic interface
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DISPLAY_CONST_H
#define DISPLAY_CONST_H

#include "game_engine/inventory.h"
#include "game_engine/field.h"

#define NB_BUTTONS 8

#define CELL_SIZE 32
#define PANEL_WIDTH (2*CELL_SIZE)
#define GAUGE_HEIGHT 128
#define BUTTON_HEIGHT CELL_SIZE

#define INVENTORY_HEIGHT (INVENTORY_SIZE / 2 * CELL_SIZE)

#define FIELD_WIDTH (CELL_SIZE*WIDTH)
#define FIELD_HEIGHT (CELL_SIZE*HEIGHT)

#endif
