#ifndef M_MAT_IMAT2_H
#define M_MAT_IMAT2_H


#include "imatn.h"
#include "../types/imat2.h"
#include "../vec/ivecn.h"


/** dst = (imat2) v */
static imat2 imat2_cast_from_float(const float *cast) {
    imat2 res;
    imatN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (imat2) v */
static imat2 imat2_cast_from_double(const double *cast) {
    imat2 res;
    imatN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (imat2) v */
static imat2 imat2_cast_from_int(const int *cast) {
    imat2 res;
    imatN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (imat2) v */
static imat2 imat2_cast_from_uchar(const unsigned char *cast) {
    imat2 res;
    imatN_cast_into(res.v, cast, 2);
    return res;
}


/** dst = mat * 255 */
static imat2 imat2_cast_from_float_1(const float *cast) {
    imat2 res;
    imatN_cast_from_float_1(res.v, cast, 2);
    return res;
}

/** dst = mat * 255 */
static imat2 imat2_cast_from_double_1(const double *cast) {
    imat2 res;
    imatN_cast_from_double_1(res.v, cast, 2);
    return res;
}

/** dst = mat * 255 */
static imat2 imat2_cast_from_longdouble_1(const long double *cast) {
    imat2 res;
    imatN_cast_from_longdouble_1(res.v, cast, 2);
    return res;
}


/** dst = r==c ? 1 : 0 (identity)  */
static imat2 imat2_eye() {
    imat2 res;
    imatN_eye(res.v, 2);
    return res;
}

/** a == b */
static bool imat2_cmp(imat2 a, imat2 b) {
    return ivecN_cmp(a.v, b.v, 2 * 2);
}


/** dst = m[row][:] */
static ivec2 imat2_get_row(imat2 m, int row) {
    ivec2 res;
    imatN_get_row(res.v, m.v, row, 2);
    return res;
}


/** dst = m[:][col] */
static ivec2 imat2_get_col(imat2 m, int col) {
    ivec2 res;
    imatN_get_col(res.v, m.v, col, 2);
    return res;
}


/** dst = m; dst[row][:] = v */
static imat2 imat2_set_row(imat2 m, ivec2 v, int row) {
    imatN_set_row(m.v, v.v, row, 2);
    return m;
}

/** m[row][:] = v; dst = m */
static imat2 imat2_set_this_row(imat2 *m, ivec2 v, int row) {
    imatN_set_row(m->v, v.v, row, 2);
    return *m;
}

/** dst = m; dst[:][col] = v */
static imat2 imat2_set_col(imat2 m, ivec2 v, int col) {
    imatN_set_col(m.v, v.v, col, 2);
    return m;
}

/** mat[:][col] = v; dst = m */
static imat2 imat2_set_this_col(imat2 *mat, ivec2 v, int col) {
    imatN_set_col(mat->v, v.v, col, 2);
    return *mat;
}


/** dst = m; dst[row][:] = s */
static imat2 imat2_set_row_sca(imat2 m, int s, int row) {
    imatN_set_row_sca(m.v, s, row, 2);
    return m;
}

/** m[row][:] = s; dst = m */
static imat2 imat2_set_this_row_sca(imat2 *m, int s, int row) {
    imatN_set_row_sca(m->v, s, row, 2);
    return *m;
}


/** dst = m; dst[:][col] = s */
static imat2 imat2_set_col_sca(imat2 m, int s, int col) {
    imatN_set_col_sca(m.v, s, col, 2);
    return m;
}

/** m[:][col] = s; dst = m */
static imat2 imat2_set_this_col_sca(imat2 *m, int s, int col) {
    imatN_set_col_sca(m->v, s, col, 2);
    return *m;
}


/** returns sum of diagonal form upper left to lower right */
static int imat2_trace(imat2 m) {
    return imatN_trace(m.v, 2);
}


/** dst = m^t */
static imat2 imat2_transpose(imat2 m) {
    imat2 res;
    imatN_transpose_no_alias(res.v, m.v, 2);
    return res;
}


/** dst = a @ b */
static imat2 imat2_mul_mat(imat2 a, imat2 b) {
    imat2 res;
    imatN_mul_mat_no_alias(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a @ b */
static ivec2 imat2_mul_vec(imat2 a, ivec2 b) {
    ivec2 res;
    imatN_mul_vec_no_alias(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a @ b */
static ivec2 ivec2_mul_mat(ivec2 a, imat2 b) {
    ivec2 res;
    ivecN_mul_mat_no_alias(res.v, a.v, b.v, 2);
    return res;
}

/** returns = determinant m */
static int imat2_det(imat2 m) {
    // from cglm/imat2.h/glm_mat2_det
    return m.m[0][0] * m.m[1][1] - m.m[1][0] * m.m[0][1];
}


/** dst = inverted m */
static imat2 imat2_inv(imat2 m) {
    // from cglm/imat2.h/glm_mat2_inv
    int a = m.m[0][0], b = m.m[0][1];
    int c = m.m[1][0], d = m.m[1][1];

    imat2 res;
    res.m[0][0] = d;
    res.m[0][1] = -b;
    res.m[1][0] = -c;
    res.m[1][1] = a;

    int det = a * d - b * c;
    ivecN_div(res.v, res.v, det, 4);

    return res;
}



#endif //M_MAT_IMAT2_H
