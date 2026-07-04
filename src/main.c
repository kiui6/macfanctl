#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#include <smc.h>

#include "signal.h"
#include "curve_point.h"
#include "config.h"

int main() {
    setup_sig_handlers();

    // Read config
    Config cfg = create_config();
    CurveGraph graph = create_curve_graph();

    if(!read_config(&cfg, &graph)) {
        // Log error
    }
    
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