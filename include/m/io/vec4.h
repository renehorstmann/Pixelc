#ifndef M_IO_VEC4_H
#define M_IO_VEC4_H


#include <stdio.h>
#include <locale.h>

#include "../sca/float.h"
#include "../types/vec4.h"
#include "terminalcolor.h"


/**
 * Example:
 * vec4 v = vec4_unit_x();
 * char buf[128];
 * vec4_snprint(buf, sizeof buf, v);
 * // (vec4) {{ 1.0, 0.0, ...}}
 */
static size_t vec4_snprint(char *str, size_t size, vec4 v) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(vec4) {{ ");
    for(int i=0; i<4; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" SCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<4-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }}");
    return used;
}

/** Calls vec4_snprint and adds a newline */
static size_t vec4_snprintln(char *str, size_t size, vec4 v) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = vec4_snprint(str, size, v);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * vec4 v = vec4_unit_x();
 * vec4_fprint(stdout, v);
 * // (vec4) {{ 1.0, 0.0, ...}}
 */
static size_t vec4_fprint(FILE *stream, vec4 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(vec4) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for(int i=0; i<4; i++) {
        used += fprintf(stream,"%" SCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<4-1? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls vec4_fprint and adds a newline */
static size_t vec4_fprintln(FILE *stream, vec4 v) {
    size_t used = vec4_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls vec4_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * vec4 v = vec4_unit_x();
 * vec4_print(v);
 * // (vec4) {{ 1.0, 0.0, ...}}
 */
static size_t vec4_print(vec4 v) {
    return vec4_fprint(stdout, v);
}

/** Calls vecN_print and adds a newline (Just calls vec4_print(stdout, v)*/
static size_t vec4_println(vec4 v) {
    return vec4_fprintln(stdout, v);
}

#endif //M_IO_VEC4_H
