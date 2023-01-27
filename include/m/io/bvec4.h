#ifndef M_IO_BVEC4_H
#define M_IO_BVEC4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/bool.h"
#include "../types/bvec4.h"
#include "terminalcolor.h"


/**
 * Example:
 * bvec4 v = bvec4_unit_x();
 * char buf[128];
 * bvec4_snprint(buf, sizeof buf, v);
 * // (bvec4) {{ 1.0, 0.0, ...}}
 */
static size_t bvec4_snprint(char *str, size_t size, bvec4 v) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(bvec4) {{ ");
    for(int i=0; i<4; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" BSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<4-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }}");
    return used;
}

/** Calls bvec4_snprint and adds a newline */
static size_t bvec4_snprintln(char *str, size_t size, bvec4 v) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = bvec4_snprint(str, size, v);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * bvec4 v = bvec4_unit_x();
 * bvec4_fprint(stdout, v);
 * // (bvec4) {{ 1.0, 0.0, ...}}
 */
static size_t bvec4_fprint(FILE *stream, bvec4 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(bvec4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for(int i=0; i<4; i++) {
        used += fprintf(stream,"%" BSCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<4-1? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls bvec4_fprint and adds a newline */
static size_t bvec4_fprintln(FILE *stream, bvec4 v) {
    size_t used = bvec4_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls bvec4_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * bvec4 v = bvec4_unit_x();
 * bvec4_print(v);
 * // (bvec4) {{ 1.0, 0.0, ...}}
 */
static size_t bvec4_print(bvec4 v) {
    return bvec4_fprint(stdout, v);
}

/** Calls bvecN_print and adds a newline (Just calls bvec4_print(stdout, v)*/
static size_t bvec4_println(bvec4 v) {
    return bvec4_fprintln(stdout, v);
}

#endif //M_IO_BVEC4_H
