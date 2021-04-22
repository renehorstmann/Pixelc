#ifndef RHC_LOG_IMPL_H
#define RHC_LOG_IMPL_H
#ifdef RHC_IMPL

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../allocator.h"
#include "../log.h"

#define RHC_LOG_SDL_MAX_LENGTH 4096

static struct {
    enum rhc_log_level level;
    bool quiet;
} rhc_log_L;


#ifdef OPTION_SDL
static SDL_LogPriority rhc_log_sdl_priority(enum rhc_log_level level) {
    switch(level) {
        case RHC_LOG_TRACE:
            return SDL_LOG_PRIORITY_VERBOSE;
        case RHC_LOG_DEBUG:
            return SDL_LOG_PRIORITY_DEBUG;
        case RHC_LOG_INFO:
            return SDL_LOG_PRIORITY_INFO;
        case RHC_LOG_WARN:
            return SDL_LOG_PRIORITY_WARN;
        case RHC_LOG_ERROR:
            return SDL_LOG_PRIORITY_ERROR;
        case RHC_LOG_WTF:
        default:
            return SDL_LOG_PRIORITY_CRITICAL;
    }
}
#endif

#ifndef RHC_LOG_DO_NOT_USE_COLOR
static const char *rhc_log_src_level_colors_[] = {
        "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif

static const char *rhc_log_src_level_names_[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "WTF"
};

void rhc_log_set_min_level(enum rhc_log_level level) {
#ifdef OPTION_SDL
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, rhc_log_sdl_priority(level));
#endif
    rhc_log_L.level = level;
}

void rhc_log_set_quiet(bool set) {
    rhc_log_L.quiet = set;
}

#ifdef OPTION_SDL
void rhc_log_base_(enum rhc_log_level level, const char *file, int line, const char *format, ...) {
    if (level < rhc_log_L.level || rhc_log_L.quiet) {
        return;
    }

    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);


    va_list args;
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';

    char msg_format[RHC_LOG_SDL_MAX_LENGTH];
    snprintf(msg_format, RHC_LOG_SDL_MAX_LENGTH, "%s %s:%d: %s", buf, file, line, format);
    va_start(args, format);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, rhc_log_sdl_priority(level), msg_format, args);
    va_end(args);
}

#else

void rhc_log_base_(enum rhc_log_level level, const char *file, int line, const char *format, ...) {
    if (level < rhc_log_L.level || rhc_log_L.quiet) {
        return;
    }

    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    /* Log to RHC_DEFAULT_FILE (stdout) */
    va_list args;
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';


#ifdef RHC_LOG_DO_NOT_USE_COLOR
    fprintf(RHC_LOG_DEFAULT_FILE, "%s %-5s %s:%d: ",
            buf, rhc_log_src_level_names_[level], file, line);
#else
    fprintf(RHC_LOG_DEFAULT_FILE, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
            buf, rhc_log_src_level_colors_[level], rhc_log_src_level_names_[level], file, line);
#endif
    va_start(args, format);
    vfprintf(RHC_LOG_DEFAULT_FILE, format, args);
    va_end(args);
    fprintf(RHC_LOG_DEFAULT_FILE, "\n");
    fflush(RHC_LOG_DEFAULT_FILE);
}
#endif

#endif //RHC_IMPL
#endif //RHC_LOG_IMPL_H
