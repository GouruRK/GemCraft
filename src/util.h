#include <stdlib.h>

double uniform(void) {
    return rand() / (double)RAND_MAX;
}

int random_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}
