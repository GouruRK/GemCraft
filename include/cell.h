#ifndef CELL_H
#define CELL_H

#include "position.h"

typedef enum {
    TOWER,
    NEST,
    CAMP,
    EMPTY,
    PATH
} Objects;


typedef struct cell {
    Position pos;
    Objects type;
} Cell;

#endif
