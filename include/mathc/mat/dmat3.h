#ifndef MATHC_MAT_DMAT3_H
#define MATHC_MAT_DMAT3_H

#include "dmatn.h"
#include "../types/double.h"
#include "../vec/dvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static dmat3 dmat3_eye() {
    dmat3 res;
    dmatN_eye(res.v, 3);
    return res;
}


/** dst = (dmat3) v */
static dmat3 dmat3_cast_from_float(const float *v) {
    dmat3 res;
    vecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (dmat3) v */
static dmat3 dmat3_cast_from_int(const int *v) {
    dmat3 res;
    vecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = (dmat3) v */
static dmat3 dmat3_cast_from_unsigned(const unsigned *v) {
    dmat3 res;
    vecN_cast_into(res.v, v, 3*3);
    return res;
}

/** dst = mat[row][:] */
static dvec3 dmat3_get_row(dmat3 mat, int row) {
    dvec3 res;
    dmatN_get_row(res.v, mat.v, row, 3);
    return res;
}
/** dst = mat[row][:] */
static dvec3 dmat3_get_row_v(const double *mat, int row) {
    return dmat3_get_row(DMat3(mat), row);
}


/** dst = mat[:][col] */
static dvec3 dmat3_get_col(dmat3 mat, int col) {
    dvec3 res;
    dmatN_get_col(res.v, mat.v, col, 3);
    return res;
}
/** dst = mat[:][col] */
static dvec3 dmat3_get_col_v(const double *mat, int col) {
    return dmat3_get_col(DMat3(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static dmat3 dmat3_set_row(dmat3 mat, dvec3 vec, int row) {
    dmatN_set_row(mat.v, vec.v, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static dmat3 dmat3_set_row_v(const double *mat, const double *vec, int row) {
    return dmat3_set_row(DMat3(mat), DVec3(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static dmat3 dmat3_set_this_row(dmat3 *mat, dvec3 vec, int row) {
    dmatN_set_row(mat->v, vec.v, row, 3);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static dmat3 dmat3_set_this_row_v(double *mat, const double *vec, int row) {
    return dmat3_set_this_row((dmat3*) mat, DVec3(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static dmat3 dmat3_set_col(dmat3 mat, dvec3 vec, int col) {
    dmatN_set_col(mat.v, vec.v, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static dmat3 dmat3_set_col_v(const double *mat, const double *vec, int col) {
    return dmat3_set_col(DMat3(mat), DVec3(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static dmat3 dmat3_set_this_col(dmat3 *mat, dvec3 vec, int col) {
    dmatN_set_col(mat->v, vec.v, col, 3);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static dmat3 dmat3_set_this_col_v(double *mat, const double *vec, int col) {
    return dmat3_set_this_col((dmat3*) mat, DVec3(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static dmat3 dmat3_set_row_sca(dmat3 mat, double scalar, int row) {
    dmatN_set_row_sca(mat.v, scalar, row, 3);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static dmat3 dmat3_set_row_sca_v(const double *mat, double scalar, int row) {
    return dmat3_set_row_sca(DMat3(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static dmat3 dmat3_set_this_row_sca(dmat3 *mat, double scalar, int row) {
    dmatN_set_row_sca(mat->v, scalar, row, 3);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static dmat3 dmat3_set_this_row_sca_v(double *mat, double scalar, int row) {
    return dmat3_set_this_row_sca((dmat3*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static dmat3 dmat3_set_col_sca(dmat3 mat, double scalar, int col) {
    dmatN_set_col_sca(mat.v, scalar, col, 3);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static dmat3 dmat3_set_col_sca_v(const double *mat, double scalar, int col) {
    return dmat3_set_col_sca(DMat3(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static dmat3 dmat3_set_this_col_sca(dmat3 *mat, double scalar, int col) {
    dmatN_set_col_sca(mat->v, scalar, col, 3);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static dmat3 dmat3_set_this_col_sca_v(double *mat, double scalar, int col) {
    return dmat3_set_this_col_sca((dmat3*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static double dmat3_trace(dmat3 mat) {
    return dmatN_trace(mat.v, 3);
}
/** returns sum of diagonal form upper left to lower right */
static double dmat3_trace_v(const double *mat) {
    return dmat3_trace(DMat3(mat));
}


/** dst = mat^t */
static dmat3 dmat3_transpose(dmat3 mat) {
    dmat3 res;
    dmatN_transpose_no_alias(res.v, mat.v, 3);
    return res;
}
/** dst = mat^t */
static dmat3 dmat3_transpose_v(const double *mat) {
    return dmat3_transpose(DMat3(mat));
}


/** dst = a @ b */
static dmat3 dmat3_mul_mat(dmat3 mat_a, dmat3 mat_b) {
    dmat3 res;
    dmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static dmat3 dmat3_mul_mat_v(const double *mat_a, const double *mat_b) {
    return dmat3_mul_mat(DMat3(mat_a), DMat3(mat_b));
}


/** dst = a @ b */
static dvec3 dmat3_mul_vec(dmat3 mat_a, dvec3 vec_b) {
    dvec3 res;
    dmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 3);
    return res;
}
/** dst = a @ b */
static dvec3 dmat3_mul_vec_v(const double *mat_a, const double *vec_b) {
    return dmat3_mul_vec(DMat3(mat_a), DVec3(vec_b));
}


/** dst = a @ b */
static dvec3 dvec3_mul_mat(dvec3 vec_a, dmat3 mat_b) {
    dvec3 res;
    dvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 3);
    return res;
}
/** dst = a @ b */
static dvec3 dvec3_mul_mat_v(const double *vec_a, const double *mat_b) {
    return dvec3_mul_mat(DVec3(vec_a), DMat3(mat_b));
}


/** returns = determinant mat */
static double dmat3_det(dmat3 mat) {
    // from cglm/dmat3.h/glm_dmat3_det
    double a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    double d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    double g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}
/** returns = determinant mat */
static double dmat3_det_v(const double *mat) {
    return dmat3_det(DMat3(mat));
}


/** dst = inverted mat */
static dmat3 dmat3_inv(dmat3 mat) {
    // from cglm/dmat3.h/glm_dmat3_inv
    double a = mat.m[0][0], b = mat.m[0][1], c = mat.m[0][2];
    double d = mat.m[1][0], e = mat.m[1][1], f = mat.m[1][2];
    double g = mat.m[2][0], h = mat.m[2][1], i = mat.m[2][2];

    dmat3 res;
    res.m[0][0] =   e * i - f * h;
    res.m[0][1] = -(b * i - h * c);
    res.m[0][2] =   b * f - e * c;
    res.m[1][0] = -(d * i - g * f);
    res.m[1][1] =   a * i - c * g;
    res.m[1][2] = -(a * f - d * c);
    res.m[2][0] =   d * h - g * e;
    res.m[2][1] = -(a * h - g * b);
    res.m[2][2] =   a * e - b * d;

    double inv_det = 1.0 / (a * res.m[0][0] + b * res.m[1][0] + c * res.m[2][0]);

    dvecN_scale(res.v, res.v, inv_det, 9);
    return res;
}
/** dst = inverted mat */
static dmat3 dmat3_inv_v(const double *mat) {
    return dmat3_inv(DMat3(mat));
}


/** dst = mat[col:col+2, row:row+2] */
static dmat2 dmat3_get_block2(dmat3 mat, int row, int col) {
    dmat2 res;
    dmatN_get_block(res.v, mat.v, row, col, 2, 3);
    return res;
}
/** dst = mat[col:col+2, row:row+2] */
static dmat2 dmat3_get_block2_v(const double *mat, int row, int col) {
    return dmat3_get_block2(DMat3(mat), row, col);
}


/** dst = mat; dst[col:col+2, row:row+2] = block */
static dmat3 dmat3_set_block2(dmat3 mat, dmat2 block_2, int row, int col) {
    dmatN_set_block(mat.v, block_2.v, row, col, 2, 3);
    return mat;
}
/** dst = mat; dst[col:col+2, row:row+2] = block */
static dmat3 dmat3_set_block2_v(const double *mat, const double *block_2, int row, int col) {
    return dmat3_set_block2(DMat3(mat), DMat2(block_2), row, col);
}

/** mat[col:col+2, row:row+2] = block; dst = mat */
static dmat3 dmat3_set_this_block2(dmat3 *mat, dmat2 block_2, int row, int col) {
    dmatN_set_block(mat->v, block_2.v, row, col, 2, 3);
    return *mat;
}
/** mat[col:col+2, row:row+2] = block; dst = mat */
static dmat3 dmat3_set_this_block2_v(double *mat, const double *block_2, int row, int col) {
    return dmat3_set_this_block2((dmat3 *) mat, DMat2(block_2), row, col);
}


/** dst = mat[:2, :2] */
static dmat2 dmat3_get_upper_left(dmat3 mat) {
    return dmat3_get_block2(mat, 0, 0);
}
/** dst = mat[:2, :2] */
static dmat2 dmat3_get_upper_left_v(const double *mat) {
    return dmat3_get_upper_left(DMat3(mat));
}


/** dst = mat; dst[:2, :2] = block */
static dmat3 dmat3_set_upper_left(dmat3 mat, dmat2 block_2) {
    return dmat3_set_block2(mat, block_2, 0, 0);
}
/** dst = mat; dst[:2, :2] = block */
static dmat3 dmat3_set_upper_left_v(const double *mat, const double *block_2) {
    return dmat3_set_upper_left(DMat3(mat), DMat2(block_2));
}


/** mat[:2, :2] = block; dst = mat */
static dmat3 dmat3_set_this_upper_left(dmat3 *mat, dmat2 block_2) {
    return dmat3_set_this_block2(mat, block_2, 0, 0);
}
/** mat[:2, :2] = block; dst = mat */
static dmat3 dmat3_set_this_upper_left_v(double *mat, const double *block_2) {
    return dmat3_set_this_upper_left((dmat3 *) mat, DMat2(block_2));
}


#endif //MATHC_MAT_DMAT3_H
