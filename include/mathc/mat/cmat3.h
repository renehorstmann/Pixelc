#ifndef MATHC_MAT_CMAT3_H
#define MATHC_MAT_CMAT3_H

#include "cmatn.h"
#include "../types/char.h"
#include "../vec/cvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static cmat3 cmat3_eye() {
    cmat3 res;
    cmatN_eye(res.v, 3);
    return res;
}

/** dst = (cmat2) v */
static cmat3 cmat3_cast_from_float(const float *v) {
    cmat3 res;
    cvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (cmat3) v */
static cmat3 cmat3_cast_from_double(const double *v) {
    cmat3 res;
    cvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (cmat3) v */
static cmat3 cmat3_cast_from_int(const int *v) {
    cmat3 res;
    cvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (cmat3) v */
static cmat3 cmat3_cast_from_unsigned(const unsigned *v) {
    cmat3 res;
    cvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (cmat3) v */
static cmat3 cmat3_cast_from_uchar(const unsigned char *v) {
    cmat3 res;
    cvecN_cast_into(res.v, v, 3*3);
    return res;
}

/** mat_a == mat_b */
static bool cmat3_cmp(cmat3 a, cmat3 b) {
    return cvecN_cmp(a.v, b.v, 3*3);
}


/** dst = mat[row][:] */
static cvec3 cmat3_get_row(cmat3 mat, int row) {
    cvec3 res;
    cmatN_get_row(res.v, mat.v, row, 3);
    return res;
}
/** dst = mat[row][:] */
static cvec3 cmat3_get_row_v(const char *mat, int row) {
    return cmat3_get_row(CMat3(mat), row);
}


/** dst = mat[:][col] */
static cvec3 cmat3_get_col(cmat3 mat, int col) {
    cvec3 res;
    cmatN_get_col(res.v, mat.v, col, 3);
    return res;
}
/** dst = mat[:][col] */
static cvec3 cmat3_get_col_v(const char *mat, int col) {
    return cmat3_get_col(CMat3(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static cmat3 cmat3_set_row(cmat3 mat, cvec3 vec, int row) {
    cmatN_set_row(mat.v, vec.v, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static cmat3 cmat3_set_row_v(const char *mat, const char *vec, int row) {
    return cmat3_set_row(CMat3(mat), CVec3(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static cmat3 cmat3_set_this_row(cmat3 *mat, cvec3 vec, int row) {
    cmatN_set_row(mat->v, vec.v, row, 3);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static cmat3 cmat3_set_this_row_v(char *mat, const char *vec, int row) {
    return cmat3_set_this_row((cmat3*) mat, CVec3(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static cmat3 cmat3_set_col(cmat3 mat, cvec3 vec, int col) {
    cmatN_set_col(mat.v, vec.v, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static cmat3 cmat3_set_col_v(const char *mat, const char *vec, int col) {
    return cmat3_set_col(CMat3(mat), CVec3(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static cmat3 cmat3_set_this_col(cmat3 *mat, cvec3 vec, int col) {
    cmatN_set_col(mat->v, vec.v, col, 3);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static cmat3 cmat3_set_this_col_v(char *mat, const char *vec, int col) {
    return cmat3_set_this_col((cmat3*) mat, CVec3(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static cmat3 cmat3_set_row_sca(cmat3 mat, char scalar, int row) {
    cmatN_set_row_sca(mat.v, scalar, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static cmat3 cmat3_set_row_sca_v(const char *mat, char scalar, int row) {
    return cmat3_set_row_sca(CMat3(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static cmat3 cmat3_set_this_row_sca(cmat3 *mat, char scalar, int row) {
    cmatN_set_row_sca(mat->v, scalar, row, 3);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static cmat3 cmat3_set_this_row_sca_v(char *mat, char scalar, int row) {
    return cmat3_set_this_row_sca((cmat3*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static cmat3 cmat3_set_col_sca(cmat3 mat, char scalar, int col) {
    cmatN_set_col_sca(mat.v, scalar, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static cmat3 cmat3_set_col_sca_v(const char *mat, char scalar, int col) {
    return cmat3_set_col_sca(CMat3(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static cmat3 cmat3_set_this_col_sca(cmat3 *mat, char scalar, int col) {
    cmatN_set_col_sca(mat->v, scalar, col, 3);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static cmat3 cmat3_set_this_col_sca_v(char *mat, char scalar, int col) {
    return cmat3_set_this_col_sca((cmat3*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static int cmat3_trace(cmat3 mat) {
    return cmatN_trace(mat.v, 3);
}
/** returns sum of diagonal form upper left to lower right */
static int cmat3_trace_v(const char *mat) {
    return cmat3_trace(CMat3(mat));
}


/** dst = mat^t */
static cmat3 cmat3_transpose(cmat3 mat) {
    cmat3 res;
    cmatN_transpose_no_alias(res.v, mat.v, 3);
    return res;
}
/** dst = mat^t */
static cmat3 cmat3_transpose_v(const char *mat) {
    return cmat3_transpose(CMat3(mat));
}


/** dst = a @ b */
static cmat3 cmat3_mul_mat(cmat3 mat_a, cmat3 mat_b) {
    cmat3 res;
    cmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static cmat3 cmat3_mul_mat_v(const char *mat_a, const char *mat_b) {
    return cmat3_mul_mat(CMat3(mat_a), CMat3(mat_b));
}


/** dst = a @ b */
static cvec3 cmat3_mul_vec(cmat3 mat_a, cvec3 vec_b) {
    cvec3 res;
    cmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 3);
    return res;
}
/** dst = a @ b */
static cvec3 cmat3_mul_vec_v(const char *mat_a, const char *vec_b) {
    return cmat3_mul_vec(CMat3(mat_a), CVec3(vec_b));
}


/** dst = a @ b */
static cvec3 cvec3_mul_mat(cvec3 vec_a, cmat3 mat_b) {
    cvec3 res;
    cvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static cvec3 cvec3_mul_mat_v(const char *vec_a, const char *mat_b) {
    return cvec3_mul_mat(CVec3(vec_a), CMat3(mat_b));
}


/** returns = determinant mat */
static int cmat3_det(cmat3 mat) {
    // from cglm/cmat3.h/glm_cmat3_det
    char a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    char d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    char g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}
/** returns = determinant mat */
static int cmat3_det_v(const char *mat) {
    return cmat3_det(CMat3(mat));
}


/** dst = inverted mat */
static cmat3 cmat3_inv(cmat3 mat) {
    // from cglm/cmat3.h/glm_cmat3_inv
    char a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    char d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    char g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    cmat3 res;
    res.m[0][0] =   e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] =   b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] =   a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] =   d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] =   a * e - b * d;

    char inv_det = (char) (1.0f / (a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0]));

    cvecN_scale(res.v, res.v, inv_det, 9);
    return res;
}
/** dst = inverted mat */
static cmat3 cmat3_inv_v(const char *mat) {
    return cmat3_inv(CMat3(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static cmat2 cmat3_get_block2(cmat3 mat, int row, int col) {
    cmat2 res;
    cmatN_get_block(res.v, mat.v, row, col, 2, 3);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static cmat2 cmat3_get_block2_v(const char *mat, int row, int col) {
    return cmat3_get_block2(CMat3(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static cmat3 cmat3_set_block2(cmat3 mat, cmat2 block_2, int row, int col) {
    cmatN_set_block(mat.v, block_2.v, row, col, 2, 3);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static cmat3 cmat3_set_block2_v(const char *mat, const char *block_2, int row, int col) {
    return cmat3_set_block2(CMat3(mat), CMat2(block_2), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static cmat3 cmat3_set_this_block2(cmat3 *mat, cmat2 block_2, int row, int col) {
    cmatN_set_block(mat->v, block_2.v, row, col, 2, 3);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static cmat3 cmat3_set_this_block2_v(char *mat, const char *block_2, int row, int col) {
    return cmat3_set_this_block2((cmat3 *) mat, CMat2(block_2), row, col);
}


/** dst = mat[:2, :2] */
static cmat2 cmat3_get_upper_left(cmat3 mat) {
    return cmat3_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static cmat2 cmat3_get_upper_left_v(const char *mat) {
    return cmat3_get_upper_left(CMat3(mat));
}


/** dst = mat; dst[:2, :2] = block */
static cmat3 cmat3_set_upper_left(cmat3 mat, cmat2 block_2) {
    return cmat3_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static cmat3 cmat3_set_upper_left_v(const char *mat, const char *block_2) {
    return cmat3_set_upper_left(CMat3(mat), CMat2(block_2));
}


/** mat[:2, :2] = block; dst = mat */
static cmat3 cmat3_set_this_upper_left(cmat3 *mat, cmat2 block_2) {
    return cmat3_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static cmat3 cmat3_set_this_upper_left_v(char *mat, const char *block_2) {
    return cmat3_set_this_upper_left((cmat3 *) mat, CMat2(block_2));
}


#endif //MATHC_MAT_CMAT3_H
