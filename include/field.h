#ifndef FIELD_H
#define FIELD_H

#include "../include/position.h"

#define WIDTH 28
#define HEIGHT 22

#define MAX_LEN WIDTH * HEIGHT

typedef enum { TOWER, NEST, CAMP, EMPTY, PATH } Objects;

typedef struct {
    int cur_len;
    Position_int path[MAX_LEN];
} MonsterPath;

typedef struct {
    Position_int nest;
    Position_int camp;
    Objects board[HEIGHT][WIDTH];
    MonsterPath monster_path;
} Field;

#endif
