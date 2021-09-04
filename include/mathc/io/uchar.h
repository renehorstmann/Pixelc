#ifndef MATHC_IO_UCHAR_H
#define MATHC_IO_UCHAR_H

#include <stdio.h>
#include <locale.h>
#include "../types/uchar.h"

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


static void ucvec2_print_f(ucvec2 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ucvec2) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 2; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ucvec2_println_f(ucvec2 vec, FILE *ostream) {
    ucvec2_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void ucvec2_print(ucvec2 vec) {
    ucvec2_print_f(vec, stdout);
}

static void ucvec2_println(ucvec2 vec) {
    ucvec2_println_f(vec, stdout);
}


static void ucmat2_println_f(ucmat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "ucmat2: " MATHC_PRINT_COLOR "\n");
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

static void ucmat2_println(ucmat2 ucmat) {
    ucmat2_println_f(ucmat, stdout);
}

static void ucmat2_print_repr_f(ucmat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ucmat2)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ucmat2_println_repr_f(ucmat2 mat, FILE *ostream) {
    ucmat2_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void ucmat2_print_repr(ucmat2 mat) {
    ucmat2_print_repr_f(mat, stdout);
}

static void ucmat2_println_repr(ucmat2 mat) {
    ucmat2_println_repr_f(mat, stdout);
}


static void ucvec3_print_f(ucvec3 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ucvec3) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 3; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ucvec3_println_f(ucvec3 vec, FILE *ostream) {
    ucvec3_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void ucvec3_print(ucvec3 vec) {
    ucvec3_print_f(vec, stdout);
}

static void ucvec3_println(ucvec3 vec) {
    ucvec3_println_f(vec, stdout);
}

static void ucmat3_println_f(ucmat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "ucmat3: " MATHC_PRINT_COLOR "\n");
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

static void ucmat3_println(ucmat3 ucmat) {
    ucmat3_println_f(ucmat, stdout);
}

static void ucmat3_print_repr_f(ucmat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ucmat3)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 9; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ucmat3_println_repr_f(ucmat3 mat, FILE *ostream) {
    ucmat3_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void ucmat3_print_repr(ucmat3 mat) {
    ucmat3_print_repr_f(mat, stdout);
}

static void ucmat3_println_repr(ucmat3 mat) {
    ucmat3_println_repr_f(mat, stdout);
}

static void ucvec4_print_f(ucvec4 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ucvec4) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ucvec4_println_f(ucvec4 vec, FILE *ostream) {
    ucvec4_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void ucvec4_print(ucvec4 vec) {
    ucvec4_print_f(vec, stdout);
}

static void ucvec4_println(ucvec4 vec) {
    ucvec4_println_f(vec, stdout);
}

static void ucmat4_println_f(ucmat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "ucmat4: " MATHC_PRINT_COLOR "\n");
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

static void ucmat4_println(ucmat4 ucmat) {
    ucmat4_println_f(ucmat, stdout);
}

static void ucmat4_print_repr_f(ucmat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(ucmat4)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 16; v++) {
        if(v>0)
            fputc(',', ostream);
        fprintf(ostream, " %u", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void ucmat4_println_repr_f(ucmat4 mat, FILE *ostream) {
    ucmat4_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void ucmat4_print_repr(ucmat4 mat) {
    ucmat4_print_repr_f(mat, stdout);
}

static void ucmat4_println_repr(ucmat4 mat) {
    ucmat4_println_repr_f(mat, stdout);
}


#endif //MATHC_IO_UCHAR_H
