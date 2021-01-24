#ifndef MATHC_MAT_DMAT2_H
#define MATHC_MAT_DMAT2_H

#include "dmatn.h"
#include "../types/double.h"


/** dst = r==c ? 1 : 0 (identity)  */
static dmat2 dmat2_eye() {
    dmat2 res;
    dmatN_eye(res.v, 2);
    return res;
}


/** dst = mat[row][:] */
static dvec2 dmat2_get_row(dmat2 mat, int row) {
    dvec2 res;
    dmatN_get_row(res.v, mat.v, row, 2);
    return res;
}
/** dst = mat[row][:] */
static dvec2 dmat2_get_row_v(const double *mat, int row) {
    return dmat2_get_row(DMat2(mat), row);
}


/** dst = mat[:][col] */
static dvec2 dmat2_get_col(dmat2 mat, int col) {
    dvec2 res;
    dmatN_get_col(res.v, mat.v, col, 2);
    return res;
}
/** dst = mat[:][col] */
static dvec2 dmat2_get_col_v(const double *mat, int col) {
    return dmat2_get_col(DMat2(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static dmat2 dmat2_set_row(dmat2 mat, dvec2 vec, int row) {
    dmatN_set_row(mat.v, vec.v, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static dmat2 dmat2_set_row_v(const double *mat, const double *vec, int row) {
    return dmat2_set_row(DMat2(mat), DVec2(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static dmat2 dmat2_set_this_row(dmat2 *mat, dvec2 vec, int row) {
    dmatN_set_row(mat->v, vec.v, row, 2);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static dmat2 dmat2_set_this_row_v(double *mat, const double *vec, int row) {
    return dmat2_set_this_row((dmat2*) mat, DVec2(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static dmat2 dmat2_set_col(dmat2 mat, dvec2 vec, int col) {
    dmatN_set_col(mat.v, vec.v, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static dmat2 dmat2_set_col_v(const double *mat, const double *vec, int col) {
    return dmat2_set_col(DMat2(mat), DVec2(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static dmat2 dmat2_set_this_col(dmat2 *mat, dvec2 vec, int col) {
    dmatN_set_col(mat->v, vec.v, col, 2);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static dmat2 dmat2_set_this_col_v(double *mat, const double *vec, int col) {
    return dmat2_set_this_col((dmat2*) mat, DVec2(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static dmat2 dmat2_set_row_sca(dmat2 mat, double scalar, int row) {
    dmatN_set_row_sca(mat.v, scalar, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static dmat2 dmat2_set_row_sca_v(const double *mat, double scalar, int row) {
    return dmat2_set_row_sca(DMat2(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static dmat2 dmat2_set_this_row_sca(dmat2 *mat, double scalar, int row) {
    dmatN_set_row_sca(mat->v, scalar, row, 2);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static dmat2 dmat2_set_this_row_sca_v(double *mat, double scalar, int row) {
    return dmat2_set_this_row_sca((dmat2*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static dmat2 dmat2_set_col_sca(dmat2 mat, double scalar, int col) {
    dmatN_set_col_sca(mat.v, scalar, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static dmat2 dmat2_set_col_sca_v(const double *mat, double scalar, int col) {
    return dmat2_set_col_sca(DMat2(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static dmat2 dmat2_set_this_col_sca(dmat2 *mat, double scalar, int col) {
    dmatN_set_col_sca(mat->v, scalar, col, 2);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static dmat2 dmat2_set_this_col_sca_v(double *mat, double scalar, int col) {
    return dmat2_set_this_col_sca((dmat2*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static double dmat2_trace(dmat2 mat) {
    return dmatN_trace(mat.v, 2);
}
/** returns sum of diagonal form upper left to lower right */
static double dmat2_trace_v(const double *mat) {
    return dmat2_trace(DMat2(mat));
}


/** dst = mat^t */
static dmat2 dmat2_transpose(dmat2 mat) {
    dmat2 res;
    dmatN_transpose_no_alias(res.v, mat.v, 2);
    return res;
}
/** dst = mat^t */
static dmat2 dmat2_transpose_v(const double *mat) {
    return dmat2_transpose(DMat2(mat));
}


/** dst = a @ b */
static dmat2 dmat2_mul_mat(dmat2 mat_a, dmat2 mat_b) {
    dmat2 res;
    dmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static dmat2 dmat2_mul_mat_v(const double *mat_a, const double *mat_b) {
    return dmat2_mul_mat(DMat2(mat_a), DMat2(mat_b));
}


/** dst = a @ b */
static dvec2 dmat2_mul_vec(dmat2 mat_a, dvec2 vec_b) {
    dvec2 res;
    dmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 2);
    return res;
}
/** dst = a @ b */
static dvec2 dmat2_mul_vec_v(const double *mat_a, const double *vec_b) {
    return dmat2_mul_vec(DMat2(mat_a), DVec2(vec_b));
}


/** dst = a @ b */
static dvec2 dvec2_mul_mat(dvec2 vec_a, dmat2 mat_b) {
    dvec2 res;
    dvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static dvec2 dvec2_mul_mat_v(const double *vec_a, const double *mat_b) {
    return dvec2_mul_mat(DVec2(vec_a), DMat2(mat_b));
}


/** returns = determinant mat */
static double dmat2_det(dmat2 mat) {
    // from cglm/dmat2.h/glm_dmat2_det
    return mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1];
}
/** returns = determinant mat */
static double dmat2_det_v(const double *mat) {
    return dmat2_det(DMat2(mat));
}


/** dst = inverted mat */
static dmat2 dmat2_inv(dmat2 mat) {
    // from cglm/dmat2.h/glm_dmat2_inv
    double a = mat.m[0][0], b = mat.m[0][1];
    double c = mat.m[1][0], d = mat.m[1][1];
    double inv_det = 1.0 / (a * d - b * c);

    dmat2 res;
    res.m[0][0] = d * inv_det;
    res.m[0][1] = -b * inv_det;
    res.m[1][0] = -c * inv_det;
    res.m[1][1] = a * inv_det;
    return res;
}
/** dst = inverted mat */
static dmat2 dmat2_inv_v(const double *mat) {
    return dmat2_inv(DMat2(mat));
}


#endif //MATHC_MAT_DMAT2_H
