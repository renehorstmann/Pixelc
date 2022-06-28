#ifndef M_IO_IMAT4_H
#define M_IO_IMAT4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/int.h"
#include "../types/imat4.h"
#include "terminalcolor.h"


/**
 * Prints the imat4 in a single line
 * Example:
 * imat4 m = imat4_eye();
 * char buf[128];
 * imat4_snprint_line(buf, sizeof buf, m);
 * // (imat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat4_snprint_line(char *str, size_t size, imat4 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(imat4) {{ ");
    for (int c = 0; c < 4; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 4; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls imat4_snprint_line and adds a newline */
static size_t imat4_snprintln_line(char *str, size_t size, imat4 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = imat4_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * imat4 m = imat4_eye();
 * char buf[128];
 * imat4_snprint(buf, sizeof buf, m);
 * // (imat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t imat4_snprint(char *str, size_t size, imat4 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(imat4) {{ ");
    for (int c = 0; c < 4; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 4; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls imat4_snprint and adds a newline */
static size_t imat4_snprintln(char *str, size_t size, imat4 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = imat4_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat4 m = imat4_eye();
 * imat4_fprint_line(stdout, m);
 * // (imat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat4_fprint_line(FILE *stream, imat4 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(imat4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 4; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 4; r++) {
            used += fprintf(stream, "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls imat4_fprint_line and adds a newline */
static size_t imat4_fprintln_line(FILE *stream, imat4 m) {
    size_t used = imat4_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat4 m = imat4_eye();
 * imat4_fprint(stdout, m);
 * // (imat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t imat4_fprint(FILE *stream, imat4 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(imat4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 4; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 4; r++) {
            used += fprintf(stream, "%12" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls imat4_fprint and adds a newline */
static size_t imat4_fprintln(FILE *stream, imat4 m) {
    size_t used = imat4_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls imat4_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat4 m = imat4_eye();
 * imat4_print_line(m);
 * // (imat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat4_print_line(imat4 m) {
    return imat4_fprint_line(stdout, m);
}

/** Calls imat4_fprint_line and adds a newline (Just calls imat4_fprintln_line(stdout, m, n)*/
static size_t imat4_println_line(imat4 m) {
    return imat4_fprintln_line(stdout, m);
}

/**
 * Calls imat4_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat4 m = imat4_eye();
 * imat4_print(m);
 * // (imat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t imat4_print(imat4 m) {
    return imat4_fprint(stdout, m);
}

/** Calls imat4_fprint and adds a newline (Just calls imat4_fprintln(stdout, m, n)*/
static size_t imat4_println(imat4 m) {
    return imat4_fprintln(stdout, m);
}

#endif //M_IO_IMAT4_H
