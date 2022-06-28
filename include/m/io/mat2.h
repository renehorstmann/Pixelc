#ifndef M_IO_MAT2_H
#define M_IO_MAT2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/float.h"
#include "../types/mat2.h"
#include "terminalcolor.h"


/**
 * Prints the mat2 in a single line
 * Example:
 * mat2 m = mat2_eye();
 * char buf[128];
 * mat2_snprint_line(buf, sizeof buf, m);
 * // (mat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat2_snprint_line(char *str, size_t size, mat2 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(mat2) {{ ");
    for (int c = 0; c < 2; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 2; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls mat2_snprint_line and adds a newline */
static size_t mat2_snprintln_line(char *str, size_t size, mat2 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = mat2_snprint_line(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Prints the matrix in multiple lines
 * Example:
 * mat2 m = mat2_eye();
 * char buf[128];
 * mat2_snprint(buf, sizeof buf, m);
 * // (mat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t mat2_snprint(char *str, size_t size, mat2 m) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(mat2) {{ ");
    for (int c = 0; c < 2; c++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 2; r++) {
            used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                             "%12" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls mat2_snprint and adds a newline */
static size_t mat2_snprintln(char *str, size_t size, mat2 m) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = mat2_snprint(str, size, m);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat2 m = mat2_eye();
 * mat2_fprint_line(stdout, m);
 * // (mat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat2_fprint_line(FILE *stream, mat2 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(mat2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 2; c++) {
        used += fprintf(stream, "%s", c > 0 ? ",   " : "");
        for (int r = 0; r < 2; r++) {
            used += fprintf(stream, "%" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls mat2_fprint_line and adds a newline */
static size_t mat2_fprintln_line(FILE *stream, mat2 m) {
    size_t used = mat2_fprint_line(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat2 m = mat2_eye();
 * mat2_fprint(stdout, m);
 * // (mat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t mat2_fprint(FILE *stream, mat2 m) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(mat2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int c = 0; c < 2; c++) {
        used += fprintf(stream, "%s\n    ", c > 0 ? "," : "");
        for (int r = 0; r < 2; r++) {
            used += fprintf(stream, "%12" SCA_PRINT_FORMAT_SPECIFIER "%s", m.m[c][r], r < 2 - 1 ? ", " : "");
        }
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls mat2_fprint and adds a newline */
static size_t mat2_fprintln(FILE *stream, mat2 m) {
    size_t used = mat2_fprint(stream, m);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls mat2_fprint_line(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat2 m = mat2_eye();
 * mat2_print_line(m);
 * // (mat2) {{ 1.0, 0.0,   0.0, 1.1,   ... }}
 */
static size_t mat2_print_line(mat2 m) {
    return mat2_fprint_line(stdout, m);
}

/** Calls mat2_fprint_line and adds a newline (Just calls mat2_fprintln_line(stdout, m, n)*/
static size_t mat2_println_line(mat2 m) {
    return mat2_fprintln_line(stdout, m);
}

/**
 * Calls mat2_fprint(stdout, m)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * mat2 m = mat2_eye();
 * mat2_print(m);
 * // (mat2) {
 * //        1.0,          0.0,
 * //        0.0,          1.0,
 * //        ...,          ... }
 */
static size_t mat2_print(mat2 m) {
    return mat2_fprint(stdout, m);
}

/** Calls mat2_fprint and adds a newline (Just calls mat2_fprintln(stdout, m, n)*/
static size_t mat2_println(mat2 m) {
    return mat2_fprintln(stdout, m);
}

#endif //M_IO_MAT2_H
