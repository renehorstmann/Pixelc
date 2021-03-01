#ifndef MATHC_IO_CHAR_H
#define MATHC_IO_CHAR_H

#include <stdio.h>
#include <locale.h>
#include "../types/char.h"

//
// from cglm/io.h
//

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


static void cvec2_print_f(cvec2 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(cvec2) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 2; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cvec2_println_f(cvec2 vec, FILE *ostream) {
    cvec2_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void cvec2_print(cvec2 vec) {
    cvec2_print_f(vec, stdout);
}

static void cvec2_println(cvec2 vec) {
    cvec2_println_f(vec, stdout);
}


static void cmat2_println_f(cmat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "cmat2: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 2; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 2; c++)
            fprintf(ostream, " %i", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cmat2_println(cmat2 cmat) {
    cmat2_println_f(cmat, stdout);
}

static void cmat2_print_repr_f(cmat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(cmat2)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cmat2_println_repr_f(cmat2 mat, FILE *ostream) {
    cmat2_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void cmat2_print_repr(cmat2 mat) {
    cmat2_print_repr_f(mat, stdout);
}

static void cmat2_println_repr(cmat2 mat) {
    cmat2_println_repr_f(mat, stdout);
}


static void cvec3_print_f(cvec3 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(cvec3) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 3; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cvec3_println_f(cvec3 vec, FILE *ostream) {
    cvec3_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void cvec3_print(cvec3 vec) {
    cvec3_print_f(vec, stdout);
}

static void cvec3_println(cvec3 vec) {
    cvec3_println_f(vec, stdout);
}

static void cmat3_println_f(cmat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "cmat3: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 3; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 3; c++)
            fprintf(ostream, " %i", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cmat3_println(cmat3 cmat) {
    cmat3_println_f(cmat, stdout);
}

static void cmat3_print_repr_f(cmat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(cmat3)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 9; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cmat3_println_repr_f(cmat3 mat, FILE *ostream) {
    cmat3_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void cmat3_print_repr(cmat3 mat) {
    cmat3_print_repr_f(mat, stdout);
}

static void cmat3_println_repr(cmat3 mat) {
    cmat3_println_repr_f(mat, stdout);
}

static void cvec4_print_f(cvec4 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(cvec4) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cvec4_println_f(cvec4 vec, FILE *ostream) {
    cvec4_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void cvec4_print(cvec4 vec) {
    cvec4_print_f(vec, stdout);
}

static void cvec4_println(cvec4 vec) {
    cvec4_println_f(vec, stdout);
}

static void cmat4_println_f(cmat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "cmat4: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 4; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 4; c++)
            fprintf(ostream, " %i", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cmat4_println(cmat4 cmat) {
    cmat4_println_f(cmat, stdout);
}

static void cmat4_print_repr_f(cmat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(cmat4)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 16; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %i", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void cmat4_println_repr_f(cmat4 mat, FILE *ostream) {
    cmat4_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void cmat4_print_repr(cmat4 mat) {
    cmat4_print_repr_f(mat, stdout);
}

static void cmat4_println_repr(cmat4 mat) {
    cmat4_println_repr_f(mat, stdout);
}


#endif //MATHC_IO_CHAR_H
