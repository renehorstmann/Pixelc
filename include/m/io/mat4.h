#ifndef M_IO_MAT4_H
#define M_IO_MAT4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/float.h"
#include "../types/mat4.h"
#include "terminalcolor.h"


#define MAT4_PRINT_FORMAT "(mat4) {{"\
 "\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER" }}"

#define MAT4_PRINT_FORMAT_COLORED "(mat4)"\
 M_TERMINALCOLOR_CYAN " {{"\
 "\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER" }}"\
 M_TERMINALCOLOR_RESET

#define MAT4_PRINT_FORMAT_LINE "(mat4) {{"\
 "%" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER" }}"

#define MAT4_PRINT_FORMAT_VALUES \
 "%" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER


/**
 * Prints the mat4 in a single line
 * Example:
 * mat4 m = mat4_eye();
 * char buf[128];
 * mat4_snprint_line(buf, sizeof buf, m);
 * // (mat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat4_snprint_line(char *str, size_t size, mat4 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(mat4) {{ ");
    for (int c = 0; c < 4; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 4; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls mat4_snprint_line and adds a newline */
static size_t mat4_snprintln_line(char *str, size_t size, mat4 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = mat4_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * mat4 m = mat4_eye();
 * char buf[128];
 * mat4_snprint(buf, sizeof buf, m);
 * // (mat4) {{
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }}
 */
static size_t mat4_snprint(char *str, size_t size, mat4 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(mat4) {{ ");
    for (int c = 0; c < 4; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 4; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls mat4_snprint and adds a newline */
static size_t mat4_snprintln(char *str, size_t size, mat4 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = mat4_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat4 m = mat4_eye();
 * mat4_fprint_line(stdout, m);
 * // (mat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat4_fprint_line(FILE *stream, mat4 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(mat4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 4; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 4; r++) {
            used += fprintf(stream, "%" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls mat4_fprint_line and adds a newline */
static size_t mat4_fprintln_line(FILE *stream, mat4 m) {
    size_t used = mat4_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat4 m = mat4_eye();
 * mat4_fprint(stdout, m);
 * // (mat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t mat4_fprint(FILE *stream, mat4 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(mat4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 4; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 4; r++) {
            used += fprintf(stream, "%12" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 4 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls mat4_fprint and adds a newline */
static size_t mat4_fprintln(FILE *stream, mat4 m) {
    size_t used = mat4_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls mat4_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat4 m = mat4_eye();
 * mat4_print_line(m);
 * // (mat4) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat4_print_line(mat4 m) {
    return mat4_fprint_line(stdout, m);
}

/** Calls mat4_fprint_line and adds a newline (Just calls mat4_fprintln_line(stdout, m, n)*/
static size_t mat4_println_line(mat4 m) {
    return mat4_fprintln_line(stdout, m);
}

/**
 * Calls mat4_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat4 m = mat4_eye();
 * mat4_print(m);
 * // (mat4) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t mat4_print(mat4 m) {
    return mat4_fprint(stdout, m);
}

/** Calls mat4_fprint and adds a newline (Just calls mat4_fprintln(stdout, m, n)*/
static size_t mat4_println(mat4 m) {
    return mat4_fprintln(stdout, m);
}

#endif //M_IO_MAT4_H
