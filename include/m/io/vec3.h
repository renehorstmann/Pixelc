#ifndef M_IO_VEC3_H
#define M_IO_VEC3_H


#include <stdio.h>
#include <locale.h>

#include "../sca/float.h"
#include "../types/vec3.h"
#include "terminalcolor.h"


/**
 * Example:
 * vec3 v = vec3_unit_x();
 * char buf[128];
 * vec3_snprint(buf, sizeof buf, v);
 * // (vec3) {{ 1.0, 0.0, ...}}
 */
static size_t vec3_snprint(char *str, size_t size, vec3 v) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(vec3) {{ ");
    for(int i=0; i<3; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" SCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<3-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }}");
    return used;
}

/** Calls vec3_snprint and adds a newline */
static size_t vec3_snprintln(char *str, size_t size, vec3 v) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = vec3_snprint(str, size, v);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * vec3 v = vec3_unit_x();
 * vec3_fprint(stdout, v);
 * // (vec3) {{ 1.0, 0.0, ...}}
 */
static size_t vec3_fprint(FILE *stream, vec3 v) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(vec3) ");
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{{ ");
    for(int i=0; i<3; i++) {
        used += fprintf(stream,"%" SCA_PRINT_FORMAT_SPECIFIER "%s", v.v[i], i<3-1? ", " : "");
    }
    used += fprintf(stream, " }}");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls vec3_fprint and adds a newline */
static size_t vec3_fprintln(FILE *stream, vec3 v) {
    size_t used = vec3_fprint(stream, v);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls vec3_fprint(stdout, v)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * vec3 v = vec3_unit_x();
 * vec3_print(v);
 * // (vec3) {{ 1.0, 0.0, ...}}
 */
static size_t vec3_print(vec3 v) {
    return vec3_fprint(stdout, v);
}

/** Calls vecN_print and adds a newline (Just calls vec3_print(stdout, v)*/
static size_t vec3_println(vec3 v) {
    return vec3_fprintln(stdout, v);
}

#endif //M_IO_VEC3_H
