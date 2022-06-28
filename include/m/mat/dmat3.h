#ifndef M_MAT_DMAT3_H
#define M_MAT_DMAT3_H


#include "dmatn.h"
#include "../types/dmat3.h"
#include "../types/dmat2.h"
#include "../vec/dvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static dmat3 dmat3_eye() {
    dmat3 res;
    dmatN_eye(res.v, 3);
    return res;
}

/** a == b */
static bool dmat3_cmp(dmat3 a, dmat3 b) {
    return dvecN_cmp(a.v, b.v, 3 * 3);
}


/** dst = m[row][:] */
static dvec3 dmat3_get_row(dmat3 m, int row) {
    dvec3 res;
    dmatN_get_row(res.v, m.v, row, 3);
    return res;
}


/** dst = m[:][col] */
static dvec3 dmat3_get_col(dmat3 m, int col) {
    dvec3 res;
    dmatN_get_col(res.v, m.v, col, 3);
    return res;
}


/** dst = m; dst[row][:] = v */
static dmat3 dmat3_set_row(dmat3 m, dvec3 v, int row) {
    dmatN_set_row(m.v, v.v, row, 3);
    return m;
}

/** m[row][:] = v; dst = m */
static dmat3 dmat3_set_this_row(dmat3 *m, dvec3 v, int row) {
    dmatN_set_row(m->v, v.v, row, 3);
    return *m;
}

/** dst = m; dst[:][col] = v */
static dmat3 dmat3_set_col(dmat3 m, dvec3 v, int col) {
    dmatN_set_col(m.v, v.v, col, 3);
    return m;
}

/** mat[:][col] = v; dst = m */
static dmat3 dmat3_set_this_col(dmat3 *mat, dvec3 v, int col) {
    dmatN_set_col(mat->v, v.v, col, 3);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static dmat3 dmat3_set_row_sca(dmat3 m, double s, int row) {
    dmatN_set_row_sca(m.v, s, row, 3);
    return m;
}

/** m[row][:] = s; dst = m */
static dmat3 dmat3_set_this_row_sca(dmat3 *m, double s, int row) {
    dmatN_set_row_sca(m->v, s, row, 3);
    return *m;
}


/** dst = m; dst[:][col] = s */
static dmat3 dmat3_set_col_sca(dmat3 m, double s, int col) {
    dmatN_set_col_sca(m.v, s, col, 3);
    return m;
}

/** m[:][col] = s; dst = m */
static dmat3 dmat3_set_this_col_sca(dmat3 *m, double s, int col) {
    dmatN_set_col_sca(m->v, s, col, 3);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static double dmat3_trace(dmat3 m) {
    return dmatN_trace(m.v, 3);
}


/** dst = m^t */
static dmat3 dmat3_transpose(dmat3 m) {
    dmat3 res;
    dmatN_transpose_no_alias(res.v, m.v, 3);
    return res;
}


/** dst = a @ b */
static dmat3 dmat3_mul_mat(dmat3 a, dmat3 b) {
    dmat3 res;
    dmatN_mul_mat_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a @ b */
static dvec3 dmat3_mul_vec(dmat3 a, dvec3 b) {
    dvec3 res;
    dmatN_mul_vec_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a @ b */
static dvec3 dvec3_mul_mat(dvec3 a, dmat3 b) {
    dvec3 res;
    dvecN_mul_mat_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** returns = determinant m */
static double dmat3_det(dmat3 m) {
    // from cglm/dmat3.h/glm_mat3_det
    double a = m.m[0][0], b = m.m[0][1], c = m.m[0][2];
    double d = m.m[1][0], e = m.m[1][1], f = m.m[1][2];
    double g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}


/** dst = inverted m */
static dmat3 dmat3_inv(dmat3 m) {
    // from cglm/dmat3.h/glm_mat3_inv
    double a = m.m[0][0], b = m.m[0][1], c = m.m[0][2];
    double d = m.m[1][0], e = m.m[1][1], f = m.m[1][2];
    double g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

    dmat3 res;
    res.m[0][0] = e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] = b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] = a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] = d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] = a * e - b * d;

    double det = a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0];
    dvecN_div(res.v, res.v, det, 9);

    return res;
}


/** dst = m[col:col+2, row:row+2] */
static dmat2 dmat3_get_block2(dmat3 m, int row, int col) {
    dmat2 res;
    dmatN_get_block(res.v, m.v, row, col, 2, 3);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static dmat3 dmat3_set_block2(dmat3 m, dmat2 block_2, int row, int col) {
    dmatN_set_block(m.v, block_2.v, row, col, 2, 3);
    return m;
}

/** m[col:col+2, row:row+2] = block; dst = m */
static dmat3 dmat3_set_this_block2(dmat3 *m, dmat2 block_2, int row, int col) {
    dmatN_set_block(m->v, block_2.v, row, col, 2, 3);
    return *m;
}


/** dst = m[:2, :2] */
static dmat2 dmat3_get_upper_left(dmat3 m) {
    return dmat3_get_block2(m, 0, 0);
}


/** dst = m; dst[:2, :2] = block */
static dmat3 dmat3_set_upper_left(dmat3 m, dmat2 block_2) {
    return dmat3_set_block2(m, block_2, 0, 0);
}


/** m[:2, :2] = block; dst = m */
static dmat3 dmat3_set_this_upper_left(dmat3 *m, dmat2 block_2) {
    return dmat3_set_this_block2(m, block_2, 0, 0);
}


#endif //M_MAT_DMAT3_H
