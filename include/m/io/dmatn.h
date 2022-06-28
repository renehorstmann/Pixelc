#ifndef M_IO_DMATN_H
#define M_IO_DMATN_H


#include <stdio.h>
#include <locale.h>

#include "../sca/double.h"
#include "terminalcolor.h"


/**
 * Prints the matrix in a single line
 * Example:
 * double m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * char buf[128];
 * dmatN_snprint_line(buf, sizeof buf, m, 2);
 * // (double[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t dmatN_snprint_line(char *str, size_t size, const double *m, int n) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(double[%i*%i]) { ", n, n);
    for (int c = 0; c < n; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < n; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }");
    return used;
}

/** Calls dmatN_snprint_line and adds a newline */
static size_t dmatN_snprintln_line(char *str, size_t size, const double *m, int n) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dmatN_snprint_line(str, size, m, n);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * double m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * char buf[128];
 * dmatN_snprint(buf, sizeof buf, m, 2);
 * // (double[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t dmatN_snprint(char *str, size_t size, const double *m, int n) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(double[%i*%i]) { ", n, n);
    for (int c = 0; c < n; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < n; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" DSCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }");
    return used;
}

/** Calls dmatN_snprint and adds a newline */
static size_t dmatN_snprintln(char *str, size_t size, const double *m, int n) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dmatN_snprint(str, size, m, n);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * double m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * dmatN_fprint_line(stdout, m, 2);
 * // (double[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t dmatN_fprint_line(FILE *stream, const double *m, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(double[%i*%i]) ", n, n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for (int c = 0; c < n; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < n; r++) {
            used += fprintf(stream, "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dmatN_fprint_line and adds a newline */
static size_t dmatN_fprintln_line(FILE *stream, const double *m, int n) {
    size_t used = dmatN_fprint_line(stream, m, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * double m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * dmatN_fprint(stdout, m, 2);
 * // (double[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t dmatN_fprint(FILE *stream, const double *m, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(double[%i*%i]) ", n, n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for (int c = 0; c < n; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < n; r++) {
            used += fprintf(stream, "%12" DSCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dmatN_fprint and adds a newline */
static size_t dmatN_fprintln(FILE *stream, const double *m, int n) {
    size_t used = dmatN_fprint(stream, m, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls dmatN_fprint_line(stdout, m, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * double m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * dmatN_print_line(v, 2);
 * // (double[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t dmatN_print_line(const double *m, int n) {
    return dmatN_fprint_line(stdout, m, n);
}

/** Calls dmatN_fprint_line and adds a newline (Just calls dmatN_fprintln_line(stdout, m, n)*/
static size_t dmatN_println_line(const double *m, int n) {
    return dmatN_fprintln_line(stdout, m, n);
}

/**
 * Calls dmatN_fprint(stdout, m, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * double m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * dmatN_print(v, 2);
 * // (double[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t dmatN_print(const double *m, int n) {
    return dmatN_fprint(stdout, m, n);
}

/** Calls dmatN_fprint and adds a newline (Just calls dmatN_fprintln(stdout, m, n)*/
static size_t dmatN_println(const double *m, int n) {
    return dmatN_fprintln(stdout, m, n);
}

#endif //M_IO_DMATN_H
