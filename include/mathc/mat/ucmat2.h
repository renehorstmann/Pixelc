#ifndef MATHC_MAT_UCMAT2_H
#define MATHC_MAT_UCMAT2_H

#include "ucmatn.h"
#include "../types/uchar.h"
#include "../vec/ucvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static ucmat2 ucmat2_eye() {
    ucmat2 res;
    ucmatN_eye(res.v, 2);
    return res;
}

/** dst = (ucmat2) v */
static ucmat2 ucmat2_cast_from_float(const float *v) {
    ucmat2 res;
    ucvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (ucmat2) v */
static ucmat2 ucmat2_cast_from_double(const double *v) {
    ucmat2 res;
    ucvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (ucmat2) v */
static ucmat2 ucmat2_cast_from_int(const int *v) {
    ucmat2 res;
    ucvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (ucmat2) v */
static ucmat2 ucmat2_cast_from_unsigned(const unsigned *v) {
    ucmat2 res;
    ucvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (ucmat2) v */
static ucmat2 ucmat2_cast_from_char(const signed char *v) {
    ucmat2 res;
    ucvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** mat_a == mat_b */
static bool ucmat2_cmp(ucmat2 a, ucmat2 b) {
    return ucvecN_cmp(a.v, b.v, 2*2);
}

/** dst = mat[row][:] */
static ucvec2 ucmat2_get_row(ucmat2 mat, int row) {
    ucvec2 res;
    ucmatN_get_row(res.v, mat.v, row, 2);
    return res;
}
/** dst = mat[row][:] */
static ucvec2 ucmat2_get_row_v(const unsigned char *mat, int row) {
    return ucmat2_get_row(UCMat2(mat), row);
}


/** dst = mat[:][col] */
static ucvec2 ucmat2_get_col(ucmat2 mat, int col) {
    ucvec2 res;
    ucmatN_get_col(res.v, mat.v, col, 2);
    return res;
}
/** dst = mat[:][col] */
static ucvec2 ucmat2_get_col_v(const unsigned char *mat, int col) {
    return ucmat2_get_col(UCMat2(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static ucmat2 ucmat2_set_row(ucmat2 mat, ucvec2 vec, int row) {
    ucmatN_set_row(mat.v, vec.v, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static ucmat2 ucmat2_set_row_v(const unsigned char *mat, const unsigned char *vec, int row) {
    return ucmat2_set_row(UCMat2(mat), UCVec2(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static ucmat2 ucmat2_set_this_row(ucmat2 *mat, ucvec2 vec, int row) {
    ucmatN_set_row(mat->v, vec.v, row, 2);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static ucmat2 ucmat2_set_this_row_v(unsigned char *mat, const unsigned char *vec, int row) {
    return ucmat2_set_this_row((ucmat2*) mat, UCVec2(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static ucmat2 ucmat2_set_col(ucmat2 mat, ucvec2 vec, int col) {
    ucmatN_set_col(mat.v, vec.v, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static ucmat2 ucmat2_set_col_v(const unsigned char *mat, const unsigned char *vec, int col) {
    return ucmat2_set_col(UCMat2(mat), UCVec2(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static ucmat2 ucmat2_set_this_col(ucmat2 *mat, ucvec2 vec, int col) {
    ucmatN_set_col(mat->v, vec.v, col, 2);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static ucmat2 ucmat2_set_this_col_v(unsigned char *mat, const unsigned char *vec, int col) {
    return ucmat2_set_this_col((ucmat2*) mat, UCVec2(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static ucmat2 ucmat2_set_row_sca(ucmat2 mat, unsigned char scalar, int row) {
    ucmatN_set_row_sca(mat.v, scalar, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static ucmat2 ucmat2_set_row_sca_v(const unsigned char *mat, unsigned char scalar, int row) {
    return ucmat2_set_row_sca(UCMat2(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static ucmat2 ucmat2_set_this_row_sca(ucmat2 *mat, unsigned char scalar, int row) {
    ucmatN_set_row_sca(mat->v, scalar, row, 2);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static ucmat2 ucmat2_set_this_row_sca_v(unsigned char *mat, unsigned char scalar, int row) {
    return ucmat2_set_this_row_sca((ucmat2*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static ucmat2 ucmat2_set_col_sca(ucmat2 mat, unsigned char scalar, int col) {
    ucmatN_set_col_sca(mat.v, scalar, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static ucmat2 ucmat2_set_col_sca_v(const unsigned char *mat, unsigned char scalar, int col) {
    return ucmat2_set_col_sca(UCMat2(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static ucmat2 ucmat2_set_this_col_sca(ucmat2 *mat, unsigned char scalar, int col) {
    ucmatN_set_col_sca(mat->v, scalar, col, 2);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static ucmat2 ucmat2_set_this_col_sca_v(unsigned char *mat, unsigned char scalar, int col) {
    return ucmat2_set_this_col_sca((ucmat2*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static unsigned char ucmat2_trace(ucmat2 mat) {
    return ucmatN_trace(mat.v, 2);
}
/** returns sum of diagonal form upper left to lower right */
static unsigned char ucmat2_trace_v(const unsigned char *mat) {
    return ucmat2_trace(UCMat2(mat));
}


/** dst = mat^t */
static ucmat2 ucmat2_transpose(ucmat2 mat) {
    ucmat2 res;
    ucmatN_transpose_no_alias(res.v, mat.v, 2);
    return res;
}
/** dst = mat^t */
static ucmat2 ucmat2_transpose_v(const unsigned char *mat) {
    return ucmat2_transpose(UCMat2(mat));
}


/** dst = a @ b */
static ucmat2 ucmat2_mul_mat(ucmat2 mat_a, ucmat2 mat_b) {
    ucmat2 res;
    ucmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static ucmat2 ucmat2_mul_mat_v(const unsigned char *mat_a, const unsigned char *mat_b) {
    return ucmat2_mul_mat(UCMat2(mat_a), UCMat2(mat_b));
}


/** dst = a @ b */
static ucvec2 ucmat2_mul_vec(ucmat2 mat_a, ucvec2 vec_b) {
    ucvec2 res;
    ucmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 2);
    return res;
}
/** dst = a @ b */
static ucvec2 ucmat2_mul_vec_v(const unsigned char *mat_a, const unsigned char *vec_b) {
    return ucmat2_mul_vec(UCMat2(mat_a), UCVec2(vec_b));
}


/** dst = a @ b */
static ucvec2 ucvec2_mul_mat(ucvec2 vec_a, ucmat2 mat_b) {
    ucvec2 res;
    ucvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static ucvec2 ucvec2_mul_mat_v(const unsigned char *vec_a, const unsigned char *mat_b) {
    return ucvec2_mul_mat(UCVec2(vec_a), UCMat2(mat_b));
}


/** returns = determinant mat */
static unsigned char ucmat2_det(ucmat2 mat) {
    // from cglm/ucmat2.h/glm_ucmat2_det
    return mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1];
}
/** returns = determinant mat */
static unsigned char ucmat2_det_v(const unsigned char *mat) {
    return ucmat2_det(UCMat2(mat));
}


/** dst = inverted mat */
static ucmat2 ucmat2_inv(ucmat2 mat) {
    // from cglm/ucmat2.h/glm_ucmat2_inv
    float a = mat.m[0][0], b = mat.m[0][1];
    float c = mat.m[1][0], d = mat.m[1][1];
    float inv_det = 1.0f / (a * d - b * c);

    ucmat2 res;
    res.m[0][0] = (unsigned char) (d * inv_det);
    res.m[0][1] = (unsigned char) (-b * inv_det);
    res.m[1][0] = (unsigned char) (-c * inv_det);
    res.m[1][1] = (unsigned char) (a * inv_det);
    return res;
}
/** dst = inverted mat */
static ucmat2 ucmat2_inv_v(const unsigned char *mat) {
    return ucmat2_inv(UCMat2(mat));
}


#endif //MATHC_MAT_UCMAT2_H
