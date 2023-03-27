#ifndef M_IO_DMAT3_H
#define M_IO_DMAT3_H


#include <stdio.h>
#include <locale.h>

#include "../sca/double.h"
#include "../types/dmat3.h"
#include "terminalcolor.h"


#define DMAT3_PRINT_FORMAT "(dmat3) {{"\
 "\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER" }}"

#define DMAT3_PRINT_FORMAT_COLORED "(dmat3)"\
 M_TERMINALCOLOR_CYAN " {{"\
 "\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER" }}"\
 M_TERMINALCOLOR_RESET

#define DMAT3_PRINT_FORMAT_LINE "(dmat3) {{"\
 "%" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER" }}"

#define DMAT3_PRINT_FORMAT_VALUES \
 "%" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER


/**
 * Prints the dmat3 in a single line
 * Example:
 * dmat3 m = dmat3_eye();
 * char buf[128];
 * dmat3_snprint_line(buf, sizeof buf, m);
 * // (dmat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat3_snprint_line(char *str, size_t size, dmat3 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(dmat3) {{ ");
    for (int c = 0; c < 3; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 3; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls dmat3_snprint_line and adds a newline */
static size_t dmat3_snprintln_line(char *str, size_t size, dmat3 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dmat3_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * dmat3 m = dmat3_eye();
 * char buf[128];
 * dmat3_snprint(buf, sizeof buf, m);
 * // (dmat3) {{
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }}
 */
static size_t dmat3_snprint(char *str, size_t size, dmat3 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(dmat3) {{ ");
    for (int c = 0; c < 3; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 3; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls dmat3_snprint and adds a newline */
static size_t dmat3_snprintln(char *str, size_t size, dmat3 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dmat3_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat3 m = dmat3_eye();
 * dmat3_fprint_line(stdout, m);
 * // (dmat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat3_fprint_line(FILE *stream, dmat3 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(dmat3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 3; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 3; r++) {
            used += fprintf(stream, "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dmat3_fprint_line and adds a newline */
static size_t dmat3_fprintln_line(FILE *stream, dmat3 m) {
    size_t used = dmat3_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat3 m = dmat3_eye();
 * dmat3_fprint(stdout, m);
 * // (dmat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t dmat3_fprint(FILE *stream, dmat3 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(dmat3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 3; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 3; r++) {
            used += fprintf(stream, "%12" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dmat3_fprint and adds a newline */
static size_t dmat3_fprintln(FILE *stream, dmat3 m) {
    size_t used = dmat3_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls dmat3_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat3 m = dmat3_eye();
 * dmat3_print_line(m);
 * // (dmat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat3_print_line(dmat3 m) {
    return dmat3_fprint_line(stdout, m);
}

/** Calls dmat3_fprint_line and adds a newline (Just calls dmat3_fprintln_line(stdout, m, n)*/
static size_t dmat3_println_line(dmat3 m) {
    return dmat3_fprintln_line(stdout, m);
}

/**
 * Calls dmat3_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat3 m = dmat3_eye();
 * dmat3_print(m);
 * // (dmat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t dmat3_print(dmat3 m) {
    return dmat3_fprint(stdout, m);
}

/** Calls dmat3_fprint and adds a newline (Just calls dmat3_fprintln(stdout, m, n)*/
static size_t dmat3_println(dmat3 m) {
    return dmat3_fprintln(stdout, m);
}

#endif //M_IO_DMAT3_H
