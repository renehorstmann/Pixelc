#ifndef M_IO_IVEC3_H
#define M_IO_IVEC3_H


#include <stdio.h>
#include <locale.h>

#include "../sca/int.h"
#include "../types/ivec3.h"
#include "terminalcolor.h"


/**
 * Example:
 * ivec3 v = ivec3_unit_x();
 * char buf[128];
 * ivec3_snprint(buf, sizeof buf, v);
 * // (ivec3) {{ 1.0, 0.0, ...}}
 */
static size_t ivec3_snprint(char *str, size_t size, ivec3 v) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(ivec3) {{ ");
    for(int i=0; i<3; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<3-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }}");
    return used;
}

/** Calls ivec3_snprint and adds a newline */
static size_t ivec3_snprintln(char *str, size_t size, ivec3 v) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ivec3_snprint(str, size, v);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ivec3 v = ivec3_unit_x();
 * ivec3_fprint(stdout, v);
 * // (ivec3) {{ 1.0, 0.0, ...}}
 */
static size_t ivec3_fprint(FILE *stream, ivec3 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(ivec3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for(int i=0; i<3; i++) {
        used += fprintf(stream,"%" ISCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<3-1? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ivec3_fprint and adds a newline */
static size_t ivec3_fprintln(FILE *stream, ivec3 v) {
    size_t used = ivec3_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ivec3_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * ivec3 v = ivec3_unit_x();
 * ivec3_print(v);
 * // (ivec3) {{ 1.0, 0.0, ...}}
 */
static size_t ivec3_print(ivec3 v) {
    return ivec3_fprint(stdout, v);
}

/** Calls ivecN_print and adds a newline (Just calls ivec3_print(stdout, v)*/
static size_t ivec3_println(ivec3 v) {
    return ivec3_fprintln(stdout, v);
}

#endif //M_IO_IVEC3_H
