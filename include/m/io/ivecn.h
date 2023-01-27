#ifndef M_IO_IVECN_H
#define M_IO_IVECN_H



#include <stdio.h>
#include <locale.h>

#include "../sca/int.h"
#include "terminalcolor.h"



/**
 * Example:
 * int v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * char buf[128];
 * ivecN_snprint(buf, sizeof buf, v, 5);
 * // (int[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t ivecN_snprint(char *str, size_t size, const int *v, int n) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(int[%i]) { ", n);
    for(int i=0; i<n; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" ISCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i<n-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }");
    return used;
}

/** Calls ivecN_snprint and adds a newline */
static size_t ivecN_snprintln(char *str, size_t size, const int *v, int n) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ivecN_snprint(str, size, v, n);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * int v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * ivecN_fprint(stdout, v, 5);
 * // (int[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t ivecN_fprint(FILE *stream, const int *v, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(int[%i]) ", n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for(int i=0; i<n; i++) {
        used += fprintf(stream,"%" ISCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i<n-1? ", " : "");
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ivecN_fprint and adds a newline */
static size_t ivecN_fprintln(FILE *stream, const int *v, int n) {
    size_t used = ivecN_fprint(stream, v, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ivecN_fprint(stdout, v, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * int v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * ivecN_print(v, 5);
 * // (int[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t ivecN_print(const int *v, int n) {
    return ivecN_fprint(stdout, v, n);
}

/** Calls ivecN_print and adds a newline (Just calls ivecN_fprintln(stdout, v, n)*/
static size_t ivecN_println(const int *v, int n) {
    return ivecN_fprintln(stdout, v, n);
}

#endif //M_IO_IVECN_H
