#ifndef _LOG_H
#define _LOG_H

#include <stdbool.h>

void logger_init(bool foreground);
void logger_shutdown();

void loginfo(const char *format, ...);
void logwarn(const char *format, ...);
void logerr(const char *format, ...);

#endif