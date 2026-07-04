#include <log/log.h>

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

FILE* gLogFile = NULL;
bool gForeground = false;

void logger_init(bool foreground) {
    gForeground = foreground;

    gLogFile = fopen("/var/log/macfanctld/service.log", "a");
}

void logger_shutdown() {
    if(gLogFile) {
        fclose(gLogFile);
    }
}

static void _log_write(const char *level, const char *format, va_list args) {
    char formatted_msg[1024];

    int writtenBytes = vsnprintf(formatted_msg, sizeof(formatted_msg), format, args);

    if ((size_t)writtenBytes >= sizeof(formatted_msg)) {
        formatted_msg[sizeof(formatted_msg) - 1] = '\0';
    }

    if (gForeground && isatty(STDOUT_FILENO)) {
        fprintf(stdout, "[%s] %s\n", level, formatted_msg);
        fflush(stdout);
    }

    if (gLogFile) {
        fprintf(gLogFile, "[%s] %s\n", level, formatted_msg);
    }
}

void loginfo(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _log_write("INFO", format, args);
    va_end(args);
}

void logwarn(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _log_write("WARN", format, args);
    va_end(args);
}

void logerr(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _log_write("ERROR", format, args);
    va_end(args);
}