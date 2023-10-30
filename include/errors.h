#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    OK                = 0,
    ALLOCATION_ERROR  = -1,
    NOT_ENOUGHT_MANA  = -2,
    DIFFERENT_GEM_LVL = -3
} Error;

#endif
