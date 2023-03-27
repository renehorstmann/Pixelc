#ifndef M_MAT_MAT3_H
#define M_MAT_MAT3_H


#include "matn.h"
#include "../types/mat3.h"
#include "../types/mat2.h"
#include "../vec/vecn.h"


/** dst = (mat3) v */
static mat3 mat3_cast_from_float(const float *cast) {
    mat3 res;
    matN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (mat3) v */
static mat3 mat3_cast_from_double(const double *cast) {
    mat3 res;
    matN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (mat3) v */
static mat3 mat3_cast_from_int(const int *cast) {
    mat3 res;
    matN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (mat3) v */
static mat3 mat3_cast_from_uchar(const unsigned char *cast) {
    mat3 res;
    matN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = v / 255 */
static mat3 mat3_cast_from_uchar_1(const unsigned char *cast) {
    mat3 res;
    matN_cast_from_uchar_1(res.v, cast, 3);
    return res;
}


/** dst = r==c ? 1 : 0 (identity)  */
static mat3 mat3_eye() {
    mat3 res;
    matN_eye(res.v, 3);
    return res;
}

/** a == b */
static bool mat3_cmp(mat3 a, mat3 b) {
    return vecN_cmp(a.v, b.v, 3 * 3);
}


/** dst = m[row][:] */
static vec3 mat3_get_row(mat3 m, int row) {
    vec3 res;
    matN_get_row(res.v, m.v, row, 3);
    return res;
}


/** dst = m[:][col] */
static vec3 mat3_get_col(mat3 m, int col) {
    vec3 res;
    matN_get_col(res.v, m.v, col, 3);
    return res;
}


/** dst = m; dst[row][:] = v */
static mat3 mat3_set_row(mat3 m, vec3 v, int row) {
    matN_set_row(m.v, v.v, row, 3);
    return m;
}

/** m[row][:] = v; dst = m */
static mat3 mat3_set_this_row(mat3 *m, vec3 v, int row) {
    matN_set_row(m->v, v.v, row, 3);
    return *m;
}

/** dst = m; dst[:][col] = v */
static mat3 mat3_set_col(mat3 m, vec3 v, int col) {
    matN_set_col(m.v, v.v, col, 3);
    return m;
}

/** mat[:][col] = v; dst = m */
static mat3 mat3_set_this_col(mat3 *mat, vec3 v, int col) {
    matN_set_col(mat->v, v.v, col, 3);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static mat3 mat3_set_row_sca(mat3 m, float s, int row) {
    matN_set_row_sca(m.v, s, row, 3);
    return m;
}

/** m[row][:] = s; dst = m */
static mat3 mat3_set_this_row_sca(mat3 *m, float s, int row) {
    matN_set_row_sca(m->v, s, row, 3);
    return *m;
}


/** dst = m; dst[:][col] = s */
static mat3 mat3_set_col_sca(mat3 m, float s, int col) {
    matN_set_col_sca(m.v, s, col, 3);
    return m;
}

/** m[:][col] = s; dst = m */
static mat3 mat3_set_this_col_sca(mat3 *m, float s, int col) {
    matN_set_col_sca(m->v, s, col, 3);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static float mat3_trace(mat3 m) {
    return matN_trace(m.v, 3);
}


/** dst = m^t */
static mat3 mat3_transpose(mat3 m) {
    mat3 res;
    matN_transpose_no_alias(res.v, m.v, 3);
    return res;
}


/** dst = a @ b */
static mat3 mat3_mul_mat(mat3 a, mat3 b) {
    mat3 res;
    matN_mul_mat_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a @ b */
static vec3 mat3_mul_vec(mat3 a, vec3 b) {
    vec3 res;
    matN_mul_vec_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a @ b */
static vec3 vec3_mul_mat(vec3 a, mat3 b) {
    vec3 res;
    vecN_mul_mat_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** returns = determinant m */
static float mat3_det(mat3 m) {
    // from cglm/mat3.h/glm_mat3_det
    float a = m.m[0][0], b = m.m[0][1], c = m.m[0][2];
    float d = m.m[1][0], e = m.m[1][1], f = m.m[1][2];
    float g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}


/** dst = inverted m */
static mat3 mat3_inv(mat3 m) {
    // from cglm/mat3.h/glm_mat3_inv
    float a = m.m[0][0], b = m.m[0][1], c = m.m[0][2];
    float d = m.m[1][0], e = m.m[1][1], f = m.m[1][2];
    float g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

    mat3 res;
    res.m[0][0] = e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] = b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] = a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] = d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] = a * e - b * d;

    float det = a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0];
    vecN_div(res.v, res.v, det, 9);

    return res;
}


/** dst = m[col:col+2, row:row+2] */
static mat2 mat3_get_block2(mat3 m, int row, int col) {
    mat2 res;
    matN_get_block(res.v, m.v, row, col, 2, 3);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static mat3 mat3_set_block2(mat3 m, mat2 block_2, int row, int col) {
    matN_set_block(m.v, block_2.v, row, col, 2, 3);
    return m;
}

/** m[col:col+2, row:row+2] = block; dst = m */
static mat3 mat3_set_this_block2(mat3 *m, mat2 block_2, int row, int col) {
    matN_set_block(m->v, block_2.v, row, col, 2, 3);
    return *m;
}


/** dst = m[:2, :2] */
static mat2 mat3_get_upper_left(mat3 m) {
    return mat3_get_block2(m, 0, 0);
}


/** dst = m; dst[:2, :2] = block */
static mat3 mat3_set_upper_left(mat3 m, mat2 block_2) {
    return mat3_set_block2(m, block_2, 0, 0);
}


/** m[:2, :2] = block; dst = m */
static mat3 mat3_set_this_upper_left(mat3 *m, mat2 block_2) {
    return mat3_set_this_block2(m, block_2, 0, 0);
}


#endif //M_MAT_MAT3_H
