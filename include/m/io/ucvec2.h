#ifndef M_IO_UCVEC2_H
#define M_IO_UCVEC2_H


#include <stdio.h>
#include <locale.h>

#include "../sca/uchar.h"
#include "../types/ucvec2.h"
#include "terminalcolor.h"


#define UCVEC2_PRINT_FORMAT "(ucvec2) {{ %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER " }}"

#define UCVEC2_PRINT_FORMAT_COLORED "(ucvec2)"\
 M_TERMINALCOLOR_CYAN " {{ %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER " }}"\
 M_TERMINALCOLOR_RESET

#define UCVEC2_PRINT_FORMAT_VALUES "%" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER


/**
 * Example:
 * ucvec2 v = ucvec2_unit_x();
 * char buf[128];
 * ucvec2_snprint(buf, sizeof buf, v);
 * // (ucvec2) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec2_snprint(char *str, size_t size, ucvec2 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucvec2) {{ ");
    for (int i = 0; i < 2; i++) {
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ucvec2_snprint and adds a newline */
static size_t ucvec2_snprintln(char *str, size_t size, ucvec2 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucvec2_snprint(str, size, v);
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucvec2 v = ucvec2_unit_x();
 * ucvec2_fprint(stdout, v);
 * // (ucvec2) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec2_fprint(FILE *stream, ucvec2 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucvec2) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 2; i++) {
        used += fprintf(stream, "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 2 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucvec2_fprint and adds a newline */
static size_t ucvec2_fprintln(FILE *stream, ucvec2 v) {
    size_t used = ucvec2_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ucvec2_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucvec2 v = ucvec2_unit_x();
 * ucvec2_print(v);
 * // (ucvec2) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec2_print(ucvec2 v) {
    return ucvec2_fprint(stdout, v);
}

/** Calls ucvecN_print and adds a newline (Just calls ucvec2_print(stdout, v)*/
static size_t ucvec2_println(ucvec2 v) {
    return ucvec2_fprintln(stdout, v);
}

#endif //M_IO_UCVEC2_H
