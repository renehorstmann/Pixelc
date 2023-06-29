#ifndef M_IO_IVEC2_H
#define M_IO_IVEC2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/int.h"
#include "../types/ivec2.h"
#include "terminalcolor.h"


#define IVEC2_PRINT_FORMAT "(ivec2) {{ %" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER " }}"

#define IVEC2_PRINT_FORMAT_COLORED "(ivec2)"\
 M_TERMINALCOLOR_CYAN " {{ %" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER " }}"\
 M_TERMINALCOLOR_RESET

#define IVEC2_PRINT_FORMAT_VALUES "%" ISCA_PRINT_FORMAT_SPECIFIER ", %" ISCA_PRINT_FORMAT_SPECIFIER


/**
 * Example:
 * ivec2 v = ivec2_unit_x();
 * char buf[128];
 * ivec2_snprint(buf, sizeof buf, v);
 * // (ivec2) {{ 1.0, 0.0, ...}}
 */
static size_t ivec2_snprint(char *str, size_t size, ivec2 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ivec2) {{ ");
    for (int i = 0; i < 2; i++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ivec2_snprint and adds a newline */
static size_t ivec2_snprintln(char *str, size_t size, ivec2 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ivec2_snprint(str, size, v);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ivec2 v = ivec2_unit_x();
 * ivec2_fprint(stdout, v);
 * // (ivec2) {{ 1.0, 0.0, ...}}
 */
static size_t ivec2_fprint(FILE *stream, ivec2 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ivec2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 2; i++) {
        used += fprintf(stream, "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ivec2_fprint and adds a newline */
static size_t ivec2_fprintln(FILE *stream, ivec2 v) {
    size_t used = ivec2_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ivec2_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ivec2 v = ivec2_unit_x();
 * ivec2_print(v);
 * // (ivec2) {{ 1.0, 0.0, ...}}
 */
static size_t ivec2_print(ivec2 v) {
    return ivec2_fprint(stdout, v);
}

/** Calls ivecN_print and adds a newline (Just calls ivec2_print(stdout, v)*/
static size_t ivec2_println(ivec2 v) {
    return ivec2_fprintln(stdout, v);
}

#endif //M_IO_IVEC2_H
