#ifndef MATHC_MAT_UMAT2_H
#define MATHC_MAT_UMAT2_H

#include "umatn.h"
#include "../types/uint.h"


/** dst = r==c ? 1 : 0 (identity)  */
static umat2 umat2_eye() {
    umat2 res;
    umatN_eye(res.v, 2);
    return res;
}

/** dst = (umat2) v */
static umat2 umat2_cast_from_float(const float *v) {
    umat2 res;
    vecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (umat2) v */
static umat2 umat2_cast_from_double(const double *v) {
    umat2 res;
    vecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (umat2) v */
static umat2 umat2_cast_from_int(const int *v) {
    umat2 res;
    vecN_cast_into(res.v, v, 2*2);
    return res;
}


/** dst = mat[row][:] */
static uvec2 umat2_get_row(umat2 mat, int row) {
    uvec2 res;
    umatN_get_row(res.v, mat.v, row, 2);
    return res;
}
/** dst = mat[row][:] */
static uvec2 umat2_get_row_v(const unsigned *mat, int row) {
    return umat2_get_row(UMat2(mat), row);
}


/** dst = mat[:][col] */
static uvec2 umat2_get_col(umat2 mat, int col) {
    uvec2 res;
    umatN_get_col(res.v, mat.v, col, 2);
    return res;
}
/** dst = mat[:][col] */
static uvec2 umat2_get_col_v(const unsigned *mat, int col) {
    return umat2_get_col(UMat2(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static umat2 umat2_set_row(umat2 mat, uvec2 vec, int row) {
    umatN_set_row(mat.v, vec.v, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static umat2 umat2_set_row_v(const unsigned *mat, const unsigned *vec, int row) {
    return umat2_set_row(UMat2(mat), UVec2(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static umat2 umat2_set_this_row(umat2 *mat, uvec2 vec, int row) {
    umatN_set_row(mat->v, vec.v, row, 2);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static umat2 umat2_set_this_row_v(unsigned *mat, const unsigned *vec, int row) {
    return umat2_set_this_row((umat2*) mat, UVec2(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static umat2 umat2_set_col(umat2 mat, uvec2 vec, int col) {
    umatN_set_col(mat.v, vec.v, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static umat2 umat2_set_col_v(const unsigned *mat, const unsigned *vec, int col) {
    return umat2_set_col(UMat2(mat), UVec2(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static umat2 umat2_set_this_col(umat2 *mat, uvec2 vec, int col) {
    umatN_set_col(mat->v, vec.v, col, 2);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static umat2 umat2_set_this_col_v(unsigned *mat, const unsigned *vec, int col) {
    return umat2_set_this_col((umat2*) mat, UVec2(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static umat2 umat2_set_row_sca(umat2 mat, unsigned scalar, int row) {
    umatN_set_row_sca(mat.v, scalar, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static umat2 umat2_set_row_sca_v(const unsigned *mat, unsigned scalar, int row) {
    return umat2_set_row_sca(UMat2(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static umat2 umat2_set_this_row_sca(umat2 *mat, unsigned scalar, int row) {
    umatN_set_row_sca(mat->v, scalar, row, 2);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static umat2 umat2_set_this_row_sca_v(unsigned *mat, unsigned scalar, int row) {
    return umat2_set_this_row_sca((umat2*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static umat2 umat2_set_col_sca(umat2 mat, unsigned scalar, int col) {
    umatN_set_col_sca(mat.v, scalar, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static umat2 umat2_set_col_sca_v(const unsigned *mat, unsigned scalar, int col) {
    return umat2_set_col_sca(UMat2(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static umat2 umat2_set_this_col_sca(umat2 *mat, unsigned scalar, int col) {
    umatN_set_col_sca(mat->v, scalar, col, 2);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static umat2 umat2_set_this_col_sca_v(unsigned *mat, unsigned scalar, int col) {
    return umat2_set_this_col_sca((umat2*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static unsigned umat2_trace(umat2 mat) {
    return umatN_trace(mat.v, 2);
}
/** returns sum of diagonal form upper left to lower right */
static unsigned umat2_trace_v(const unsigned *mat) {
    return umat2_trace(UMat2(mat));
}


/** dst = mat^t */
static umat2 umat2_transpose(umat2 mat) {
    umat2 res;
    umatN_transpose_no_alias(res.v, mat.v, 2);
    return res;
}
/** dst = mat^t */
static umat2 umat2_transpose_v(const unsigned *mat) {
    return umat2_transpose(UMat2(mat));
}


/** dst = a @ b */
static umat2 umat2_mul_mat(umat2 mat_a, umat2 mat_b) {
    umat2 res;
    umatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static umat2 umat2_mul_mat_v(const unsigned *mat_a, const unsigned *mat_b) {
    return umat2_mul_mat(UMat2(mat_a), UMat2(mat_b));
}


/** dst = a @ b */
static uvec2 umat2_mul_vec(umat2 mat_a, uvec2 vec_b) {
    uvec2 res;
    umatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 2);
    return res;
}
/** dst = a @ b */
static uvec2 umat2_mul_vec_v(const unsigned *mat_a, const unsigned *vec_b) {
    return umat2_mul_vec(UMat2(mat_a), UVec2(vec_b));
}


/** dst = a @ b */
static uvec2 uvec2_mul_mat(uvec2 vec_a, umat2 mat_b) {
    uvec2 res;
    uvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static uvec2 uvec2_mul_mat_v(const unsigned *vec_a, const unsigned *mat_b) {
    return uvec2_mul_mat(UVec2(vec_a), UMat2(mat_b));
}


/** returns = determinant mat */
static unsigned umat2_det(umat2 mat) {
    // from cglm/umat2.h/glm_umat2_det
    return mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1];
}
/** returns = determinant mat */
static unsigned umat2_det_v(const unsigned *mat) {
    return umat2_det(UMat2(mat));
}


/** dst = inverted mat */
static umat2 umat2_inv(umat2 mat) {
    // from cglm/umat2.h/glm_umat2_inv
    float a = mat.m[0][0], b = mat.m[0][1];
    float c = mat.m[1][0], d = mat.m[1][1];
    float inv_det = 1.0f / (a * d - b * c);

    umat2 res;
    res.m[0][0] = (unsigned) (d * inv_det);
    res.m[0][1] = (unsigned) (-b * inv_det);
    res.m[1][0] = (unsigned) (-c * inv_det);
    res.m[1][1] = (unsigned) (a * inv_det);
    return res;
}
/** dst = inverted mat */
static umat2 umat2_inv_v(const unsigned *mat) {
    return umat2_inv(UMat2(mat));
}


#endif //MATHC_MAT_UMAT2_H
