#include "utils/util.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

double uniform(void) { return rand() / (double)RAND_MAX; }

int random_int(int min, int max) { return (rand() % (max - min + 1)) + min; }

struct timespec diff_time(struct timespec start, struct timespec end) {
    struct timespec diff;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        diff.tv_sec = end.tv_sec - start.tv_sec - 1;
        diff.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        diff.tv_sec = end.tv_sec - start.tv_sec;
        diff.tv_nsec = end.tv_nsec - start.tv_nsec;
    }

    return diff;
}

color random_color() { return random_int(0, 359); }

long long max(long long a, long long b) {
    return (a > b) ? a : b; 
}

long long min(long long a, long long b) {
    return (a > b) ? b : a;
}

double degree_to_rad(int angle) {
    return angle * M_PI / 180;
}
