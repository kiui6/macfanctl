#include <macfanctl/macfanctl.h>

 struct {
    macfanctl_sensor_id_t id;
    uint32_t refCount;
    const char key[5];
} macfanctl_sensor;

typedef struct {
    macfanctl_fan_index_t id;
    uint32_t refCount;
    const char key[5];
} macfanctl_fan;

bool macfanctl_init(void) {
    return true;
}

void macfanctl_shutdown(void) {

}

macfanctl_sensor_t* macfanctl_sensor_open(macfanctl_sensor_id_t id) {
    return NULL;
}

void macfanctl_sensor_close(macfanctl_sensor_t* sensor) {

}

float macfanctl_sensor_read_celcius(macfanctl_sensor_t* sensor) {
    return 0;
}

macfanctl_fan_index_t macfanctl_get_fan_count(void) {
    return 0;
}

macfanctl_fan_t* macfanctl_fan_open(macfanctl_fan_index_t id) {
    return NULL;
}

void macfanctl_fan_close(macfanctl_fan_t* fan) {

}

bool macfanctl_fan_set_rpm(macfanctl_fan_t* fan, uint16_t rpm) {
    return true;
}