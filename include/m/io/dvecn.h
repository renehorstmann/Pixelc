#ifndef M_IO_DVECN_H
#define M_IO_DVECN_H



#include <stdio.h>
#include <locale.h>

#include "../sca/double.h"
#include "terminalcolor.h"



/**
 * Example:
 * double v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * char buf[128];
 * dvecN_snprint(buf, sizeof buf, v, 5);
 * // (double[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t dvecN_snprint(char *str, size_t size, const double *v, int n) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(double[%i]) { ", n);
    for(int i=0; i<n; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i<n-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }");
    return used;
}

/** Calls dvecN_snprint and adds a newline */
static size_t dvecN_snprintln(char *str, size_t size, const double *v, int n) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dvecN_snprint(str, size, v, n);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * double v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * dvecN_fprint(stdout, v, 5);
 * // (double[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t dvecN_fprint(FILE *stream, const double *v, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(double[%i]) ", n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for(int i=0; i<n; i++) {
        used += fprintf(stream,"%" DSCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i<n-1? ", " : "");
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dvecN_fprint and adds a newline */
static size_t dvecN_fprintln(FILE *stream, const double *v, int n) {
    size_t used = dvecN_fprint(stream, v, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls dvecN_fprint(stdout, v, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * double v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * dvecN_print(v, 5);
 * // (double[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t dvecN_print(const double *v, int n) {
    return dvecN_fprint(stdout, v, n);
}

/** Calls dvecN_print and adds a newline (Just calls dvecN_fprintln(stdout, v, n)*/
static size_t dvecN_println(const double *v, int n) {
    return dvecN_fprintln(stdout, v, n);
}

#endif //M_IO_DVECN_H
