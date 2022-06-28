#ifndef M_MAT_MAT4_H
#define M_MAT_MAT4_H


#include "matn.h"
#include "../types/mat4.h"
#include "../types/mat2.h"
#include "../types/mat3.h"
#include "../vec/vecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static mat4 mat4_eye() {
    mat4 res;
    matN_eye(res.v, 4);
    return res;
}

/** a == b */
static bool mat4_cmp(mat4 a, mat4 b) {
    return vecN_cmp(a.v, b.v, 4 * 4);
}


/** dst = m[row][:] */
static vec4 mat4_get_row(mat4 m, int row) {
    vec4 res;
    matN_get_row(res.v, m.v, row, 4);
    return res;
}


/** dst = m[:][col] */
static vec4 mat4_get_col(mat4 m, int col) {
    vec4 res;
    matN_get_col(res.v, m.v, col, 4);
    return res;
}


/** dst = m; dst[row][:] = v */
static mat4 mat4_set_row(mat4 m, vec4 v, int row) {
    matN_set_row(m.v, v.v, row, 4);
    return m;
}

/** m[row][:] = v; dst = m */
static mat4 mat4_set_this_row(mat4 *m, vec4 v, int row) {
    matN_set_row(m->v, v.v, row, 4);
    return *m;
}

/** dst = m; dst[:][col] = v */
static mat4 mat4_set_col(mat4 m, vec4 v, int col) {
    matN_set_col(m.v, v.v, col, 4);
    return m;
}

