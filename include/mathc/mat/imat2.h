#ifndef MATHC_MAT_IMAT2_H
#define MATHC_MAT_IMAT2_H

#include "imatn.h"
#include "../types/int.h"


/** dst = r==c ? 1 : 0 (identity)  */
static imat2 imat2_eye() {
    imat2 res;
    imatN_eye(res.v, 2);
    return res;
}


/** dst = mat[row][:] */
static ivec2 imat2_get_row(imat2 mat, int row) {
    ivec2 res;
    imatN_get_row(res.v, mat.v, row, 2);
    return res;
}
/** dst = mat[row][:] */
static ivec2 imat2_get_row_v(const int *mat, int row) {
    return imat2_get_row(IMat2(mat), row);
}


/** dst = mat[:][col] */
static ivec2 imat2_get_col(imat2 mat, int col) {
    ivec2 res;
    imatN_get_col(res.v, mat.v, col, 2);
    return res;
}
/** dst = mat[:][col] */
static ivec2 imat2_get_col_v(const int *mat, int col) {
    return imat2_get_col(IMat2(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static imat2 imat2_set_row(imat2 mat, ivec2 vec, int row) {
    imatN_set_row(mat.v, vec.v, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static imat2 imat2_set_row_v(const int *mat, const int *vec, int row) {
    return imat2_set_row(IMat2(mat), IVec2(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static imat2 imat2_set_this_row(imat2 *mat, ivec2 vec, int row) {
    imatN_set_row(mat->v, vec.v, row, 2);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static imat2 imat2_set_this_row_v(int *mat, const int *vec, int row) {
    return imat2_set_this_row((imat2*) mat, IVec2(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static imat2 imat2_set_col(imat2 mat, ivec2 vec, int col) {
    imatN_set_col(mat.v, vec.v, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static imat2 imat2_set_col_v(const int *mat, const int *vec, int col) {
    return imat2_set_col(IMat2(mat), IVec2(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static imat2 imat2_set_this_col(imat2 *mat, ivec2 vec, int col) {
    imatN_set_col(mat->v, vec.v, col, 2);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static imat2 imat2_set_this_col_v(int *mat, const int *vec, int col) {
    return imat2_set_this_col((imat2*) mat, IVec2(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static imat2 imat2_set_row_sca(imat2 mat, int scalar, int row) {
    imatN_set_row_sca(mat.v, scalar, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static imat2 imat2_set_row_sca_v(const int *mat, int scalar, int row) {
    return imat2_set_row_sca(IMat2(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static imat2 imat2_set_this_row_sca(imat2 *mat, int scalar, int row) {
    imatN_set_row_sca(mat->v, scalar, row, 2);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static imat2 imat2_set_this_row_sca_v(int *mat, int scalar, int row) {
    return imat2_set_this_row_sca((imat2*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static imat2 imat2_set_col_sca(imat2 mat, int scalar, int col) {
    imatN_set_col_sca(mat.v, scalar, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static imat2 imat2_set_col_sca_v(const int *mat, int scalar, int col) {
    return imat2_set_col_sca(IMat2(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static imat2 imat2_set_this_col_sca(imat2 *mat, int scalar, int col) {
    imatN_set_col_sca(mat->v, scalar, col, 2);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static imat2 imat2_set_this_col_sca_v(int *mat, int scalar, int col) {
    return imat2_set_this_col_sca((imat2*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static int imat2_trace(imat2 mat) {
    return imatN_trace(mat.v, 2);
}
/** returns sum of diagonal form upper left to lower right */
static int imat2_trace_v(const int *mat) {
    return imat2_trace(IMat2(mat));
}


/** dst = mat^t */
static imat2 imat2_transpose(imat2 mat) {
    imat2 res;
    imatN_transpose_no_alias(res.v, mat.v, 2);
    return res;
}
/** dst = mat^t */
static imat2 imat2_transpose_v(const int *mat) {
    return imat2_transpose(IMat2(mat));
}


/** dst = a @ b */
static imat2 imat2_mul_mat(imat2 mat_a, imat2 mat_b) {
    imat2 res;
    imatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static imat2 imat2_mul_mat_v(const int *mat_a, const int *mat_b) {
    return imat2_mul_mat(IMat2(mat_a), IMat2(mat_b));
}


/** dst = a @ b */
static ivec2 imat2_mul_vec(imat2 mat_a, ivec2 vec_b) {
    ivec2 res;
    imatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 2);
    return res;
}
/** dst = a @ b */
static ivec2 imat2_mul_vec_v(const int *mat_a, const int *vec_b) {
    return imat2_mul_vec(IMat2(mat_a), IVec2(vec_b));
}


/** dst = a @ b */
static ivec2 ivec2_mul_mat(ivec2 vec_a, imat2 mat_b) {
    ivec2 res;
    ivecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static ivec2 ivec2_mul_mat_v(const int *vec_a, const int *mat_b) {
    return ivec2_mul_mat(IVec2(vec_a), IMat2(mat_b));
}


/** returns = determinant mat */
static int imat2_det(imat2 mat) {
    // from cglm/imat2.h/glm_imat2_det
    return mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1];
}
/** returns = determinant mat */
static int imat2_det_v(const int *mat) {
    return imat2_det(IMat2(mat));
}


/** dst = inverted mat */
static imat2 imat2_inv(imat2 mat) {
    // from cglm/imat2.h/glm_imat2_inv
    float a = mat.m[0][0], b = mat.m[0][1];
    float c = mat.m[1][0], d = mat.m[1][1];
    float inv_det = 1.0f / (a * d - b * c);

    imat2 res;
    res.m[0][0] = (int) (d * inv_det);
    res.m[0][1] = (int) (-b * inv_det);
    res.m[1][0] = (int) (-c * inv_det);
    res.m[1][1] = (int) (a * inv_det);
    return res;
}
/** dst = inverted mat */
static imat2 imat2_inv_v(const int *mat) {
    return imat2_inv(IMat2(mat));
}


#endif //MATHC_MAT_IMAT2_H
