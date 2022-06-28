#ifndef S_ASSUME_H
#define S_ASSUME_H

// assert like function, that also uses formatting print to stderr.
// Calls raise(SIG_ABRT).
// If NDEBUG is defined, only msg will get displayed (without expression, file and line infos)
#define s_assume(EX, ...) \
(void)((EX) || (s__s_assume_impl (#EX, __FILE__, __LINE__, __VA_ARGS__),0))

void s__s_assume_impl(const char *expression, const char *file, int line, const char *format, ...);

#endif //S_ASSUME_H
