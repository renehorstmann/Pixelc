#ifndef MATHC_MAT_UMAT3_H
#define MATHC_MAT_UMAT3_H

#include "umatn.h"
#include "../types/uint.h"
#include "../vec/uvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static umat3 umat3_eye() {
    umat3 res;
    umatN_eye(res.v, 3);
    return res;
}


/** dst = mat[row][:] */
static uvec3 umat3_get_row(umat3 mat, int row) {
    uvec3 res;
    umatN_get_row(res.v, mat.v, row, 3);
    return res;
}
/** dst = mat[row][:] */
static uvec3 umat3_get_row_v(const unsigned *mat, int row) {
    return umat3_get_row(UMat3(mat), row);
}


/** dst = mat[:][col] */
static uvec3 umat3_get_col(umat3 mat, int col) {
    uvec3 res;
    umatN_get_col(res.v, mat.v, col, 3);
    return res;
}
/** dst = mat[:][col] */
static uvec3 umat3_get_col_v(const unsigned *mat, int col) {
    return umat3_get_col(UMat3(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static umat3 umat3_set_row(umat3 mat, uvec3 vec, int row) {
    umatN_set_row(mat.v, vec.v, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static umat3 umat3_set_row_v(const unsigned *mat, const unsigned *vec, int row) {
    return umat3_set_row(UMat3(mat), UVec3(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static umat3 umat3_set_this_row(umat3 *mat, uvec3 vec, int row) {
    umatN_set_row(mat->v, vec.v, row, 3);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static umat3 umat3_set_this_row_v(unsigned *mat, const unsigned *vec, int row) {
    return umat3_set_this_row((umat3*) mat, UVec3(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static umat3 umat3_set_col(umat3 mat, uvec3 vec, int col) {
    umatN_set_col(mat.v, vec.v, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static umat3 umat3_set_col_v(const unsigned *mat, const unsigned *vec, int col) {
    return umat3_set_col(UMat3(mat), UVec3(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static umat3 umat3_set_this_col(umat3 *mat, uvec3 vec, int col) {
    umatN_set_col(mat->v, vec.v, col, 3);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static umat3 umat3_set_this_col_v(unsigned *mat, const unsigned *vec, int col) {
    return umat3_set_this_col((umat3*) mat, UVec3(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static umat3 umat3_set_row_sca(umat3 mat, unsigned scalar, int row) {
    umatN_set_row_sca(mat.v, scalar, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static umat3 umat3_set_row_sca_v(const unsigned *mat, unsigned scalar, int row) {
    return umat3_set_row_sca(UMat3(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static umat3 umat3_set_this_row_sca(umat3 *mat, unsigned scalar, int row) {
    umatN_set_row_sca(mat->v, scalar, row, 3);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static umat3 umat3_set_this_row_sca_v(unsigned *mat, unsigned scalar, int row) {
    return umat3_set_this_row_sca((umat3*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static umat3 umat3_set_col_sca(umat3 mat, unsigned scalar, int col) {
    umatN_set_col_sca(mat.v, scalar, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static umat3 umat3_set_col_sca_v(const unsigned *mat, unsigned scalar, int col) {
    return umat3_set_col_sca(UMat3(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static umat3 umat3_set_this_col_sca(umat3 *mat, unsigned scalar, int col) {
    umatN_set_col_sca(mat->v, scalar, col, 3);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static umat3 umat3_set_this_col_sca_v(unsigned *mat, unsigned scalar, int col) {
    return umat3_set_this_col_sca((umat3*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static unsigned umat3_trace(umat3 mat) {
    return umatN_trace(mat.v, 3);
}
/** returns sum of diagonal form upper left to lower right */
static unsigned umat3_trace_v(const unsigned *mat) {
    return umat3_trace(UMat3(mat));
}


/** dst = mat^t */
static umat3 umat3_transpose(umat3 mat) {
    umat3 res;
    umatN_transpose_no_alias(res.v, mat.v, 3);
    return res;
}
/** dst = mat^t */
static umat3 umat3_transpose_v(const unsigned *mat) {
    return umat3_transpose(UMat3(mat));
}


/** dst = a @ b */
static umat3 umat3_mul_mat(umat3 mat_a, umat3 mat_b) {
    umat3 res;
    umatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static umat3 umat3_mul_mat_v(const unsigned *mat_a, const unsigned *mat_b) {
    return umat3_mul_mat(UMat3(mat_a), UMat3(mat_b));
}


/** dst = a @ b */
static uvec3 umat3_mul_vec(umat3 mat_a, uvec3 vec_b) {
    uvec3 res;
    umatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 3);
    return res;
}
/** dst = a @ b */
static uvec3 umat3_mul_vec_v(const unsigned *mat_a, const unsigned *vec_b) {
    return umat3_mul_vec(UMat3(mat_a), UVec3(vec_b));
}


/** dst = a @ b */
static uvec3 uvec3_mul_mat(uvec3 vec_a, umat3 mat_b) {
    uvec3 res;
    uvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static uvec3 uvec3_mul_mat_v(const unsigned *vec_a, const unsigned *mat_b) {
    return uvec3_mul_mat(UVec3(vec_a), UMat3(mat_b));
}


/** returns = determinant mat */
static unsigned umat3_det(umat3 mat) {
    // from cglm/umat3.h/glm_umat3_det
    unsigned a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    unsigned d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    unsigned g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}
/** returns = determinant mat */
static unsigned umat3_det_v(const unsigned *mat) {
    return umat3_det(UMat3(mat));
}


/** dst = inverted mat */
static umat3 umat3_inv(umat3 mat) {
    // from cglm/umat3.h/glm_umat3_inv
    unsigned a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    unsigned d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    unsigned g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    umat3 res;
    res.m[0][0] =   e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] =   b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] =   a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] =   d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] =   a * e - b * d;

    unsigned inv_det = (unsigned) (1.0f / (a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0]));

    uvecN_scale(res.v, res.v, inv_det, 9);
    return res;
}
/** dst = inverted mat */
static umat3 umat3_inv_v(const unsigned *mat) {
    return umat3_inv(UMat3(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static umat2 umat3_get_block2(umat3 mat, int row, int col) {
    umat2 res;
    umatN_get_block(res.v, mat.v, row, col, 2, 3);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static umat2 umat3_get_block2_v(const unsigned *mat, int row, int col) {
    return umat3_get_block2(UMat3(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static umat3 umat3_set_block2(umat3 mat, umat2 block_2, int row, int col) {
    umatN_set_block(mat.v, block_2.v, row, col, 2, 3);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static umat3 umat3_set_block2_v(const unsigned *mat, const unsigned *block_2, int row, int col) {
    return umat3_set_block2(UMat3(mat), UMat2(block_2), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static umat3 umat3_set_this_block2(umat3 *mat, umat2 block_2, int row, int col) {
    umatN_set_block(mat->v, block_2.v, row, col, 2, 3);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static umat3 umat3_set_this_block2_v(unsigned *mat, const unsigned *block_2, int row, int col) {
    return umat3_set_this_block2((umat3 *) mat, UMat2(block_2), row, col);
}


/** dst = mat[:2, :2] */
static umat2 umat3_get_upper_left(umat3 mat) {
    return umat3_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static umat2 umat3_get_upper_left_v(const unsigned *mat) {
    return umat3_get_upper_left(UMat3(mat));
}


/** dst = mat; dst[:2, :2] = block */
static umat3 umat3_set_upper_left(umat3 mat, umat2 block_2) {
    return umat3_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static umat3 umat3_set_upper_left_v(const unsigned *mat, const unsigned *block_2) {
    return umat3_set_upper_left(UMat3(mat), UMat2(block_2));
}


/** mat[:2, :2] = block; dst = mat */
static umat3 umat3_set_this_upper_left(umat3 *mat, umat2 block_2) {
    return umat3_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static umat3 umat3_set_this_upper_left_v(unsigned *mat, const unsigned *block_2) {
    return umat3_set_this_upper_left((umat3 *) mat, UMat2(block_2));
}


#endif //MATHC_MAT_UMAT3_H
