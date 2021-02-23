#ifndef MATHC_MAT_IMAT3_H
#define MATHC_MAT_IMAT3_H

#include "imatn.h"
#include "../types/int.h"
#include "../vec/ivecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static imat3 imat3_eye() {
    imat3 res;
    imatN_eye(res.v, 3);
    return res;
}

/** dst = (imat2) v */
static imat3 imat3_cast_from_float(const float *v) {
    imat3 res;
    vecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (imat3) v */
static imat3 imat3_cast_from_double(const double *v) {
    imat3 res;
    vecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (imat3) v */
static imat3 imat3_cast_from_unsigned(const unsigned *v) {
    imat3 res;
    vecN_cast_into(res.v, v, 3*3);
    return res;
}


/** dst = mat[row][:] */
static ivec3 imat3_get_row(imat3 mat, int row) {
    ivec3 res;
    imatN_get_row(res.v, mat.v, row, 3);
    return res;
}
/** dst = mat[row][:] */
static ivec3 imat3_get_row_v(const int *mat, int row) {
    return imat3_get_row(IMat3(mat), row);
}


/** dst = mat[:][col] */
static ivec3 imat3_get_col(imat3 mat, int col) {
    ivec3 res;
    imatN_get_col(res.v, mat.v, col, 3);
    return res;
}
/** dst = mat[:][col] */
static ivec3 imat3_get_col_v(const int *mat, int col) {
    return imat3_get_col(IMat3(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static imat3 imat3_set_row(imat3 mat, ivec3 vec, int row) {
    imatN_set_row(mat.v, vec.v, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static imat3 imat3_set_row_v(const int *mat, const int *vec, int row) {
    return imat3_set_row(IMat3(mat), IVec3(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static imat3 imat3_set_this_row(imat3 *mat, ivec3 vec, int row) {
    imatN_set_row(mat->v, vec.v, row, 3);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static imat3 imat3_set_this_row_v(int *mat, const int *vec, int row) {
    return imat3_set_this_row((imat3*) mat, IVec3(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static imat3 imat3_set_col(imat3 mat, ivec3 vec, int col) {
    imatN_set_col(mat.v, vec.v, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static imat3 imat3_set_col_v(const int *mat, const int *vec, int col) {
    return imat3_set_col(IMat3(mat), IVec3(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static imat3 imat3_set_this_col(imat3 *mat, ivec3 vec, int col) {
    imatN_set_col(mat->v, vec.v, col, 3);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static imat3 imat3_set_this_col_v(int *mat, const int *vec, int col) {
    return imat3_set_this_col((imat3*) mat, IVec3(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static imat3 imat3_set_row_sca(imat3 mat, int scalar, int row) {
    imatN_set_row_sca(mat.v, scalar, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static imat3 imat3_set_row_sca_v(const int *mat, int scalar, int row) {
    return imat3_set_row_sca(IMat3(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static imat3 imat3_set_this_row_sca(imat3 *mat, int scalar, int row) {
    imatN_set_row_sca(mat->v, scalar, row, 3);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static imat3 imat3_set_this_row_sca_v(int *mat, int scalar, int row) {
    return imat3_set_this_row_sca((imat3*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static imat3 imat3_set_col_sca(imat3 mat, int scalar, int col) {
    imatN_set_col_sca(mat.v, scalar, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static imat3 imat3_set_col_sca_v(const int *mat, int scalar, int col) {
    return imat3_set_col_sca(IMat3(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static imat3 imat3_set_this_col_sca(imat3 *mat, int scalar, int col) {
    imatN_set_col_sca(mat->v, scalar, col, 3);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static imat3 imat3_set_this_col_sca_v(int *mat, int scalar, int col) {
    return imat3_set_this_col_sca((imat3*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static int imat3_trace(imat3 mat) {
    return imatN_trace(mat.v, 3);
}
/** returns sum of diagonal form upper left to lower right */
static int imat3_trace_v(const int *mat) {
    return imat3_trace(IMat3(mat));
}


/** dst = mat^t */
static imat3 imat3_transpose(imat3 mat) {
    imat3 res;
    imatN_transpose_no_alias(res.v, mat.v, 3);
    return res;
}
/** dst = mat^t */
static imat3 imat3_transpose_v(const int *mat) {
    return imat3_transpose(IMat3(mat));
}


/** dst = a @ b */
static imat3 imat3_mul_mat(imat3 mat_a, imat3 mat_b) {
    imat3 res;
    imatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static imat3 imat3_mul_mat_v(const int *mat_a, const int *mat_b) {
    return imat3_mul_mat(IMat3(mat_a), IMat3(mat_b));
}


/** dst = a @ b */
static ivec3 imat3_mul_vec(imat3 mat_a, ivec3 vec_b) {
    ivec3 res;
    imatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 3);
    return res;
}
/** dst = a @ b */
static ivec3 imat3_mul_vec_v(const int *mat_a, const int *vec_b) {
    return imat3_mul_vec(IMat3(mat_a), IVec3(vec_b));
}


/** dst = a @ b */
static ivec3 ivec3_mul_mat(ivec3 vec_a, imat3 mat_b) {
    ivec3 res;
    ivecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static ivec3 ivec3_mul_mat_v(const int *vec_a, const int *mat_b) {
    return ivec3_mul_mat(IVec3(vec_a), IMat3(mat_b));
}


/** returns = determinant mat */
static int imat3_det(imat3 mat) {
    // from cglm/imat3.h/glm_imat3_det
    int a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    int d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    int g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}
/** returns = determinant mat */
static int imat3_det_v(const int *mat) {
    return imat3_det(IMat3(mat));
}


/** dst = inverted mat */
static imat3 imat3_inv(imat3 mat) {
    // from cglm/imat3.h/glm_imat3_inv
    int a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    int d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    int g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    imat3 res;
    res.m[0][0] =   e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] =   b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] =   a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] =   d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] =   a * e - b * d;

    int inv_det = (int) (1.0f / (a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0]));

    ivecN_scale(res.v, res.v, inv_det, 9);
    return res;
}
/** dst = inverted mat */
static imat3 imat3_inv_v(const int *mat) {
    return imat3_inv(IMat3(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static imat2 imat3_get_block2(imat3 mat, int row, int col) {
    imat2 res;
    imatN_get_block(res.v, mat.v, row, col, 2, 3);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static imat2 imat3_get_block2_v(const int *mat, int row, int col) {
    return imat3_get_block2(IMat3(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static imat3 imat3_set_block2(imat3 mat, imat2 block_2, int row, int col) {
    imatN_set_block(mat.v, block_2.v, row, col, 2, 3);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static imat3 imat3_set_block2_v(const int *mat, const int *block_2, int row, int col) {
    return imat3_set_block2(IMat3(mat), IMat2(block_2), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static imat3 imat3_set_this_block2(imat3 *mat, imat2 block_2, int row, int col) {
    imatN_set_block(mat->v, block_2.v, row, col, 2, 3);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static imat3 imat3_set_this_block2_v(int *mat, const int *block_2, int row, int col) {
    return imat3_set_this_block2((imat3 *) mat, IMat2(block_2), row, col);
}


/** dst = mat[:2, :2] */
static imat2 imat3_get_upper_left(imat3 mat) {
    return imat3_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static imat2 imat3_get_upper_left_v(const int *mat) {
    return imat3_get_upper_left(IMat3(mat));
}


/** dst = mat; dst[:2, :2] = block */
static imat3 imat3_set_upper_left(imat3 mat, imat2 block_2) {
    return imat3_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static imat3 imat3_set_upper_left_v(const int *mat, const int *block_2) {
    return imat3_set_upper_left(IMat3(mat), IMat2(block_2));
}


/** mat[:2, :2] = block; dst = mat */
static imat3 imat3_set_this_upper_left(imat3 *mat, imat2 block_2) {
    return imat3_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static imat3 imat3_set_this_upper_left_v(int *mat, const int *block_2) {
    return imat3_set_this_upper_left((imat3 *) mat, IMat2(block_2));
}


#endif //MATHC_MAT_IMAT3_H
