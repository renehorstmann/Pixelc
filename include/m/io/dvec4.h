#ifndef M_IO_DVEC4_H
#define M_IO_DVEC4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/double.h"
#include "../types/dvec4.h"
#include "terminalcolor.h"


/**
 * Example:
 * dvec4 v = dvec4_unit_x();
 * char buf[128];
 * dvec4_snprint(buf, sizeof buf, v);
 * // (dvec4) {{ 1.0, 0.0, ...}}
 */
static size_t dvec4_snprint(char *str, size_t size, dvec4 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(dvec4) {{ ");
    for (int i = 0; i < 4; i++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 4 - 1 ? ", " : "");
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls dvec4_snprint and adds a newline */
static size_t dvec4_snprintln(char *str, size_t size, dvec4 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dvec4_snprint(str, size, v);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dvec4 v = dvec4_unit_x();
 * dvec4_fprint(stdout, v);
 * // (dvec4) {{ 1.0, 0.0, ...}}
 */
static size_t dvec4_fprint(FILE *stream, dvec4 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(dvec4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 4; i++) {
        used += fprintf(stream, "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 4 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dvec4_fprint and adds a newline */
static size_t dvec4_fprintln(FILE *stream, dvec4 v) {
    size_t used = dvec4_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls dvec4_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dvec4 v = dvec4_unit_x();
 * dvec4_print(v);
 * // (dvec4) {{ 1.0, 0.0, ...}}
 */
static size_t dvec4_print(dvec4 v) {
    return dvec4_fprint(stdout, v);
}

/** Calls dvecN_print and adds a newline (Just calls dvec4_print(stdout, v)*/
static size_t dvec4_println(dvec4 v) {
    return dvec4_fprintln(stdout, v);
}

#endif //M_IO_DVEC4_H
