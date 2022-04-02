#ifndef RHC_LOG_H
#define RHC_LOG_H

#include <stdbool.h>

//
// Options:
//

#ifndef RHC_LOG_DEFAULT_FILE
#define RHC_LOG_DEFAULT_FILE stdout
#endif


// use the following definition to stop using colors (not in sdl...)
// #define RHC_LOG_DO_NOT_USE_COLOR

// use the following definition to stop printing time and file info
// #define RHC_LOG_DO_NOT_PRINT_TIME_FILE


enum rhc_log_level {
    RHC_LOG_TRACE, RHC_LOG_DEBUG, RHC_LOG_INFO, RHC_LOG_WARN, RHC_LOG_ERROR, RHC_LOG_WTF, RHC_LOG_NUM_LEVELS
};

#define log_trace(...) rhc_log_base_(RHC_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)

#define log_debug(...) rhc_log_base_(RHC_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

#define log_info(...)  rhc_log_base_(RHC_LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)

#define log_warn(...)  rhc_log_base_(RHC_LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)

#define log_error(...) rhc_log_base_(RHC_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

#define log_wtf(...)   rhc_log_base_(RHC_LOG_WTF, __FILE__, __LINE__, __VA_ARGS__)


void rhc_log_set_min_level(enum rhc_log_level level);

void rhc_log_set_quiet(bool set);

void rhc_log_base_(enum rhc_log_level level, const char *file, int line, const char *format, ...);

#endif //RHC_LOG
