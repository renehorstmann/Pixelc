#ifndef M_IO_BVECN_H
#define M_IO_BVECN_H


#include <stdbool.h>

#include <stdio.h>
#include <locale.h>

#include "../sca/bool.h"
#include "terminalcolor.h"



/**
 * Example:
 * bool v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * char buf[128];
 * bvecN_snprint(buf, sizeof buf, v, 5);
 * // (bool[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t bvecN_snprint(char *str, size_t size, const bool *v, int n) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(bool[%i]) { ", n);
    for(int i=0; i<n; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" BSCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i<n-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }");
    return used;
}

/** Calls bvecN_snprint and adds a newline */
static size_t bvecN_snprintln(char *str, size_t size, const bool *v, int n) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = bvecN_snprint(str, size, v, n);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * bool v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * bvecN_fprint(stdout, v, 5);
 * // (bool[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t bvecN_fprint(FILE *stream, const bool *v, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(bool[%i]) ", n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for(int i=0; i<n; i++) {
        used += fprintf(stream,"%" BSCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i<n-1? ", " : "");
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls bvecN_fprint and adds a newline */
static size_t bvecN_fprintln(FILE *stream, const bool *v, int n) {
    size_t used = bvecN_fprint(stream, v, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls bvecN_fprint(stdout, v, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * bool v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * bvecN_print(v, 5);
 * // (bool[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t bvecN_print(const bool *v, int n) {
    return bvecN_fprint(stdout, v, n);
}

/** Calls bvecN_print and adds a newline (Just calls bvecN_fprintln(stdout, v, n)*/
static size_t bvecN_println(const bool *v, int n) {
    return bvecN_fprintln(stdout, v, n);
}

#endif //M_IO_BVECN_H
