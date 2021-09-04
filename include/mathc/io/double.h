#ifndef MATHC_IO_DOUBLE_H
#define MATHC_IO_DOUBLE_H

#include <stdio.h>
#include <locale.h>
#include "../types/double.h"

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

static void dvec2_print_f(dvec2 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(dvec2) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 2; v++) {
        if(v>0)
            fputc(',', ostream);
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " )" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void dvec2_println_f(dvec2 vec, FILE *ostream) {
    dvec2_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void dvec2_print(dvec2 vec) {
    dvec2_print_f(vec, stdout);
}

static void dvec2_println(dvec2 vec) {
    dvec2_println_f(vec, stdout);
}

static void dmat2_println_f(dmat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "dmat2: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 2; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 2; c++)
            if (mat.m[c][r] < MATHC_PRINT_MAX_TO_SHORT)
                fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.m[c][r]);
            else
                fprintf(ostream, " %g", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
#ifndef MATHC_NO_PRINT_COLOR
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
#endif
    setlocale(LC_ALL, local_save);
}

static void dmat2_println(dmat2 mat) {
    dmat2_println_f(mat, stdout);
}

static void dmat2_print_repr_f(dmat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(dmat2)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        if (mat.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.v[v]);
        else
            fprintf(ostream, " %g", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void dmat2_println_repr_f(dmat2 mat, FILE *ostream) {
    dmat2_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void dmat2_print_repr(dmat2 mat) {
    dmat2_print_repr_f(mat, stdout);
}

static void dmat2_println_repr(dmat2 mat) {
    dmat2_println_repr_f(mat, stdout);
}


static void dvec3_print_f(dvec3 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(dvec3) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 3; v++) {
        if(v>0)
            fputc(',', ostream);
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void dvec3_println_f(dvec3 vec, FILE *ostream) {
    dvec3_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void dvec3_print(dvec3 vec) {
    dvec3_print_f(vec, stdout);
}

static void dvec3_println(dvec3 vec) {
    dvec3_println_f(vec, stdout);
}

static void dmat3_println_f(dmat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "dmat3: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 3; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 3; c++)
            if (mat.m[c][r] < MATHC_PRINT_MAX_TO_SHORT)
                fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.m[c][r]);
            else
                fprintf(ostream, " %g", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
#ifndef MATHC_NO_PRINT_COLOR
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
#endif
    setlocale(LC_ALL, local_save);
}

static void dmat3_println(dmat3 mat) {
    dmat3_println_f(mat, stdout);
}

static void dmat3_print_repr_f(dmat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(dmat3)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 9; v++) {
        if(v>0)
            fputc(',', ostream);
        if (mat.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.v[v]);
        else
            fprintf(ostream, " %g", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void dmat3_println_repr_f(dmat3 mat, FILE *ostream) {
    dmat3_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void dmat3_print_repr(dmat3 mat) {
    dmat3_print_repr_f(mat, stdout);
}

static void dmat3_println_repr(dmat3 mat) {
    dmat3_println_repr_f(mat, stdout);
}

static void dvec4_print_f(dvec4 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(dvec4) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        if (vec.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, vec.v[v]);
        else
            fprintf(ostream, " %g", vec.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void dvec4_println_f(dvec4 vec, FILE *ostream) {
    dvec4_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void dvec4_print(dvec4 vec) {
    dvec4_print_f(vec, stdout);
}

static void dvec4_println(dvec4 vec) {
    dvec4_println_f(vec, stdout);
}

static void dmat4_println_f(dmat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "dmat4: " MATHC_PRINT_COLOR "\n");
    for (int r = 0; r < 4; r++) {
        fprintf(ostream, "  |");
        for (int c = 0; c < 4; c++)
            if (mat.m[c][r] < MATHC_PRINT_MAX_TO_SHORT)
                fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.m[c][r]);
            else
                fprintf(ostream, " %g", mat.m[c][r]);

        fprintf(ostream, " |\n");
    }
#ifndef MATHC_NO_PRINT_COLOR
    fprintf(ostream, MATHC_PRINT_COLOR_RESET);
#endif
    setlocale(LC_ALL, local_save);
}

static void dmat4_println(dmat4 mat) {
    dmat4_println_f(mat, stdout);
}

static void dmat4_print_repr_f(dmat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(dmat4)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 16; v++) {
        if(v>0)
            fputc(',', ostream);
        if (mat.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, mat.v[v]);
        else
            fprintf(ostream, " %g", mat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void dmat4_println_repr_f(dmat4 mat, FILE *ostream) {
    dmat4_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void dmat4_print_repr(dmat4 mat) {
    dmat4_print_repr_f(mat, stdout);
}

static void dmat4_println_repr(dmat4 mat) {
    dmat4_println_repr_f(mat, stdout);
}


//
// quat
//

static void dquat_print_f(dquat quat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(dquat) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 4; v++) {
        if (quat.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, quat.v[v]);
        else
            fprintf(ostream, " %g", quat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void dquat_println_f(dquat quat, FILE *ostream) {
    dquat_print_f(quat, ostream);
    fputc('\n', ostream);
}

static void dquat_print(dquat quat) {
    dquat_print_f(quat, stdout);
}

static void dquat_println(dquat quat) {
    dquat_println_f(quat, stdout);
}

#endif //MATHC_IO_DOUBLE_H
