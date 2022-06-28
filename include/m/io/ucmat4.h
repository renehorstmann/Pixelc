#ifndef M_IO_UCMAT4_H
#define M_IO_UCMAT4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/uchar.h"
#include "../types/ucmat4.h"
#include "terminalcolor.h"


/**
 * Prints the ucmat4 in a single line
 * Example:
 * ucmat4 m = ucmat4_eye();
 * char buf[128];
 * ucmat4_snprint_line(buf, sizeof buf, m);
 * // (ucmat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat4_snprint_line(char *str, size_t size, ucmat4 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucmat4) {{ ");
    for (int c = 0; c < 4; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 4; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ucmat4_snprint_line and adds a newline */
static size_t ucmat4_snprintln_line(char *str, size_t size, ucmat4 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucmat4_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * ucmat4 m = ucmat4_eye();
 * char buf[128];
 * ucmat4_snprint(buf, sizeof buf, m);
 * // (ucmat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t ucmat4_snprint(char *str, size_t size, ucmat4 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucmat4) {{ ");
    for (int c = 0; c < 4; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 4; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ucmat4_snprint and adds a newline */
static size_t ucmat4_snprintln(char *str, size_t size, ucmat4 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucmat4_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat4 m = ucmat4_eye();
 * ucmat4_fprint_line(stdout, m);
 * // (ucmat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat4_fprint_line(FILE *stream, ucmat4 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucmat4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 4; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 4; r++) {
            used += fprintf(stream, "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucmat4_fprint_line and adds a newline */
static size_t ucmat4_fprintln_line(FILE *stream, ucmat4 m) {
    size_t used = ucmat4_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat4 m = ucmat4_eye();
 * ucmat4_fprint(stdout, m);
 * // (ucmat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t ucmat4_fprint(FILE *stream, ucmat4 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucmat4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 4; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 4; r++) {
            used += fprintf(stream, "%12" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucmat4_fprint and adds a newline */
static size_t ucmat4_fprintln(FILE *stream, ucmat4 m) {
    size_t used = ucmat4_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ucmat4_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat4 m = ucmat4_eye();
 * ucmat4_print_line(m);
 * // (ucmat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat4_print_line(ucmat4 m) {
    return ucmat4_fprint_line(stdout, m);
}

/** Calls ucmat4_fprint_line and adds a newline (Just calls ucmat4_fprintln_line(stdout, m, n)*/
static size_t ucmat4_println_line(ucmat4 m) {
    return ucmat4_fprintln_line(stdout, m);
}

/**
 * Calls ucmat4_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat4 m = ucmat4_eye();
 * ucmat4_print(m);
 * // (ucmat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t ucmat4_print(ucmat4 m) {
    return ucmat4_fprint(stdout, m);
}

/** Calls ucmat4_fprint and adds a newline (Just calls ucmat4_fprintln(stdout, m, n)*/
static size_t ucmat4_println(ucmat4 m) {
    return ucmat4_fprintln(stdout, m);
}

#endif //M_IO_UCMAT4_H
