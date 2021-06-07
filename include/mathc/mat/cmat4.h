#ifndef MATHC_MAT_CMAT4_H
#define MATHC_MAT_CMAT4_H

#include "cmatn.h"
#include "../types/char.h"
#include "../vec/cvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static cmat4 cmat4_eye() {
    cmat4 res;
    cmatN_eye(res.v, 4);
    return res;
}

/** dst = (cmat4) v */
static cmat4 cmat4_cast_from_float(const float *v) {
    cmat4 res;
    cvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (cmat4) v */
static cmat4 cmat4_cast_from_double(const double *v) {
    cmat4 res;
    cvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (cmat4) v */
static cmat4 cmat4_cast_from_int(const int *v) {
    cmat4 res;
    cvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (cmat4) v */
static cmat4 cmat4_cast_from_unsigned(const unsigned *v) {
    cmat4 res;
    cvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (cmat4) v */
static cmat4 cmat4_cast_from_uint8_t(const uint8_t *v) {
    cmat4 res;
    cvecN_cast_into(res.v, v, 4*4);
    return res;
}


/** mat_a == mat_b */
static bool cmat4_cmp(cmat4 a, cmat4 b) {
    return cvecN_cmp(a.v, b.v, 4*4);
}


/** dst = mat[row][:] */
static cvec4 cmat4_get_row(cmat4 mat, int row) {
    cvec4 res;
    cmatN_get_row(res.v, mat.v, row, 4);
    return res;
}
/** dst = mat[row][:] */
static cvec4 cmat4_get_row_v(const int8_t *mat, int row) {
    return cmat4_get_row(CMat4(mat), row);
}


/** dst = mat[:][col] */
static cvec4 cmat4_get_col(cmat4 mat, int col) {
    cvec4 res;
    cmatN_get_col(res.v, mat.v, col, 4);
    return res;
}
/** dst = mat[:][col] */
static cvec4 cmat4_get_col_v(const int8_t *mat, int col) {
    return cmat4_get_col(CMat4(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static cmat4 cmat4_set_row(cmat4 mat, cvec4 vec, int row) {
    cmatN_set_row(mat.v, vec.v, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static cmat4 cmat4_set_row_v(const int8_t *mat, const int8_t *vec, int row) {
    return cmat4_set_row(CMat4(mat), CVec4(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static cmat4 cmat4_set_this_row(cmat4 *mat, cvec4 vec, int row) {
    cmatN_set_row(mat->v, vec.v, row, 4);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static cmat4 cmat4_set_this_row_v(int8_t *mat, const int8_t *vec, int row) {
    return cmat4_set_this_row((cmat4*) mat, CVec4(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static cmat4 cmat4_set_col(cmat4 mat, cvec4 vec, int col) {
    cmatN_set_col(mat.v, vec.v, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static cmat4 cmat4_set_col_v(const int8_t *mat, const int8_t *vec, int col) {
    return cmat4_set_col(CMat4(mat), CVec4(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static cmat4 cmat4_set_this_col(cmat4 *mat, cvec4 vec, int col) {
    cmatN_set_col(mat->v, vec.v, col, 4);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static cmat4 cmat4_set_this_col_v(int8_t *mat, const int8_t *vec, int col) {
    return cmat4_set_this_col((cmat4*) mat, CVec4(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static cmat4 cmat4_set_row_sca(cmat4 mat, int8_t scalar, int row) {
    cmatN_set_row_sca(mat.v, scalar, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static cmat4 cmat4_set_row_sca_v(const int8_t *mat, int8_t scalar, int row) {
    return cmat4_set_row_sca(CMat4(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static cmat4 cmat4_set_this_row_sca(cmat4 *mat, int8_t scalar, int row) {
    cmatN_set_row_sca(mat->v, scalar, row, 4);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static cmat4 cmat4_set_this_row_sca_v(int8_t *mat, int8_t scalar, int row) {
    return cmat4_set_this_row_sca((cmat4*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static cmat4 cmat4_set_col_sca(cmat4 mat, int8_t scalar, int col) {
    cmatN_set_col_sca(mat.v, scalar, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static cmat4 cmat4_set_col_sca_v(const int8_t *mat, int8_t scalar, int col) {
    return cmat4_set_col_sca(CMat4(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static cmat4 cmat4_set_this_col_sca(cmat4 *mat, int8_t scalar, int col) {
    cmatN_set_col_sca(mat->v, scalar, col, 4);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static cmat4 cmat4_set_this_col_sca_v(int8_t *mat, int8_t scalar, int col) {
    return cmat4_set_this_col_sca((cmat4*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static int cmat4_trace(cmat4 mat) {
    return cmatN_trace(mat.v, 4);
}
/** returns sum of diagonal form upper left to lower right */
static int cmat4_trace_v(const int8_t *mat) {
    return cmat4_trace(CMat4(mat));
}


/** dst = mat^t */
static cmat4 cmat4_transpose(cmat4 mat) {
    cmat4 res;
    cmatN_transpose_no_alias(res.v, mat.v, 4);
    return res;
}
/** dst = mat^t */
static cmat4 cmat4_transpose_v(const int8_t *mat) {
    return cmat4_transpose(CMat4(mat));
}


/** dst = a @ b */
static cmat4 cmat4_mul_mat(cmat4 mat_a, cmat4 mat_b) {
    cmat4 res;
    cmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static cmat4 cmat4_mul_mat_v(const int8_t *mat_a, const int8_t *mat_b) {
    return cmat4_mul_mat(CMat4(mat_a), CMat4(mat_b));
}


/** dst = a @ b */
static cvec4 cmat4_mul_vec(cmat4 mat_a, cvec4 vec_b) {
    cvec4 res;
    cmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 4);
    return res;
}
/** dst = a @ b */
static cvec4 cmat4_mul_vec_v(const int8_t *mat_a, const int8_t *vec_b) {
    return cmat4_mul_vec(CMat4(mat_a), CVec4(vec_b));
}


/** dst = a @ b */
static cvec4 cvec4_mul_mat(cvec4 vec_a, cmat4 mat_b) {
    cvec4 res;
    cvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static cvec4 cvec4_mul_mat_v(const int8_t *vec_a, const int8_t *mat_b) {
    return cvec4_mul_mat(CVec4(vec_a), CMat4(mat_b));
}


/** returns = determinant mat */
static int cmat4_det(cmat4 mat) {
    // from cglm/cmat4.h/glm_cmat4_det
    /* [square] det(A) = det(At) */
    int8_t t[6];
    int8_t a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3],
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
static int cmat4_det_v(const int8_t *mat) {
    return cmat4_det(CMat4(mat));
}


/** dst = inverted mat */
static cmat4 cmat4_inv(cmat4 mat) {
    // from cglm/cmat4.h/glm_cmat4_inv
    int8_t t[6];
    int8_t a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3];
    int8_t e = mat.m[1][0], f = mat.m[1][1], g = mat.m[1][2], h = mat.m[1][3];
    int8_t i = mat.m[2][0], j = mat.m[2][1], k = mat.m[2][2], l = mat.m[2][3];
    int8_t m = mat.m[3][0], n = mat.m[3][1], o = mat.m[3][2], p = mat.m[3][3];

    t[0] = k * p - o * l; t[1] = j * p - n * l; t[2] = j * o - n * k;
    t[3] = i * p - m * l; t[4] = i * o - m * k; t[5] = i * n - m * j;

    cmat4 res;
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

    int8_t inv_det = 1.0f / (a * res.m[0][0] + b * res.m[1][0]
                  + c * res.m[2][0] + d * res.m[3][0]);

    cvecN_scale(res.v, res.v, inv_det, 16);
    return res;
}
/** dst = inverted mat */
static cmat4 cmat4_inv_v(const int8_t *mat) {
    return cmat4_inv(CMat4(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static cmat2 cmat4_get_block2(cmat4 mat, int row, int col) {
    cmat2 res;
    cmatN_get_block(res.v, mat.v, row, col, 2, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static cmat2 cmat4_get_block2_v(const int8_t *mat, int row, int col) {
    return cmat4_get_block2(CMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static cmat4 cmat4_set_block2(cmat4 mat, cmat2 block_2, int row, int col) {
    cmatN_set_block(mat.v, block_2.v, row, col, 2, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static cmat4 cmat4_set_block2_v(const int8_t *mat, const int8_t *block_2, int row, int col) {
    return cmat4_set_block2(CMat4(mat), CMat2(block_2), row, col);
}


/** mat[col:col+2, row:row+2] = block; dst = mat */
static cmat4 cmat4_set_this_block2(cmat4 *mat, cmat2 block_2, int row, int col) {
    cmatN_set_block(mat->v, block_2.v, row, col, 2, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static cmat4 cmat4_set_this_block2_v(int8_t *mat, const int8_t *block_2, int row, int col) {
    return cmat4_set_this_block2((cmat4 *) mat, CMat2(block_2), row, col);
}


/** dst = mat[col:col+2, row:row+2] */
static cmat3 cmat4_get_block3(cmat4 mat, int row, int col) {
    cmat3 res;
    cmatN_get_block(res.v, mat.v, row, col, 3, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static cmat3 cmat4_get_block3_v(const int8_t *mat, int row, int col) {
    return cmat4_get_block3(CMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static cmat4 cmat4_set_block3(cmat4 mat, cmat3 block_3, int row, int col) {
    cmatN_set_block(mat.v, block_3.v, row, col, 3, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static cmat4 cmat4_set_block3_v(const int8_t *mat, const int8_t *block_3, int row, int col) {
    return cmat4_set_block3(CMat4(mat), CMat3(block_3), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static cmat4 cmat4_set_this_block3(cmat4 *mat, cmat3 block_3, int row, int col) {
    cmatN_set_block(mat->v, block_3.v, row, col, 3, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static cmat4 cmat4_set_this_block3_v(int8_t *mat, const int8_t *block_3, int row, int col) {
    return cmat4_set_this_block3((cmat4 *) mat, CMat3(block_3), row, col);
}


/** dst = mat[:2, :2] */
static cmat2 cmat4_get_upper_left2(cmat4 mat) {
    return cmat4_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static cmat2 cmat4_get_upper_left2_v(const int8_t *mat) {
    return cmat4_get_upper_left2(CMat4(mat));
}


/** dst = mat; dst[:2, :2] = block */
static cmat4 cmat4_set_upper_left2(cmat4 mat, cmat2 block_2) {
    return cmat4_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static cmat4 cmat4_set_upper_left2_v(const int8_t *mat, const int8_t *block_2) {
    return cmat4_set_upper_left2(CMat4(mat), CMat2(block_2));
}

/** mat[:2, :2] = block; dst = mat */
static cmat4 cmat4_set_this_upper_left2(cmat4 *mat, cmat2 block_2) {
    return cmat4_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static cmat4 cmat4_set_this_upper_left2_v(int8_t *mat, const int8_t *block_2) {
    return cmat4_set_this_upper_left2((cmat4 *) mat, CMat2(block_2));
}


/** dst = mat[:3, :3] */
static cmat3 cmat4_get_upper_left3(cmat4 mat) {
    return cmat4_get_block3(mat, 0, 0);
}
/** dst = mat[:3, :3] */
static cmat3 cmat4_get_upper_left3_v(const int8_t *mat) {
    return cmat4_get_upper_left3(CMat4(mat));
}


/** dst = mat; dst[:3, :3] = block */
static cmat4 cmat4_set_upper_left3(cmat4 mat, cmat3 block_3) {
    return cmat4_set_block3(mat, block_3, 0, 0);
}
/** dst = mat; dst[:3, :3] = block */
static cmat4 cmat4_set_upper_left3_v(const int8_t *mat, const int8_t *block_3) {
    return cmat4_set_upper_left3(CMat4(mat), CMat3(block_3));
}

/** mat[:3, :3] = block; dst = mat */
static cmat4 cmat4_set_this_upper_left3(cmat4 *mat, cmat3 block_3) {
    return cmat4_set_this_block3(mat, block_3, 0, 0);
}
/** mat[:3, :3] = block; dst = mat */
static cmat4 cmat4_set_this_upper_left3_v(int8_t *mat, const int8_t *block_3) {
    return cmat4_set_this_upper_left3((cmat4 *) mat, CMat3(block_3));
}

#endif //MATHC_MAT_CMAT4_H
