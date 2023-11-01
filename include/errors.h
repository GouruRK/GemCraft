#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    OK                = 0,
    ALLOCATION_ERROR  = -1,
    NOT_ENOUGHT_MANA  = -2,
    DIFFERENT_GEM_LVL = -3,
    TOWER_ARRAY_FULL  = -4,
    NON_EMPTY_PLACE   = -5
} Error;

#endif
