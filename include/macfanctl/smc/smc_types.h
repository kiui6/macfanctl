#ifndef SMC_TYPES_H
#define SMC_TYPES_H

#include <stdint.h>

typedef int16_t sp78_t;

static inline float sp78_to_float(sp78_t value) {
    return (float)value / 256.0f;
}

static inline sp78_t float_to_sp78(float value) {
    return (int)value * 256.0f;
}

#endif