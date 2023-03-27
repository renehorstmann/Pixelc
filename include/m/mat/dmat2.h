#ifndef M_MAT_DMAT2_H
#define M_MAT_DMAT2_H


#include "dmatn.h"
#include "../types/dmat2.h"
#include "../vec/dvecn.h"


/** dst = (dmat2) v */
static dmat2 dmat2_cast_from_float(const float *cast) {
    dmat2 res;
    dmatN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (dmat2) v */
static dmat2 dmat2_cast_from_double(const double *cast) {
    dmat2 res;
    dmatN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (dmat2) v */
static dmat2 dmat2_cast_from_int(const int *cast) {
    dmat2 res;
    dmatN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (dmat2) v */
static dmat2 dmat2_cast_from_uchar(const unsigned char *cast) {
    dmat2 res;
    dmatN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = v / 255 */
static dmat2 dmat2_cast_from_uchar_1(const unsigned char *cast) {
    dmat2 res;
    dmatN_cast_from_uchar_1(res.v, cast, 2);
    return res;
}


/** dst = r==c ? 1 : 0 (identity)  */
static dmat2 dmat2_eye() {
    dmat2 res;
    dmatN_eye(res.v, 2);
    return res;
}

/** a == b */
static bool dmat2_cmp(dmat2 a, dmat2 b) {
    return dvecN_cmp(a.v, b.v, 2 * 2);
}


/** dst = m[row][:] */
static dvec2 dmat2_get_row(dmat2 m, int row) {
    dvec2 res;
    dmatN_get_row(res.v, m.v, row, 2);
    return res;
}


/** dst = m[:][col] */
static dvec2 dmat2_get_col(dmat2 m, int col) {
    dvec2 res;
    dmatN_get_col(res.v, m.v, col, 2);
    return res;
}


/** dst = m; dst[row][:] = v */
static dmat2 dmat2_set_row(dmat2 m, dvec2 v, int row) {
    dmatN_set_row(m.v, v.v, row, 2);
    return m;
}

/** m[row][:] = v; dst = m */
static dmat2 dmat2_set_this_row(dmat2 *m, dvec2 v, int row) {
    dmatN_set_row(m->v, v.v, row, 2);
    return *m;
}

/** dst = m; dst[:][col] = v */
static dmat2 dmat2_set_col(dmat2 m, dvec2 v, int col) {
    dmatN_set_col(m.v, v.v, col, 2);
    return m;
}

/** mat[:][col] = v; dst = m */
static dmat2 dmat2_set_this_col(dmat2 *mat, dvec2 v, int col) {
    dmatN_set_col(mat->v, v.v, col, 2);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static dmat2 dmat2_set_row_sca(dmat2 m, double s, int row) {
    dmatN_set_row_sca(m.v, s, row, 2);
    return m;
}

/** m[row][:] = s; dst = m */
static dmat2 dmat2_set_this_row_sca(dmat2 *m, double s, int row) {
    dmatN_set_row_sca(m->v, s, row, 2);
    return *m;
}


/** dst = m; dst[:][col] = s */
static dmat2 dmat2_set_col_sca(dmat2 m, double s, int col) {
    dmatN_set_col_sca(m.v, s, col, 2);
    return m;
}

/** m[:][col] = s; dst = m */
static dmat2 dmat2_set_this_col_sca(dmat2 *m, double s, int col) {
    dmatN_set_col_sca(m->v, s, col, 2);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static double dmat2_trace(dmat2 m) {
    return dmatN_trace(m.v, 2);
}


/** dst = m^t */
static dmat2 dmat2_transpose(dmat2 m) {
    dmat2 res;
    dmatN_transpose_no_alias(res.v, m.v, 2);
    return res;
}


/** dst = a @ b */
static dmat2 dmat2_mul_mat(dmat2 a, dmat2 b) {
    dmat2 res;
    dmatN_mul_mat_no_alias(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a @ b */
static dvec2 dmat2_mul_vec(dmat2 a, dvec2 b) {
    dvec2 res;
    dmatN_mul_vec_no_alias(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a @ b */
static dvec2 dvec2_mul_mat(dvec2 a, dmat2 b) {
    dvec2 res;
    dvecN_mul_mat_no_alias(res.v, a.v, b.v, 2);
    return res;
}

/** returns = determinant m */
static double dmat2_det(dmat2 m) {
    // from cglm/dmat2.h/glm_mat2_det
    return m.m[0][0] * m.m[1][1] - m.m[1][0] * m.m[0][1];
}


/** dst = inverted m */
static dmat2 dmat2_inv(dmat2 m) {
    // from cglm/dmat2.h/glm_mat2_inv
    double a = m.m[0][0], b = m.m[0][1];
    double c = m.m[1][0], d = m.m[1][1];

    dmat2 res;
    res.m[0][0] = d;
    res.m[0][1] = -b;
    res.m[1][0] = -c;
    res.m[1][1] = a;

    double det = a * d - b * c;
    dvecN_div(res.v, res.v, det, 4);

    return res;
}


#endif //M_MAT_DMAT2_H
