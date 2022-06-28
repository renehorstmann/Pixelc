#ifndef M_IO_IVEC4_H
#define M_IO_IVEC4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/int.h"
#include "../types/ivec4.h"
#include "terminalcolor.h"


/**
 * Example:
 * ivec4 v = ivec4_unit_x();
 * char buf[128];
 * ivec4_snprint(buf, sizeof buf, v);
 * // (ivec4) {{ 1.0, 0.0, ...}}
 */
static size_t ivec4_snprint(char *str, size_t size, ivec4 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ivec4) {{ ");
    for (int i = 0; i < 4; i++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 4 - 1 ? ", " : "");
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ivec4_snprint and adds a newline */
static size_t ivec4_snprintln(char *str, size_t size, ivec4 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ivec4_snprint(str, size, v);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ivec4 v = ivec4_unit_x();
 * ivec4_fprint(stdout, v);
 * // (ivec4) {{ 1.0, 0.0, ...}}
 */
static size_t ivec4_fprint(FILE *stream, ivec4 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ivec4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 4; i++) {
        used += fprintf(stream, "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 4 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ivec4_fprint and adds a newline */
static size_t ivec4_fprintln(FILE *stream, ivec4 v) {
    size_t used = ivec4_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ivec4_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ivec4 v = ivec4_unit_x();
 * ivec4_print(v);
 * // (ivec4) {{ 1.0, 0.0, ...}}
 */
static size_t ivec4_print(ivec4 v) {
    return ivec4_fprint(stdout, v);
}

/** Calls ivecN_print and adds a newline (Just calls ivec4_print(stdout, v)*/
static size_t ivec4_println(ivec4 v) {
    return ivec4_fprintln(stdout, v);
}

#endif //M_IO_IVEC4_H
