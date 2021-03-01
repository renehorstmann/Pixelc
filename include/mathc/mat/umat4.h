#ifndef MATHC_MAT_UMAT4_H
#define MATHC_MAT_UMAT4_H

#include "umatn.h"
#include "../types/uint.h"
#include "../vec/uvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static umat4 umat4_eye() {
    umat4 res;
    umatN_eye(res.v, 4);
    return res;
}

/** dst = (umat4) v */
static umat4 umat4_cast_from_float(const float *v) {
    umat4 res;
    uvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (umat4) v */
static umat4 umat4_cast_from_double(const double *v) {
    umat4 res;
    uvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (umat4) v */
static umat4 umat4_cast_from_int(const int *v) {
    umat4 res;
    uvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** mat_a == mat_b */
static bool umat4_cmp(umat4 a, umat4 b) {
    return uvecN_cmp(a.v, b.v, 4*4);
}

/** dst = mat[row][:] */
static uvec4 umat4_get_row(umat4 mat, int row) {
    uvec4 res;
    umatN_get_row(res.v, mat.v, row, 4);
    return res;
}
/** dst = mat[row][:] */
static uvec4 umat4_get_row_v(const unsigned *mat, int row) {
    return umat4_get_row(UMat4(mat), row);
}


/** dst = mat[:][col] */
static uvec4 umat4_get_col(umat4 mat, int col) {
    uvec4 res;
    umatN_get_col(res.v, mat.v, col, 4);
    return res;
}
/** dst = mat[:][col] */
static uvec4 umat4_get_col_v(const unsigned *mat, int col) {
    return umat4_get_col(UMat4(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static umat4 umat4_set_row(umat4 mat, uvec4 vec, int row) {
    umatN_set_row(mat.v, vec.v, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static umat4 umat4_set_row_v(const unsigned *mat, const unsigned *vec, int row) {
    return umat4_set_row(UMat4(mat), UVec4(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static umat4 umat4_set_this_row(umat4 *mat, uvec4 vec, int row) {
    umatN_set_row(mat->v, vec.v, row, 4);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static umat4 umat4_set_this_row_v(unsigned *mat, const unsigned *vec, int row) {
    return umat4_set_this_row((umat4*) mat, UVec4(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static umat4 umat4_set_col(umat4 mat, uvec4 vec, int col) {
    umatN_set_col(mat.v, vec.v, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static umat4 umat4_set_col_v(const unsigned *mat, const unsigned *vec, int col) {
    return umat4_set_col(UMat4(mat), UVec4(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static umat4 umat4_set_this_col(umat4 *mat, uvec4 vec, int col) {
    umatN_set_col(mat->v, vec.v, col, 4);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static umat4 umat4_set_this_col_v(unsigned *mat, const unsigned *vec, int col) {
    return umat4_set_this_col((umat4*) mat, UVec4(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static umat4 umat4_set_row_sca(umat4 mat, unsigned scalar, int row) {
    umatN_set_row_sca(mat.v, scalar, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static umat4 umat4_set_row_sca_v(const unsigned *mat, unsigned scalar, int row) {
    return umat4_set_row_sca(UMat4(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static umat4 umat4_set_this_row_sca(umat4 *mat, unsigned scalar, int row) {
    umatN_set_row_sca(mat->v, scalar, row, 4);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static umat4 umat4_set_this_row_sca_v(unsigned *mat, unsigned scalar, int row) {
    return umat4_set_this_row_sca((umat4*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static umat4 umat4_set_col_sca(umat4 mat, unsigned scalar, int col) {
    umatN_set_col_sca(mat.v, scalar, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static umat4 umat4_set_col_sca_v(const unsigned *mat, unsigned scalar, int col) {
    return umat4_set_col_sca(UMat4(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static umat4 umat4_set_this_col_sca(umat4 *mat, unsigned scalar, int col) {
    umatN_set_col_sca(mat->v, scalar, col, 4);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static umat4 umat4_set_this_col_sca_v(unsigned *mat, unsigned scalar, int col) {
    return umat4_set_this_col_sca((umat4*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static unsigned umat4_trace(umat4 mat) {
    return umatN_trace(mat.v, 4);
}
/** returns sum of diagonal form upper left to lower right */
static unsigned umat4_trace_v(const unsigned *mat) {
    return umat4_trace(UMat4(mat));
}


/** dst = mat^t */
static umat4 umat4_transpose(umat4 mat) {
    umat4 res;
    umatN_transpose_no_alias(res.v, mat.v, 4);
    return res;
}
/** dst = mat^t */
static umat4 umat4_transpose_v(const unsigned *mat) {
    return umat4_transpose(UMat4(mat));
}


/** dst = a @ b */
static umat4 umat4_mul_mat(umat4 mat_a, umat4 mat_b) {
    umat4 res;
    umatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static umat4 umat4_mul_mat_v(const unsigned *mat_a, const unsigned *mat_b) {
    return umat4_mul_mat(UMat4(mat_a), UMat4(mat_b));
}


/** dst = a @ b */
static uvec4 umat4_mul_vec(umat4 mat_a, uvec4 vec_b) {
    uvec4 res;
    umatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 4);
    return res;
}
/** dst = a @ b */
static uvec4 umat4_mul_vec_v(const unsigned *mat_a, const unsigned *vec_b) {
    return umat4_mul_vec(UMat4(mat_a), UVec4(vec_b));
}


/** dst = a @ b */
static uvec4 uvec4_mul_mat(uvec4 vec_a, umat4 mat_b) {
    uvec4 res;
    uvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static uvec4 uvec4_mul_mat_v(const unsigned *vec_a, const unsigned *mat_b) {
    return uvec4_mul_mat(UVec4(vec_a), UMat4(mat_b));
}


/** returns = determinant mat */
static unsigned umat4_det(umat4 mat) {
    // from cglm/umat4.h/glm_umat4_det
    /* [square] det(A) = det(At) */
    unsigned t[6];
    unsigned a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3],
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
static unsigned umat4_det_v(const unsigned *mat) {
    return umat4_det(UMat4(mat));
}


/** dst = inverted mat */
static umat4 umat4_inv(umat4 mat) {
    // from cglm/umat4.h/glm_umat4_inv
    unsigned t[6];
    unsigned a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3];
    unsigned e = mat.m[1][0], f = mat.m[1][1], g = mat.m[1][2], h = mat.m[1][3];
    unsigned i = mat.m[2][0], j = mat.m[2][1], k = mat.m[2][2], l = mat.m[2][3];
    unsigned m = mat.m[3][0], n = mat.m[3][1], o = mat.m[3][2], p = mat.m[3][3];

    t[0] = k * p - o * l; t[1] = j * p - n * l; t[2] = j * o - n * k;
    t[3] = i * p - m * l; t[4] = i * o - m * k; t[5] = i * n - m * j;

    umat4 res;
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

    unsigned inv_det = 1.0f / (a * res.m[0][0] + b * res.m[1][0]
                  + c * res.m[2][0] + d * res.m[3][0]);

    uvecN_scale(res.v, res.v, inv_det, 16);
    return res;
}
/** dst = inverted mat */
static umat4 umat4_inv_v(const unsigned *mat) {
    return umat4_inv(UMat4(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static umat2 umat4_get_block2(umat4 mat, int row, int col) {
    umat2 res;
    umatN_get_block(res.v, mat.v, row, col, 2, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static umat2 umat4_get_block2_v(const unsigned *mat, int row, int col) {
    return umat4_get_block2(UMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static umat4 umat4_set_block2(umat4 mat, umat2 block_2, int row, int col) {
    umatN_set_block(mat.v, block_2.v, row, col, 2, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static umat4 umat4_set_block2_v(const unsigned *mat, const unsigned *block_2, int row, int col) {
    return umat4_set_block2(UMat4(mat), UMat2(block_2), row, col);
}


/** mat[col:col+2, row:row+2] = block; dst = mat */
static umat4 umat4_set_this_block2(umat4 *mat, umat2 block_2, int row, int col) {
    umatN_set_block(mat->v, block_2.v, row, col, 2, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static umat4 umat4_set_this_block2_v(unsigned *mat, const unsigned *block_2, int row, int col) {
    return umat4_set_this_block2((umat4 *) mat, UMat2(block_2), row, col);
}


/** dst = mat[col:col+2, row:row+2] */
static umat3 umat4_get_block3(umat4 mat, int row, int col) {
    umat3 res;
    umatN_get_block(res.v, mat.v, row, col, 3, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static umat3 umat4_get_block3_v(const unsigned *mat, int row, int col) {
    return umat4_get_block3(UMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static umat4 umat4_set_block3(umat4 mat, umat3 block_3, int row, int col) {
    umatN_set_block(mat.v, block_3.v, row, col, 3, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static umat4 umat4_set_block3_v(const unsigned *mat, const unsigned *block_3, int row, int col) {
    return umat4_set_block3(UMat4(mat), UMat3(block_3), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static umat4 umat4_set_this_block3(umat4 *mat, umat3 block_3, int row, int col) {
    umatN_set_block(mat->v, block_3.v, row, col, 3, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static umat4 umat4_set_this_block3_v(unsigned *mat, const unsigned *block_3, int row, int col) {
    return umat4_set_this_block3((umat4 *) mat, UMat3(block_3), row, col);
}


/** dst = mat[:2, :2] */
static umat2 umat4_get_upper_left2(umat4 mat) {
    return umat4_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static umat2 umat4_get_upper_left2_v(const unsigned *mat) {
    return umat4_get_upper_left2(UMat4(mat));
}


/** dst = mat; dst[:2, :2] = block */
static umat4 umat4_set_upper_left2(umat4 mat, umat2 block_2) {
    return umat4_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static umat4 umat4_set_upper_left2_v(const unsigned *mat, const unsigned *block_2) {
    return umat4_set_upper_left2(UMat4(mat), UMat2(block_2));
}

/** mat[:2, :2] = block; dst = mat */
static umat4 umat4_set_this_upper_left2(umat4 *mat, umat2 block_2) {
    return umat4_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static umat4 umat4_set_this_upper_left2_v(unsigned *mat, const unsigned *block_2) {
    return umat4_set_this_upper_left2((umat4 *) mat, UMat2(block_2));
}


/** dst = mat[:3, :3] */
static umat3 umat4_get_upper_left3(umat4 mat) {
    return umat4_get_block3(mat, 0, 0);
}
/** dst = mat[:3, :3] */
static umat3 umat4_get_upper_left3_v(const unsigned *mat) {
    return umat4_get_upper_left3(UMat4(mat));
}


/** dst = mat; dst[:3, :3] = block */
static umat4 umat4_set_upper_left3(umat4 mat, umat3 block_3) {
    return umat4_set_block3(mat, block_3, 0, 0);
}
/** dst = mat; dst[:3, :3] = block */
static umat4 umat4_set_upper_left3_v(const unsigned *mat, const unsigned *block_3) {
    return umat4_set_upper_left3(UMat4(mat), UMat3(block_3));
}

/** mat[:3, :3] = block; dst = mat */
static umat4 umat4_set_this_upper_left3(umat4 *mat, umat3 block_3) {
    return umat4_set_this_block3(mat, block_3, 0, 0);
}
/** mat[:3, :3] = block; dst = mat */
static umat4 umat4_set_this_upper_left3_v(unsigned *mat, const unsigned *block_3) {
    return umat4_set_this_upper_left3((umat4 *) mat, UMat3(block_3));
}

#endif //MATHC_MAT_UMAT4_H
