#ifndef MATHC_MAT_MAT4_H
#define MATHC_MAT_MAT4_H

#include "matn.h"
#include "../types/float.h"
#include "../vec/vecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static mat4 mat4_eye() {
    mat4 res;
    matN_eye(res.v, 4);
    return res;
}

/** dst = (mat4) v */
static mat4 mat4_cast_from_double(const double *v) {
    mat4 res;
    vecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (mat4) v */
static mat4 mat4_cast_from_int(const int *v) {
    mat4 res;
    vecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (mat4) v */
static mat4 mat4_cast_from_unsigned(const unsigned *v) {
    mat4 res;
    vecN_cast_into(res.v, v, 4*4);
    return res;
}


/** dst = mat[row][:] */
static vec4 mat4_get_row(mat4 mat, int row) {
    vec4 res;
    matN_get_row(res.v, mat.v, row, 4);
    return res;
}
/** dst = mat[row][:] */
static vec4 mat4_get_row_v(const float *mat, int row) {
    return mat4_get_row(Mat4(mat), row);
}


/** dst = mat[:][col] */
static vec4 mat4_get_col(mat4 mat, int col) {
    vec4 res;
    matN_get_col(res.v, mat.v, col, 4);
    return res;
}
/** dst = mat[:][col] */
static vec4 mat4_get_col_v(const float *mat, int col) {
    return mat4_get_col(Mat4(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static mat4 mat4_set_row(mat4 mat, vec4 vec, int row) {
    matN_set_row(mat.v, vec.v, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static mat4 mat4_set_row_v(const float *mat, const float *vec, int row) {
    return mat4_set_row(Mat4(mat), Vec4(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static mat4 mat4_set_this_row(mat4 *mat, vec4 vec, int row) {
    matN_set_row(mat->v, vec.v, row, 4);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static mat4 mat4_set_this_row_v(float *mat, const float *vec, int row) {
    return mat4_set_this_row((mat4*) mat, Vec4(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static mat4 mat4_set_col(mat4 mat, vec4 vec, int col) {
    matN_set_col(mat.v, vec.v, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static mat4 mat4_set_col_v(const float *mat, const float *vec, int col) {
    return mat4_set_col(Mat4(mat), Vec4(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static mat4 mat4_set_this_col(mat4 *mat, vec4 vec, int col) {
    matN_set_col(mat->v, vec.v, col, 4);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static mat4 mat4_set_this_col_v(float *mat, const float *vec, int col) {
    return mat4_set_this_col((mat4*) mat, Vec4(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static mat4 mat4_set_row_sca(mat4 mat, float scalar, int row) {
    matN_set_row_sca(mat.v, scalar, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static mat4 mat4_set_row_sca_v(const float *mat, float scalar, int row) {
    return mat4_set_row_sca(Mat4(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static mat4 mat4_set_this_row_sca(mat4 *mat, float scalar, int row) {
    matN_set_row_sca(mat->v, scalar, row, 4);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static mat4 mat4_set_this_row_sca_v(float *mat, float scalar, int row) {
    return mat4_set_this_row_sca((mat4*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static mat4 mat4_set_col_sca(mat4 mat, float scalar, int col) {
    matN_set_col_sca(mat.v, scalar, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static mat4 mat4_set_col_sca_v(const float *mat, float scalar, int col) {
    return mat4_set_col_sca(Mat4(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static mat4 mat4_set_this_col_sca(mat4 *mat, float scalar, int col) {
    matN_set_col_sca(mat->v, scalar, col, 4);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static mat4 mat4_set_this_col_sca_v(float *mat, float scalar, int col) {
    return mat4_set_this_col_sca((mat4*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static float mat4_trace(mat4 mat) {
    return matN_trace(mat.v, 4);
}
/** returns sum of diagonal form upper left to lower right */
static float mat4_trace_v(const float *mat) {
    return mat4_trace(Mat4(mat));
}


/** dst = mat^t */
static mat4 mat4_transpose(mat4 mat) {
    mat4 res;
    matN_transpose_no_alias(res.v, mat.v, 4);
    return res;
}
/** dst = mat^t */
static mat4 mat4_transpose_v(const float *mat) {
    return mat4_transpose(Mat4(mat));
}


/** dst = a @ b */
static mat4 mat4_mul_mat(mat4 mat_a, mat4 mat_b) {
    mat4 res;
    matN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static mat4 mat4_mul_mat_v(const float *mat_a, const float *mat_b) {
    return mat4_mul_mat(Mat4(mat_a), Mat4(mat_b));
}


/** dst = a @ b */
static vec4 mat4_mul_vec(mat4 mat_a, vec4 vec_b) {
    vec4 res;
    matN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 4);
    return res;
}
/** dst = a @ b */
static vec4 mat4_mul_vec_v(const float *mat_a, const float *vec_b) {
    return mat4_mul_vec(Mat4(mat_a), Vec4(vec_b));
}


/** dst = a @ b */
static vec4 vec4_mul_mat(vec4 vec_a, mat4 mat_b) {
    vec4 res;
    vecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static vec4 vec4_mul_mat_v(const float *vec_a, const float *mat_b) {
    return vec4_mul_mat(Vec4(vec_a), Mat4(mat_b));
}


/** returns = determinant mat */
static float mat4_det(mat4 mat) {
    // from cglm/mat4.h/glm_mat4_det
    /* [square] det(A) = det(At) */
    float t[6];
    float a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3],
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
static float mat4_det_v(const float *mat) {
    return mat4_det(Mat4(mat));
}


/** dst = inverted mat */
static mat4 mat4_inv(mat4 mat) {
    // from cglm/mat4.h/glm_mat4_inv
    float t[6];
    float a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3];
    float e = mat.m[1][0], f = mat.m[1][1], g = mat.m[1][2], h = mat.m[1][3];
    float i = mat.m[2][0], j = mat.m[2][1], k = mat.m[2][2], l = mat.m[2][3];
    float m = mat.m[3][0], n = mat.m[3][1], o = mat.m[3][2], p = mat.m[3][3];

    t[0] = k * p - o * l; t[1] = j * p - n * l; t[2] = j * o - n * k;
    t[3] = i * p - m * l; t[4] = i * o - m * k; t[5] = i * n - m * j;

    mat4 res;
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

    float inv_det = 1.0f / (a * res.m[0][0] + b * res.m[1][0]
                  + c * res.m[2][0] + d * res.m[3][0]);

    vecN_scale(res.v, res.v, inv_det, 16);
    return res;
}
/** dst = inverted mat */
static mat4 mat4_inv_v(const float *mat) {
    return mat4_inv(Mat4(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static mat2 mat4_get_block2(mat4 mat, int row, int col) {
    mat2 res;
    matN_get_block(res.v, mat.v, row, col, 2, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static mat2 mat4_get_block2_v(const float *mat, int row, int col) {
    return mat4_get_block2(Mat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static mat4 mat4_set_block2(mat4 mat, mat2 block_2, int row, int col) {
    matN_set_block(mat.v, block_2.v, row, col, 2, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static mat4 mat4_set_block2_v(const float *mat, const float *block_2, int row, int col) {
    return mat4_set_block2(Mat4(mat), Mat2(block_2), row, col);
}


/** mat[col:col+2, row:row+2] = block; dst = mat */
static mat4 mat4_set_this_block2(mat4 *mat, mat2 block_2, int row, int col) {
    matN_set_block(mat->v, block_2.v, row, col, 2, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static mat4 mat4_set_this_block2_v(float *mat, const float *block_2, int row, int col) {
    return mat4_set_this_block2((mat4 *) mat, Mat2(block_2), row, col);
}


/** dst = mat[col:col+2, row:row+2] */
static mat3 mat4_get_block3(mat4 mat, int row, int col) {
    mat3 res;
    matN_get_block(res.v, mat.v, row, col, 3, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static mat3 mat4_get_block3_v(const float *mat, int row, int col) {
    return mat4_get_block3(Mat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static mat4 mat4_set_block3(mat4 mat, mat3 block_3, int row, int col) {
    matN_set_block(mat.v, block_3.v, row, col, 3, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static mat4 mat4_set_block3_v(const float *mat, const float *block_3, int row, int col) {
    return mat4_set_block3(Mat4(mat), Mat3(block_3), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static mat4 mat4_set_this_block3(mat4 *mat, mat3 block_3, int row, int col) {
    matN_set_block(mat->v, block_3.v, row, col, 3, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static mat4 mat4_set_this_block3_v(float *mat, const float *block_3, int row, int col) {
    return mat4_set_this_block3((mat4 *) mat, Mat3(block_3), row, col);
}


/** dst = mat[:2, :2] */
static mat2 mat4_get_upper_left2(mat4 mat) {
    return mat4_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static mat2 mat4_get_upper_left2_v(const float *mat) {
    return mat4_get_upper_left2(Mat4(mat));
}


/** dst = mat; dst[:2, :2] = block */
static mat4 mat4_set_upper_left2(mat4 mat, mat2 block_2) {
    return mat4_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static mat4 mat4_set_upper_left2_v(const float *mat, const float *block_2) {
    return mat4_set_upper_left2(Mat4(mat), Mat2(block_2));
}

/** mat[:2, :2] = block; dst = mat */
static mat4 mat4_set_this_upper_left2(mat4 *mat, mat2 block_2) {
    return mat4_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static mat4 mat4_set_this_upper_left2_v(float *mat, const float *block_2) {
    return mat4_set_this_upper_left2((mat4 *) mat, Mat2(block_2));
}


/** dst = mat[:3, :3] */
static mat3 mat4_get_upper_left3(mat4 mat) {
    return mat4_get_block3(mat, 0, 0);
}
/** dst = mat[:3, :3] */
static mat3 mat4_get_upper_left3_v(const float *mat) {
    return mat4_get_upper_left3(Mat4(mat));
}


/** dst = mat; dst[:3, :3] = block */
static mat4 mat4_set_upper_left3(mat4 mat, mat3 block_3) {
    return mat4_set_block3(mat, block_3, 0, 0);
}
/** dst = mat; dst[:3, :3] = block */
static mat4 mat4_set_upper_left3_v(const float *mat, const float *block_3) {
    return mat4_set_upper_left3(Mat4(mat), Mat3(block_3));
}

/** mat[:3, :3] = block; dst = mat */
static mat4 mat4_set_this_upper_left3(mat4 *mat, mat3 block_3) {
    return mat4_set_this_block3(mat, block_3, 0, 0);
}
/** mat[:3, :3] = block; dst = mat */
static mat4 mat4_set_this_upper_left3_v(float *mat, const float *block_3) {
    return mat4_set_this_upper_left3((mat4 *) mat, Mat3(block_3));
}

#endif //MATHC_MAT_MAT4_H
