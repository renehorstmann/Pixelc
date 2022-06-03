#ifndef RHC_LOG_IMPL_H
#define RHC_LOG_IMPL_H
#ifdef RHC_IMPL

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../alloc.h"
#include "../terminalcolor.h"
#include "../log.h"

#ifdef OPTION_SDL
#include "SDL2/SDL.h"
#endif

#define RHC_LOG_MAX_LENGTH 4096     // Should be the same as SDL's log max


#ifdef RHC_LOG_DO_NOT_USE_COLOR
#define RHC_LOG_COLORED false
#else
#define RHC_LOG_COLORED true
#endif

static struct {
    enum rhc_log_level level;
    bool quiet;
} rhc_log_L;


static const char *rhc_log_src_level_colors_[] = {
        RHC_TERMINALCOLOR_HIGHINTENSITY_BLUE,
        RHC_TERMINALCOLOR_CYAN,
        RHC_TERMINALCOLOR_GREEN,
        RHC_TERMINALCOLOR_YELLOW,
        RHC_TERMINALCOLOR_RED,
        RHC_TERMINALCOLOR_MAGENTA
};

static const char *rhc_log_src_level_names_[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "WTF"
};

static int rhc_log_to_str_v(char *str, size_t n,
                            enum rhc_log_level level, const char *opt_file, int line, const char *opt_func,
                            bool colored,
                            const char *time_str,
                            const char *format, va_list vl) {
    if (!str)
        n = 0;

    size_t size = 0;
    if (opt_file && *opt_file != '\0') {
        if (colored) {
            size = snprintf(str, n,
                            "%s %s%-5s "
                            RHC_TERMINALCOLOR_RESET RHC_TERMINALCOLOR_HIGHINTENSITY_BLACK
                            "%s:%d"
                            RHC_TERMINALCOLOR_RESET
                            " [%s] ",
                            time_str, rhc_log_src_level_colors_[level], rhc_log_src_level_names_[level], opt_file, line,
                            opt_func);
        } else {
            size = snprintf(str, n,
                            "%s %-5s %s:%d [%s] ",
                            time_str, rhc_log_src_level_names_[level], opt_file, line, opt_func);
        }
    } else {
        if (colored) {
            size = snprintf(str, n,
                            "%s %s%-5s"
                            RHC_TERMINALCOLOR_RESET
                            " [%s] ",
                            time_str, rhc_log_src_level_colors_[level], rhc_log_src_level_names_[level], opt_func);
        } else {
            size = snprintf(str, n,
                            "%s %-5s [%s] ",
                            time_str, rhc_log_src_level_names_[level], opt_func);
        }
    }

    size += vsnprintf(str ? str + size : NULL, str ? n - size : 0, format, vl);
    size += snprintf(str ? str + size : NULL, str ? n - size : 0, "\n");
    return (int) size;
}


//
// public
//

void rhc_log_set_min_level(enum rhc_log_level level) {
    rhc_log_L.level = level;
}

void rhc_log_set_quiet(bool set) {
    rhc_log_L.quiet = set;
}


void rhc_log_base(enum rhc_log_level level, const char *opt_file, int line,
                  const char *opt_func, const char *format, ...) {
    if (level < rhc_log_L.level || rhc_log_L.quiet) {
        return;
    }

    if (!opt_func)
        opt_func = "";

#ifdef RHC_LOG_DO_NOT_PRINT_TIME_FILE
    char *time_str = "";
    opt_file = NULL;
#else
    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    char time_str[16];
    size_t time_size = strftime(time_str, sizeof time_str, "%H:%M:%S", lt);
    time_str[time_size] = '\0';
#endif

    va_list args;
    va_start(args, format);
    char msg[RHC_LOG_MAX_LENGTH];
    rhc_log_to_str_v(msg, sizeof msg,
                     level, opt_file, line, opt_func, RHC_LOG_COLORED, time_str,
                     format, args);

#ifdef OPTION_SDL
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%s", msg);
#else //!OPTION_SDL
    rhc_terminalcolor_start();
    fprintf(RHC_LOG_DEFAULT_FILE, "%s", msg);
    fflush(RHC_LOG_DEFAULT_FILE);
    rhc_terminalcolor_stop();
#endif //OPTION_SDL
}


#endif //RHC_IMPL
#endif //RHC_LOG_IMPL_H
