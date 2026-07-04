#ifndef SMC_H
#define SMC_H

#include <stdbool.h>

#include "smc_types.h"

bool smc_read_sp78(const char* key, sp78_t* out);
bool smc_write_sp78(const char* key, sp78_t value);

bool smc_read_u16(const char* key, uint16_t* out);
bool smc_write_u16(const char* key, uint16_t value);

#endif