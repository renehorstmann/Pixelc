#ifndef M_IO_DMAT4_H
#define M_IO_DMAT4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/double.h"
#include "../types/dmat4.h"
#include "terminalcolor.h"


/**
 * Prints the dmat4 in a single line
 * Example:
 * dmat4 m = dmat4_eye();
 * char buf[128];
 * dmat4_snprint_line(buf, sizeof buf, m);
 * // (dmat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat4_snprint_line(char *str, size_t size, dmat4 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(dmat4) {{ ");
    for (int c = 0; c < 4; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 4; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls dmat4_snprint_line and adds a newline */
static size_t dmat4_snprintln_line(char *str, size_t size, dmat4 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dmat4_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * dmat4 m = dmat4_eye();
 * char buf[128];
 * dmat4_snprint(buf, sizeof buf, m);
 * // (dmat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t dmat4_snprint(char *str, size_t size, dmat4 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(dmat4) {{ ");
    for (int c = 0; c < 4; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 4; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls dmat4_snprint and adds a newline */
static size_t dmat4_snprintln(char *str, size_t size, dmat4 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dmat4_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat4 m = dmat4_eye();
 * dmat4_fprint_line(stdout, m);
 * // (dmat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat4_fprint_line(FILE *stream, dmat4 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(dmat4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 4; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 4; r++) {
            used += fprintf(stream, "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dmat4_fprint_line and adds a newline */
static size_t dmat4_fprintln_line(FILE *stream, dmat4 m) {
    size_t used = dmat4_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat4 m = dmat4_eye();
 * dmat4_fprint(stdout, m);
 * // (dmat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t dmat4_fprint(FILE *stream, dmat4 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(dmat4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 4; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 4; r++) {
            used += fprintf(stream, "%12" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dmat4_fprint and adds a newline */
static size_t dmat4_fprintln(FILE *stream, dmat4 m) {
    size_t used = dmat4_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls dmat4_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat4 m = dmat4_eye();
 * dmat4_print_line(m);
 * // (dmat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat4_print_line(dmat4 m) {
    return dmat4_fprint_line(stdout, m);
}

/** Calls dmat4_fprint_line and adds a newline (Just calls dmat4_fprintln_line(stdout, m, n)*/
static size_t dmat4_println_line(dmat4 m) {
    return dmat4_fprintln_line(stdout, m);
}

/**
 * Calls dmat4_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat4 m = dmat4_eye();
 * dmat4_print(m);
 * // (dmat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t dmat4_print(dmat4 m) {
    return dmat4_fprint(stdout, m);
}

/** Calls dmat4_fprint and adds a newline (Just calls dmat4_fprintln(stdout, m, n)*/
static size_t dmat4_println(dmat4 m) {
    return dmat4_fprintln(stdout, m);
}

#endif //M_IO_DMAT4_H
