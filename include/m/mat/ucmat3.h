#ifndef M_MAT_UCMAT3_H
#define M_MAT_UCMAT3_H


#include "ucmatn.h"
#include "../types/ucmat3.h"
#include "../types/ucmat2.h"
#include "../vec/ucvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static ucmat3 ucmat3_eye() {
    ucmat3 res;
    ucmatN_eye(res.v, 3);
    return res;
}

/** a == b */
static bool ucmat3_cmp(ucmat3 a, ucmat3 b) {
    return ucvecN_cmp(a.v, b.v, 3 * 3);
}


/** dst = m[row][:] */
static ucvec3 ucmat3_get_row(ucmat3 m, int row) {
    ucvec3 res;
    ucmatN_get_row(res.v, m.v, row, 3);
    return res;
}


/** dst = m[:][col] */
static ucvec3 ucmat3_get_col(ucmat3 m, int col) {
    ucvec3 res;
    ucmatN_get_col(res.v, m.v, col, 3);
    return res;
}


/** dst = m; dst[row][:] = v */
static ucmat3 ucmat3_set_row(ucmat3 m, ucvec3 v, int row) {
    ucmatN_set_row(m.v, v.v, row, 3);
    return m;
}

/** m[row][:] = v; dst = m */
static ucmat3 ucmat3_set_this_row(ucmat3 *m, ucvec3 v, int row) {
    ucmatN_set_row(m->v, v.v, row, 3);
    return *m;
}

/** dst = m; dst[:][col] = v */
static ucmat3 ucmat3_set_col(ucmat3 m, ucvec3 v, int col) {
    ucmatN_set_col(m.v, v.v, col, 3);
    return m;
}

/** mat[:][col] = v; dst = m */
static ucmat3 ucmat3_set_this_col(ucmat3 *mat, ucvec3 v, int col) {
    ucmatN_set_col(mat->v, v.v, col, 3);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static ucmat3 ucmat3_set_row_sca(ucmat3 m, unsigned char s, int row) {
    ucmatN_set_row_sca(m.v, s, row, 3);
    return m;
}

/** m[row][:] = s; dst = m */
static ucmat3 ucmat3_set_this_row_sca(ucmat3 *m, unsigned char s, int row) {
    ucmatN_set_row_sca(m->v, s, row, 3);
    return *m;
}


/** dst = m; dst[:][col] = s */
static ucmat3 ucmat3_set_col_sca(ucmat3 m, unsigned char s, int col) {
    ucmatN_set_col_sca(m.v, s, col, 3);
    return m;
}

/** m[:][col] = s; dst = m */
static ucmat3 ucmat3_set_this_col_sca(ucmat3 *m, unsigned char s, int col) {
    ucmatN_set_col_sca(m->v, s, col, 3);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static unsigned char ucmat3_trace(ucmat3 m) {
    return ucmatN_trace(m.v, 3);
}


/** dst = m^t */
static ucmat3 ucmat3_transpose(ucmat3 m) {
    ucmat3 res;
    ucmatN_transpose_no_alias(res.v, m.v, 3);
    return res;
}


/** dst = a @ b */
static ucmat3 ucmat3_mul_mat(ucmat3 a, ucmat3 b) {
    ucmat3 res;
    ucmatN_mul_mat_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a @ b */
static ucvec3 ucmat3_mul_vec(ucmat3 a, ucvec3 b) {
    ucvec3 res;
    ucmatN_mul_vec_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a @ b */
static ucvec3 ucvec3_mul_mat(ucvec3 a, ucmat3 b) {
    ucvec3 res;
    ucvecN_mul_mat_no_alias(res.v, a.v, b.v, 3);
    return res;
}


/** returns = determinant m */
static unsigned char ucmat3_det(ucmat3 m) {
    // from cglm/ucmat3.h/glm_mat3_det
    unsigned char a = m.m[0][0], b = m.m[0][1], c = m.m[0][2];
    unsigned char d = m.m[1][0], e = m.m[1][1], f = m.m[1][2];
    unsigned char g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}


/** dst = inverted m */
static ucmat3 ucmat3_inv(ucmat3 m) {
    // from cglm/ucmat3.h/glm_mat3_inv
    unsigned char a = m.m[0][0], b = m.m[0][1], c = m.m[0][2];
    unsigned char d = m.m[1][0], e = m.m[1][1], f = m.m[1][2];
    unsigned char g = m.m[2][0], h = m.m[2][1], i = m.m[2][2];

    ucmat3 res;
    res.m[0][0] = e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] = b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] = a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] = d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] = a * e - b * d;

    unsigned char det = a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0];
    ucvecN_div(res.v, res.v, det, 9);

    return res;
}


/** dst = m[col:col+2, row:row+2] */
static ucmat2 ucmat3_get_block2(ucmat3 m, int row, int col) {
    ucmat2 res;
    ucmatN_get_block(res.v, m.v, row, col, 2, 3);
    return res;
}


/** dst = m; dst[col:col+2, row:row+2] = block */
static ucmat3 ucmat3_set_block2(ucmat3 m, ucmat2 block_2, int row, int col) {
    ucmatN_set_block(m.v, block_2.v, row, col, 2, 3);
    return m;
}

/** m[col:col+2, row:row+2] = block; dst = m */
static ucmat3 ucmat3_set_this_block2(ucmat3 *m, ucmat2 block_2, int row, int col) {
    ucmatN_set_block(m->v, block_2.v, row, col, 2, 3);
    return *m;
}


/** dst = m[:2, :2] */
static ucmat2 ucmat3_get_upper_left(ucmat3 m) {
    return ucmat3_get_block2(m, 0, 0);
}


/** dst = m; dst[:2, :2] = block */
static ucmat3 ucmat3_set_upper_left(ucmat3 m, ucmat2 block_2) {
    return ucmat3_set_block2(m, block_2, 0, 0);
}


/** m[:2, :2] = block; dst = m */
static ucmat3 ucmat3_set_this_upper_left(ucmat3 *m, ucmat2 block_2) {
    return ucmat3_set_this_block2(m, block_2, 0, 0);
}


#endif //M_MAT_UCMAT3_H
