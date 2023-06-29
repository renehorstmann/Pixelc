#ifndef M_IO_UCMATN_H
#define M_IO_UCMATN_H


#include <stdio.h>
#include <locale.h>

#include "../sca/uchar.h"
#include "terminalcolor.h"


/**
 * Prints the matrix in a single line
 * Example:
 * unsigned char m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * char buf[128];
 * ucmatN_snprint_line(buf, sizeof buf, m, 2);
 * // (unsigned char[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t ucmatN_snprint_line(char *str, size_t size, const unsigned char *m, int n) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(unsigned char[%i*%i]) { ", n, n);
    for (int c = 0; c < n; c++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < n; r++) {
            if (used >= size) {
                str = NULL;
            }
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }");
    return used;
}

/** Calls ucmatN_snprint_line and adds a newline */
static size_t ucmatN_snprintln_line(char *str, size_t size, const unsigned char *m, int n) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucmatN_snprint_line(str, size, m, n);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * unsigned char m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * char buf[128];
 * ucmatN_snprint(buf, sizeof buf, m, 2);
 * // (unsigned char[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t ucmatN_snprint(char *str, size_t size, const unsigned char *m, int n) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(unsigned char[%i*%i]) { ", n, n);
    for (int c = 0; c < n; c++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < n; r++) {
            if (used >= size) {
                str = NULL;
            }
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }");
    return used;
}

/** Calls ucmatN_snprint and adds a newline */
static size_t ucmatN_snprintln(char *str, size_t size, const unsigned char *m, int n) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucmatN_snprint(str, size, m, n);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * unsigned char m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * ucmatN_fprint_line(stdout, m, 2);
 * // (unsigned char[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t ucmatN_fprint_line(FILE *stream, const unsigned char *m, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(unsigned char[%i*%i]) ", n, n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for (int c = 0; c < n; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < n; r++) {
            used += fprintf(stream, "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucmatN_fprint_line and adds a newline */
static size_t ucmatN_fprintln_line(FILE *stream, const unsigned char *m, int n) {
    size_t used = ucmatN_fprint_line(stream, m, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * unsigned char m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * ucmatN_fprint(stdout, m, 2);
 * // (unsigned char[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t ucmatN_fprint(FILE *stream, const unsigned char *m, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(unsigned char[%i*%i]) ", n, n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for (int c = 0; c < n; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < n; r++) {
            used += fprintf(stream, "%12" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m[r + c * n], r < n - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucmatN_fprint and adds a newline */
static size_t ucmatN_fprintln(FILE *stream, const unsigned char *m, int n) {
    size_t used = ucmatN_fprint(stream, m, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ucmatN_fprint_line(stdout, m, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * unsigned char m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * ucmatN_print_line(v, 2);
 * // (unsigned char[2*2]) { 1.1, 2.2,   3.3, 4.4 }
 */
static size_t ucmatN_print_line(const unsigned char *m, int n) {
    return ucmatN_fprint_line(stdout, m, n);
}

/** Calls ucmatN_fprint_line and adds a newline (Just calls ucmatN_fprintln_line(stdout, m, n)*/
static size_t ucmatN_println_line(const unsigned char *m, int n) {
    return ucmatN_fprintln_line(stdout, m, n);
}

/**
 * Calls ucmatN_fprint(stdout, m, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * unsigned char m[2*2] = {1.1, 2.2, 3.3, 4.4};
 * ucmatN_print(v, 2);
 * // (unsigned char[2*2]) {
 * //        1.1,          2.2,
 * //        3.3,          4.4 }
 */
static size_t ucmatN_print(const unsigned char *m, int n) {
    return ucmatN_fprint(stdout, m, n);
}

/** Calls ucmatN_fprint and adds a newline (Just calls ucmatN_fprintln(stdout, m, n)*/
static size_t ucmatN_println(const unsigned char *m, int n) {
    return ucmatN_fprintln(stdout, m, n);
}

#endif //M_IO_UCMATN_H
