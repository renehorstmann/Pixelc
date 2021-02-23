#ifndef MATHC_MAT_IMAT4_H
#define MATHC_MAT_IMAT4_H

#include "imatn.h"
#include "../types/int.h"
#include "../vec/ivecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static imat4 imat4_eye() {
    imat4 res;
    imatN_eye(res.v, 4);
    return res;
}

/** dst = (imat4) v */
static imat4 imat4_cast_from_float(const float *v) {
    imat4 res;
    ivecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (imat4) v */
static imat4 imat4_cast_from_double(const double *v) {
    imat4 res;
    ivecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (imat4) v */
static imat4 imat4_cast_from_unsigned(const unsigned *v) {
    imat4 res;
    ivecN_cast_into(res.v, v, 4 * 4);
    return res;
}


/** dst = mat[row][:] */
static ivec4 imat4_get_row(imat4 mat, int row) {
    ivec4 res;
    imatN_get_row(res.v, mat.v, row, 4);
    return res;
}
/** dst = mat[row][:] */
static ivec4 imat4_get_row_v(const int *mat, int row) {
    return imat4_get_row(IMat4(mat), row);
}


/** dst = mat[:][col] */
static ivec4 imat4_get_col(imat4 mat, int col) {
    ivec4 res;
    imatN_get_col(res.v, mat.v, col, 4);
    return res;
}
/** dst = mat[:][col] */
static ivec4 imat4_get_col_v(const int *mat, int col) {
    return imat4_get_col(IMat4(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static imat4 imat4_set_row(imat4 mat, ivec4 vec, int row) {
    imatN_set_row(mat.v, vec.v, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static imat4 imat4_set_row_v(const int *mat, const int *vec, int row) {
    return imat4_set_row(IMat4(mat), IVec4(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static imat4 imat4_set_this_row(imat4 *mat, ivec4 vec, int row) {
    imatN_set_row(mat->v, vec.v, row, 4);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static imat4 imat4_set_this_row_v(int *mat, const int *vec, int row) {
    return imat4_set_this_row((imat4*) mat, IVec4(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static imat4 imat4_set_col(imat4 mat, ivec4 vec, int col) {
    imatN_set_col(mat.v, vec.v, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static imat4 imat4_set_col_v(const int *mat, const int *vec, int col) {
    return imat4_set_col(IMat4(mat), IVec4(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static imat4 imat4_set_this_col(imat4 *mat, ivec4 vec, int col) {
    imatN_set_col(mat->v, vec.v, col, 4);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static imat4 imat4_set_this_col_v(int *mat, const int *vec, int col) {
    return imat4_set_this_col((imat4*) mat, IVec4(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static imat4 imat4_set_row_sca(imat4 mat, int scalar, int row) {
    imatN_set_row_sca(mat.v, scalar, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static imat4 imat4_set_row_sca_v(const int *mat, int scalar, int row) {
    return imat4_set_row_sca(IMat4(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static imat4 imat4_set_this_row_sca(imat4 *mat, int scalar, int row) {
    imatN_set_row_sca(mat->v, scalar, row, 4);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static imat4 imat4_set_this_row_sca_v(int *mat, int scalar, int row) {
    return imat4_set_this_row_sca((imat4*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static imat4 imat4_set_col_sca(imat4 mat, int scalar, int col) {
    imatN_set_col_sca(mat.v, scalar, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static imat4 imat4_set_col_sca_v(const int *mat, int scalar, int col) {
    return imat4_set_col_sca(IMat4(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static imat4 imat4_set_this_col_sca(imat4 *mat, int scalar, int col) {
    imatN_set_col_sca(mat->v, scalar, col, 4);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static imat4 imat4_set_this_col_sca_v(int *mat, int scalar, int col) {
    return imat4_set_this_col_sca((imat4*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static int imat4_trace(imat4 mat) {
    return imatN_trace(mat.v, 4);
}
/** returns sum of diagonal form upper left to lower right */
static int imat4_trace_v(const int *mat) {
    return imat4_trace(IMat4(mat));
}


/** dst = mat^t */
static imat4 imat4_transpose(imat4 mat) {
    imat4 res;
    imatN_transpose_no_alias(res.v, mat.v, 4);
    return res;
}
/** dst = mat^t */
static imat4 imat4_transpose_v(const int *mat) {
    return imat4_transpose(IMat4(mat));
}


/** dst = a @ b */
static imat4 imat4_mul_mat(imat4 mat_a, imat4 mat_b) {
    imat4 res;
    imatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static imat4 imat4_mul_mat_v(const int *mat_a, const int *mat_b) {
    return imat4_mul_mat(IMat4(mat_a), IMat4(mat_b));
}


/** dst = a @ b */
static ivec4 imat4_mul_vec(imat4 mat_a, ivec4 vec_b) {
    ivec4 res;
    imatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 4);
    return res;
}
/** dst = a @ b */
static ivec4 imat4_mul_vec_v(const int *mat_a, const int *vec_b) {
    return imat4_mul_vec(IMat4(mat_a), IVec4(vec_b));
}


/** dst = a @ b */
static ivec4 ivec4_mul_mat(ivec4 vec_a, imat4 mat_b) {
    ivec4 res;
    ivecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static ivec4 ivec4_mul_mat_v(const int *vec_a, const int *mat_b) {
    return ivec4_mul_mat(IVec4(vec_a), IMat4(mat_b));
}


/** returns = determinant mat */
static int imat4_det(imat4 mat) {
    // from cglm/imat4.h/glm_imat4_det
    /* [square] det(A) = det(At) */
    int t[6];
    int a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3],
            e = mat.m[1][0], f = mat.m[1][1], g = mat.m[1][2], h = mat.m[1][3],
            i = mat.m[2][0], j = mat.m[2][1], k = mat.m[2][2], l = mat.m[2][3],
            m = mat.m[3][0], n = mat.m[3][1], o = mat.m[3][2], p = mat.m[3][3];

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
/** returns = determinant mat */
static int imat4_det_v(const int *mat) {
    return imat4_det(IMat4(mat));
}


/** dst = inverted mat */
static imat4 imat4_inv(imat4 mat) {
    // from cglm/imat4.h/glm_imat4_inv
    int t[6];
    int a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3];
    int e = mat.m[1][0], f = mat.m[1][1], g = mat.m[1][2], h = mat.m[1][3];
    int i = mat.m[2][0], j = mat.m[2][1], k = mat.m[2][2], l = mat.m[2][3];
    int m = mat.m[3][0], n = mat.m[3][1], o = mat.m[3][2], p = mat.m[3][3];

    t[0] = k * p - o * l; t[1] = j * p - n * l; t[2] = j * o - n * k;
    t[3] = i * p - m * l; t[4] = i * o - m * k; t[5] = i * n - m * j;

    imat4 res;
    res.m[0][0] =  f * t[0] - g * t[1] + h * t[2];
    res.m[1][0] =-(e * t[0] - g * t[3] + h * t[4]);
    res.m[2][0] =  e * t[1] - f * t[3] + h * t[5];
    res.m[3][0] =-(e * t[2] - f * t[4] + g * t[5]);

    res.m[0][1] =-(b * t[0] - c * t[1] + d * t[2]);
    res.m[1][1] =  a * t[0] - c * t[3] + d * t[4];
    res.m[2][1] =-(a * t[1] - b * t[3] + d * t[5]);
    res.m[3][1] =  a * t[2] - b * t[4] + c * t[5];

    t[0] = g * p - o * h; t[1] = f * p - n * h; t[2] = f * o - n * g;
    t[3] = e * p - m * h; t[4] = e * o - m * g; t[5] = e * n - m * f;

    res.m[0][2] =  b * t[0] - c * t[1] + d * t[2];
    res.m[1][2] =-(a * t[0] - c * t[3] + d * t[4]);
    res.m[2][2] =  a * t[1] - b * t[3] + d * t[5];
    res.m[3][2] =-(a * t[2] - b * t[4] + c * t[5]);

    t[0] = g * l - k * h; t[1] = f * l - j * h; t[2] = f * k - j * g;
    t[3] = e * l - i * h; t[4] = e * k - i * g; t[5] = e * j - i * f;

    res.m[0][3] =-(b * t[0] - c * t[1] + d * t[2]);
    res.m[1][3] =  a * t[0] - c * t[3] + d * t[4];
    res.m[2][3] =-(a * t[1] - b * t[3] + d * t[5]);
    res.m[3][3] =  a * t[2] - b * t[4] + c * t[5];

    int inv_det = 1.0f / (a * res.m[0][0] + b * res.m[1][0]
                  + c * res.m[2][0] + d * res.m[3][0]);

    ivecN_scale(res.v, res.v, inv_det, 16);
    return res;
}
/** dst = inverted mat */
static imat4 imat4_inv_v(const int *mat) {
    return imat4_inv(IMat4(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static imat2 imat4_get_block2(imat4 mat, int row, int col) {
    imat2 res;
    imatN_get_block(res.v, mat.v, row, col, 2, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static imat2 imat4_get_block2_v(const int *mat, int row, int col) {
    return imat4_get_block2(IMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static imat4 imat4_set_block2(imat4 mat, imat2 block_2, int row, int col) {
    imatN_set_block(mat.v, block_2.v, row, col, 2, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static imat4 imat4_set_block2_v(const int *mat, const int *block_2, int row, int col) {
    return imat4_set_block2(IMat4(mat), IMat2(block_2), row, col);
}


/** mat[col:col+2, row:row+2] = block; dst = mat */
static imat4 imat4_set_this_block2(imat4 *mat, imat2 block_2, int row, int col) {
    imatN_set_block(mat->v, block_2.v, row, col, 2, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static imat4 imat4_set_this_block2_v(int *mat, const int *block_2, int row, int col) {
    return imat4_set_this_block2((imat4 *) mat, IMat2(block_2), row, col);
}


/** dst = mat[col:col+2, row:row+2] */
static imat3 imat4_get_block3(imat4 mat, int row, int col) {
    imat3 res;
    imatN_get_block(res.v, mat.v, row, col, 3, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static imat3 imat4_get_block3_v(const int *mat, int row, int col) {
    return imat4_get_block3(IMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static imat4 imat4_set_block3(imat4 mat, imat3 block_3, int row, int col) {
    imatN_set_block(mat.v, block_3.v, row, col, 3, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static imat4 imat4_set_block3_v(const int *mat, const int *block_3, int row, int col) {
    return imat4_set_block3(IMat4(mat), IMat3(block_3), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static imat4 imat4_set_this_block3(imat4 *mat, imat3 block_3, int row, int col) {
    imatN_set_block(mat->v, block_3.v, row, col, 3, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static imat4 imat4_set_this_block3_v(int *mat, const int *block_3, int row, int col) {
    return imat4_set_this_block3((imat4 *) mat, IMat3(block_3), row, col);
}


/** dst = mat[:2, :2] */
static imat2 imat4_get_upper_left2(imat4 mat) {
    return imat4_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static imat2 imat4_get_upper_left2_v(const int *mat) {
    return imat4_get_upper_left2(IMat4(mat));
}


/** dst = mat; dst[:2, :2] = block */
static imat4 imat4_set_upper_left2(imat4 mat, imat2 block_2) {
    return imat4_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static imat4 imat4_set_upper_left2_v(const int *mat, const int *block_2) {
    return imat4_set_upper_left2(IMat4(mat), IMat2(block_2));
}

/** mat[:2, :2] = block; dst = mat */
static imat4 imat4_set_this_upper_left2(imat4 *mat, imat2 block_2) {
    return imat4_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static imat4 imat4_set_this_upper_left2_v(int *mat, const int *block_2) {
    return imat4_set_this_upper_left2((imat4 *) mat, IMat2(block_2));
}


/** dst = mat[:3, :3] */
static imat3 imat4_get_upper_left3(imat4 mat) {
    return imat4_get_block3(mat, 0, 0);
}
/** dst = mat[:3, :3] */
static imat3 imat4_get_upper_left3_v(const int *mat) {
    return imat4_get_upper_left3(IMat4(mat));
}


/** dst = mat; dst[:3, :3] = block */
static imat4 imat4_set_upper_left3(imat4 mat, imat3 block_3) {
    return imat4_set_block3(mat, block_3, 0, 0);
}
/** dst = mat; dst[:3, :3] = block */
static imat4 imat4_set_upper_left3_v(const int *mat, const int *block_3) {
    return imat4_set_upper_left3(IMat4(mat), IMat3(block_3));
}

/** mat[:3, :3] = block; dst = mat */
static imat4 imat4_set_this_upper_left3(imat4 *mat, imat3 block_3) {
    return imat4_set_this_block3(mat, block_3, 0, 0);
}
/** mat[:3, :3] = block; dst = mat */
static imat4 imat4_set_this_upper_left3_v(int *mat, const int *block_3) {
    return imat4_set_this_upper_left3((imat4 *) mat, IMat3(block_3));
}

#endif //MATHC_MAT_IMAT4_H
