#ifndef S_ASSUME_IMPL_H
#define S_ASSUME_IMPL_H
#ifdef S_IMPL

#include <stdio.h>
#include <stdarg.h>
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
    char msg[S_ASSUME_MAX_FORMATED_MSG_SIZE];
    vsnprintf(msg, S_ASSUME_MAX_FORMATED_MSG_SIZE, format, args);
    va_end(args);
#ifdef NDEBUG
    fprintf(stderr, "An assumption in the program failed: %s\n", msg);
#else
    fprintf(stderr, "Assumption failed: %s at %s:%d %s\n", expression, file, line, msg);
#endif
    raise(S_ASSUME_SIGNAL);

#ifdef PLATFORM_EMSCRIPTEN
    // exit emscriptens main loop and call js error handler
    emscripten_cancel_main_loop();
    EM_ASM(
            set_exit_failure_error_msg();
            );
    // emscripten does not handle signals
    exit(EXIT_FAILURE);
#endif

}

#endif //S_IMPL
#endif //S_ASSUME_IMPL_H
