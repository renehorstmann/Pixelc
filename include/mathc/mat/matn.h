#ifndef MATHC_MAT_MATN_H
#define MATHC_MAT_MATN_H

// restrict
#ifdef __cplusplus
#define restrict __restrict
#endif

#ifndef MATHC_MAX_SIZE
#ifdef __STDC_NO_VLA__
#define MATHC_MAX_SIZE 16
#endif
#endif

#include <math.h>
#include <assert.h>


/** dst = r==c ? 1 : 0 (identity) */
static void matN_eye(float *dst_mat, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            dst_mat[r * n + c] = r == c ? 1 : 0;
    }
}

/** dst = mat[row][:] */
static void matN_get_row(float *dst_vec, const float *mat, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_vec[c] = mat[c * n + row];
}

/** dst = mat[:][col] */
static void matN_get_col(float *dst_vec, const float *mat, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_vec[r] = mat[col * n + r];
}

/** dst[row][:] = vec */
static void matN_set_row(float *dst_mat, const float *vec, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_mat[c * n + row] = vec[c];
}

/** dst[:][col] = vec */
static void matN_set_col(float *dst_mat, const float *vec, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_mat[col * n + r] = vec[r];
}

/** dst[row][:] = scalar */
static void matN_set_row_sca(float *dst_mat, float scalar, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_mat[c * n + row] = scalar;
}

/** dst[:][col] = scalar */
static void matN_set_col_sca(float *dst_mat, float scalar, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_mat[col * n + r] = scalar;
}

/** returns sum of diagonal form upper left to lower right */
static float matN_trace(const float *mat, int n) {
    float sum = 0;
    for(int i=0; i<n; i++)
        sum += mat[i*n + i];
    return sum;
}

/** dst = mat^t  (restrict data) */
static void matN_transpose_no_alias(float *restrict dst_mat, const float *restrict mat, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst_mat[c * n + r] = mat[c * n + r];
        }
    }
}

/** dst = mat^t */
static void matN_transpose(float *dst_mat, const float *mat, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    float tmp[MATHC_MAX_SIZE * MATHC_MAX_SIZE];
#else
    float tmp[n * n];
#endif
    matN_transpose_no_alias(tmp, mat, n);
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void matN_mul_mat_no_alias(float *restrict dst_mat, const float *restrict mat_a,
                                  const float *restrict mat_b, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst_mat[c * n + r] = 0;
            for (int k = 0; k < n; k++)
                dst_mat[c * n + r] += mat_a[k * n + r] * mat_b[c * n + k];
        }
    }
}

/** dst = a @ b */
static void matN_mul_mat(float *dst_mat, const float *mat_a, const float *mat_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    float tmp[MATHC_MAX_SIZE * MATHC_MAX_SIZE];
#else
    float tmp[n * n];
#endif
    matN_mul_mat_no_alias(tmp, mat_a, mat_b, n);
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void matN_mul_vec_no_alias(float *restrict dst_vec, const float *restrict mat_a,
                                  const float *restrict vec_b, int n) {
    for (int r = 0; r < n; r++) {
        dst_vec[r] = 0;
        for (int c = 0; c < n; c++) {
            dst_vec[r] += mat_a[c * n + r] * vec_b[c];
        }
    }
}

/** dst = a @ b */
static void matN_mul_vec(float *dst_vec, const float *mat_a, const float *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    float tmp[MATHC_MAX_SIZE];
#else
    float tmp[n];
#endif
    matN_mul_vec_no_alias(tmp, mat_a, vec_b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void vecN_mul_mat_no_alias(float *restrict dst_vec, const float *restrict vec_a,
                                  const float *restrict mat_b, int n) {
    for (int c = 0; c < n; c++) {
        dst_vec[c] = 0;
        for (int r = 0; r < n; r++) {
            dst_vec[c] += mat_b[c * n + r] * vec_a[r];
        }
    }
}

/** dst = a @ b */
static void vecN_mul_mat(float *dst_vec, const float *vec_a, const float *mat_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    float tmp[MATHC_MAX_SIZE];
#else
    float tmp[n];
#endif
    vecN_mul_mat_no_alias(tmp, vec_a, mat_b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** block<block_n*block_n> = mat<n*n>[col:col+block_n, row:row+block_n] */
static void matN_get_block(float * restrict dst_block, const float * restrict mat, int row, int col, int block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for(int c=0; c<block_n; c++) {
        for(int r=0; r<block_n; r++) {
            dst_block[c * block_n + r] = mat[c * n + r];
        }
    }
}

/** dst<n*n>[col:col+block_n, row:row+block_n] = block<block_n*block_n> */
static void matN_set_block(float * restrict dst_mat, const float * restrict block, int row, int col, int block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for(int c=0; c<block_n; c++) {
        for(int r=0; r<block_n; r++) {
            dst_mat[c * n + r] = block[c * block_n + r];
        }
    }
}

#endif //MATHC_MAT_MATN_H
