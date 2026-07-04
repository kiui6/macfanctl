#include <smc.h>

#include <IOKit/IOKitLib.h>

typedef struct {
    io_connect_t connection;
    int refCount;
    bool isOpen;
} SMCContext;

static SMCContext g_smc = { .connection = 0, .refCount = 0, .isOpen = false };



bool smc_read_sp78(const char* key, sp78_t* out) {
    return true;
}

bool smc_write_sp78(const char* key, sp78_t value) {
    return true;
}

bool smc_read_u16(const char* key, uint16_t* out) {
    return true;
}

bool smc_write_u16(const char* key, uint16_t value) {
    return true;
}