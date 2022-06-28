#ifndef M_MAT_UCMAT2_H
#define M_MAT_UCMAT2_H


#include "ucmatn.h"
#include "../types/ucmat2.h"
#include "../vec/ucvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static ucmat2 ucmat2_eye() {
    ucmat2 res;
    ucmatN_eye(res.v, 2);
    return res;
}

/** a == b */
static bool ucmat2_cmp(ucmat2 a, ucmat2 b) {
    return ucvecN_cmp(a.v, b.v, 2 * 2);
}


/** dst = m[row][:] */
static ucvec2 ucmat2_get_row(ucmat2 m, int row) {
    ucvec2 res;
    ucmatN_get_row(res.v, m.v, row, 2);
    return res;
}


/** dst = m[:][col] */
static ucvec2 ucmat2_get_col(ucmat2 m, int col) {
    ucvec2 res;
    ucmatN_get_col(res.v, m.v, col, 2);
    return res;
}


/** dst = m; dst[row][:] = v */
static ucmat2 ucmat2_set_row(ucmat2 m, ucvec2 v, int row) {
    ucmatN_set_row(m.v, v.v, row, 2);
    return m;
}

/** m[row][:] = v; dst = m */
static ucmat2 ucmat2_set_this_row(ucmat2 *m, ucvec2 v, int row) {
    ucmatN_set_row(m->v, v.v, row, 2);
    return *m;
}

/** dst = m; dst[:][col] = v */
static ucmat2 ucmat2_set_col(ucmat2 m, ucvec2 v, int col) {
    ucmatN_set_col(m.v, v.v, col, 2);
    return m;
}

/** mat[:][col] = v; dst = m */
static ucmat2 ucmat2_set_this_col(ucmat2 *mat, ucvec2 v, int col) {
    ucmatN_set_col(mat->v, v.v, col, 2);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static ucmat2 ucmat2_set_row_sca(ucmat2 m, unsigned char s, int row) {
    ucmatN_set_row_sca(m.v, s, row, 2);
    return m;
}

/** m[row][:] = s; dst = m */
static ucmat2 ucmat2_set_this_row_sca(ucmat2 *m, unsigned char s, int row) {
    ucmatN_set_row_sca(m->v, s, row, 2);
    return *m;
}


/** dst = m; dst[:][col] = s */
static ucmat2 ucmat2_set_col_sca(ucmat2 m, unsigned char s, int col) {
    ucmatN_set_col_sca(m.v, s, col, 2);
    return m;
}

/** m[:][col] = s; dst = m */
static ucmat2 ucmat2_set_this_col_sca(ucmat2 *m, unsigned char s, int col) {
    ucmatN_set_col_sca(m->v, s, col, 2);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static unsigned char ucmat2_trace(ucmat2 m) {
    return ucmatN_trace(m.v, 2);
}


/** dst = m^t */
static ucmat2 ucmat2_transpose(ucmat2 m) {
    ucmat2 res;
    ucmatN_transpose_no_alias(res.v, m.v, 2);
    return res;
}


/** dst = a @ b */
static ucmat2 ucmat2_mul_mat(ucmat2 a, ucmat2 b) {
    ucmat2 res;
    ucmatN_mul_mat_no_alias(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a @ b */
static ucvec2 ucmat2_mul_vec(ucmat2 a, ucvec2 b) {
    ucvec2 res;
    ucmatN_mul_vec_no_alias(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a @ b */
static ucvec2 ucvec2_mul_mat(ucvec2 a, ucmat2 b) {
    ucvec2 res;
    ucvecN_mul_mat_no_alias(res.v, a.v, b.v, 2);
    return res;
}

/** returns = determinant m */
static unsigned char ucmat2_det(ucmat2 m) {
    // from cglm/ucmat2.h/glm_mat2_det
    return m.m[0][0] * m.m[1][1] - m.m[1][0] * m.m[0][1];
}


/** dst = inverted m */
static ucmat2 ucmat2_inv(ucmat2 m) {
    // from cglm/ucmat2.h/glm_mat2_inv
    unsigned char a = m.m[0][0], b = m.m[0][1];
    unsigned char c = m.m[1][0], d = m.m[1][1];

    ucmat2 res;
    res.m[0][0] = d;
    res.m[0][1] = -b;
    res.m[1][0] = -c;
    res.m[1][1] = a;

    unsigned char det = a * d - b * c;
    ucvecN_div(res.v, res.v, det, 4);

    return res;
}


#endif //M_MAT_UCMAT2_H
