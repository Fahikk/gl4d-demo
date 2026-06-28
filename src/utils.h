#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

static inline float randf(float a, float b) {
    return a + (float)rand() / RAND_MAX * (b - a);
}

#endif