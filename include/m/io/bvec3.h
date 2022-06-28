#ifndef M_IO_BVEC3_H
#define M_IO_BVEC3_H


#include <stdio.h>
#include <locale.h>

#include "../sca/bool.h"
#include "../types/bvec3.h"
#include "terminalcolor.h"


/**
 * Example:
 * bvec3 v = bvec3_unit_x();
 * char buf[128];
 * bvec3_snprint(buf, sizeof buf, v);
 * // (bvec3) {{ 1.0, 0.0, ...}}
 */
static size_t bvec3_snprint(char *str, size_t size, bvec3 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(bvec3) {{ ");
    for (int i = 0; i < 3; i++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" BSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 3 - 1 ? ", " : "");
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls bvec3_snprint and adds a newline */
static size_t bvec3_snprintln(char *str, size_t size, bvec3 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = bvec3_snprint(str, size, v);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * bvec3 v = bvec3_unit_x();
 * bvec3_fprint(stdout, v);
 * // (bvec3) {{ 1.0, 0.0, ...}}
 */
static size_t bvec3_fprint(FILE *stream, bvec3 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(bvec3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 3; i++) {
        used += fprintf(stream, "%" BSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 3 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls bvec3_fprint and adds a newline */
static size_t bvec3_fprintln(FILE *stream, bvec3 v) {
    size_t used = bvec3_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls bvec3_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * bvec3 v = bvec3_unit_x();
 * bvec3_print(v);
 * // (bvec3) {{ 1.0, 0.0, ...}}
 */
static size_t bvec3_print(bvec3 v) {
    return bvec3_fprint(stdout, v);
}

/** Calls bvecN_print and adds a newline (Just calls bvec3_print(stdout, v)*/
static size_t bvec3_println(bvec3 v) {
    return bvec3_fprintln(stdout, v);
}

#endif //M_IO_BVEC3_H
