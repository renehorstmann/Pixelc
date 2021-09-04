#ifndef MATHC_IO_FLOAT_H
#define MATHC_IO_FLOAT_H

#include <stdio.h>
#include <locale.h>
#include "../types/float.h"

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


static void vec2_print_f(vec2 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(vec2)" MATHC_PRINT_COLOR " {{");
    for (int v = 0; v < 2; v++) {
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

static void vec2_println_f(vec2 vec, FILE *ostream) {
    vec2_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void vec2_print(vec2 vec) {
    vec2_print_f(vec, stdout);
}

static void vec2_println(vec2 vec) {
    vec2_println_f(vec, stdout);
}

static void mat2_println_f(mat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "mat2: " MATHC_PRINT_COLOR "\n");
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

static void mat2_println(mat2 mat) {
    mat2_println_f(mat, stdout);
}

static void mat2_print_repr_f(mat2 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(mat2)" MATHC_PRINT_COLOR " {{");
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

static void mat2_println_repr_f(mat2 mat, FILE *ostream) {
    mat2_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void mat2_print_repr(mat2 mat) {
    mat2_print_repr_f(mat, stdout);
}

static void mat2_println_repr(mat2 mat) {
    mat2_println_repr_f(mat, stdout);
}


static void vec3_print_f(vec3 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(vec3) " MATHC_PRINT_COLOR "{{");
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

static void vec3_println_f(vec3 vec, FILE *ostream) {
    vec3_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void vec3_print(vec3 vec) {
    vec3_print_f(vec, stdout);
}

static void vec3_println(vec3 vec) {
    vec3_println_f(vec, stdout);
}


static void mat3_println_f(mat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "mat3: " MATHC_PRINT_COLOR "\n");
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

static void mat3_println(mat3 mat) {
    mat3_println_f(mat, stdout);
}

static void mat3_print_repr_f(mat3 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(mat3)" MATHC_PRINT_COLOR " {{");
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

static void mat3_println_repr_f(mat3 mat, FILE *ostream) {
    mat3_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void mat3_print_repr(mat3 mat) {
    mat3_print_repr_f(mat, stdout);
}

static void mat3_println_repr(mat3 mat) {
    mat3_println_repr_f(mat, stdout);
}

static void vec4_print_f(vec4 vec, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(vec4) " MATHC_PRINT_COLOR "{{");
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

static void vec4_println_f(vec4 vec, FILE *ostream) {
    vec4_print_f(vec, ostream);
    fputc('\n', ostream);
}

static void vec4_print(vec4 vec) {
    vec4_print_f(vec, stdout);
}

static void vec4_println(vec4 vec) {
    vec4_println_f(vec, stdout);
}


static void mat4_println_f(mat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "mat4: " MATHC_PRINT_COLOR "\n");
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

static void mat4_println(mat4 mat) {
    mat4_println_f(mat, stdout);
}

static void mat4_print_repr_f(mat4 mat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(mat4)" MATHC_PRINT_COLOR " {{");
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

static void mat4_println_repr_f(mat4 mat, FILE *ostream) {
    mat4_print_repr_f(mat, ostream);
    fputc('\n', ostream);
}

static void mat4_print_repr(mat4 mat) {
    mat4_print_repr_f(mat, stdout);
}

static void mat4_println_repr(mat4 mat) {
    mat4_println_repr_f(mat, stdout);
}


//
// quat
//

static void quat_print_f(quat quat, FILE *ostream) {
    char *local_save = setlocale(LC_ALL, "C");
    fprintf(ostream, "(quat) " MATHC_PRINT_COLOR "{{");
    for (int v = 0; v < 4; v++) {
        if(v>0)
            fputc(',', ostream);
        if (quat.v[v] < MATHC_PRINT_MAX_TO_SHORT)
            fprintf(ostream, " %.*f", MATHC_PRINT_PRECISION, quat.v[v]);
        else
            fprintf(ostream, " %g", quat.v[v]);
    }
    fprintf(ostream, " }}" MATHC_PRINT_COLOR_RESET);
    setlocale(LC_ALL, local_save);
}

static void quat_println_f(quat quat, FILE *ostream) {
    quat_print_f(quat, ostream);
    fputc('\n', ostream);
}

static void quat_print(quat quat) {
    quat_print_f(quat, stdout);
}

static void quat_println(quat quat) {
    quat_println_f(quat, stdout);
}

#endif //MATHC_IO_FLOAT_H
