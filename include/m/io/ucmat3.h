#ifndef M_IO_UCMAT3_H
#define M_IO_UCMAT3_H


#include <stdio.h>
#include <locale.h>

#include "../sca/uchar.h"
#include "../types/ucmat3.h"
#include "terminalcolor.h"


#define UCMAT3_PRINT_FORMAT "(ucmat3) {{"\
 "\n%12" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER" }}"

#define UCMAT3_PRINT_FORMAT_COLORED "(ucmat3)"\
 M_TERMINALCOLOR_CYAN " {{"\
 "\n%12" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER" }}"\
 M_TERMINALCOLOR_RESET

#define UCMAT3_PRINT_FORMAT_LINE "(ucmat3) {{"\
 "%" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER\
 ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER\
 ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER" }}"

#define UCMAT3_PRINT_FORMAT_VALUES \
 "%" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER\
 ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER\
 ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER


/**
 * Prints the ucmat3 in a single line
 * Example:
 * ucmat3 m = ucmat3_eye();
 * char buf[128];
 * ucmat3_snprint_line(buf, sizeof buf, m);
 * // (ucmat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat3_snprint_line(char *str, size_t size, ucmat3 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucmat3) {{ ");
    for (int c = 0; c < 3; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 3; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ucmat3_snprint_line and adds a newline */
static size_t ucmat3_snprintln_line(char *str, size_t size, ucmat3 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucmat3_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * ucmat3 m = ucmat3_eye();
 * char buf[128];
 * ucmat3_snprint(buf, sizeof buf, m);
 * // (ucmat3) {{
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }}
 */
static size_t ucmat3_snprint(char *str, size_t size, ucmat3 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucmat3) {{ ");
    for (int c = 0; c < 3; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 3; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ucmat3_snprint and adds a newline */
static size_t ucmat3_snprintln(char *str, size_t size, ucmat3 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucmat3_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat3 m = ucmat3_eye();
 * ucmat3_fprint_line(stdout, m);
 * // (ucmat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat3_fprint_line(FILE *stream, ucmat3 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucmat3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 3; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 3; r++) {
            used += fprintf(stream, "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucmat3_fprint_line and adds a newline */
static size_t ucmat3_fprintln_line(FILE *stream, ucmat3 m) {
    size_t used = ucmat3_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat3 m = ucmat3_eye();
 * ucmat3_fprint(stdout, m);
 * // (ucmat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t ucmat3_fprint(FILE *stream, ucmat3 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucmat3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 3; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 3; r++) {
            used += fprintf(stream, "%12" UCSCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucmat3_fprint and adds a newline */
static size_t ucmat3_fprintln(FILE *stream, ucmat3 m) {
    size_t used = ucmat3_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ucmat3_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat3 m = ucmat3_eye();
 * ucmat3_print_line(m);
 * // (ucmat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t ucmat3_print_line(ucmat3 m) {
    return ucmat3_fprint_line(stdout, m);
}

/** Calls ucmat3_fprint_line and adds a newline (Just calls ucmat3_fprintln_line(stdout, m, n)*/
static size_t ucmat3_println_line(ucmat3 m) {
    return ucmat3_fprintln_line(stdout, m);
}

/**
 * Calls ucmat3_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucmat3 m = ucmat3_eye();
 * ucmat3_print(m);
 * // (ucmat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t ucmat3_print(ucmat3 m) {
    return ucmat3_fprint(stdout, m);
}

/** Calls ucmat3_fprint and adds a newline (Just calls ucmat3_fprintln(stdout, m, n)*/
static size_t ucmat3_println(ucmat3 m) {
    return ucmat3_fprintln(stdout, m);
}

#endif //M_IO_UCMAT3_H
