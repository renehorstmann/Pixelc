#ifndef S_ASSUME_IMPL_H
#define S_ASSUME_IMPL_H
#ifdef S_IMPL

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>
#include "../assume.h"

#ifdef PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#endif

//
// options
//

#ifndef S_ASSUME_SIGNAL
#define S_ASSUME_SIGNAL SIGABRT
#endif

#ifndef S_ASSUME_MAX_FORMATED_MSG_SIZE
#define S_ASSUME_MAX_FORMATED_MSG_SIZE 4096
#endif


//
// functions
//


void s__s_assume_impl(const char *expression, const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *msg = malloc(S_ASSUME_MAX_FORMATED_MSG_SIZE);
    vsnprintf(msg, S_ASSUME_MAX_FORMATED_MSG_SIZE, format, args);
    va_end(args);
#ifdef NDEBUG
    fprintf(stderr, "An assumption in the program failed: %s\n", msg);
#else
    fprintf(stderr, "Assumption failed: %s at %s:%d %s\n", expression, file, line, msg);
#endif
    
    
#ifdef PLATFORM_EMSCRIPTEN
    // exit emscriptens main loop and call js error handler
    int script_size = 2*S_ASSUME_MAX_FORMATED_MSG_SIZE;
    char *script = malloc(script_size);
#ifdef NDEBUG
    snprintf(script, script_size, "set_assume(\'An assumption in the program failed: %s\');", msg);
#else
    snprintf(script, script_size, "set_assume(\'Assumption failed: %s at %s:%d %s\');", expression, file, line, msg);
#endif
    emscripten_cancel_main_loop();
    emscripten_run_script(script);
    free(script);
    exit(EXIT_FAILURE);
#endif

    free(msg);
    raise(S_ASSUME_SIGNAL);
}

#endif //S_IMPL
#endif //S_ASSUME_IMPL_H
