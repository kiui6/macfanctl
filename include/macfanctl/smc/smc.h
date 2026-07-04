#ifndef SMC_H
#define SMC_H

#include <stdbool.h>

#include "smc_types.h"

#define SMC_KEY_TEMP_CPU_PROXIMITY  "TC0P"
#define SMC_KEY_TEMP_CPU_DIE        "TC0D"
#define SMC_KEY_TEMP_GPU_PROXIMITY  "TC1P"
#define SMC_KEY_TEMP_BATTERY        "TC0D"

bool smc_init(void);
void smc_shutdown(void);

bool smc_read_sp78(const char* key, sp78_t* out);
bool smc_write_sp78(const char* key, sp78_t value);

bool smc_read_u16(const char* key, uint16_t* out);
bool smc_write_u16(const char* key, uint16_t value);

#endif