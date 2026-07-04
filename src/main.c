#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#include <smc.h>

#include "curve_point.h"
#include "config.h"

int main() {
    // Read config
    Config cfg = create_config();
    CurveGraph graph = create_curve_graph();

    if(!read_config(&cfg, &graph)) {
        // Log error
    }
    
    printf("MinRPM: %u", cfg.minRPM);

    // Find SMC

    uint16_t currentSpeed = 0;

    bool bRunning = true;
    while(bRunning) {
        // Query sensors

        // Calculate target
        uint16_t targetSpeed = 0;

        // Interpolate for this tick
        if(targetSpeed > currentSpeed) {
            // Ramp up
        } else {
            //
        }

        // Set fan speed

        // Wait 250ms (4Hz)
        usleep(250000);
    }

    return 0;
}