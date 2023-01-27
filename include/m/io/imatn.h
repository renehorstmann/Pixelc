#ifndef M_IO_IMATN_H
#define M_IO_IMATN_H



#include <stdio.h>
#include <locale.h>

#include "../sca/int.h"
#include "terminalcolor.h"


/**
 * Prints the matrix in a single line
 * Example:
 * int m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * char buf[128];
 * imatN_snprint_line(buf, sizeof buf, m, 2);
 * // (int[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t imatN_snprint_line(char *str, size_t size, const int *m, int n) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(int[%i*%i]) { ", n, n);
    for (int c = 0; c < n; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < n; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }");
    return used;
}

/** Calls imatN_snprint_line and adds a newline */
static size_t imatN_snprintln_line(char *str, size_t size, const int *m, int n) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = imatN_snprint_line(str, size, m, n);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * int m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * char buf[128];
 * imatN_snprint(buf, sizeof buf, m, 2);
 * // (int[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t imatN_snprint(char *str, size_t size, const int *m, int n) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(int[%i*%i]) { ", n, n);
    for (int c = 0; c < n; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < n; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" ISCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }");
    return used;
}

/** Calls imatN_snprint and adds a newline */
static size_t imatN_snprintln(char *str, size_t size, const int *m, int n) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = imatN_snprint(str, size, m, n);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * int m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * imatN_fprint_line(stdout, m, 2);
 * // (int[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t imatN_fprint_line(FILE *stream, const int *m, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(int[%i*%i]) ", n, n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for (int c = 0; c < n; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < n; r++) {
            used += fprintf(stream, "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls imatN_fprint_line and adds a newline */
static size_t imatN_fprintln_line(FILE *stream, const int *m, int n) {
    size_t used = imatN_fprint_line(stream, m, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * int m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * imatN_fprint(stdout, m, 2);
 * // (int[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t imatN_fprint(FILE *stream, const int *m, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(int[%i*%i]) ", n, n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for (int c = 0; c < n; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < n; r++) {
            used += fprintf(stream, "%12" ISCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls imatN_fprint and adds a newline */
static size_t imatN_fprintln(FILE *stream, const int *m, int n) {
    size_t used = imatN_fprint(stream, m, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls imatN_fprint_line(stdout, m, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * int m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * imatN_print_line(v, 2);
 * // (int[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t imatN_print_line(const int *m, int n) {
    return imatN_fprint_line(stdout, m, n);
}

/** Calls imatN_fprint_line and adds a newline (Just calls imatN_fprintln_line(stdout, m, n)*/
static size_t imatN_println_line(const int *m, int n) {
    return imatN_fprintln_line(stdout, m, n);
}

/**
 * Calls imatN_fprint(stdout, m, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * int m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * imatN_print(v, 2);
 * // (int[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t imatN_print(const int *m, int n) {
    return imatN_fprint(stdout, m, n);
}

/** Calls imatN_fprint and adds a newline (Just calls imatN_fprintln(stdout, m, n)*/
static size_t imatN_println(const int *m, int n) {
    return imatN_fprintln(stdout, m, n);
}

#endif //M_IO_IMATN_H
