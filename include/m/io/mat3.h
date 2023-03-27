#ifndef M_IO_MAT3_H
#define M_IO_MAT3_H


#include <stdio.h>
#include <locale.h>

#include "../sca/float.h"
#include "../types/mat3.h"
#include "terminalcolor.h"


#define MAT3_PRINT_FORMAT "(mat3) {{"\
 "\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER" }}"

#define MAT3_PRINT_FORMAT_COLORED "(mat3)"\
 M_TERMINALCOLOR_CYAN " {{"\
 "\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ",\n%12" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER" }}"\
 M_TERMINALCOLOR_RESET

#define MAT3_PRINT_FORMAT_LINE "(mat3) {{"\
 "%" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER" }}"

#define MAT3_PRINT_FORMAT_VALUES \
 "%" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER\
 ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER


/**
 * Prints the mat3 in a single line
 * Example:
 * mat3 m = mat3_eye();
 * char buf[128];
 * mat3_snprint_line(buf, sizeof buf, m);
 * // (mat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat3_snprint_line(char *str, size_t size, mat3 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(mat3) {{ ");
    for (int c = 0; c < 3; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 3; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls mat3_snprint_line and adds a newline */
static size_t mat3_snprintln_line(char *str, size_t size, mat3 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = mat3_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * mat3 m = mat3_eye();
 * char buf[128];
 * mat3_snprint(buf, sizeof buf, m);
 * // (mat3) {{
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }}
 */
static size_t mat3_snprint(char *str, size_t size, mat3 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(mat3) {{ ");
    for (int c = 0; c < 3; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 3; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls mat3_snprint and adds a newline */
static size_t mat3_snprintln(char *str, size_t size, mat3 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = mat3_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat3 m = mat3_eye();
 * mat3_fprint_line(stdout, m);
 * // (mat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat3_fprint_line(FILE *stream, mat3 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(mat3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 3; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 3; r++) {
            used += fprintf(stream, "%" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls mat3_fprint_line and adds a newline */
static size_t mat3_fprintln_line(FILE *stream, mat3 m) {
    size_t used = mat3_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat3 m = mat3_eye();
 * mat3_fprint(stdout, m);
 * // (mat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t mat3_fprint(FILE *stream, mat3 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(mat3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 3; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 3; r++) {
            used += fprintf(stream, "%12" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 3 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls mat3_fprint and adds a newline */
static size_t mat3_fprintln(FILE *stream, mat3 m) {
    size_t used = mat3_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls mat3_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat3 m = mat3_eye();
 * mat3_print_line(m);
 * // (mat3) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat3_print_line(mat3 m) {
    return mat3_fprint_line(stdout, m);
}

/** Calls mat3_fprint_line and adds a newline (Just calls mat3_fprintln_line(stdout, m, n)*/
static size_t mat3_println_line(mat3 m) {
    return mat3_fprintln_line(stdout, m);
}

/**
 * Calls mat3_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat3 m = mat3_eye();
 * mat3_print(m);
 * // (mat3) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t mat3_print(mat3 m) {
    return mat3_fprint(stdout, m);
}

/** Calls mat3_fprint and adds a newline (Just calls mat3_fprintln(stdout, m, n)*/
static size_t mat3_println(mat3 m) {
    return mat3_fprintln(stdout, m);
}

#endif //M_IO_MAT3_H
