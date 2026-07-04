#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <smc.h>

#include "log/log.h"

#include "signal.h"
#include "curve_point.h"
#include "config.h"

int main(int argc, char* argv[]) {
    bool foreground = (argc > 1 && strcmp(argv[1], "-f") == 0);

    logger_init(true);
    
    setup_sig_handlers();
    
    // Read config
    Config cfg = create_config();
    CurveGraph graph = create_curve_graph();

    if(!read_config(&cfg, &graph)) {
        logerr("Failed to read config, using default settings.");
    }

    loginfo("macfanctld started!");
    
    // Find SMC

    uint16_t currentSpeed = cfg.minRPM;

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

    logger_shutdown();

    return 0;
}