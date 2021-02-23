#ifndef MATHC_MAT_DMAT4_H
#define MATHC_MAT_DMAT4_H

#include "dmatn.h"
#include "../types/double.h"
#include "../vec/dvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static dmat4 dmat4_eye() {
    dmat4 res;
    dmatN_eye(res.v, 4);
    return res;
}


/** dst = (dmat4) v */
static dmat4 dmat4_cast_from_float(const float *v) {
    dmat4 res;
    dvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (dmat4) v */
static dmat4 dmat4_cast_from_int(const int *v) {
    dmat4 res;
    dvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = (dmat4) v */
static dmat4 dmat4_cast_from_unsigned(const unsigned *v) {
    dmat4 res;
    dvecN_cast_into(res.v, v, 4*4);
    return res;
}

/** dst = mat[row][:] */
static dvec4 dmat4_get_row(dmat4 mat, int row) {
    dvec4 res;
    dmatN_get_row(res.v, mat.v, row, 4);
    return res;
}
/** dst = mat[row][:] */
static dvec4 dmat4_get_row_v(const double *mat, int row) {
    return dmat4_get_row(DMat4(mat), row);
}


/** dst = mat[:][col] */
static dvec4 dmat4_get_col(dmat4 mat, int col) {
    dvec4 res;
    dmatN_get_col(res.v, mat.v, col, 4);
    return res;
}
/** dst = mat[:][col] */
static dvec4 dmat4_get_col_v(const double *mat, int col) {
    return dmat4_get_col(DMat4(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static dmat4 dmat4_set_row(dmat4 mat, dvec4 vec, int row) {
    dmatN_set_row(mat.v, vec.v, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static dmat4 dmat4_set_row_v(const double *mat, const double *vec, int row) {
    return dmat4_set_row(DMat4(mat), DVec4(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static dmat4 dmat4_set_this_row(dmat4 *mat, dvec4 vec, int row) {
    dmatN_set_row(mat->v, vec.v, row, 4);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static dmat4 dmat4_set_this_row_v(double *mat, const double *vec, int row) {
    return dmat4_set_this_row((dmat4*) mat, DVec4(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static dmat4 dmat4_set_col(dmat4 mat, dvec4 vec, int col) {
    dmatN_set_col(mat.v, vec.v, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static dmat4 dmat4_set_col_v(const double *mat, const double *vec, int col) {
    return dmat4_set_col(DMat4(mat), DVec4(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static dmat4 dmat4_set_this_col(dmat4 *mat, dvec4 vec, int col) {
    dmatN_set_col(mat->v, vec.v, col, 4);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static dmat4 dmat4_set_this_col_v(double *mat, const double *vec, int col) {
    return dmat4_set_this_col((dmat4*) mat, DVec4(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static dmat4 dmat4_set_row_sca(dmat4 mat, double scalar, int row) {
    dmatN_set_row_sca(mat.v, scalar, row, 4);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static dmat4 dmat4_set_row_sca_v(const double *mat, double scalar, int row) {
    return dmat4_set_row_sca(DMat4(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static dmat4 dmat4_set_this_row_sca(dmat4 *mat, double scalar, int row) {
    dmatN_set_row_sca(mat->v, scalar, row, 4);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static dmat4 dmat4_set_this_row_sca_v(double *mat, double scalar, int row) {
    return dmat4_set_this_row_sca((dmat4*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static dmat4 dmat4_set_col_sca(dmat4 mat, double scalar, int col) {
    dmatN_set_col_sca(mat.v, scalar, col, 4);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static dmat4 dmat4_set_col_sca_v(const double *mat, double scalar, int col) {
    return dmat4_set_col_sca(DMat4(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static dmat4 dmat4_set_this_col_sca(dmat4 *mat, double scalar, int col) {
    dmatN_set_col_sca(mat->v, scalar, col, 4);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static dmat4 dmat4_set_this_col_sca_v(double *mat, double scalar, int col) {
    return dmat4_set_this_col_sca((dmat4*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static double dmat4_trace(dmat4 mat) {
    return dmatN_trace(mat.v, 4);
}
/** returns sum of diagonal form upper left to lower right */
static double dmat4_trace_v(const double *mat) {
    return dmat4_trace(DMat4(mat));
}


/** dst = mat^t */
static dmat4 dmat4_transpose(dmat4 mat) {
    dmat4 res;
    dmatN_transpose_no_alias(res.v, mat.v, 4);
    return res;
}
/** dst = mat^t */
static dmat4 dmat4_transpose_v(const double *mat) {
    return dmat4_transpose(DMat4(mat));
}


/** dst = a @ b */
static dmat4 dmat4_mul_mat(dmat4 mat_a, dmat4 mat_b) {
    dmat4 res;
    dmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static dmat4 dmat4_mul_mat_v(const double *mat_a, const double *mat_b) {
    return dmat4_mul_mat(DMat4(mat_a), DMat4(mat_b));
}


/** dst = a @ b */
static dvec4 dmat4_mul_vec(dmat4 mat_a, dvec4 vec_b) {
    dvec4 res;
    dmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 4);
    return res;
}
/** dst = a @ b */
static dvec4 dmat4_mul_vec_v(const double *mat_a, const double *vec_b) {
    return dmat4_mul_vec(DMat4(mat_a), DVec4(vec_b));
}


/** dst = a @ b */
static dvec4 dvec4_mul_mat(dvec4 vec_a, dmat4 mat_b) {
    dvec4 res;
    dvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 4);
    return res;
}
/** dst = a @ b */
static dvec4 dvec4_mul_mat_v(const double *vec_a, const double *mat_b) {
    return dvec4_mul_mat(DVec4(vec_a), DMat4(mat_b));
}


/** returns = determinant mat */
static double dmat4_det(dmat4 mat) {
    // from cglm/dmat4.h/glm_dmat4_det
    /* [square] det(A) = det(At) */
    double t[6];
    double a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3],
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
static double dmat4_det_v(const double *mat) {
    return dmat4_det(DMat4(mat));
}


/** dst = inverted mat */
static dmat4 dmat4_inv(dmat4 mat) {
    // from cglm/dmat4.h/glm_dmat4_inv
    double t[6];
    double a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2], d = mat.m[0][3];
    double e = mat.m[1][0], f = mat.m[1][1], g = mat.m[1][2], h = mat.m[1][3];
    double i = mat.m[2][0], j = mat.m[2][1], k = mat.m[2][2], l = mat.m[2][3];
    double m = mat.m[3][0], n = mat.m[3][1], o = mat.m[3][2], p = mat.m[3][3];

    t[0] = k * p - o * l; t[1] = j * p - n * l; t[2] = j * o - n * k;
    t[3] = i * p - m * l; t[4] = i * o - m * k; t[5] = i * n - m * j;

    dmat4 res;
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

    double inv_det = 1.0 / (a * res.m[0][0] + b * res.m[1][0]
                  + c * res.m[2][0] + d * res.m[3][0]);

    dvecN_scale(res.v, res.v, inv_det, 16);
    return res;
}
/** dst = inverted mat */
static dmat4 dmat4_inv_v(const double *mat) {
    return dmat4_inv(DMat4(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static dmat2 dmat4_get_block2(dmat4 mat, int row, int col) {
    dmat2 res;
    dmatN_get_block(res.v, mat.v, row, col, 2, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static dmat2 dmat4_get_block2_v(const double *mat, int row, int col) {
    return dmat4_get_block2(DMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static dmat4 dmat4_set_block2(dmat4 mat, dmat2 block_2, int row, int col) {
    dmatN_set_block(mat.v, block_2.v, row, col, 2, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static dmat4 dmat4_set_block2_v(const double *mat, const double *block_2, int row, int col) {
    return dmat4_set_block2(DMat4(mat), DMat2(block_2), row, col);
}


/** mat[col:col+2, row:row+2] = block; dst = mat */
static dmat4 dmat4_set_this_block2(dmat4 *mat, dmat2 block_2, int row, int col) {
    dmatN_set_block(mat->v, block_2.v, row, col, 2, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static dmat4 dmat4_set_this_block2_v(double *mat, const double *block_2, int row, int col) {
    return dmat4_set_this_block2((dmat4 *) mat, DMat2(block_2), row, col);
}


/** dst = mat[col:col+2, row:row+2] */
static dmat3 dmat4_get_block3(dmat4 mat, int row, int col) {
    dmat3 res;
    dmatN_get_block(res.v, mat.v, row, col, 3, 4);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static dmat3 dmat4_get_block3_v(const double *mat, int row, int col) {
    return dmat4_get_block3(DMat4(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static dmat4 dmat4_set_block3(dmat4 mat, dmat3 block_3, int row, int col) {
    dmatN_set_block(mat.v, block_3.v, row, col, 3, 4);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static dmat4 dmat4_set_block3_v(const double *mat, const double *block_3, int row, int col) {
    return dmat4_set_block3(DMat4(mat), DMat3(block_3), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static dmat4 dmat4_set_this_block3(dmat4 *mat, dmat3 block_3, int row, int col) {
    dmatN_set_block(mat->v, block_3.v, row, col, 3, 4);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static dmat4 dmat4_set_this_block3_v(double *mat, const double *block_3, int row, int col) {
    return dmat4_set_this_block3((dmat4 *) mat, DMat3(block_3), row, col);
}


/** dst = mat[:2, :2] */
static dmat2 dmat4_get_upper_left2(dmat4 mat) {
    return dmat4_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static dmat2 dmat4_get_upper_left2_v(const double *mat) {
    return dmat4_get_upper_left2(DMat4(mat));
}


/** dst = mat; dst[:2, :2] = block */
static dmat4 dmat4_set_upper_left2(dmat4 mat, dmat2 block_2) {
    return dmat4_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static dmat4 dmat4_set_upper_left2_v(const double *mat, const double *block_2) {
    return dmat4_set_upper_left2(DMat4(mat), DMat2(block_2));
}

/** mat[:2, :2] = block; dst = mat */
static dmat4 dmat4_set_this_upper_left2(dmat4 *mat, dmat2 block_2) {
    return dmat4_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static dmat4 dmat4_set_this_upper_left2_v(double *mat, const double *block_2) {
    return dmat4_set_this_upper_left2((dmat4 *) mat, DMat2(block_2));
}


/** dst = mat[:3, :3] */
static dmat3 dmat4_get_upper_left3(dmat4 mat) {
    return dmat4_get_block3(mat, 0, 0);
}
/** dst = mat[:3, :3] */
static dmat3 dmat4_get_upper_left3_v(const double *mat) {
    return dmat4_get_upper_left3(DMat4(mat));
}


/** dst = mat; dst[:3, :3] = block */
static dmat4 dmat4_set_upper_left3(dmat4 mat, dmat3 block_3) {
    return dmat4_set_block3(mat, block_3, 0, 0);
}
/** dst = mat; dst[:3, :3] = block */
static dmat4 dmat4_set_upper_left3_v(const double *mat, const double *block_3) {
    return dmat4_set_upper_left3(DMat4(mat), DMat3(block_3));
}

/** mat[:3, :3] = block; dst = mat */
static dmat4 dmat4_set_this_upper_left3(dmat4 *mat, dmat3 block_3) {
    return dmat4_set_this_block3(mat, block_3, 0, 0);
}
/** mat[:3, :3] = block; dst = mat */
static dmat4 dmat4_set_this_upper_left3_v(double *mat, const double *block_3) {
    return dmat4_set_this_upper_left3((dmat4 *) mat, DMat3(block_3));
}

#endif //MATHC_MAT_DMAT4_H
