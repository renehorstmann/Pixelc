#ifndef MATHC_IO_UINT_H
#define MATHC_IO_UINT_H

#include <stdio.h>
#include <locale.h>
#include "../types/uint.h"

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


static void uvec2_print_f(uvec2 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(uvec2) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 2; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void uvec2_println_f(uvec2 vec, FILE *ostream) {
    uvec2_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void uvec2_print(uvec2 vec) {
    uvec2_print_f(vec, stdout);
}

static void uvec2_println(uvec2 vec) {
    uvec2_println_f(vec, stdout);
}


static void umat2_println_f(umat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "umat2: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 2; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 2; c++)
            fprintf(ostream, " %u", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
#ifndef MATHC_NO_PRINT_COLOR
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
#endif
    setlocale(LC_ALL, local_save);
}

static void umat2_println(umat2 umat) {
    umat2_println_f(umat, stdout);
}

static void umat2_print_repr_f(umat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(umat2)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void umat2_println_repr_f(umat2 mat, FILE *ostream) {
    umat2_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void umat2_print_repr(umat2 mat) {
    umat2_print_repr_f(mat, stdout);
}

static void umat2_println_repr(umat2 mat) {
    umat2_println_repr_f(mat, stdout);
}


static void uvec3_print_f(uvec3 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(uvec3) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 3; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void uvec3_println_f(uvec3 vec, FILE *ostream) {
    uvec3_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void uvec3_print(uvec3 vec) {
    uvec3_print_f(vec, stdout);
}

static void uvec3_println(uvec3 vec) {
    uvec3_println_f(vec, stdout);
}

static void umat3_println_f(umat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "umat3: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 3; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 3; c++)
            fprintf(ostream, " %u", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
#ifndef MATHC_NO_PRINT_COLOR
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
#endif
    setlocale(LC_ALL, local_save);
}

static void umat3_println(umat3 umat) {
    umat3_println_f(umat, stdout);
}

static void umat3_print_repr_f(umat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(umat3)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 9; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void umat3_println_repr_f(umat3 mat, FILE *ostream) {
    umat3_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void umat3_print_repr(umat3 mat) {
    umat3_print_repr_f(mat, stdout);
}

static void umat3_println_repr(umat3 mat) {
    umat3_println_repr_f(mat, stdout);
}

static void uvec4_print_f(uvec4 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(uvec4) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void uvec4_println_f(uvec4 vec, FILE *ostream) {
    uvec4_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void uvec4_print(uvec4 vec) {
    uvec4_print_f(vec, stdout);
}

static void uvec4_println(uvec4 vec) {
    uvec4_println_f(vec, stdout);
}

static void umat4_println_f(umat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "umat4: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 4; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 4; c++)
            fprintf(ostream, " %u", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
#ifndef MATHC_NO_PRINT_COLOR
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
#endif
    setlocale(LC_ALL, local_save);
}

static void umat4_println(umat4 umat) {
    umat4_println_f(umat, stdout);
}

static void umat4_print_repr_f(umat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(umat4)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 16; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void umat4_println_repr_f(umat4 mat, FILE *ostream) {
    umat4_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void umat4_print_repr(umat4 mat) {
    umat4_print_repr_f(mat, stdout);
}

static void umat4_println_repr(umat4 mat) {
    umat4_println_repr_f(mat, stdout);
}


#endif //MATHC_IO_UINT_H
