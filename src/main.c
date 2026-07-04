#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <macfanctl/macfanctl.h>
#include <macfanctl/smc/smc.h>

#include "log/log.h"

#include "globals.h"
#include "signal.h"
#include "curve_point.h"
#include "config.h"
#include "interpolate.h"

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

    if(cfg.minRPM < 2000) {
        cfg.minRPM = 2000;
    }

    loginfo("macfanctld started!");
    
    // Initialize libmacfanctl

    // Main loop
    uint16_t currentSpeed = cfg.minRPM;
    uint64_t rampStartMs = 0;
    uint16_t targetSpeed = currentSpeed;
    uint64_t totalRampMs = cfg.rampDownTimeMiliseconds;

    struct timeval timeValue;

    gRunning = 1;
    while(gRunning) {
        // Query sensors
        sp78_t temperature = 0;
        bool smcReadSuccess = smc_read_sp78(cfg.sensorKey, &temperature);

        // fail-safe
        if(!smcReadSuccess || temperature >= float_to_sp78(90)) {
            smc_write_u16("F0Mx", 0xFFFF);
            smc_write_u16("F0Mn", 0xFFFF);
            usleep(cfg.sleepTimeMiliseconds * 1000);
            continue;
        }

        float tempC = sp78_to_float(temperature);

        size_t lowPointIdx = get_floor_curve_point_from_graph(&graph, (uint16_t)tempC);
        
        CurvePoint* lowPoint = &graph.pCurvePoints[lowPointIdx];
        CurvePoint* highPoint = (lowPointIdx + 1 < graph.uCurvePoints) ? &graph.pCurvePoints[lowPointIdx + 1] : lowPoint;

        // Calculate normalized point between low & high points of the graph
        float lowTemperature = (float)lowPoint->temperature;
        float highTemperature = (float)highPoint->temperature;

        float normalizedFactorBetweenPoints = (tempC - lowTemperature) / (highTemperature - lowTemperature);
        if (normalizedFactorBetweenPoints < 0.0f) normalizedFactorBetweenPoints = 0.0f;
        
        // Calculate target
        uint16_t newTargetSpeed = (highPoint->roundPerMinute - lowPoint->roundPerMinute) * normalizedFactorBetweenPoints + lowPoint->roundPerMinute;

        gettimeofday(&timeValue, NULL);
        uint64_t nowMs = (uint64_t)(timeValue.tv_sec) * 1000 + (uint64_t)(timeValue.tv_usec) / 1000;
        if (newTargetSpeed != targetSpeed) {
            targetSpeed = newTargetSpeed;
            rampStartMs = nowMs;
            if (targetSpeed > currentSpeed) {
                totalRampMs = highPoint->interpolationTimeMiliseconds;
            } else {
                totalRampMs = cfg.rampDownTimeMiliseconds;
            }
        }

        // Interpolate for this tick
        uint64_t elapsedMs = nowMs - rampStartMs;
        float dT = (float)elapsedMs / (float)totalRampMs;
        if(dT < 0.f) dT = 0.f;
        uint16_t newSpeed = interpolate_uint16(currentSpeed, targetSpeed, dT);

        // Set fan speed
        smc_write_u16("F0Mx", newSpeed);
        smc_write_u16("F0Mn", newSpeed);

        // Wait
        usleep(cfg.sleepTimeMiliseconds * 1000);
    }

    logger_shutdown();

    return 0;
}