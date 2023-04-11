#ifndef M_MAT_IMAT4_H
#define M_MAT_IMAT4_H


#include "imatn.h"
#include "../types/imat4.h"
#include "../types/imat2.h"
#include "../types/imat3.h"
#include "../vec/ivecn.h"

// macro to create a imat4
#define imat4_(v0, v1, v2, v3 \
, v4, v5, v6, v7, v8\
, v9, v10, v11, v12, v13, v14, v15\
) (imat4) {{(v0), (v1), (v2), (v3)\
, (v4), (v5), (v6), (v7), (v8)\
, (v9), (v10), (v11), (v12), (v13), (v14), (v15)\
}}


/** dst = (imat4) v */
static imat4 imat4_cast_from_float(const float *cast) {
    imat4 res;
    imatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (imat4) v */
static imat4 imat4_cast_from_double(const double *cast) {
    imat4 res;
    imatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (imat4) v */
static imat4 imat4_cast_from_int(const int *cast) {
    imat4 res;
    imatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (imat4) v */
static imat4 imat4_cast_from_uchar(const unsigned char *cast) {
    imat4 res;
    imatN_cast_into(res.v, cast, 4);
    return res;
}


/** dst = mat * 255 */
static imat4 imat4_cast_from_float_1(const float *cast) {
    imat4 res;
    imatN_cast_from_float_1(res.v, cast, 4);
    return res;
}

/** dst = mat * 255 */
static imat4 imat4_cast_from_double_1(const double *cast) {
    imat4 res;
    imatN_cast_from_double_1(res.v, cast, 4);
    return res;
}

/** dst = mat * 255 */
static imat4 imat4_cast_from_longdouble_1(const long double *cast) {
    imat4 res;
    imatN_cast_from_longdouble_1(res.v, cast, 4);
    return res;
}


/** dst = r==c ? 1 : 0 (identity)  */
static imat4 imat4_eye() {
    imat4 res;
    imatN_eye(res.v, 4);
    return res;
}

/** a == b */
static bool imat4_cmp(imat4 a, imat4 b) {
    return ivecN_cmp(a.v, b.v, 4 * 4);
}


/** dst = m[row][:] */
static ivec4 imat4_get_row(imat4 m, int row) {
    ivec4 res;
    imatN_get_row(res.v, m.v, row, 4);
    return res;
}


/** dst = m[:][col] */
static ivec4 imat4_get_col(imat4 m, int col) {
    ivec4 res;
    imatN_get_col(res.v, m.v, col, 4);
    return res;
}


/** dst = m; dst[row][:] = v */
static imat4 imat4_set_row(imat4 m, ivec4 v, int row) {
    imatN_set_row(m.v, v.v, row, 4);
    return m;
}

/** m[row][:] = v; dst = m */
static imat4 imat4_set_this_row(imat4 *m, ivec4 v, int row) {
    imatN_set_row(m->v, v.v, row, 4);
    return *m;
}

/** dst = m; dst[:][col] = v */
static imat4 imat4_set_col(imat4 m, ivec4 v, int col) {
    imatN_set_col(m.v, v.v, col, 4);
    return m;
}

/** mat[:][col] = v; dst = m */
static imat4 imat4_set_this_col(imat4 *mat, ivec4 v, int col) {
    imatN_set_col(mat->v, v.v, col, 4);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static imat4 imat4_set_row_sca(imat4 m, int s, int row) {
    imatN_set_row_sca(m.v, s, row, 4);
    return m;
}

/** m[row][:] = s; dst = m */
static imat4 imat4_set_this_row_sca(imat4 *m, int s, int row) {
    imatN_set_row_sca(m->v, s, row, 4);
    return *m;
}


/** dst = m; dst[:][col] = s */
static imat4 imat4_set_col_sca(imat4 m, int s, int col) {
    imatN_set_col_sca(m.v, s, col, 4);
    return m;
}

/** m[:][col] = s; dst = m */
static imat4 imat4_set_this_col_sca(imat4 *m, int s, int col) {
    imatN_set_col_sca(m->v, s, col, 4);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static int imat4_trace(imat4 m) {
    return imatN_trace(m.v, 4);
}


/** dst = m^t */
static imat4 imat4_transpose(imat4 m) {
    imat4 res;
    imatN_transpose_no_alias(res.v, m.v, 4);
    return res;
}


/** dst = a @ b */
static imat4 imat4_mul_mat(imat4 a, imat4 b) {
    imat4 res;
    imatN_mul_mat_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a @ b */
static ivec4 imat4_mul_vec(imat4 a, ivec4 b) {
    ivec4 res;
    imatN_mul_vec_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a @ b */
static ivec4 ivec4_mul_mat(ivec4 a, imat4 b) {
    ivec4 res;
    ivecN_mul_mat_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** returns = determinant mm */
static int imat4_det(imat4 mm) {
    // from cglm/imat4.h/glm_mat4_det
    /* [square] det(A) = det(At) */
    int t[6];
    int a = mm.m[0][0], b = mm.m[0][1], c = mm.m[0][2], d = mm.m[0][3],
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
static imat4 imat4_inv(imat4 mm) {
    // from cglm/imat4.h/glm_mat4_inv
    int t[6];
    int a = mm.m[0][0], b = mm.m[0][1], c = mm.m[0][2], d = mm.m[0][3];
    int e = mm.m[1][0], f = mm.m[1][1], g = mm.m[1][2], h = mm.m[1][3];
    int i = mm.m[2][0], j = mm.m[2][1], k = mm.m[2][2], l = mm.m[2][3];
    int m = mm.m[3][0], n = mm.m[3][1], o = mm.m[3][2], p = mm.m[3][3];

    t[0] = k * p - o * l;
    t[1] = j * p - n * l;
    t[2] = j * o - n * k;
    t[3] = i * p - m * l;
    t[4] = i * o - m * k;
    t[5] = i * n - m * j;

    imat4 res;
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

    int det = a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0] + d * res.m[3][0];
    ivecN_div(res.v, res.v, det, 16);

    return res;
}

/** dst = m[col:col+2, row:row+2] */
static imat2 imat4_get_block2(imat4 m, int row, int col) {
    imat2 res;
    imatN_get_block(res.v, m.v, row, col, 2, 4);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static imat4 imat4_set_block2(imat4 m, imat2 block_2, int row, int col) {
    imatN_set_block(m.v, block_2.v, row, col, 2, 4);
    return m;
}


/** m[col:col+2, row:row+2] = block; dst = m */
static imat4 imat4_set_this_block2(imat4 *m, imat2 block_2, int row, int col) {
    imatN_set_block(m->v, block_2.v, row, col, 2, 4);
    return *m;
}


/** dst = m[col:col+2, row:row+2] */
static imat3 imat4_get_block3(imat4 m, int row, int col) {
    imat3 res;
    imatN_get_block(res.v, m.v, row, col, 3, 4);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static imat4 imat4_set_block3(imat4 m, imat3 block_3, int row, int col) {
    imatN_set_block(m.v, block_3.v, row, col, 3, 4);
    return m;
}

/** m[col:col+2, row:row+2] = block; dst = m */
static imat4 imat4_set_this_block3(imat4 *m, imat3 block_3, int row, int col) {
    imatN_set_block(m->v, block_3.v, row, col, 3, 4);
    return *m;
}


/** dst = m[:2, :2] */
static imat2 imat4_get_upper_left2(imat4 m) {
    return imat4_get_block2(m, 0, 0);
}


/** dst = m; dst[:2, :2] = block */
static imat4 imat4_set_upper_left2(imat4 m, imat2 block_2) {
    return imat4_set_block2(m, block_2, 0, 0);
}

/** m[:2, :2] = block; dst = m */
static imat4 imat4_set_this_upper_left2(imat4 *m, imat2 block_2) {
    return imat4_set_this_block2(m, block_2, 0, 0);
}


/** dst = m[:3, :3] */
static imat3 imat4_get_upper_left3(imat4 m) {
    return imat4_get_block3(m, 0, 0);
}


/** dst = m; dst[:3, :3] = block */
static imat4 imat4_set_upper_left3(imat4 m, imat3 block_3) {
    return imat4_set_block3(m, block_3, 0, 0);
}

/** m[:3, :3] = block; dst = m */
static imat4 imat4_set_this_upper_left3(imat4 *m, imat3 block_3) {
    return imat4_set_this_block3(m, block_3, 0, 0);
}

#endif //M_MAT_IMAT4_H
