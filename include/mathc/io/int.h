#ifndef MATHC_IO_INT_H
#define MATHC_IO_INT_H

#include <stdio.h>
#include <locale.h>
#include "../types/int.h"

//
// from cglm/io.h
//

#ifndef MATHC_PRINT_PRECISION
#  define MATHC_PRINT_PRECISION 5
#endif

#ifndef MATHC_PRINT_MAX_TO_SHORT
#  define MATHC_PRINT_MAX_TO_SHORT 1e5
#endif

#ifdef MATHC_NO_PRINT_COLOR
#define MATHC_PRINT_COLOR ""
#define MATHC_PRINT_COLOR_RESET ""
#endif

#ifndef MATHC_PRINT_COLOR
#  define MATHC_PRINT_COLOR "\033[36m"
#endif

#ifndef MATHC_PRINT_COLOR_RESET
#  define MATHC_PRINT_COLOR_RESET "\033[0m"
#endif


static void ivec2_print_f(ivec2 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ivec2) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 2; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ivec2_println_f(ivec2 vec, FILE *ostream) {
    ivec2_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void ivec2_print(ivec2 vec) {
    ivec2_print_f(vec, stdout);
}

static void ivec2_println(ivec2 vec) {
    ivec2_println_f(vec, stdout);
}


static void imat2_println_f(imat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "imat2: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 2; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 2; c++)
            fprintf(ostream, " %i", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void imat2_println(imat2 imat) {
    imat2_println_f(imat, stdout);
}

static void imat2_print_repr_f(imat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(imat2)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void imat2_println_repr_f(imat2 mat, FILE *ostream) {
    imat2_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void imat2_print_repr(imat2 mat) {
    imat2_print_repr_f(mat, stdout);
}

static void imat2_println_repr(imat2 mat) {
    imat2_println_repr_f(mat, stdout);
}


static void ivec3_print_f(ivec3 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ivec3) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 3; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ivec3_println_f(ivec3 vec, FILE *ostream) {
    ivec3_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void ivec3_print(ivec3 vec) {
    ivec3_print_f(vec, stdout);
}

static void ivec3_println(ivec3 vec) {
    ivec3_println_f(vec, stdout);
}

static void imat3_println_f(imat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "imat3: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 3; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 3; c++)
            fprintf(ostream, " %i", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void imat3_println(imat3 imat) {
    imat3_println_f(imat, stdout);
}

static void imat3_print_repr_f(imat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(imat3)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 9; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void imat3_println_repr_f(imat3 mat, FILE *ostream) {
    imat3_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void imat3_print_repr(imat3 mat) {
    imat3_print_repr_f(mat, stdout);
}

static void imat3_println_repr(imat3 mat) {
    imat3_println_repr_f(mat, stdout);
}

static void ivec4_print_f(ivec4 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ivec4) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ivec4_println_f(ivec4 vec, FILE *ostream) {
    ivec4_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void ivec4_print(ivec4 vec) {
    ivec4_print_f(vec, stdout);
}

static void ivec4_println(ivec4 vec) {
    ivec4_println_f(vec, stdout);
}

static void imat4_println_f(imat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "imat4: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 4; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 4; c++)
            fprintf(ostream, " %i", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void imat4_println(imat4 imat) {
    imat4_println_f(imat, stdout);
}

static void imat4_print_repr_f(imat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(imat4)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 16; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void imat4_println_repr_f(imat4 mat, FILE *ostream) {
    imat4_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void imat4_print_repr(imat4 mat) {
    imat4_print_repr_f(mat, stdout);
}

static void imat4_println_repr(imat4 mat) {
    imat4_println_repr_f(mat, stdout);
}


#endif //MATHC_IO_INT_H
