#include "interpolate.h"

uint16_t interpolate_uint16(uint16_t current, uint16_t target, float dT) {
    return current + (((float)target - current) * dT);
}