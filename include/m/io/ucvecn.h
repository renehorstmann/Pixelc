#ifndef M_IO_UCVECN_H
#define M_IO_UCVECN_H



#include <stdio.h>
#include <locale.h>

#include "../sca/uchar.h"
#include "terminalcolor.h"



/**
 * Example:
 * unsigned char v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * char buf[128];
 * ucvecN_snprint(buf, sizeof buf, v, 5);
 * // (unsigned char[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t ucvecN_snprint(char *str, size_t size, const unsigned char *v, int n) {
    setlocale(LC_ALL, "C");
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = 0;
    used += snprintf(str, size, "(unsigned char[%i]) { ", n);
    for(int i=0; i<n; i++) {
        used += snprintf(!str? NULL : str+used, !size? 0 : size - used,
                         "%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i<n-1? ", " : "");
    }
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, " }");
    return used;
}

/** Calls ucvecN_snprint and adds a newline */
static size_t ucvecN_snprintln(char *str, size_t size, const unsigned char *v, int n) {
    if(!str || !size) {
        str = NULL;
        size = 0;
    }
    size_t used = ucvecN_snprint(str, size, v, n);
    used += snprintf(!str? NULL : str+used, !size? 0 : size - used, "\n");
    return used;
}

/**
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * unsigned char v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * ucvecN_fprint(stdout, v, 5);
 * // (unsigned char[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t ucvecN_fprint(FILE *stream, const unsigned char *v, int n) {
    setlocale(LC_ALL, "C");
    size_t used = 0;
    used += fprintf(stream, "(unsigned char[%i]) ", n);
#ifndef M_NO_PRINT_COLOR
    m_terminalcolor_start();
    used += fprintf(stream, M_TERMINALCOLOR_CYAN);
#endif
    used += fprintf(stream, "{ ");
    for(int i=0; i<n; i++) {
        used += fprintf(stream,"%" UCSCA_PRINT_FORMAT_SPECIFIER "%s", v[i], i<n-1? ", " : "");
    }
    used += fprintf(stream, " }");
#ifndef M_NO_PRINT_COLOR
    used += fprintf(stream, M_TERMINALCOLOR_RESET);
    m_terminalcolor_stop();
#endif
    return used;
}

/** Calls ucvecN_fprint and adds a newline */
static size_t ucvecN_fprintln(FILE *stream, const unsigned char *v, int n) {
    size_t used = ucvecN_fprint(stream, v, n);
    used += fprintf(stream, "\n");
    return used;
}

/**
 * Calls ucvecN_fprint(stdout, v, n)
 * Uses terminal colors, unless M_NO_PRINT_COLOR is set
 * Example:
 * unsigned char v[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
 * ucvecN_print(v, 5);
 * // (unsigned char[5]) { 1.1, 2.2, 3.3, 4.4, 5.5 }
 */
static size_t ucvecN_print(const unsigned char *v, int n) {
    return ucvecN_fprint(stdout, v, n);
}

/** Calls ucvecN_print and adds a newline (Just calls ucvecN_fprintln(stdout, v, n)*/
static size_t ucvecN_println(const unsigned char *v, int n) {
    return ucvecN_fprintln(stdout, v, n);
}

#endif //M_IO_UCVECN_H
