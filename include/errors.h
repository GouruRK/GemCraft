#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    OK = 0,
    ALLOCATION_ERROR = -1,
    NOT_ENOUGHT_MANA = -2,
    DIFFERENT_GEM_LVL = -3,
    INCOHERENT_ARRAY_DATA = -4,
    TOWER_ARRAY_FULL = -5,
    NON_EMPTY_PLACE = -6,
    NON_EMPTY_TOWER = -7,
    EMPTY_TOWER = -8,
} Error;

#endif
