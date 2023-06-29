#ifndef M_IO_VEC2_H
#define M_IO_VEC2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/float.h"
#include "../types/vec2.h"
#include "terminalcolor.h"


#define VEC2_PRINT_FORMAT "(vec2) {{ %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER " }}"

#define VEC2_PRINT_FORMAT_COLORED "(vec2)"\
 M_TERMINALCOLOR_CYAN " {{ %" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER " }}"\
 M_TERMINALCOLOR_RESET

#define VEC2_PRINT_FORMAT_VALUES "%" SCA_PRINT_FORMAT_SPECIFIER ", %" SCA_PRINT_FORMAT_SPECIFIER


/**
 * Example:
 * vec2 v = vec2_unit_x();
 * char buf[128];
 * vec2_snprint(buf, sizeof buf, v);
 * // (vec2) {{ 1.0, 0.0, ...}}
 */
static size_t vec2_snprint(char *str, size_t size, vec2 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(vec2) {{ ");
    for (int i = 0; i < 2; i++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" SCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls vec2_snprint and adds a newline */
static size_t vec2_snprintln(char *str, size_t size, vec2 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = vec2_snprint(str, size, v);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * vec2 v = vec2_unit_x();
 * vec2_fprint(stdout, v);
 * // (vec2) {{ 1.0, 0.0, ...}}
 */
static size_t vec2_fprint(FILE *stream, vec2 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(vec2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 2; i++) {
        used += fprintf(stream, "%" SCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls vec2_fprint and adds a newline */
static size_t vec2_fprintln(FILE *stream, vec2 v) {
    size_t used = vec2_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls vec2_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * vec2 v = vec2_unit_x();
 * vec2_print(v);
 * // (vec2) {{ 1.0, 0.0, ...}}
 */
static size_t vec2_print(vec2 v) {
    return vec2_fprint(stdout, v);
}

/** Calls vecN_print and adds a newline (Just calls vec2_print(stdout, v)*/
static size_t vec2_println(vec2 v) {
    return vec2_fprintln(stdout, v);
}

#endif //M_IO_VEC2_H
