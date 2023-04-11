#ifndef M_MAT_IMAT3_H
#define M_MAT_IMAT3_H


#include "imatn.h"
#include "../types/imat3.h"
#include "../types/imat2.h"
#include "../vec/ivecn.h"

// macro to create a imat3
#define imat3_(v0, v1, v2, v3 \
, v4, v5, v6, v7, v8\
) (imat3) {{(v0), (v1), (v2), (v3)\
, (v4), (v5), (v6), (v7), (v8)\
}}


/** dst = (imat3) v */
static imat3 imat3_cast_from_float(const float *cast) {
    imat3 res;
    imatN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (imat3) v */
static imat3 imat3_cast_from_double(const double *cast) {
    imat3 res;
    imatN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (imat3) v */
static imat3 imat3_cast_from_int(const int *cast) {
    imat3 res;
    imatN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (imat3) v */
static imat3 imat3_cast_from_uchar(const unsigned char *cast) {
    imat3 res;
    imatN_cast_into(res.v, cast, 3);
    return res;
}


/** dst = mat * 255 */
static imat3 imat3_cast_from_float_1(const float *cast) {
    imat3 res;
    imatN_cast_from_float_1(res.v, cast, 3);
    return res;
}

/** dst = mat * 255 */
static imat3 imat3_cast_from_double_1(const double *cast) {
    imat3 res;
    imatN_cast_from_double_1(res.v, cast, 3);
    return res;
}

/** dst = mat * 255 */
static imat3 imat3_cast_from_longdouble_1(const long double *cast) {
    imat3 res;
    imatN_cast_from_longdouble_1(res.v, cast, 3);
    return res;
}


/** dst = r==c ? 1 : 0 (identity)  */
static imat3 imat3_eye() {
    imat3 res;
    imatN_eye(res.v, 3);
    return res;
}

/** a == b */
static bool imat3_cmp(imat3 a, imat3 b) {
    return ivecN_cmp(a.v, b.v, 3 * 3);
}


/** dst = m[row][:] */
static ivec3 imat3_get_row(imat3 m, int row) {
    ivec3 res;
    imatN_get_row(res.v, m.v, row, 3);
    return res;
}


/** dst = m[:][col] */
static ivec3 imat3_get_col(imat3 m, int col) {
    ivec3 res;
    imatN_get_col(res.v, m.v, col, 3);
    return res;
}


/** dst = m; dst[row][:] = v */
static imat3 imat3_set_row(imat3 m, ivec3 v, int row) {
    imatN_set_row(m.v, v.v, row, 3);
    return m;
}

/** m[row][:] = v; dst = m */
static imat3 imat3_set_this_row(imat3 *m, ivec3 v, int row) {
    imatN_set_row(m->v, v.v, row, 3);
    return *m;
}

/** dst = m; dst[:][col] = v */
static imat3 imat3_set_col(imat3 m, ivec3 v, int col) {
    imatN_set_col(m.v, v.v, col, 3);
    return m;
}

/** mat[:][col] = v; dst = m */
static imat3 imat3_set_this_col(imat3 *mat, ivec3 v, int col) {
    imatN_set_col(mat->v, v.v, col, 3);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static imat3 imat3_set_row_sca(imat3 m, int s, int row) {
    imatN_set_row_sca(m.v, s, row, 3);
    return m;
}

/** m[row][:] = s; dst = m */
static imat3 imat3_set_this_row_sca(imat3 *m, int s, int row) {
    imatN_set_row_sca(m->v, s, row, 3);
    return *m;
}


/** dst = m; dst[:][col] = s */
static imat3 imat3_set_col_sca(imat3 m, int s, int col) {
    imatN_set_col_sca(m.v, s, col, 3);
    return m;
}

/** m[:][col] = s; dst = m */
static imat3 imat3_set_this_col_sca(imat3 *m, int s, int col) {
    imatN_set_col_sca(m->v, s, col, 3);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static int imat3_trace(imat3 m) {
    return imatN_trace(m.v, 3);
}


/** dst = m^t */
static imat3 imat3_transpose(imat3 m) {
    imat3 res;
    imatN_transpose_no_alias(res.v, m.v, 3);
    return res;
}


/** dst = a @ b */
static imat3 imat3_mul_mat(imat3 a, imat3 b) {
    imat3 res;
    imatN_mul_mat_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a @ b */
static ivec3 imat3_mul_vec(imat3 a, ivec3 b) {
    ivec3 res;
    imatN_mul_vec_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a @ b */
static ivec3 ivec3_mul_mat(ivec3 a, imat3 b) {
    ivec3 res;
    ivecN_mul_mat_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** returns = determinant m */
static int imat3_det(imat3 m) {
    // from cglm/imat3.h/glm_mat3_det
    int a = m.m[0][0], b = m.m[0][1], c = m.m[0][2];
    int d = m.m[1][0], e = m.m[1][1], f = m.m[1][2];
    int g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}


/** dst = inverted m */
static imat3 imat3_inv(imat3 m) {
    // from cglm/imat3.h/glm_mat3_inv
    int a = m.m[0][0], b = m.m[0][1], c = m.m[0][2];
    int d = m.m[1][0], e = m.m[1][1], f = m.m[1][2];
    int g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

    imat3 res;
    res.m[0][0] = e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] = b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] = a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] = d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] = a * e - b * d;

    int det = a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0];
    ivecN_div(res.v, res.v, det, 9);

    return res;
}


/** dst = m[col:col+2, row:row+2] */
static imat2 imat3_get_block2(imat3 m, int row, int col) {
    imat2 res;
    imatN_get_block(res.v, m.v, row, col, 2, 3);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static imat3 imat3_set_block2(imat3 m, imat2 block_2, int row, int col) {
    imatN_set_block(m.v, block_2.v, row, col, 2, 3);
    return m;
}

/** m[col:col+2, row:row+2] = block; dst = m */
static imat3 imat3_set_this_block2(imat3 *m, imat2 block_2, int row, int col) {
    imatN_set_block(m->v, block_2.v, row, col, 2, 3);
    return *m;
}


/** dst = m[:2, :2] */
static imat2 imat3_get_upper_left(imat3 m) {
    return imat3_get_block2(m, 0, 0);
}


/** dst = m; dst[:2, :2] = block */
static imat3 imat3_set_upper_left(imat3 m, imat2 block_2) {
    return imat3_set_block2(m, block_2, 0, 0);
}


/** m[:2, :2] = block; dst = m */
static imat3 imat3_set_this_upper_left(imat3 *m, imat2 block_2) {
    return imat3_set_this_block2(m, block_2, 0, 0);
}


#endif //M_MAT_IMAT3_H
