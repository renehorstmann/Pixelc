#ifndef MATHC_MAT_CMAT2_H
#define MATHC_MAT_CMAT2_H

#include "cmatn.h"
#include "../types/char.h"
#include "../vec/cvecn.h"


/** dst = r==c ? 1 : 0 (identity)  */
static cmat2 cmat2_eye() {
    cmat2 res;
    cmatN_eye(res.v, 2);
    return res;
}

/** dst = (cmat2) v */
static cmat2 cmat2_cast_from_float(const float *v) {
    cmat2 res;
    cvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (cmat2) v */
static cmat2 cmat2_cast_from_double(const double *v) {
    cmat2 res;
    cvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (cmat2) v */
static cmat2 cmat2_cast_from_int(const int *v) {
    cmat2 res;
    cvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (cmat2) v */
static cmat2 cmat2_cast_from_unsigned(const unsigned *v) {
    cmat2 res;
    cvecN_cast_into(res.v, v, 2*2);
    return res;
}

/** dst = (cmat2) v */
static cmat2 cmat2_cast_from_uchar(const unsigned char *v) {
    cmat2 res;
    cvecN_cast_into(res.v, v, 2*2);
    return res;
}


/** mat_a == mat_b */
static bool cmat2_cmp(cmat2 a, cmat2 b) {
    return cvecN_cmp(a.v, b.v, 2*2);
}

/** dst = mat[row][:] */
static cvec2 cmat2_get_row(cmat2 mat, int row) {
    cvec2 res;
    cmatN_get_row(res.v, mat.v, row, 2);
    return res;
}
/** dst = mat[row][:] */
static cvec2 cmat2_get_row_v(const char *mat, int row) {
    return cmat2_get_row(CMat2(mat), row);
}


/** dst = mat[:][col] */
static cvec2 cmat2_get_col(cmat2 mat, int col) {
    cvec2 res;
    cmatN_get_col(res.v, mat.v, col, 2);
    return res;
}
/** dst = mat[:][col] */
static cvec2 cmat2_get_col_v(const char *mat, int col) {
    return cmat2_get_col(CMat2(mat), col);
}


/** dst = mat; dst[row][:] = vec */
static cmat2 cmat2_set_row(cmat2 mat, cvec2 vec, int row) {
    cmatN_set_row(mat.v, vec.v, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = vec */
static cmat2 cmat2_set_row_v(const char *mat, const char *vec, int row) {
    return cmat2_set_row(CMat2(mat), CVec2(vec), row);
}

/** mat[row][:] = vec; dst = mat */
static cmat2 cmat2_set_this_row(cmat2 *mat, cvec2 vec, int row) {
    cmatN_set_row(mat->v, vec.v, row, 2);
    return *mat;
}
/** mat[row][:] = vec; dst = mat */
static cmat2 cmat2_set_this_row_v(char *mat, const char *vec, int row) {
    return cmat2_set_this_row((cmat2*) mat, CVec2(vec), row);
}

/** dst = mat; dst[:][col] = vec */
static cmat2 cmat2_set_col(cmat2 mat, cvec2 vec, int col) {
    cmatN_set_col(mat.v, vec.v, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = vec */
static cmat2 cmat2_set_col_v(const char *mat, const char *vec, int col) {
    return cmat2_set_col(CMat2(mat), CVec2(vec), col);
}

/** mat[:][col] = vec; dst = mat */
static cmat2 cmat2_set_this_col(cmat2 *mat, cvec2 vec, int col) {
    cmatN_set_col(mat->v, vec.v, col, 2);
    return *mat;
}
/** mat[:][col] = vec; dst = mat */
static cmat2 cmat2_set_this_col_v(char *mat, const char *vec, int col) {
    return cmat2_set_this_col((cmat2*) mat, CVec2(vec), col);
}


/** dst = mat; dst[row][:] = scalar */
static cmat2 cmat2_set_row_sca(cmat2 mat, char scalar, int row) {
    cmatN_set_row_sca(mat.v, scalar, row, 2);
    return mat;
}
/** dst = mat; dst[row][:] = scalar */
static cmat2 cmat2_set_row_sca_v(const char *mat, char scalar, int row) {
    return cmat2_set_row_sca(CMat2(mat), scalar, row);
}

/** mat[row][:] = scalar; dst = mat */
static cmat2 cmat2_set_this_row_sca(cmat2 *mat, char scalar, int row) {
    cmatN_set_row_sca(mat->v, scalar, row, 2);
    return *mat;
}
/** mat[row][:] = scalar; dst = mat */
static cmat2 cmat2_set_this_row_sca_v(char *mat, char scalar, int row) {
    return cmat2_set_this_row_sca((cmat2*) mat, scalar, row);
}


/** dst = mat; dst[:][col] = scalar */
static cmat2 cmat2_set_col_sca(cmat2 mat, char scalar, int col) {
    cmatN_set_col_sca(mat.v, scalar, col, 2);
    return mat;
}
/** dst = mat; dst[:][col] = scalar */
static cmat2 cmat2_set_col_sca_v(const char *mat, char scalar, int col) {
    return cmat2_set_col_sca(CMat2(mat), scalar, col);
}

/** mat[:][col] = scalar; dst = mat */
static cmat2 cmat2_set_this_col_sca(cmat2 *mat, char scalar, int col) {
    cmatN_set_col_sca(mat->v, scalar, col, 2);
    return *mat;
}
/** mat[:][col] = scalar; dst = mat */
static cmat2 cmat2_set_this_col_sca_v(char *mat, char scalar, int col) {
    return cmat2_set_this_col_sca((cmat2*) mat, scalar, col);
}


/** returns sum of diagonal form upper left to lower right */
static int cmat2_trace(cmat2 mat) {
    return cmatN_trace(mat.v, 2);
}
/** returns sum of diagonal form upper left to lower right */
static int cmat2_trace_v(const char *mat) {
    return cmat2_trace(CMat2(mat));
}


/** dst = mat^t */
static cmat2 cmat2_transpose(cmat2 mat) {
    cmat2 res;
    cmatN_transpose_no_alias(res.v, mat.v, 2);
    return res;
}
/** dst = mat^t */
static cmat2 cmat2_transpose_v(const char *mat) {
    return cmat2_transpose(CMat2(mat));
}


/** dst = a @ b */
static cmat2 cmat2_mul_mat(cmat2 mat_a, cmat2 mat_b) {
    cmat2 res;
    cmatN_mul_mat_no_alias(res.v, mat_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static cmat2 cmat2_mul_mat_v(const char *mat_a, const char *mat_b) {
    return cmat2_mul_mat(CMat2(mat_a), CMat2(mat_b));
}


/** dst = a @ b */
static cvec2 cmat2_mul_vec(cmat2 mat_a, cvec2 vec_b) {
    cvec2 res;
    cmatN_mul_vec_no_alias(res.v, mat_a.v, vec_b.v, 2);
    return res;
}
/** dst = a @ b */
static cvec2 cmat2_mul_vec_v(const char *mat_a, const char *vec_b) {
    return cmat2_mul_vec(CMat2(mat_a), CVec2(vec_b));
}


/** dst = a @ b */
static cvec2 cvec2_mul_mat(cvec2 vec_a, cmat2 mat_b) {
    cvec2 res;
    cvecN_mul_mat_no_alias(res.v, vec_a.v, mat_b.v, 2);
    return res;
}
/** dst = a @ b */
static cvec2 cvec2_mul_mat_v(const char *vec_a, const char *mat_b) {
    return cvec2_mul_mat(CVec2(vec_a), CMat2(mat_b));
}


/** returns = determinant mat */
static int cmat2_det(cmat2 mat) {
    // from cglm/cmat2.h/glm_cmat2_det
    return mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1];
}
/** returns = determinant mat */
static int cmat2_det_v(const char *mat) {
    return cmat2_det(CMat2(mat));
}


/** dst = inverted mat */
static cmat2 cmat2_inv(cmat2 mat) {
    // from cglm/cmat2.h/glm_cmat2_inv
    float a = mat.m[0][0], b = mat.m[0][1];
    float c = mat.m[1][0], d = mat.m[1][1];
    float inv_det = 1.0f / (a * d - b * c);

    cmat2 res;
    res.m[0][0] = (char) (d * inv_det);
    res.m[0][1] = (char) (-b * inv_det);
    res.m[1][0] = (char) (-c * inv_det);
    res.m[1][1] = (char) (a * inv_det);
    return res;
}
/** dst = inverted mat */
static cmat2 cmat2_inv_v(const char *mat) {
    return cmat2_inv(CMat2(mat));
}


#endif //MATHC_MAT_CMAT2_H
