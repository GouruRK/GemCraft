#ifndef FIELD_H
#define FIELD_H

#include "cell.h"

#define WIDTH 28
#define HEIGHT 22

typedef struct {
    Objects board[HEIGHT][WIDTH];
    Cell nest;
    Cell camp;
} Field;

// Prototype
Field create_empty_field(void);

#endif
