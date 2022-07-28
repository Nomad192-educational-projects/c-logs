#include "logs.h"

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#define LEVEL_LOGS (warning)
#define CLEAR_FILE_LOG (false)
#define OPEN_FILE_EVERY_TIME (true)
#define W_TIME (true)

static void clear_log_file(const LOGS *logs)
{
    remove(logs->file_name);
}

static void safe_clear_log_file(const LOGS *logs)
{
    #ifdef CLEAR_FILE_LOG
        #if CLEAR_FILE_LOG
            remove(logs->file_name);
        #endif
    #endif /// if not specified, not clear
}

static char *my_copy(const char *str)
{
    size_t len = 0; //length filename
    while(str[len] != '\0') len++;
    size_t len_byte = sizeof(char) * (len+1); //length in byte filename
    char *copy = (char *)malloc(len_byte);
    if(!copy) return NULL;
    memcpy(copy, str, len_byte);
    return copy;
}

LOGS *quick_start(const char *file_name)
{
    {
        FILE *file = fopen(file_name, "a");
        if(!file) return NULL;

        #ifdef OPEN_FILE_EVERY_TIME
            #if OPEN_FILE_EVERY_TIME
                fclose(file);
            #endif
        #else
            fclose(file);   /// if not specified, open every time
        #endif
    }
    LOGS *logs = (LOGS *)malloc(sizeof (LOGS));
    if(!logs) return NULL;
    logs->file_name = my_copy(file_name);
    if(!logs->file_name) { free(logs); return NULL;}

    logs->level = LEVEL_LOGS;
    safe_clear_log_file(logs);
    logs->open_file_every_time = OPEN_FILE_EVERY_TIME;
    logs->w_time = W_TIME;
    return logs;
}

LOGS *full_start(const char *file_name, enum Level level, bool is_clear_log_file,  bool open_file_every_time)
{
    {
        FILE *file = fopen(file_name, "a");
        if(!file) return NULL;
        if(open_file_every_time) fclose(file);
    }
    LOGS *logs = (LOGS *)malloc(sizeof (LOGS));
    if(!logs) return NULL;
    logs->file_name = my_copy(file_name);
    if(!logs->file_name) { free(logs); return NULL;}
    logs->level = level;
    if(is_clear_log_file) clear_log_file(logs);
    return logs;
}

void lclose(LOGS *logs)
{
    if(!logs->open_file_every_time) fclose(logs->file);
    free(logs->file_name);
    free(logs);
}

bool flog(LOGS *logs, const enum Level level, const char *str_log, ...)
{
	if (logs->level >= level)
	{
        FILE *out_logs = logs->file;
		if(logs->open_file_every_time)
        {
            out_logs = fopen(logs->file_name, "a");
            if (!out_logs)
            {
                fprintf(stderr, "I can't create a file for logging errors");
                return false;
            }
        }

		if (logs->w_time)
		{
			time_t current_time;
			current_time = time(NULL);
			fprintf(out_logs, "%s", ctime(&current_time));
		}
		va_list args;
		va_start(args, str_log);
		vfprintf(out_logs, str_log, args);
		va_end(args);
		fclose(out_logs);
	}
	return true;
}

bool flog_l(LOGS *logs, const size_t line, const enum Level level, const char *str_log, ...)
{
    if (logs->level >= level)
    {
        FILE *out_logs = logs->file;
        if(logs->open_file_every_time)
        {
            out_logs = fopen(logs->file_name, "a");
            if (!out_logs)
            {
                fprintf(stderr, "I can't create a file for logging errors");
                return false;
            }
        }

        if (logs->w_time)
        {
            time_t current_time;
            current_time = time(NULL);
            fprintf(out_logs, "%s", ctime(&current_time));
        }
        va_list args;
        va_start(args, str_log);
        fprintf(out_logs, "in line - %zu\n", line);
        vfprintf(out_logs, str_log, args);
        va_end(args);
        fclose(out_logs);
    }
    return true;
}

bool flog_t(LOGS *logs, bool w_time, const enum Level level, const char *str_log, ...)
{
    if (logs->level >= level)
    {
        FILE *out_logs = logs->file;
        if(logs->open_file_every_time)
        {
            out_logs = fopen(logs->file_name, "a");
            if (!out_logs)
            {
                fprintf(stderr, "I can't create a file for logging errors");
                return false;
            }
        }

        if (w_time)
        {
            time_t current_time;
            current_time = time(NULL);
            fprintf(out_logs, "%s", ctime(&current_time));
        }
        va_list args;
        va_start(args, str_log);
        vfprintf(out_logs, str_log, args);
        va_end(args);
        fclose(out_logs);
    }
    return true;
}

bool flog_tl(LOGS *logs, bool w_time, const size_t line, const enum Level level, const char *str_log, ...)
{
    if (logs->level >= level)
    {
        FILE *out_logs = logs->file;
        if(logs->open_file_every_time)
        {
            out_logs = fopen(logs->file_name, "a");
            if (!out_logs)
            {
                fprintf(stderr, "I can't create a file for logging errors");
                return false;
            }
        }

        if (w_time)
        {
            time_t current_time;
            current_time = time(NULL);
            fprintf(out_logs, "%s", ctime(&current_time));
        }
        va_list args;
        va_start(args, str_log);
        fprintf(out_logs, "in line - %zu\n", line);
        vfprintf(out_logs, str_log, args);
        va_end(args);
        fclose(out_logs);
    }
    return true;
}

bool vflog(LOGS *logs, const size_t line, const enum Level level, const char *str_log, va_list args)
{
    if (logs->level >= level)
    {
        FILE *out_logs = logs->file;
        if(logs->open_file_every_time)
        {
            out_logs = fopen(logs->file_name, "a");
            if (!out_logs)
            {
                fprintf(stderr, "I can't create a file for logging errors");
                return false;
            }
        }
        if (logs->w_time)
        {
            time_t current_time;
            current_time = time(NULL);
            fprintf(out_logs, "%s ", ctime(&current_time));
        }
        fprintf(out_logs, "in line - %zu\n", line);
        vfprintf(out_logs, str_log, args);

        fclose(out_logs);
    }

    return true;
}

bool vflog_t(LOGS *logs, bool w_time, const size_t line, const enum Level level, const char *str_log, va_list args)
{
	if (logs->level >= level)
	{
        FILE *out_logs = logs->file;
        if(logs->open_file_every_time)
        {
            out_logs = fopen(logs->file_name, "a");
            if (!out_logs)
            {
                fprintf(stderr, "I can't create a file for logging errors");
                return false;
            }
        }
		if (w_time)
		{
			time_t current_time;
			current_time = time(NULL);
			fprintf(out_logs, "%s ", ctime(&current_time));
		}
		fprintf(out_logs, "in line - %zu\n", line);
		vfprintf(out_logs, str_log, args);

		fclose(out_logs);
	}

	return true;
}

int print_err(LOGS *logs, const enum Level level, const size_t line, const char *str_err, ...)
{
	int result;
	va_list args;
	va_start(args, str_err);
	vprintf(str_err, args);
	result = vflog_t(logs, true, line, level, str_err, args);
	va_end(args);
	return result;
}