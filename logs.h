#ifndef LOGS_H
#define LOGS_H

#include <stdio.h>
#include <stdbool.h>

typedef struct logs_t
{
    char *file_name;
    enum Level
    {
        off,
        critical_error,
        error,
        warning,
        info,
        verbose
    } Level;
    enum Level level;
    _Bool open_file_every_time;
    FILE *file;
    _Bool w_time;
} LOGS;

LOGS *quick_start(const char *file_name);
LOGS *full_start(const char *file_name, enum Level level, bool w_time, bool is_clear_log_file,  bool open_file_every_time);

void lclose(LOGS *);

bool flog(LOGS *logs, enum Level level, const char *str_log, ...);
bool flog_l(LOGS *logs, size_t line, enum Level level, const char *str_log, ...);
bool flog_t(LOGS *logs, bool w_time, enum Level level, const char *str_log, ...);
bool flog_tl(LOGS *logs, bool w_time, size_t line, enum Level level, const char *str_log, ...);

bool vflog(LOGS *logs, size_t line, enum Level level, const char *str_log, va_list args);
bool vflog_t(LOGS *logs, bool w_time, size_t line, enum Level level, const char *str_log, va_list args);

int print_err(LOGS *logs, enum Level level, size_t line, const char *str_err, ...);

#endif /// LOGS_H