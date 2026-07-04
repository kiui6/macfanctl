#ifndef MACFANCTL_H
#define MACFANCTL_H

#include <stdint.h>

bool macfanctl_init(void);
void macfanctl_shutdown(void);

typedef struct {

} macfanctl_sensor_t;

typedef enum {
    MACFANCTL_SENSOR_CPU_CORE,
    MACFANCTL_SENSOR_CPU_PROXIMITY,
    MACFANCTL_SENSOR_GPU_DIODE,
    MACFANCTL_SENSOR_AMBIENT,
    MACFANCTL_SENSOR_COUNT
} macfanctl_sensor_id_t;

macfanctl_sensor_t* macfanctl_open_sensor(macfanctl_sensor_id_t id);
void macfanctl_open_sensor(macfanctl_sensor_t* sensor);

float macfanctl_sensor_read_celcius(macfanctl_sensor_t* sensor);

typedef struct {

} macfanctl_fan_t;

typedef enum {
    MACFANCTL_FAN_0,
    MACFANCTL_FAN_1,
    MACFANCTL_FAN_2,
    MACFANCTL_FAN_3
} macfanctl_fan_id_t;

macfanctl_fan_t* macfanctl_fan_open(macfanctl_fan_id_t id);
void macfanctl_fan_close(macfanctl_fan_t* fan);

bool macfanctl_fan_set_rpm(macfanctl_fan_t* fan, uint16_t rpm);

#endif