#ifndef UTILC_ASSUME_H
#define UTILC_ASSUME_H

#include <stdio.h>
#include <stdarg.h>
#include <signal.h>

#ifndef ASSUME_SIGNAL
#define ASSUME_SIGNAL SIGABRT
#endif

#ifndef ASSUME_MAX_FORMATED_MSG_SIZE
#define ASSUME_MAX_FORMATED_MSG_SIZE 4096
#endif

/**
 * assert like function, that also uses formatting print to stderr.
 * Calls raise(SIG_ABRT).
 * If NDEBUG is defined, only msg will get displayed (without expression, file and line infos)
 */
#define assume(EX, ...) \
(void)((EX) || (assume_function_impl__ (#EX, __FILE__, __LINE__, __VA_ARGS__),0))

static void assume_function_impl__(const char *expression, const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char msg[ASSUME_MAX_FORMATED_MSG_SIZE];
    vsnprintf(msg, ASSUME_MAX_FORMATED_MSG_SIZE, format, args);
    va_end(args);
#ifdef NDEBUG
    fprintf(stderr, "An assumption in the program failed: %s\n", msg);
#else
    fprintf(stderr, "Assumption failed: %s at %s:%d %s\n", expression, file, line, msg);
#endif
    raise(ASSUME_SIGNAL);
}


#endif //UTILC_ASSUME_H
