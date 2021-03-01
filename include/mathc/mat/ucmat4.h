#ifndef MATHC_MAT_UCMAT4_H
#define MATHC_MAT_UCMAT4_H

#include "ucmatn.h"
#include "../types/uchar.h"
#include "../vec/ucvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static ucmat4 ucmat4_eye() {
    ucmat4 res;
    ucmatN_eye(res.v, 4);
    return res;
}

/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_float(const float *v) {
    ucmat4 res;
    ucvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_double(const double *v) {
    ucmat4 res;
    ucvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_int(const int *v) {
    ucmat4 res;
    ucvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_unsigned(const unsigned *v) {
    ucmat4 res;
    ucvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (ucmat4) v */
static ucmat4 ucmat4_cast_from_char(const char *v) {
    ucmat4 res;
    ucvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** mat_a == mat_b */
static bool ucmat4_cmp(ucmat4 a, ucmat4 b) {
    return ucvecN_cmp(a.v, b.v, 4*4);
}

/** dst = mat[row][:] */
static ucvec4 ucmat4_get_row(ucmat4 mat, int row) {
    ucvec4 res;
    ucmatN_get_row(res.v, mat.v, row, 4);
    return res;
}
/** dst = mat[row][:] */
static ucvec4 ucmat4_get_row_v(const unsigned *mat, int row) {
    return ucmat4_get_row(UCMat4(mat), row);
}


/** dst = mat[:][col] */
static ucvec4 ucmat4_get_col(ucmat4 mat, int col) {
    ucvec4 res;
    ucmatN_get_col(res.v, mat.v, col, 4);
    return res;
}
/** dst = mat[:][col] */
static ucvec4 ucmat4_get_col_v(const unsigned *mat, int col) {
    return ucmat4_get_col(UCMat4(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static ucmat4 ucmat4_set_row(ucmat4 mat, ucvec4 vec, int row) {
    ucmatN_set_row(mat.v, vec.v, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static ucmat4 ucmat4_set_row_v(const unsigned *mat, const unsigned *vec, int row) {
    return ucmat4_set_row(UCMat4(mat), UCVec4(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static ucmat4 ucmat4_set_this_row(ucmat4 *mat, ucvec4 vec, int row) {
    ucmatN_set_row(mat->v, vec.v, row, 4);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static ucmat4 ucmat4_set_this_row_v(unsigned *mat, const unsigned *vec, int row) {
    return ucmat4_set_this_row((ucmat4*) mat, UCVec4(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static ucmat4 ucmat4_set_col(ucmat4 mat, ucvec4 vec, int col) {
    ucmatN_set_col(mat.v, vec.v, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static ucmat4 ucmat4_set_col_v(const unsigned *mat, const unsigned *vec, int col) {
    return ucmat4_set_col(UCMat4(mat), UCVec4(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static ucmat4 ucmat4_set_this_col(ucmat4 *mat, ucvec4 vec, int col) {
    ucmatN_set_col(mat->v, vec.v, col, 4);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static ucmat4 ucmat4_set_this_col_v(unsigned *mat, const unsigned *vec, int col) {
    return ucmat4_set_this_col((ucmat4*) mat, UCVec4(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static ucmat4 ucmat4_set_row_sca(ucmat4 mat, unsigned scalar, int row) {
    ucmatN_set_row_sca(mat.v, scalar, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static ucmat4 ucmat4_set_row_sca_v(const unsigned *mat, unsigned scalar, int row) {
    return ucmat4_set_row_sca(UCMat4(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static ucmat4 ucmat4_set_this_row_sca(ucmat4 *mat, unsigned scalar, int row) {
    ucmatN_set_row_sca(mat->v, scalar, row, 4);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static ucmat4 ucmat4_set_this_row_sca_v(unsigned *mat, unsigned scalar, int row) {
    return ucmat4_set_this_row_sca((ucmat4*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static ucmat4 ucmat4_set_col_sca(ucmat4 mat, unsigned scalar, int col) {
    ucmatN_set_col_sca(mat.v, scalar, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static ucmat4 ucmat4_set_col_sca_v(const unsigned *mat, unsigned scalar, int col) {
    return ucmat4_set_col_sca(UCMat4(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static ucmat4 ucmat4_set_this_col_sca(ucmat4 *mat, unsigned scalar, int col) {
    ucmatN_set_col_sca(mat->v, scalar, col, 4);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static ucmat4 ucmat4_set_this_col_sca_v(unsigned *mat, unsigned scalar, int col) {
    return ucmat4_set_this_col_sca((ucmat4*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static unsigned ucmat4_trace(ucmat4 mat) {
    return ucmatN_trace(mat.v, 4);
}
/** returns sum of diagonal form upper left to lower right */
static unsigned ucmat4_trace_v(const unsigned *mat) {
    return ucmat4_trace(UCMat4(mat));
}


/** dst = mat^t */
static ucmat4 ucmat4_transpose(ucmat4 mat) {
    ucmat4 res;
    ucmatN_transpose_no_alias(res.v, mat.v, 4);
    return res;
}
/** dst = mat^t */
static ucmat4 ucmat4_transpose_v(const unsigned *mat) {
    return ucmat4_transpose(UCMat4(mat));
}


/** dst = a @ b */
static ucmat4 ucmat4_mul_mat(ucmat4 mat_a, ucmat4 mat_b) {
    ucmat4 res;
    ucmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static ucmat4 ucmat4_mul_mat_v(const unsigned *mat_a, const unsigned *mat_b) {
    return ucmat4_mul_mat(UCMat4(mat_a), UCMat4(mat_b));
}


/** dst = a @ b */
static ucvec4 ucmat4_mul_vec(ucmat4 mat_a, ucvec4 vec_b) {
    ucvec4 res;
    ucmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 4);
    return res;
}
/** dst = a @ b */
static ucvec4 ucmat4_mul_vec_v(const unsigned *mat_a, const unsigned *vec_b) {
    return ucmat4_mul_vec(UCMat4(mat_a), UCVec4(vec_b));
}


/** dst = a @ b */
static ucvec4 ucvec4_mul_mat(ucvec4 vec_a, ucmat4 mat_b) {
    ucvec4 res;
    ucvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static ucvec4 ucvec4_mul_mat_v(const unsigned *vec_a, const unsigned *mat_b) {
    return ucvec4_mul_mat(UCVec4(vec_a), UCMat4(mat_b));
}


/** returns = determinant mat */
static unsigned ucmat4_det(ucmat4 mat) {
    // from cglm/ucmat4.h/glm_ucmat4_det
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
static unsigned ucmat4_det_v(const unsigned *mat) {
    return ucmat4_det(UCMat4(mat));
}


/** dst = inverted mat */
static ucmat4 ucmat4_inv(ucmat4 mat) {
    // from cglm/ucmat4.h/glm_ucmat4_inv
    unsigned t[6];
    unsigned a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3];
    unsigned e = mat.m[1][0], f = mat.m[1][1], g = mat.m[1][2], h = mat.m[1][3];
    unsigned i = mat.m[2][0], j = mat.m[2][1], k = mat.m[2][2], l = mat.m[2][3];
    unsigned m = mat.m[3][0], n = mat.m[3][1], o = mat.m[3][2], p = mat.m[3][3];

    t[0] = k * p - o * l; t[1] = j * p - n * l; t[2] = j * o - n * k;
    t[3] = i * p - m * l; t[4] = i * o - m * k; t[5] = i * n - m * j;

    ucmat4 res;
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

    ucvecN_scale(res.v, res.v, inv_det, 16);
    return res;
}
/** dst = inverted mat */
static ucmat4 ucmat4_inv_v(const unsigned *mat) {
    return ucmat4_inv(UCMat4(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static ucmat2 ucmat4_get_block2(ucmat4 mat, int row, int col) {
    ucmat2 res;
    ucmatN_get_block(res.v, mat.v, row, col, 2, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static ucmat2 ucmat4_get_block2_v(const unsigned *mat, int row, int col) {
    return ucmat4_get_block2(UCMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static ucmat4 ucmat4_set_block2(ucmat4 mat, ucmat2 block_2, int row, int col) {
    ucmatN_set_block(mat.v, block_2.v, row, col, 2, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static ucmat4 ucmat4_set_block2_v(const unsigned *mat, const unsigned *block_2, int row, int col) {
    return ucmat4_set_block2(UCMat4(mat), UCMat2(block_2), row, col);
}


/** mat[col:col+2, row:row+2] = block; dst = mat */
static ucmat4 ucmat4_set_this_block2(ucmat4 *mat, ucmat2 block_2, int row, int col) {
    ucmatN_set_block(mat->v, block_2.v, row, col, 2, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static ucmat4 ucmat4_set_this_block2_v(unsigned *mat, const unsigned *block_2, int row, int col) {
    return ucmat4_set_this_block2((ucmat4 *) mat, UCMat2(block_2), row, col);
}


/** dst = mat[col:col+2, row:row+2] */
static ucmat3 ucmat4_get_block3(ucmat4 mat, int row, int col) {
    ucmat3 res;
    ucmatN_get_block(res.v, mat.v, row, col, 3, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static ucmat3 ucmat4_get_block3_v(const unsigned *mat, int row, int col) {
    return ucmat4_get_block3(UCMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static ucmat4 ucmat4_set_block3(ucmat4 mat, ucmat3 block_3, int row, int col) {
    ucmatN_set_block(mat.v, block_3.v, row, col, 3, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static ucmat4 ucmat4_set_block3_v(const unsigned *mat, const unsigned *block_3, int row, int col) {
    return ucmat4_set_block3(UCMat4(mat), UCMat3(block_3), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static ucmat4 ucmat4_set_this_block3(ucmat4 *mat, ucmat3 block_3, int row, int col) {
    ucmatN_set_block(mat->v, block_3.v, row, col, 3, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static ucmat4 ucmat4_set_this_block3_v(unsigned *mat, const unsigned *block_3, int row, int col) {
    return ucmat4_set_this_block3((ucmat4 *) mat, UCMat3(block_3), row, col);
}


/** dst = mat[:2, :2] */
static ucmat2 ucmat4_get_upper_left2(ucmat4 mat) {
    return ucmat4_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static ucmat2 ucmat4_get_upper_left2_v(const unsigned *mat) {
    return ucmat4_get_upper_left2(UCMat4(mat));
}


/** dst = mat; dst[:2, :2] = block */
static ucmat4 ucmat4_set_upper_left2(ucmat4 mat, ucmat2 block_2) {
    return ucmat4_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static ucmat4 ucmat4_set_upper_left2_v(const unsigned *mat, const unsigned *block_2) {
    return ucmat4_set_upper_left2(UCMat4(mat), UCMat2(block_2));
}

/** mat[:2, :2] = block; dst = mat */
static ucmat4 ucmat4_set_this_upper_left2(ucmat4 *mat, ucmat2 block_2) {
    return ucmat4_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static ucmat4 ucmat4_set_this_upper_left2_v(unsigned *mat, const unsigned *block_2) {
    return ucmat4_set_this_upper_left2((ucmat4 *) mat, UCMat2(block_2));
}


/** dst = mat[:3, :3] */
static ucmat3 ucmat4_get_upper_left3(ucmat4 mat) {
    return ucmat4_get_block3(mat, 0, 0);
}
/** dst = mat[:3, :3] */
static ucmat3 ucmat4_get_upper_left3_v(const unsigned *mat) {
    return ucmat4_get_upper_left3(UCMat4(mat));
}


/** dst = mat; dst[:3, :3] = block */
static ucmat4 ucmat4_set_upper_left3(ucmat4 mat, ucmat3 block_3) {
    return ucmat4_set_block3(mat, block_3, 0, 0);
}
/** dst = mat; dst[:3, :3] = block */
static ucmat4 ucmat4_set_upper_left3_v(const unsigned *mat, const unsigned *block_3) {
    return ucmat4_set_upper_left3(UCMat4(mat), UCMat3(block_3));
}

/** mat[:3, :3] = block; dst = mat */
static ucmat4 ucmat4_set_this_upper_left3(ucmat4 *mat, ucmat3 block_3) {
    return ucmat4_set_this_block3(mat, block_3, 0, 0);
}
/** mat[:3, :3] = block; dst = mat */
static ucmat4 ucmat4_set_this_upper_left3_v(unsigned *mat, const unsigned *block_3) {
    return ucmat4_set_this_upper_left3((ucmat4 *) mat, UCMat3(block_3));
}

#endif //MATHC_MAT_UCMAT4_H
