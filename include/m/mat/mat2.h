#ifndef M_MAT_MAT2_H
#define M_MAT_MAT2_H


#include "matn.h"
#include "../types/mat2.h"
#include "../vec/vecn.h"


/** dst = (mat2) v */
static mat2 mat2_cast_from_float(const float *cast) {
    mat2 res;
    matN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (mat2) v */
static mat2 mat2_cast_from_double(const double *cast) {
    mat2 res;
    matN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (mat2) v */
static mat2 mat2_cast_from_int(const int *cast) {
    mat2 res;
    matN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (mat2) v */
static mat2 mat2_cast_from_uchar(const unsigned char *cast) {
    mat2 res;
    matN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = v / 255 */
static mat2 mat2_cast_from_uchar_1(const unsigned char *cast) {
    mat2 res;
    matN_cast_from_uchar_1(res.v, cast, 2);
    return res;
}


/** dst = r==c ? 1 : 0 (identity)  */
static mat2 mat2_eye() {
    mat2 res;
    matN_eye(res.v, 2);
    return res;
}

/** a == b */
static bool mat2_cmp(mat2 a, mat2 b) {
    return vecN_cmp(a.v, b.v, 2 * 2);
}


/** dst = m[row][:] */
static vec2 mat2_get_row(mat2 m, int row) {
    vec2 res;
    matN_get_row(res.v, m.v, row, 2);
    return res;
}


/** dst = m[:][col] */
static vec2 mat2_get_col(mat2 m, int col) {
    vec2 res;
    matN_get_col(res.v, m.v, col, 2);
    return res;
}


/** dst = m; dst[row][:] = v */
static mat2 mat2_set_row(mat2 m, vec2 v, int row) {
    matN_set_row(m.v, v.v, row, 2);
    return m;
}

/** m[row][:] = v; dst = m */
static mat2 mat2_set_this_row(mat2 *m, vec2 v, int row) {
    matN_set_row(m->v, v.v, row, 2);
    return *m;
}

/** dst = m; dst[:][col] = v */
static mat2 mat2_set_col(mat2 m, vec2 v, int col) {
    matN_set_col(m.v, v.v, col, 2);
    return m;
}

/** mat[:][col] = v; dst = m */
static mat2 mat2_set_this_col(mat2 *mat, vec2 v, int col) {
    matN_set_col(mat->v, v.v, col, 2);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static mat2 mat2_set_row_sca(mat2 m, float s, int row) {
    matN_set_row_sca(m.v, s, row, 2);
    return m;
}

/** m[row][:] = s; dst = m */
static mat2 mat2_set_this_row_sca(mat2 *m, float s, int row) {
    matN_set_row_sca(m->v, s, row, 2);
    return *m;
}


/** dst = m; dst[:][col] = s */
static mat2 mat2_set_col_sca(mat2 m, float s, int col) {
    matN_set_col_sca(m.v, s, col, 2);
    return m;
}

/** m[:][col] = s; dst = m */
static mat2 mat2_set_this_col_sca(mat2 *m, float s, int col) {
    matN_set_col_sca(m->v, s, col, 2);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static float mat2_trace(mat2 m) {
    return matN_trace(m.v, 2);
}


/** dst = m^t */
static mat2 mat2_transpose(mat2 m) {
    mat2 res;
    matN_transpose_no_alias(res.v, m.v, 2);
    return res;
}


/** dst = a @ b */
static mat2 mat2_mul_mat(mat2 a, mat2 b) {
    mat2 res;
    matN_mul_mat_no_alias(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a @ b */
static vec2 mat2_mul_vec(mat2 a, vec2 b) {
    vec2 res;
    matN_mul_vec_no_alias(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a @ b */
static vec2 vec2_mul_mat(vec2 a, mat2 b) {
    vec2 res;
    vecN_mul_mat_no_alias(res.v, a.v, b.v, 2);
    return res;
}

/** returns = determinant m */
static float mat2_det(mat2 m) {
    // from cglm/mat2.h/glm_mat2_det
    return m.m[0][0] * m.m[1][1] - m.m[1][0] * m.m[0][1];
}


/** dst = inverted m */
static mat2 mat2_inv(mat2 m) {
    // from cglm/mat2.h/glm_mat2_inv
    float a = m.m[0][0], b = m.m[0][1];
    float c = m.m[1][0], d = m.m[1][1];

    mat2 res;
    res.m[0][0] = d;
    res.m[0][1] = -b;
    res.m[1][0] = -c;
    res.m[1][1] = a;

    float det = a * d - b * c;
    vecN_div(res.v, res.v, det, 4);

    return res;
}


#endif //M_MAT_MAT2_H
