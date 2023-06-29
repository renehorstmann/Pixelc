#ifndef M_IO_VECN_H
#define M_IO_VECN_H


#include <stdio.h>
#include <locale.h>

#include "../sca/float.h"
#include "terminalcolor.h"


/**
 * Example:
 * float v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * char buf[128];
 * vecN_snprint(buf, sizeof buf, v, 5);
 * // (float[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t vecN_snprint(char *str, size_t size, const float *v, int n) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(float[%i]) { ", n);
    for (int i = 0; i < n; i++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" SCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i < n - 1 ? ", " : "");
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }");
    return used;
}

/** Calls vecN_snprint and adds a newline */
static size_t vecN_snprintln(char *str, size_t size, const float *v, int n) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = vecN_snprint(str, size, v, n);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * float v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * vecN_fprint(stdout, v, 5);
 * // (float[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t vecN_fprint(FILE *stream, const float *v, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(float[%i]) ", n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for (int i = 0; i < n; i++) {
        used += fprintf(stream, "%" SCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i < n - 1 ? ", " : "");
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls vecN_fprint and adds a newline */
static size_t vecN_fprintln(FILE *stream, const float *v, int n) {
    size_t used = vecN_fprint(stream, v, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls vecN_fprint(stdout, v, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * float v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * vecN_print(v, 5);
 * // (float[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t vecN_print(const float *v, int n) {
    return vecN_fprint(stdout, v, n);
}

/** Calls vecN_print and adds a newline (Just calls vecN_fprintln(stdout, v, n)*/
static size_t vecN_println(const float *v, int n) {
    return vecN_fprintln(stdout, v, n);
}

#endif //M_IO_VECN_H
