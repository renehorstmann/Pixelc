#ifndef S_LOG_IMPL_H
#define S_LOG_IMPL_H
#ifdef S_IMPL

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../memory.h"
#include "../terminalcolor.h"
#include "../log.h"

#ifdef OPTION_SDL
#include <SDL2/SDL.h>
#endif

#define S_LOG_MAX_LENGTH 4096     // Should be the same as SDL's log max


#ifdef S_LOG_DO_NOT_USE_COLOR
#define S_LOG_COLORED false
#else
#define S_LOG_COLORED true
#endif


#if !defined(S_LOG_DO_NOT_USE_MULTILINE) && defined(PLATFORM_MSVC)
#define S_LOG_OPT_NEWLINE "\n   ->    "
#else
#define S_LOG_OPT_NEWLINE ""
#endif

static struct {
    enum s_log_level level;
    bool quiet;
} s_log_L;


static const char *s_log_src_level_colors_[] = {
        S_TERMINALCOLOR_HIGHINTENSITY_BLUE,
        S_TERMINALCOLOR_CYAN,
        S_TERMINALCOLOR_GREEN,
        S_TERMINALCOLOR_YELLOW,
        S_TERMINALCOLOR_RED,
        S_TERMINALCOLOR_MAGENTA
};

static const char *s_log_src_level_names_[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "WTF"
};

static int s_log_to_str_v(char *str, ssize n,
                            enum s_log_level level, const char *opt_file, int line, const char *opt_func,
                            bool colored,
                            const char *time_str,
                            const char *format, va_list vl) {
    assert(str);

    ssize size = 0;
    if (opt_file && *opt_file != '\0') {
        if (colored) {
            size = snprintf(str, n,
                            "%s %s%-5s "
                            S_TERMINALCOLOR_RESET S_TERMINALCOLOR_HIGHINTENSITY_BLACK
                            "%s:%d"
                            S_TERMINALCOLOR_RESET
                            S_LOG_OPT_NEWLINE
                            S_TERMINALCOLOR_HIGHINTENSITY_BLACK
                            "[%s] "
                            S_TERMINALCOLOR_RESET,
                            time_str, s_log_src_level_colors_[level], s_log_src_level_names_[level], opt_file, line,
                            opt_func);
        } else {
            size = snprintf(str, n,
                            "%s %-5s %s:%d"
                            S_LOG_OPT_NEWLINE
                            "[%s] ",
                            time_str, s_log_src_level_names_[level], opt_file, line, opt_func);
        }
    } else {
        if (colored) {
            size = snprintf(str, n,
                            "%s %s%-5s"
                            S_TERMINALCOLOR_RESET
                            S_LOG_OPT_NEWLINE
                            S_TERMINALCOLOR_HIGHINTENSITY_BLACK
                            "[%s] "
                            S_TERMINALCOLOR_RESET,
                            time_str, s_log_src_level_colors_[level], s_log_src_level_names_[level], opt_func);
        } else {
            size = snprintf(str, n,
                            "%s %-5s"
                            S_LOG_OPT_NEWLINE
                            "[%s] ",
                            time_str, s_log_src_level_names_[level], opt_func);
        }
    }

    ssize format_size = vsnprintf(str + size, n - size, format, vl);
    if (size + format_size > n)
        return snprintf(str + size, n - size, "LOG_ERROR:MSG_SIZE_TOO_LONG");
    size += format_size;
    size += snprintf(str + size, n - size, "\n");
    return (int) size;
}


//
// public
//

void s_log_set_min_level(enum s_log_level level) {
    s_log_L.level = level;
}

void s_log_set_quiet(bool set) {
    s_log_L.quiet = set;
}


void s_log_base(enum s_log_level level, const char *opt_file, int line,
                  const char *opt_func, const char *format, ...) {
    if (level < s_log_L.level || s_log_L.quiet) {
        return;
    }

    if (!opt_func)
        opt_func = "";

#ifdef S_LOG_DO_NOT_PRINT_TIME_FILE
    char *time_str = "";
    opt_file = NULL;
#else
    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    char time_str[16];
    ssize time_size = strftime(time_str, sizeof time_str, "%H:%M:%S", lt);
    time_str[time_size] = '\0';
#endif

    va_list args;
            va_start(args, format);
    char msg[S_LOG_MAX_LENGTH];
    s_log_to_str_v(msg, sizeof msg,
                     level, opt_file, line, opt_func, S_LOG_COLORED, time_str,
                     format, args);

#ifdef OPTION_SDL
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%s", msg);
#else //!OPTION_SDL
    s_terminalcolor_start();
    fprintf(S_LOG_DEFAULT_FILE, "%s", msg);
    fflush(S_LOG_DEFAULT_FILE);
    s_terminalcolor_stop();
#endif //OPTION_SDL
}


#endif //S_IMPL
#endif //S_LOG_IMPL_H
