/**
 * @file generation.h
 * @author Coserariu Alain & Kies Remy
 * @brief Create a random game field
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GENERATION_H
#define GENERATION_H

#include "game_engine/field.h"

/**
 * @brief Generate a field containing a nest, a camp, and a path for monsters 
 * joining both
 * 
 * @return Field 
 */
Field generate_field();

#endif
