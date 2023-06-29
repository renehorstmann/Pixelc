#ifndef M_IO_DMAT2_H
#define M_IO_DMAT2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/double.h"
#include "../types/dmat2.h"
#include "terminalcolor.h"

#define DMAT2_PRINT_FORMAT "(dmat2) {{"\
 "\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER" }}"

#define DMAT2_PRINT_FORMAT_COLORED "(dmat2)"\
 M_TERMINALCOLOR_CYAN" {{"\
 "\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER" }}"\
 M_TERMINALCOLOR_RESET

#define DMAT2_PRINT_FORMAT_LINE "(dmat2) {{"\
 "%" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER" }}"

#define DMAT2_PRINT_FORMAT_VALUES \
 "%" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER\
 ", %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER


/**
 * Prints the dmat2 in a single line
 * Example:
 * dmat2 m = dmat2_eye();
 * char buf[128];
 * dmat2_snprint_line(buf, sizeof buf, m);
 * // (dmat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat2_snprint_line(char *str, size_t size, dmat2 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(dmat2) {{ ");
    for (int c = 0; c < 2; c++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 2; r++) {
            if (used >= size) {
                str = NULL;
            }
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls dmat2_snprint_line and adds a newline */
static size_t dmat2_snprintln_line(char *str, size_t size, dmat2 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dmat2_snprint_line(str, size, m);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * dmat2 m = dmat2_eye();
 * char buf[128];
 * dmat2_snprint(buf, sizeof buf, m);
 * // (dmat2) {{
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }}
 */
static size_t dmat2_snprint(char *str, size_t size, dmat2 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(dmat2) {{ ");
    for (int c = 0; c < 2; c++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 2; r++) {
            if (used >= size) {
                str = NULL;
            }
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls dmat2_snprint and adds a newline */
static size_t dmat2_snprintln(char *str, size_t size, dmat2 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dmat2_snprint(str, size, m);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat2 m = dmat2_eye();
 * dmat2_fprint_line(stdout, m);
 * // (dmat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat2_fprint_line(FILE *stream, dmat2 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(dmat2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 2; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 2; r++) {
            used += fprintf(stream, "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dmat2_fprint_line and adds a newline */
static size_t dmat2_fprintln_line(FILE *stream, dmat2 m) {
    size_t used = dmat2_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat2 m = dmat2_eye();
 * dmat2_fprint(stdout, m);
 * // (dmat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t dmat2_fprint(FILE *stream, dmat2 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(dmat2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 2; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 2; r++) {
            used += fprintf(stream, "%12" DSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dmat2_fprint and adds a newline */
static size_t dmat2_fprintln(FILE *stream, dmat2 m) {
    size_t used = dmat2_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls dmat2_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat2 m = dmat2_eye();
 * dmat2_print_line(m);
 * // (dmat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t dmat2_print_line(dmat2 m) {
    return dmat2_fprint_line(stdout, m);
}

/** Calls dmat2_fprint_line and adds a newline (Just calls dmat2_fprintln_line(stdout, m, n)*/
static size_t dmat2_println_line(dmat2 m) {
    return dmat2_fprintln_line(stdout, m);
}

/**
 * Calls dmat2_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dmat2 m = dmat2_eye();
 * dmat2_print(m);
 * // (dmat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t dmat2_print(dmat2 m) {
    return dmat2_fprint(stdout, m);
}

/** Calls dmat2_fprint and adds a newline (Just calls dmat2_fprintln(stdout, m, n)*/
static size_t dmat2_println(dmat2 m) {
    return dmat2_fprintln(stdout, m);
}

#endif //M_IO_DMAT2_H
