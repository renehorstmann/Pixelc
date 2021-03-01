#ifndef MATHC_MAT_UCMAT3_H
#define MATHC_MAT_UCMAT3_H

#include "ucmatn.h"
#include "../types/uchar.h"
#include "../vec/ucvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static ucmat3 ucmat3_eye() {
    ucmat3 res;
    ucmatN_eye(res.v, 3);
    return res;
}

/** dst = (ucmat3) v */
static ucmat3 ucmat3_cast_from_float(const float *v) {
    ucmat3 res;
    ucvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (ucmat3) v */
static ucmat3 ucmat3_cast_from_double(const double *v) {
    ucmat3 res;
    ucvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (ucmat3) v */
static ucmat3 ucmat3_cast_from_int(const int *v) {
    ucmat3 res;
    ucvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (ucmat3) v */
static ucmat3 ucmat3_cast_from_unsigned(const unsigned *v) {
    ucmat3 res;
    ucvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (ucmat3) v */
static ucmat3 ucmat3_cast_from_char(const char *v) {
    ucmat3 res;
    ucvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** mat_a == mat_b */
static bool ucmat3_cmp(ucmat3 a, ucmat3 b) {
    return ucvecN_cmp(a.v, b.v, 3*3);
}

/** dst = mat[row][:] */
static ucvec3 ucmat3_get_row(ucmat3 mat, int row) {
    ucvec3 res;
    ucmatN_get_row(res.v, mat.v, row, 3);
    return res;
}
/** dst = mat[row][:] */
static ucvec3 ucmat3_get_row_v(const uchar *mat, int row) {
    return ucmat3_get_row(UCMat3(mat), row);
}


/** dst = mat[:][col] */
static ucvec3 ucmat3_get_col(ucmat3 mat, int col) {
    ucvec3 res;
    ucmatN_get_col(res.v, mat.v, col, 3);
    return res;
}
/** dst = mat[:][col] */
static ucvec3 ucmat3_get_col_v(const uchar *mat, int col) {
    return ucmat3_get_col(UCMat3(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static ucmat3 ucmat3_set_row(ucmat3 mat, ucvec3 vec, int row) {
    ucmatN_set_row(mat.v, vec.v, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static ucmat3 ucmat3_set_row_v(const uchar *mat, const uchar *vec, int row) {
    return ucmat3_set_row(UCMat3(mat), UCVec3(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static ucmat3 ucmat3_set_this_row(ucmat3 *mat, ucvec3 vec, int row) {
    ucmatN_set_row(mat->v, vec.v, row, 3);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static ucmat3 ucmat3_set_this_row_v(uchar *mat, const uchar *vec, int row) {
    return ucmat3_set_this_row((ucmat3*) mat, UCVec3(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static ucmat3 ucmat3_set_col(ucmat3 mat, ucvec3 vec, int col) {
    ucmatN_set_col(mat.v, vec.v, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static ucmat3 ucmat3_set_col_v(const uchar *mat, const uchar *vec, int col) {
    return ucmat3_set_col(UCMat3(mat), UCVec3(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static ucmat3 ucmat3_set_this_col(ucmat3 *mat, ucvec3 vec, int col) {
    ucmatN_set_col(mat->v, vec.v, col, 3);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static ucmat3 ucmat3_set_this_col_v(uchar *mat, const uchar *vec, int col) {
    return ucmat3_set_this_col((ucmat3*) mat, UCVec3(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static ucmat3 ucmat3_set_row_sca(ucmat3 mat, uchar scalar, int row) {
    ucmatN_set_row_sca(mat.v, scalar, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static ucmat3 ucmat3_set_row_sca_v(const uchar *mat, uchar scalar, int row) {
    return ucmat3_set_row_sca(UCMat3(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static ucmat3 ucmat3_set_this_row_sca(ucmat3 *mat, uchar scalar, int row) {
    ucmatN_set_row_sca(mat->v, scalar, row, 3);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static ucmat3 ucmat3_set_this_row_sca_v(uchar *mat, uchar scalar, int row) {
    return ucmat3_set_this_row_sca((ucmat3*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static ucmat3 ucmat3_set_col_sca(ucmat3 mat, uchar scalar, int col) {
    ucmatN_set_col_sca(mat.v, scalar, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static ucmat3 ucmat3_set_col_sca_v(const uchar *mat, uchar scalar, int col) {
    return ucmat3_set_col_sca(UCMat3(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static ucmat3 ucmat3_set_this_col_sca(ucmat3 *mat, uchar scalar, int col) {
    ucmatN_set_col_sca(mat->v, scalar, col, 3);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static ucmat3 ucmat3_set_this_col_sca_v(uchar *mat, uchar scalar, int col) {
    return ucmat3_set_this_col_sca((ucmat3*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static uchar ucmat3_trace(ucmat3 mat) {
    return ucmatN_trace(mat.v, 3);
}
/** returns sum of diagonal form upper left to lower right */
static uchar ucmat3_trace_v(const uchar *mat) {
    return ucmat3_trace(UCMat3(mat));
}


/** dst = mat^t */
static ucmat3 ucmat3_transpose(ucmat3 mat) {
    ucmat3 res;
    ucmatN_transpose_no_alias(res.v, mat.v, 3);
    return res;
}
/** dst = mat^t */
static ucmat3 ucmat3_transpose_v(const uchar *mat) {
    return ucmat3_transpose(UCMat3(mat));
}


/** dst = a @ b */
static ucmat3 ucmat3_mul_mat(ucmat3 mat_a, ucmat3 mat_b) {
    ucmat3 res;
    ucmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static ucmat3 ucmat3_mul_mat_v(const uchar *mat_a, const uchar *mat_b) {
    return ucmat3_mul_mat(UCMat3(mat_a), UCMat3(mat_b));
}


/** dst = a @ b */
static ucvec3 ucmat3_mul_vec(ucmat3 mat_a, ucvec3 vec_b) {
    ucvec3 res;
    ucmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 3);
    return res;
}
/** dst = a @ b */
static ucvec3 ucmat3_mul_vec_v(const uchar *mat_a, const uchar *vec_b) {
    return ucmat3_mul_vec(UCMat3(mat_a), UCVec3(vec_b));
}


/** dst = a @ b */
static ucvec3 ucvec3_mul_mat(ucvec3 vec_a, ucmat3 mat_b) {
    ucvec3 res;
    ucvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static ucvec3 ucvec3_mul_mat_v(const uchar *vec_a, const uchar *mat_b) {
    return ucvec3_mul_mat(UCVec3(vec_a), UCMat3(mat_b));
}


/** returns = determinant mat */
static uchar ucmat3_det(ucmat3 mat) {
    // from cglm/ucmat3.h/glm_ucmat3_det
    uchar a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    uchar d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    uchar g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}
/** returns = determinant mat */
static uchar ucmat3_det_v(const uchar *mat) {
    return ucmat3_det(UCMat3(mat));
}


/** dst = inverted mat */
static ucmat3 ucmat3_inv(ucmat3 mat) {
    // from cglm/ucmat3.h/glm_ucmat3_inv
    uchar a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    uchar d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    uchar g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    ucmat3 res;
    res.m[0][0] =   e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] =   b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] =   a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] =   d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] =   a * e - b * d;

    uchar inv_det = (uchar) (1.0f / (a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0]));

    ucvecN_scale(res.v, res.v, inv_det, 9);
    return res;
}
/** dst = inverted mat */
static ucmat3 ucmat3_inv_v(const uchar *mat) {
    return ucmat3_inv(UCMat3(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static ucmat2 ucmat3_get_block2(ucmat3 mat, int row, int col) {
    ucmat2 res;
    ucmatN_get_block(res.v, mat.v, row, col, 2, 3);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static ucmat2 ucmat3_get_block2_v(const uchar *mat, int row, int col) {
    return ucmat3_get_block2(UCMat3(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static ucmat3 ucmat3_set_block2(ucmat3 mat, ucmat2 block_2, int row, int col) {
    ucmatN_set_block(mat.v, block_2.v, row, col, 2, 3);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static ucmat3 ucmat3_set_block2_v(const uchar *mat, const uchar *block_2, int row, int col) {
    return ucmat3_set_block2(UCMat3(mat), UCMat2(block_2), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static ucmat3 ucmat3_set_this_block2(ucmat3 *mat, ucmat2 block_2, int row, int col) {
    ucmatN_set_block(mat->v, block_2.v, row, col, 2, 3);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static ucmat3 ucmat3_set_this_block2_v(uchar *mat, const uchar *block_2, int row, int col) {
    return ucmat3_set_this_block2((ucmat3 *) mat, UCMat2(block_2), row, col);
}


/** dst = mat[:2, :2] */
static ucmat2 ucmat3_get_upper_left(ucmat3 mat) {
    return ucmat3_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static ucmat2 ucmat3_get_upper_left_v(const uchar *mat) {
    return ucmat3_get_upper_left(UCMat3(mat));
}


/** dst = mat; dst[:2, :2] = block */
static ucmat3 ucmat3_set_upper_left(ucmat3 mat, ucmat2 block_2) {
    return ucmat3_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static ucmat3 ucmat3_set_upper_left_v(const uchar *mat, const uchar *block_2) {
    return ucmat3_set_upper_left(UCMat3(mat), UCMat2(block_2));
}


/** mat[:2, :2] = block; dst = mat */
static ucmat3 ucmat3_set_this_upper_left(ucmat3 *mat, ucmat2 block_2) {
    return ucmat3_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static ucmat3 ucmat3_set_this_upper_left_v(uchar *mat, const uchar *block_2) {
    return ucmat3_set_this_upper_left((ucmat3 *) mat, UCMat2(block_2));
}


#endif //MATHC_MAT_UCMAT3_H
