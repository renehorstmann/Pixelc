#ifndef M_IO_IMAT3_H
#define M_IO_IMAT3_H


#include <stdio.h>
#include <locale.h>

#include "../sca/int.h"
#include "../types/imat3.h"
#include "terminalcolor.h"


/**
 * Prints the imat3 in a single line
 * Example:
 * imat3 m = imat3_eye();
 * char buf[128];
 * imat3_snprint_line(buf, sizeof buf, m);
 * // (imat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat3_snprint_line(char *str, size_t size, imat3 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(imat3) {{ ");
    for (int c = 0; c < 3; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 3; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls imat3_snprint_line and adds a newline */
static size_t imat3_snprintln_line(char *str, size_t size, imat3 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = imat3_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * imat3 m = imat3_eye();
 * char buf[128];
 * imat3_snprint(buf, sizeof buf, m);
 * // (imat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t imat3_snprint(char *str, size_t size, imat3 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(imat3) {{ ");
    for (int c = 0; c < 3; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 3; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls imat3_snprint and adds a newline */
static size_t imat3_snprintln(char *str, size_t size, imat3 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = imat3_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat3 m = imat3_eye();
 * imat3_fprint_line(stdout, m);
 * // (imat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat3_fprint_line(FILE *stream, imat3 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(imat3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 3; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 3; r++) {
            used += fprintf(stream, "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls imat3_fprint_line and adds a newline */
static size_t imat3_fprintln_line(FILE *stream, imat3 m) {
    size_t used = imat3_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat3 m = imat3_eye();
 * imat3_fprint(stdout, m);
 * // (imat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t imat3_fprint(FILE *stream, imat3 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(imat3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 3; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 3; r++) {
            used += fprintf(stream, "%12" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls imat3_fprint and adds a newline */
static size_t imat3_fprintln(FILE *stream, imat3 m) {
    size_t used = imat3_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls imat3_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat3 m = imat3_eye();
 * imat3_print_line(m);
 * // (imat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat3_print_line(imat3 m) {
    return imat3_fprint_line(stdout, m);
}

/** Calls imat3_fprint_line and adds a newline (Just calls imat3_fprintln_line(stdout, m, n)*/
static size_t imat3_println_line(imat3 m) {
    return imat3_fprintln_line(stdout, m);
}

/**
 * Calls imat3_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat3 m = imat3_eye();
 * imat3_print(m);
 * // (imat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t imat3_print(imat3 m) {
    return imat3_fprint(stdout, m);
}

/** Calls imat3_fprint and adds a newline (Just calls imat3_fprintln(stdout, m, n)*/
static size_t imat3_println(imat3 m) {
    return imat3_fprintln(stdout, m);
}

#endif //M_IO_IMAT3_H
