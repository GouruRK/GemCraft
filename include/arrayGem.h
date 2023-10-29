#ifndef ARRAY_GEM_H
#define ARRAY_GEM_H

#include "gem.h"

typedef struct {
    int cur_size;
    int max_len;
    Gem* array;
} ArrayGem;

#endif