/** mat[:][col] = v; dst = m */
static mat4 mat4_set_this_col(mat4 *mat, vec4 v, int col) {
    matN_set_col(mat->v, v.v, col, 4);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static mat4 mat4_set_row_sca(mat4 m, float s, int row) {
    matN_set_row_sca(m.v, s, row, 4);
    return m;
}

/** m[row][:] = s; dst = m */
static mat4 mat4_set_this_row_sca(mat4 *m, float s, int row) {
    matN_set_row_sca(m->v, s, row, 4);
    return *m;
}


/** dst = m; dst[:][col] = s */
static mat4 mat4_set_col_sca(mat4 m, float s, int col) {
    matN_set_col_sca(m.v, s, col, 4);
    return m;
}

/** m[:][col] = s; dst = m */
static mat4 mat4_set_this_col_sca(mat4 *m, float s, int col) {
    matN_set_col_sca(m->v, s, col, 4);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static float mat4_trace(mat4 m) {
    return matN_trace(m.v, 4);
}


/** dst = m^t */
static mat4 mat4_transpose(mat4 m) {
    mat4 res;
    matN_transpose_no_alias(res.v, m.v, 4);
    return res;
}


/** dst = a @ b */
static mat4 mat4_mul_mat(mat4 a, mat4 b) {
    mat4 res;
    matN_mul_mat_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a @ b */
static vec4 mat4_mul_vec(mat4 a, vec4 b) {
    vec4 res;
    matN_mul_vec_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a @ b */
static vec4 vec4_mul_mat(vec4 a, mat4 b) {
    vec4 res;
    vecN_mul_mat_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** returns = determinant mm */
static float mat4_det(mat4 mm) {
    // from cglm/mat4.h/glm_mat4_det
    /* [square] det(A) = det(At) */
    float t[6];
    float a = mm.m[0][0], b = mm.m[0][1], c = mm.m[0][2], d = mm.m[0][3],
            e = mm.m[1][0], f = mm.m[1][1], g = mm.m[1][2], h = mm.m[1][3],
            i = mm.m[2][0], j = mm.m[2][1], k = mm.m[2][2], l = mm.m[2][3],
            m = mm.m[3][0], n = mm.m[3][1], o = mm.m[3][2], p = mm.m[3][3];

    t[0] = k * p - o * l;
    t[1] = j * p - n * l;
    t[2] = j * o - n * k;
    t[3] = i * p - m * l;
    t[4] = i * o - m * k;
    t[5] = i * n - m * j;

    return a * (f * t[0] - g * t[1] + h * t[2])
           - b * (e * t[0] - g * t[3] + h * t[4])
           + c * (e * t[1] - f * t[3] + h * t[5])
           - d * (e * t[2] - f * t[4] + g * t[5]);
}


/** dst = inverted mm */
static mat4 mat4_inv(mat4 mm) {
    // from cglm/mat4.h/glm_mat4_inv
    float t[6];
    float a = mm.m[0][0], b = mm.m[0][1], c = mm.m[0][2], d = mm.m[0][3];
    float e = mm.m[1][0], f = mm.m[1][1], g = mm.m[1][2], h = mm.m[1][3];
    float i = mm.m[2][0], j = mm.m[2][1], k = mm.m[2][2], l = mm.m[2][3];
    float m = mm.m[3][0], n = mm.m[3][1], o = mm.m[3][2], p = mm.m[3][3];

    t[0] = k * p - o * l;
    t[1] = j * p - n * l;
    t[2] = j * o - n * k;
    t[3] = i * p - m * l;
    t[4] = i * o - m * k;
    t[5] = i * n - m * j;

    mat4 res;
    res.m[0][0] = f * t[0] - g * t[1] + h * t[2];
    res.m[1][0] = -(e * t[0] - g * t[3] + h * t[4]);
    res.m[2][0] = e * t[1] - f * t[3] + h * t[5];
    res.m[3][0] = -(e * t[2] - f * t[4] + g * t[5]);

    res.m[0][1] = -(b * t[0] - c * t[1] + d * t[2]);
    res.m[1][1] = a * t[0] - c * t[3] + d * t[4];
    res.m[2][1] = -(a * t[1] - b * t[3] + d * t[5]);
    res.m[3][1] = a * t[2] - b * t[4] + c * t[5];

    t[0] = g * p - o * h;
    t[1] = f * p - n * h;
    t[2] = f * o - n * g;
    t[3] = e * p - m * h;
    t[4] = e * o - m * g;
    t[5] = e * n - m * f;

    res.m[0][2] = b * t[0] - c * t[1] + d * t[2];
    res.m[1][2] = -(a * t[0] - c * t[3] + d * t[4]);
    res.m[2][2] = a * t[1] - b * t[3] + d * t[5];
    res.m[3][2] = -(a * t[2] - b * t[4] + c * t[5]);

    t[0] = g * l - k * h;
    t[1] = f * l - j * h;
    t[2] = f * k - j * g;
    t[3] = e * l - i * h;
    t[4] = e * k - i * g;
    t[5] = e * j - i * f;

    res.m[0][3] = -(b * t[0] - c * t[1] + d * t[2]);
    res.m[1][3] = a * t[0] - c * t[3] + d * t[4];
    res.m[2][3] = -(a * t[1] - b * t[3] + d * t[5]);
    res.m[3][3] = a * t[2] - b * t[4] + c * t[5];

    float det = a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0] + d * res.m[3][0];
    vecN_div(res.v, res.v, det, 16);

    return res;
}

/** dst = m[col:col+2, row:row+2] */
static mat2 mat4_get_block2(mat4 m, int row, int col) {
    mat2 res;
    matN_get_block(res.v, m.v, row, col, 2, 4);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static mat4 mat4_set_block2(mat4 m, mat2 block_2, int row, int col) {
    matN_set_block(m.v, block_2.v, row, col, 2, 4);
    return m;
}


/** m[col:col+2, row:row+2] = block; dst = m */
static mat4 mat4_set_this_block2(mat4 *m, mat2 block_2, int row, int col) {
    matN_set_block(m->v, block_2.v, row, col, 2, 4);
    return *m;
}


/** dst = m[col:col+2, row:row+2] */
static mat3 mat4_get_block3(mat4 m, int row, int col) {
    mat3 res;
    matN_get_block(res.v, m.v, row, col, 3, 4);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static mat4 mat4_set_block3(mat4 m, mat3 block_3, int row, int col) {
    matN_set_block(m.v, block_3.v, row, col, 3, 4);
    return m;
}

/** m[col:col+2, row:row+2] = block; dst = m */
static mat4 mat4_set_this_block3(mat4 *m, mat3 block_3, int row, int col) {
    matN_set_block(m->v, block_3.v, row, col, 3, 4);
    return *m;
}


/** dst = m[:2, :2] */
static mat2 mat4_get_upper_left2(mat4 m) {
    return mat4_get_block2(m, 0, 0);
}


/** dst = m; dst[:2, :2] = block */
static mat4 mat4_set_upper_left2(mat4 m, mat2 block_2) {
    return mat4_set_block2(m, block_2, 0, 0);
}

/** m[:2, :2] = block; dst = m */
static mat4 mat4_set_this_upper_left2(mat4 *m, mat2 block_2) {
    return mat4_set_this_block2(m, block_2, 0, 0);
}


/** dst = m[:3, :3] */
static mat3 mat4_get_upper_left3(mat4 m) {
    return mat4_get_block3(m, 0, 0);
}


/** dst = m; dst[:3, :3] = block */
static mat4 mat4_set_upper_left3(mat4 m, mat3 block_3) {
    return mat4_set_block3(m, block_3, 0, 0);
}

/** m[:3, :3] = block; dst = m */
static mat4 mat4_set_this_upper_left3(mat4 *m, mat3 block_3) {
    return mat4_set_this_block3(m, block_3, 0, 0);
}

#endif //M_MAT_MAT4_H
