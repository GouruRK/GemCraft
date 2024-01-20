/**
 * @file errors.h
 * @author Coserariu Alain & Kies Remy
 * @brief Contains all possible errors that can occur during the program
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    OK = 0,
    ALLOCATION_ERROR = -1,
    NOT_ENOUGHT_MANA = -2,
    DIFFERENT_GEM_LVL = -3,
    MONSTER_ARRAY_IS_FULL = -4,
    TOWER_ARRAY_FULL = -5,
    NON_EMPTY_PLACE = -6,
    NON_EMPTY_TOWER = -7,
    EMPTY_TOWER = -8,
    OUT_OF_FIELD = -9,
    NON_EMPTY_INVENTORY_PLACE = -10,
    EMPTY_INVENTORY_PLACE = -11,
    INVENTORY_FULL = -12,
    ACTION_ALREADY_IN_PROGRESS = -13,
    INVALID_ACTION = -14,
    INVALID_TILE = -15,
    NO_TOWER_FOUND = -16,
    WAVE_IS_ALREADY_SPAWNING = -17,
    MAXIMUM_LEVEL_REACH = -18,
    UNKNOWN_ARGUMENT = -19
} Error;

#endif
