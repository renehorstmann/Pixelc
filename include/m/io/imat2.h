#ifndef M_IO_IMAT2_H
#define M_IO_IMAT2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/int.h"
#include "../types/imat2.h"
#include "terminalcolor.h"

#define IMAT2_PRINT_FORMAT "(imat2) {{"\
 "\n%12" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER" }}"

#define IMAT2_PRINT_FORMAT_COLORED "(imat2)"\
 M_TERMINALCOLOR_CYAN" {{"\
 "\n%12" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER" }}"\
 M_TERMINALCOLOR_RESET

#define IMAT2_PRINT_FORMAT_LINE "(imat2) {{"\
 "%" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER\
 ", %" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER" }}"

#define IMAT2_PRINT_FORMAT_VALUES \
 "%" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER\
 ", %" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER


/**
 * Prints the imat2 in a single line
 * Example:
 * imat2 m = imat2_eye();
 * char buf[128];
 * imat2_snprint_line(buf, sizeof buf, m);
 * // (imat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat2_snprint_line(char *str, size_t size, imat2 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(imat2) {{ ");
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
                             "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls imat2_snprint_line and adds a newline */
static size_t imat2_snprintln_line(char *str, size_t size, imat2 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = imat2_snprint_line(str, size, m);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * imat2 m = imat2_eye();
 * char buf[128];
 * imat2_snprint(buf, sizeof buf, m);
 * // (imat2) {{
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }}
 */
static size_t imat2_snprint(char *str, size_t size, imat2 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(imat2) {{ ");
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
                             "%12" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls imat2_snprint and adds a newline */
static size_t imat2_snprintln(char *str, size_t size, imat2 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = imat2_snprint(str, size, m);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat2 m = imat2_eye();
 * imat2_fprint_line(stdout, m);
 * // (imat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat2_fprint_line(FILE *stream, imat2 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(imat2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 2; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 2; r++) {
            used += fprintf(stream, "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls imat2_fprint_line and adds a newline */
static size_t imat2_fprintln_line(FILE *stream, imat2 m) {
    size_t used = imat2_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat2 m = imat2_eye();
 * imat2_fprint(stdout, m);
 * // (imat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t imat2_fprint(FILE *stream, imat2 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(imat2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 2; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 2; r++) {
            used += fprintf(stream, "%12" ISCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls imat2_fprint and adds a newline */
static size_t imat2_fprintln(FILE *stream, imat2 m) {
    size_t used = imat2_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls imat2_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat2 m = imat2_eye();
 * imat2_print_line(m);
 * // (imat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t imat2_print_line(imat2 m) {
    return imat2_fprint_line(stdout, m);
}

/** Calls imat2_fprint_line and adds a newline (Just calls imat2_fprintln_line(stdout, m, n)*/
static size_t imat2_println_line(imat2 m) {
    return imat2_fprintln_line(stdout, m);
}

/**
 * Calls imat2_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * imat2 m = imat2_eye();
 * imat2_print(m);
 * // (imat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t imat2_print(imat2 m) {
    return imat2_fprint(stdout, m);
}

/** Calls imat2_fprint and adds a newline (Just calls imat2_fprintln(stdout, m, n)*/
static size_t imat2_println(imat2 m) {
    return imat2_fprintln(stdout, m);
}

#endif //M_IO_IMAT2_H
