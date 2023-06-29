#ifndef M_IO_UCVEC3_H
#define M_IO_UCVEC3_H


#include <stdio.h>
#include <locale.h>

#include "../sca/uchar.h"
#include "../types/ucvec3.h"
#include "terminalcolor.h"


#define UCVEC3_PRINT_FORMAT "(ucvec3) {{  %" UCSCA_PRINT_FORMAT_SPECIFIER \
 ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER " }}"

#define UCVEC3_PRINT_FORMAT_COLORED "(ucvec3)"\
 M_TERMINALCOLOR_CYAN " {{  %" UCSCA_PRINT_FORMAT_SPECIFIER \
 ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER " }}"\
 M_TERMINALCOLOR_RESET

#define UCVEC3_PRINT_FORMAT_VALUES  "%" UCSCA_PRINT_FORMAT_SPECIFIER \
 ", %" UCSCA_PRINT_FORMAT_SPECIFIER ", %" UCSCA_PRINT_FORMAT_SPECIFIER


/**
 * Example:
 * ucvec3 v = ucvec3_unit_x();
 * char buf[128];
 * ucvec3_snprint(buf, sizeof buf, v);
 * // (ucvec3) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec3_snprint(char *str, size_t size, ucvec3 v) {
    setlocale(LC_ALL, "C");
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucvec3) {{ ");
    for (int i = 0; i < 3; i++) {
        if (used >= size) {
            str = NULL;
        }
        used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used,
                         "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 3 - 1 ? ", " : "");
    }
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, " }}");
    return used;
}

/** Calls ucvec3_snprint and adds a newline */
static size_t ucvec3_snprintln(char *str, size_t size, ucvec3 v) {
    if (!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucvec3_snprint(str, size, v);
    if (used >= size) {
        str = NULL;
    }
    used += snprintf(!str ? NULL : str + used, !size ? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucvec3 v = ucvec3_unit_x();
 * ucvec3_fprint(stdout, v);
 * // (ucvec3) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec3_fprint(FILE *stream, ucvec3 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucvec3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for (int i = 0; i < 3; i++) {
        used += fprintf(stream, "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i < 3 - 1 ? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucvec3_fprint and adds a newline */
static size_t ucvec3_fprintln(FILE *stream, ucvec3 v) {
    size_t used = ucvec3_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ucvec3_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucvec3 v = ucvec3_unit_x();
 * ucvec3_print(v);
 * // (ucvec3) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec3_print(ucvec3 v) {
    return ucvec3_fprint(stdout, v);
}

/** Calls ucvecN_print and adds a newline (Just calls ucvec3_print(stdout, v)*/
static size_t ucvec3_println(ucvec3 v) {
    return ucvec3_fprintln(stdout, v);
}

#endif //M_IO_UCVEC3_H
