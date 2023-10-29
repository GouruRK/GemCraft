#ifndef CELL_H
#define CELL_H

#include "position.h"

typedef enum {
    TOWER,
    MONSTER,
    NEST,
    CAMP,
    EMPTY
} Objects;


typedef struct cell {
    Position pos;
    Objects type;
} Cell;

#endif
