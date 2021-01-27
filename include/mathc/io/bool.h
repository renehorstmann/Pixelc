#ifndef MATHC_IO_BOOL_H
#define MATHC_IO_BOOL_H

#include <stdio.h>
#include <locale.h>
#include "../types/bool.h"

//
// from cglm/io.h
//

#ifndef MATHC_PRINT_PRECISION
#  define MATHC_PRINT_PRECISION 5
#endif

#ifndef MATHC_PRINT_MAX_TO_SHORT
#  define MATHC_PRINT_MAX_TO_SHORT 1e5
#endif

#ifndef MATHC_PRINT_COLOR
#  define MATHC_PRINT_COLOR "\033[36m"
#endif

#ifndef MATHC_PRINT_COLOR_RESET
#  define MATHC_PRINT_COLOR_RESET "\033[0m"
#endif

static void bvec2_print_f(bvec2 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(bvec2) " MATHC_PRINT_COLOR "{{");
    for(int v=0; v<2; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void bvec2_println_f(bvec2 vec, FILE *ostream) {
    bvec2_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void bvec2_print(bvec2 vec) {
    bvec2_print_f(vec, stdout);
}

static void bvec2_println(bvec2 vec) {
    bvec2_println_f(vec, stdout);
}

static void bvec3_print_f(bvec3 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(bvec3) " MATHC_PRINT_COLOR "{{");
    for(int v=0; v<3; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void bvec3_println_f(bvec3 vec, FILE *ostream) {
    bvec3_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void bvec3_print(bvec3 vec) {
    bvec3_print_f(vec, stdout);
}

static void bvec3_println(bvec3 vec) {
    bvec3_println_f(vec, stdout);
}

static void bvec4_print_f(bvec4 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(bvec4) " MATHC_PRINT_COLOR "{{");
    for(int v=0; v<4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void bvec4_println_f(bvec4 vec, FILE *ostream) {
    bvec4_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void bvec4_print(bvec4 vec) {
    bvec4_print_f(vec, stdout);
}

static void bvec4_println(bvec4 vec) {
    bvec4_println_f(vec, stdout);
}

#endif //MATHC_IO_BOOL_H
