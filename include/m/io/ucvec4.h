#ifndef M_IO_UCVEC4_H
#define M_IO_UCVEC4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/uchar.h"
#include "../types/ucvec4.h"
#include "terminalcolor.h"


/**
 * Example:
 * ucvec4 v = ucvec4_unit_x();
 * char buf[128];
 * ucvec4_snprint(buf, sizeof buf, v);
 * // (ucvec4) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec4_snprint(char *str, size_t size, ucvec4 v) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ucvec4) {{ ");
    for(int i=0; i<4; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<4-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }}");
    return used;
}

/** Calls ucvec4_snprint and adds a newline */
static size_t ucvec4_snprintln(char *str, size_t size, ucvec4 v) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucvec4_snprint(str, size, v);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucvec4 v = ucvec4_unit_x();
 * ucvec4_fprint(stdout, v);
 * // (ucvec4) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec4_fprint(FILE *stream, ucvec4 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ucvec4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for(int i=0; i<4; i++) {
        used += fprintf(stream,"%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<4-1? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucvec4_fprint and adds a newline */
static size_t ucvec4_fprintln(FILE *stream, ucvec4 v) {
    size_t used = ucvec4_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ucvec4_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ucvec4 v = ucvec4_unit_x();
 * ucvec4_print(v);
 * // (ucvec4) {{ 1.0, 0.0, ...}}
 */
static size_t ucvec4_print(ucvec4 v) {
    return ucvec4_fprint(stdout, v);
}

/** Calls ucvecN_print and adds a newline (Just calls ucvec4_print(stdout, v)*/
static size_t ucvec4_println(ucvec4 v) {
    return ucvec4_fprintln(stdout, v);
}

#endif //M_IO_UCVEC4_H
