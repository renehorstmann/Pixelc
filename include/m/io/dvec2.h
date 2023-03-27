#ifndef M_IO_DVEC2_H
#define M_IO_DVEC2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/double.h"
#include "../types/dvec2.h"
#include "terminalcolor.h"


#define DVEC2_PRINT_FORMAT "(dvec2) {{ %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER " }}"

#define DVEC2_PRINT_FORMAT_COLORED "(dvec2)"\
 M_TERMINALCOLOR_CYAN " {{ %" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER " }}"\
 M_TERMINALCOLOR_RESET

#define DVEC2_PRINT_FORMAT_VALUES "%" DSCA_PRINT_FORMAT_SPECIFIER ", %" DSCA_PRINT_FORMAT_SPECIFIER


/**
 * Example:
 * dvec2 v = dvec2_unit_x();
 * char buf[128];
 * dvec2_snprint(buf, sizeof buf, v);
 * // (dvec2) {{ 1.0, 0.0, ...}}
 */
static size_t dvec2_snprint(char *str, size_t size, dvec2 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(dvec2) {{ ");
    for (int i = 0; i < 2; i++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls dvec2_snprint and adds a newline */
static size_t dvec2_snprintln(char *str, size_t size, dvec2 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = dvec2_snprint(str, size, v);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dvec2 v = dvec2_unit_x();
 * dvec2_fprint(stdout, v);
 * // (dvec2) {{ 1.0, 0.0, ...}}
 */
static size_t dvec2_fprint(FILE *stream, dvec2 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(dvec2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 2; i++) {
        used += fprintf(stream, "%" DSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls dvec2_fprint and adds a newline */
static size_t dvec2_fprintln(FILE *stream, dvec2 v) {
    size_t used = dvec2_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls dvec2_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * dvec2 v = dvec2_unit_x();
 * dvec2_print(v);
 * // (dvec2) {{ 1.0, 0.0, ...}}
 */
static size_t dvec2_print(dvec2 v) {
    return dvec2_fprint(stdout, v);
}

/** Calls dvecN_print and adds a newline (Just calls dvec2_print(stdout, v)*/
static size_t dvec2_println(dvec2 v) {
    return dvec2_fprintln(stdout, v);
}

#endif //M_IO_DVEC2_H
