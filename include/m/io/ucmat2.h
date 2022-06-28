#ifndef M_IO_UCMAT2_H
#define M_IO_UCMAT2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/uchar.h"
#include "../types/ucmat2.h"
#include "terminalcolor.h"


/**
 * Prints the ucmat2 in a single line
 * Example:
 * ucmat2 m = ucmat2_eye();
 * char buf[128];
 * ucmat2_snprint_line(buf, sizeof buf, m);
 * // (ucmat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat2_snprint_line(char *str, size_t size, ucmat2 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucmat2) {{ ");
    for (int c = 0; c < 2; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 2; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ucmat2_snprint_line and adds a newline */
static size_t ucmat2_snprintln_line(char *str, size_t size, ucmat2 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucmat2_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * ucmat2 m = ucmat2_eye();
 * char buf[128];
 * ucmat2_snprint(buf, sizeof buf, m);
 * // (ucmat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t ucmat2_snprint(char *str, size_t size, ucmat2 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucmat2) {{ ");
    for (int c = 0; c < 2; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 2; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ucmat2_snprint and adds a newline */
static size_t ucmat2_snprintln(char *str, size_t size, ucmat2 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucmat2_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat2 m = ucmat2_eye();
 * ucmat2_fprint_line(stdout, m);
 * // (ucmat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat2_fprint_line(FILE *stream, ucmat2 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucmat2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 2; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 2; r++) {
            used += fprintf(stream, "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucmat2_fprint_line and adds a newline */
static size_t ucmat2_fprintln_line(FILE *stream, ucmat2 m) {
    size_t used = ucmat2_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat2 m = ucmat2_eye();
 * ucmat2_fprint(stdout, m);
 * // (ucmat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t ucmat2_fprint(FILE *stream, ucmat2 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucmat2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 2; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 2; r++) {
            used += fprintf(stream, "%12" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucmat2_fprint and adds a newline */
static size_t ucmat2_fprintln(FILE *stream, ucmat2 m) {
    size_t used = ucmat2_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ucmat2_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat2 m = ucmat2_eye();
 * ucmat2_print_line(m);
 * // (ucmat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat2_print_line(ucmat2 m) {
    return ucmat2_fprint_line(stdout, m);
}

/** Calls ucmat2_fprint_line and adds a newline (Just calls ucmat2_fprintln_line(stdout, m, n)*/
static size_t ucmat2_println_line(ucmat2 m) {
    return ucmat2_fprintln_line(stdout, m);
}

/**
 * Calls ucmat2_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat2 m = ucmat2_eye();
 * ucmat2_print(m);
 * // (ucmat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t ucmat2_print(ucmat2 m) {
    return ucmat2_fprint(stdout, m);
}

/** Calls ucmat2_fprint and adds a newline (Just calls ucmat2_fprintln(stdout, m, n)*/
static size_t ucmat2_println(ucmat2 m) {
    return ucmat2_fprintln(stdout, m);
}

#endif //M_IO_UCMAT2_H
