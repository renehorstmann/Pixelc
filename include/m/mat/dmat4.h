#ifndef M_MAT_DMAT4_H
#define M_MAT_DMAT4_H


#include "dmatn.h"
#include "../types/dmat4.h"
#include "../types/dmat2.h"
#include "../types/dmat3.h"
#include "../vec/dvecn.h"

// macro to create a dmat4
#define dmat4_(v0, v1, v2, v3 \
, v4, v5, v6, v7, v8\
, v9, v10, v11, v12, v13, v14, v15\
) (dmat4) {{(v0), (v1), (v2), (v3)\
, (v4), (v5), (v6), (v7), (v8)\
, (v9), (v10), (v11), (v12), (v13), (v14), (v15)\
}}


/** dst = (dmat4) v */
static dmat4 dmat4_cast_from_float(const float *cast) {
    dmat4 res;
    dmatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (dmat4) v */
static dmat4 dmat4_cast_from_double(const double *cast) {
    dmat4 res;
    dmatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (dmat4) v */
static dmat4 dmat4_cast_from_int(const int *cast) {
    dmat4 res;
    dmatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (dmat4) v */
static dmat4 dmat4_cast_from_uchar(const unsigned char *cast) {
    dmat4 res;
    dmatN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = v / 255 */
static dmat4 dmat4_cast_from_uchar_1(const unsigned char *cast) {
    dmat4 res;
    dmatN_cast_from_uchar_1(res.v, cast, 4);
    return res;
}


/** dst = r==c ? 1 : 0 (identity)  */
static dmat4 dmat4_eye() {
    dmat4 res;
    dmatN_eye(res.v, 4);
    return res;
}

/** a == b */
static bool dmat4_cmp(dmat4 a, dmat4 b) {
    return dvecN_cmp(a.v, b.v, 4 * 4);
}


/** dst = m[row][:] */
static dvec4 dmat4_get_row(dmat4 m, int row) {
    dvec4 res;
    dmatN_get_row(res.v, m.v, row, 4);
    return res;
}


/** dst = m[:][col] */
static dvec4 dmat4_get_col(dmat4 m, int col) {
    dvec4 res;
    dmatN_get_col(res.v, m.v, col, 4);
    return res;
}


/** dst = m; dst[row][:] = v */
static dmat4 dmat4_set_row(dmat4 m, dvec4 v, int row) {
    dmatN_set_row(m.v, v.v, row, 4);
    return m;
}

/** m[row][:] = v; dst = m */
static dmat4 dmat4_set_this_row(dmat4 *m, dvec4 v, int row) {
    dmatN_set_row(m->v, v.v, row, 4);
    return *m;
}

/** dst = m; dst[:][col] = v */
static dmat4 dmat4_set_col(dmat4 m, dvec4 v, int col) {
    dmatN_set_col(m.v, v.v, col, 4);
    return m;
}

/** mat[:][col] = v; dst = m */
static dmat4 dmat4_set_this_col(dmat4 *mat, dvec4 v, int col) {
    dmatN_set_col(mat->v, v.v, col, 4);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static dmat4 dmat4_set_row_sca(dmat4 m, double s, int row) {
    dmatN_set_row_sca(m.v, s, row, 4);
    return m;
}

/** m[row][:] = s; dst = m */
static dmat4 dmat4_set_this_row_sca(dmat4 *m, double s, int row) {
    dmatN_set_row_sca(m->v, s, row, 4);
    return *m;
}


/** dst = m; dst[:][col] = s */
static dmat4 dmat4_set_col_sca(dmat4 m, double s, int col) {
    dmatN_set_col_sca(m.v, s, col, 4);
    return m;
}

/** m[:][col] = s; dst = m */
static dmat4 dmat4_set_this_col_sca(dmat4 *m, double s, int col) {
    dmatN_set_col_sca(m->v, s, col, 4);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static double dmat4_trace(dmat4 m) {
    return dmatN_trace(m.v, 4);
}


/** dst = m^t */
static dmat4 dmat4_transpose(dmat4 m) {
    dmat4 res;
    dmatN_transpose_no_alias(res.v, m.v, 4);
    return res;
}


/** dst = a @ b */
static dmat4 dmat4_mul_mat(dmat4 a, dmat4 b) {
    dmat4 res;
    dmatN_mul_mat_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a @ b */
static dvec4 dmat4_mul_vec(dmat4 a, dvec4 b) {
    dvec4 res;
    dmatN_mul_vec_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a @ b */
static dvec4 dvec4_mul_mat(dvec4 a, dmat4 b) {
    dvec4 res;
    dvecN_mul_mat_no_alias(res.v, a.v, b.v, 4);
    return res;
}


/** returns = determinant mm */
static double dmat4_det(dmat4 mm) {
    // from cglm/dmat4.h/glm_mat4_det
    /* [square] det(A) = det(At) */
    double t[6];
    double a = mm.m[0][0], b = mm.m[0][1], c = mm.m[0][2], d = mm.m[0][3],
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
static dmat4 dmat4_inv(dmat4 mm) {
    // from cglm/dmat4.h/glm_mat4_inv
    double t[6];
    double a = mm.m[0][0], b = mm.m[0][1], c = mm.m[0][2], d = mm.m[0][3];
    double e = mm.m[1][0], f = mm.m[1][1], g = mm.m[1][2], h = mm.m[1][3];
    double i = mm.m[2][0], j = mm.m[2][1], k = mm.m[2][2], l = mm.m[2][3];
    double m = mm.m[3][0], n = mm.m[3][1], o = mm.m[3][2], p = mm.m[3][3];

    t[0] = k * p - o * l;
    t[1] = j * p - n * l;
    t[2] = j * o - n * k;
    t[3] = i * p - m * l;
    t[4] = i * o - m * k;
    t[5] = i * n - m * j;

    dmat4 res;
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

    double det = a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0] + d * res.m[3][0];
    dvecN_div(res.v, res.v, det, 16);

    return res;
}

/** dst = m[col:col+2, row:row+2] */
static dmat2 dmat4_get_block2(dmat4 m, int row, int col) {
    dmat2 res;
    dmatN_get_block(res.v, m.v, row, col, 2, 4);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static dmat4 dmat4_set_block2(dmat4 m, dmat2 block_2, int row, int col) {
    dmatN_set_block(m.v, block_2.v, row, col, 2, 4);
    return m;
}


/** m[col:col+2, row:row+2] = block; dst = m */
static dmat4 dmat4_set_this_block2(dmat4 *m, dmat2 block_2, int row, int col) {
    dmatN_set_block(m->v, block_2.v, row, col, 2, 4);
    return *m;
}


/** dst = m[col:col+2, row:row+2] */
static dmat3 dmat4_get_block3(dmat4 m, int row, int col) {
    dmat3 res;
    dmatN_get_block(res.v, m.v, row, col, 3, 4);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static dmat4 dmat4_set_block3(dmat4 m, dmat3 block_3, int row, int col) {
    dmatN_set_block(m.v, block_3.v, row, col, 3, 4);
    return m;
}

/** m[col:col+2, row:row+2] = block; dst = m */
static dmat4 dmat4_set_this_block3(dmat4 *m, dmat3 block_3, int row, int col) {
    dmatN_set_block(m->v, block_3.v, row, col, 3, 4);
    return *m;
}


/** dst = m[:2, :2] */
static dmat2 dmat4_get_upper_left2(dmat4 m) {
    return dmat4_get_block2(m, 0, 0);
}


/** dst = m; dst[:2, :2] = block */
static dmat4 dmat4_set_upper_left2(dmat4 m, dmat2 block_2) {
    return dmat4_set_block2(m, block_2, 0, 0);
}

/** m[:2, :2] = block; dst = m */
static dmat4 dmat4_set_this_upper_left2(dmat4 *m, dmat2 block_2) {
    return dmat4_set_this_block2(m, block_2, 0, 0);
}


/** dst = m[:3, :3] */
static dmat3 dmat4_get_upper_left3(dmat4 m) {
    return dmat4_get_block3(m, 0, 0);
}


/** dst = m; dst[:3, :3] = block */
static dmat4 dmat4_set_upper_left3(dmat4 m, dmat3 block_3) {
    return dmat4_set_block3(m, block_3, 0, 0);
}

/** m[:3, :3] = block; dst = m */
static dmat4 dmat4_set_this_upper_left3(dmat4 *m, dmat3 block_3) {
    return dmat4_set_this_block3(m, block_3, 0, 0);
}

#endif //M_MAT_DMAT4_H
