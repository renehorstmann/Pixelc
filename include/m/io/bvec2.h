#ifndef M_IO_BVEC2_H
#define M_IO_BVEC2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/bool.h"
#include "../types/bvec2.h"
#include "terminalcolor.h"


#define BVEC2_PRINT_FORMAT "(bvec2) {{ %" BSCA_PRINT_FORMAT_SPECIFIER ", %" BSCA_PRINT_FORMAT_SPECIFIER " }}"

#define BVEC2_PRINT_FORMAT_COLORED "(bvec2)"\
 M_TERMINALCOLOR_CYAN " {{ %" BSCA_PRINT_FORMAT_SPECIFIER ", %" BSCA_PRINT_FORMAT_SPECIFIER " }}"\
 M_TERMINALCOLOR_RESET

#define BVEC2_PRINT_FORMAT_VALUES "%" BSCA_PRINT_FORMAT_SPECIFIER ", %" BSCA_PRINT_FORMAT_SPECIFIER


/**
 * Example:
 * bvec2 v = bvec2_unit_x();
 * char buf[128];
 * bvec2_snprint(buf, sizeof buf, v);
 * // (bvec2) {{ 1.0, 0.0, ...}}
 */
static size_t bvec2_snprint(char *str, size_t size, bvec2 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(bvec2) {{ ");
    for (int i = 0; i < 2; i++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" BSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls bvec2_snprint and adds a newline */
static size_t bvec2_snprintln(char *str, size_t size, bvec2 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = bvec2_snprint(str, size, v);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * bvec2 v = bvec2_unit_x();
 * bvec2_fprint(stdout, v);
 * // (bvec2) {{ 1.0, 0.0, ...}}
 */
static size_t bvec2_fprint(FILE *stream, bvec2 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(bvec2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 2; i++) {
        used += fprintf(stream, "%" BSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls bvec2_fprint and adds a newline */
static size_t bvec2_fprintln(FILE *stream, bvec2 v) {
    size_t used = bvec2_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls bvec2_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * bvec2 v = bvec2_unit_x();
 * bvec2_print(v);
 * // (bvec2) {{ 1.0, 0.0, ...}}
 */
static size_t bvec2_print(bvec2 v) {
    return bvec2_fprint(stdout, v);
}

/** Calls bvecN_print and adds a newline (Just calls bvec2_print(stdout, v)*/
static size_t bvec2_println(bvec2 v) {
    return bvec2_fprintln(stdout, v);
}

#endif //M_IO_BVEC2_H
