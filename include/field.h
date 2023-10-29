#ifndef __INIT_FIELD__
#define __INIT_FIELD__

#include "cell.h"

#define WIDTH 28
#define HEIGHT 22

typedef struct {
    Cell board[HEIGHT][WIDTH];
    Cell nest;
    Cell camp;
} Field;

#endif
