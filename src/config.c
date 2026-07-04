#include "config.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <log/log.h>

#ifdef _WIN32
    #define CONFIG_PATH "C:\\ProgramData\\macfanctld\\config.ini"
#elif __APPLE__
    #define CONFIG_PATH "/Library/Application Support/macfanctld/config"
#elif __linux__
    #define CONFIG_PATH "/etc/macfanctld/config"
#else
    #error "Unsupported OS"
#endif

Config create_config() {
    return (Config){
        .sensorKey = "TC0P",
        .minRPM = 2000,
        .maxRPM = 6200,
        .sleepTimeMiliseconds = 250,
        .rampDownTimeMiliseconds = 5000
    };
}

void get_config_path(char* buffer, size_t* size) {
    size_t len = strlen(CONFIG_PATH);

    if(size) {
        *size = len + 1;
    }

    if(buffer) {
        strncpy(buffer, CONFIG_PATH, len);
        buffer[len] = '\0';
    }
}

static void parse_config_line(const char* line, Config* cfg, CurveGraph* graph) {
    char key[32]; int val, val2, val3;
    if (sscanf(line, "Sensor=%4s", key) == 1) {
        strcpy(cfg->sensorKey, key);
    } else if (sscanf(line, "MinRPM=%d", &val) == 1) {
        cfg->minRPM = val > 2000 ? (uint16_t)val : 2000;
    } else if (sscanf(line, "MaxRPM=%d", &val) == 1) {
        cfg->maxRPM = (uint16_t)val;
    } else if (sscanf(line, "IntervalMs=%d", &val) == 1) {
        cfg->sleepTimeMiliseconds = (uint32_t)val;
    } else if (sscanf(line, "RampDownMs=%d", &val) == 1) {
        cfg->rampDownTimeMiliseconds = (uint32_t)val;
    } else if (sscanf(line, "%d=%d,%d", &val, &val2, &val3) == 3) {
        // Curve point: temp=rpm,rampupms
        CurvePoint point = { (uint16_t)val, (uint16_t)val2, (uint16_t)val3 };
        insert_curve_point(graph, point);
    }
}

bool read_config(Config* cfg, CurveGraph* graph) {
    size_t pathSize = 0;
    get_config_path(0, &pathSize);

    char* pathStr = malloc(pathSize);
    if (!pathStr) {
        logerr("Failed to allocate config path");
        return false;
    }

    get_config_path(pathStr, 0);
    
    FILE *file = fopen(pathStr, "r");
    free(pathStr);

    if(!file) {
        logerr("Failed to open config file: %s", strerror(errno));
        return false;
    }

    char line[1024];
    int lineNumber = 0;

    while (fgets(line, sizeof(line), file)) {
        lineNumber++;

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        }
        if (len > 0 && line[len - 1] == '\r') {
            // Remove '\r' (for Windows CRLF)
            line[--len] = '\0'; 
        }

        char* trimmed = line;
        while (isspace((unsigned char)*trimmed)) {
            trimmed++;
        }

        if (*trimmed == '\0' || *trimmed == '#') {
            continue;
        }

        parse_config_line(trimmed, cfg, graph);
    }

    if (ferror(file)) {
        perror("Error reading config file");
        finalize_curve_graph(graph);
        fclose(file);
        return false;
    }
    
    finalize_curve_graph(graph);
    fclose(file);
    return true;
}