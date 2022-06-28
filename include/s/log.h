#ifndef S_LOG_H
#define S_LOG_H

//
// logging
//

#include "common.h"

//
// Options:
//

#ifndef S_LOG_DEFAULT_FILE
#define S_LOG_DEFAULT_FILE stdout
#endif


// use the following definition to stop using colors (not in sdl...)
// #define S_LOG_DO_NOT_USE_COLOR

// use the following definition to stop printing time and file info
// #define S_LOG_DO_NOT_PRINT_TIME_FILE


enum s_log_level {
    S_LOG_TRACE, S_LOG_DEBUG, S_LOG_INFO, S_LOG_WARN, S_LOG_ERROR, S_LOG_WTF, S_LOG_NUM_LEVELS
};

#define s_log_trace(...) s_log_base(S_LOG_TRACE, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define s_log_debug(...) s_log_base(S_LOG_DEBUG, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define s_log_info(...)  s_log_base(S_LOG_INFO, __FILE__, __LINE__, __func__, __VA_ARGS__)

// same as s_log_info
#define s_log(...)  s_log_base(S_LOG_INFO, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define s_log_warn(...)  s_log_base(S_LOG_WARN, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define s_log_error(...) s_log_base(S_LOG_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define s_log_wtf(...)   s_log_base(S_LOG_WTF, __FILE__, __LINE__, __func__, __VA_ARGS__)


void s_log_set_min_level(enum s_log_level level);

void s_log_set_quiet(bool set);

/**
 * Logging function.
 * If opt_file is NULL, file and line will be omitted. (Useful for helper functions (like s_assume))
 * If opt_func is not NULL, the function name will be printed before format
 */
void s_log_base(enum s_log_level level, const char *opt_file, int line,
                  const char *opt_func, const char *format, ...);

#endif //S_LOG
