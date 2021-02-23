#ifndef MATHC_MAT_MAT2_H
#define MATHC_MAT_MAT2_H

#include "matn.h"
#include "../types/float.h"


/** dst = r==c ? 1 : 0 (identity)  */
static mat2 mat2_eye() {
    mat2 res;
    matN_eye(res.v, 2);
    return res;
}

/** dst = (mat2) v */
static mat2 mat2_cast_from_double(const double *v) {
    mat2 res;
    vecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (mat2) v */
static mat2 mat2_cast_from_int(const int *v) {
    mat2 res;
    vecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (mat2) v */
static mat2 mat2_cast_from_unsigned(const unsigned *v) {
    mat2 res;
    vecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = mat[row][:] */
static vec2 mat2_get_row(mat2 mat, int row) {
    vec2 res;
    matN_get_row(res.v, mat.v, row, 2);
    return res;
}
/** dst = mat[row][:] */
static vec2 mat2_get_row_v(const float *mat, int row) {
    return mat2_get_row(Mat2(mat), row);
}


/** dst = mat[:][col] */
static vec2 mat2_get_col(mat2 mat, int col) {
    vec2 res;
    matN_get_col(res.v, mat.v, col, 2);
    return res;
}
/** dst = mat[:][col] */
static vec2 mat2_get_col_v(const float *mat, int col) {
    return mat2_get_col(Mat2(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static mat2 mat2_set_row(mat2 mat, vec2 vec, int row) {
    matN_set_row(mat.v, vec.v, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static mat2 mat2_set_row_v(const float *mat, const float *vec, int row) {
    return mat2_set_row(Mat2(mat), Vec2(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static mat2 mat2_set_this_row(mat2 *mat, vec2 vec, int row) {
    matN_set_row(mat->v, vec.v, row, 2);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static mat2 mat2_set_this_row_v(float *mat, const float *vec, int row) {
    return mat2_set_this_row((mat2*) mat, Vec2(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static mat2 mat2_set_col(mat2 mat, vec2 vec, int col) {
    matN_set_col(mat.v, vec.v, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static mat2 mat2_set_col_v(const float *mat, const float *vec, int col) {
    return mat2_set_col(Mat2(mat), Vec2(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static mat2 mat2_set_this_col(mat2 *mat, vec2 vec, int col) {
    matN_set_col(mat->v, vec.v, col, 2);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static mat2 mat2_set_this_col_v(float *mat, const float *vec, int col) {
    return mat2_set_this_col((mat2*) mat, Vec2(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static mat2 mat2_set_row_sca(mat2 mat, float scalar, int row) {
    matN_set_row_sca(mat.v, scalar, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static mat2 mat2_set_row_sca_v(const float *mat, float scalar, int row) {
    return mat2_set_row_sca(Mat2(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static mat2 mat2_set_this_row_sca(mat2 *mat, float scalar, int row) {
    matN_set_row_sca(mat->v, scalar, row, 2);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static mat2 mat2_set_this_row_sca_v(float *mat, float scalar, int row) {
    return mat2_set_this_row_sca((mat2*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static mat2 mat2_set_col_sca(mat2 mat, float scalar, int col) {
    matN_set_col_sca(mat.v, scalar, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static mat2 mat2_set_col_sca_v(const float *mat, float scalar, int col) {
    return mat2_set_col_sca(Mat2(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static mat2 mat2_set_this_col_sca(mat2 *mat, float scalar, int col) {
    matN_set_col_sca(mat->v, scalar, col, 2);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static mat2 mat2_set_this_col_sca_v(float *mat, float scalar, int col) {
    return mat2_set_this_col_sca((mat2*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static float mat2_trace(mat2 mat) {
    return matN_trace(mat.v, 2);
}
/** returns sum of diagonal form upper left to lower right */
static float mat2_trace_v(const float *mat) {
    return mat2_trace(Mat2(mat));
}


/** dst = mat^t */
static mat2 mat2_transpose(mat2 mat) {
    mat2 res;
    matN_transpose_no_alias(res.v, mat.v, 2);
    return res;
}
/** dst = mat^t */
static mat2 mat2_transpose_v(const float *mat) {
    return mat2_transpose(Mat2(mat));
}


/** dst = a @ b */
static mat2 mat2_mul_mat(mat2 mat_a, mat2 mat_b) {
    mat2 res;
    matN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static mat2 mat2_mul_mat_v(const float *mat_a, const float *mat_b) {
    return mat2_mul_mat(Mat2(mat_a), Mat2(mat_b));
}


/** dst = a @ b */
static vec2 mat2_mul_vec(mat2 mat_a, vec2 vec_b) {
    vec2 res;
    matN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 2);
    return res;
}
/** dst = a @ b */
static vec2 mat2_mul_vec_v(const float *mat_a, const float *vec_b) {
    return mat2_mul_vec(Mat2(mat_a), Vec2(vec_b));
}


/** dst = a @ b */
static vec2 vec2_mul_mat(vec2 vec_a, mat2 mat_b) {
    vec2 res;
    vecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static vec2 vec2_mul_mat_v(const float *vec_a, const float *mat_b) {
    return vec2_mul_mat(Vec2(vec_a), Mat2(mat_b));
}


/** returns = determinant mat */
static float mat2_det(mat2 mat) {
    // from cglm/mat2.h/glm_mat2_det
    return mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1];
}
/** returns = determinant mat */
static float mat2_det_v(const float *mat) {
    return mat2_det(Mat2(mat));
}


/** dst = inverted mat */
static mat2 mat2_inv(mat2 mat) {
    // from cglm/mat2.h/glm_mat2_inv
    float a = mat.m[0][0], b = mat.m[0][1];
    float c = mat.m[1][0], d = mat.m[1][1];
    float inv_det = 1.0f / (a * d - b * c);

    mat2 res;
    res.m[0][0] = d * inv_det;
    res.m[0][1] = -b * inv_det;
    res.m[1][0] = -c * inv_det;
    res.m[1][1] = a * inv_det;
    return res;
}
/** dst = inverted mat */
static mat2 mat2_inv_v(const float *mat) {
    return mat2_inv(Mat2(mat));
}


#endif //MATHC_MAT_MAT2_H
