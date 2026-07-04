#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include <macfanctl/point_curve.h>

typedef struct {
    char sensorKey[5];
    uint16_t minRPM;
    uint16_t maxRPM;
    uint32_t sleepTimeMiliseconds;
    uint32_t rampDownTimeMiliseconds;
} Config;

Config create_config();

void get_config_path(char* buffer, size_t* size);

bool read_config(Config* cfg, CurveGraph* graph);

#endif