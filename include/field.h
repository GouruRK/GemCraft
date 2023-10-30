#ifndef FIELD_H
#define FIELD_H

#include "../include/position.h"

#define WIDTH 28
#define HEIGHT 22

#define MAX_LEN WIDTH * HEIGHT

typedef enum { TOWER, NEST, CAMP, EMPTY, PATH } Objects;

typedef struct {
    int cur_len;
    PositionInt path[MAX_LEN];
} MonsterPath;

typedef struct {
    PositionInt nest;
    PositionInt camp;
    Objects board[HEIGHT][WIDTH];
    MonsterPath monster_path;
} Field;

#endif
