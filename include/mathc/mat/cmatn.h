#ifndef MATHC_MAT_CMATN_H
#define MATHC_MAT_CMATN_H

// restrict
#ifdef __cplusplus
#define restrict __restrict
#endif

#ifndef MATHC_MAX_SIZE
#ifdef __STDC_NO_VLA__
#define MATHC_MAX_SIZE 16
#endif
#endif

#include <stdint.h>
#include <math.h>
#include <assert.h>


/** dst = r==c ? 1 : 0 (identity) */
static void cmatN_eye(int8_t *dst_mat, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            dst_mat[r * n + c] = r == c ? 1 : 0;
    }
}

/** dst = mat[row][:] */
static void cmatN_get_row(int8_t *dst_vec, const int8_t *mat, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_vec[c] = mat[c * n + row];
}

/** dst = mat[:][col] */
static void cmatN_get_col(int8_t *dst_vec, const int8_t *mat, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_vec[r] = mat[col * n + r];
}

/** dst[row][:] = vec */
static void cmatN_set_row(int8_t *dst_mat, const int8_t *vec, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_mat[c * n + row] = vec[c];
}

/** dst[:][col] = vec */
static void cmatN_set_col(int8_t *dst_mat, const int8_t *vec, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_mat[col * n + r] = vec[r];
}

/** dst[row][:] = scalar */
static void cmatN_set_row_sca(int8_t *dst_mat, int8_t scalar, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_mat[c * n + row] = scalar;
}

/** dst[:][col] = scalar */
static void cmatN_set_col_sca(int8_t *dst_mat, int8_t scalar, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_mat[col * n + r] = scalar;
}

/** returns sum of diagonal form upper left to lower right */
static int cmatN_trace(const int8_t *mat, int n) {
    int sum = 0;
    for(int i=0; i<n; i++)
        sum += mat[i*n + i];
    return sum;
}

/** dst = mat^t  (restrict data) */
static void cmatN_transpose_no_alias(int8_t *restrict dst_mat, const int8_t *restrict mat, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst_mat[c * n + r] = mat[r * n + c];
        }
    }
}

/** dst = mat^t */
static void cmatN_transpose(int8_t *dst_mat, const int8_t *mat, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    int8_t tmp[MATHC_MAX_SIZE * MATHC_MAX_SIZE];
#else
    int8_t tmp[n * n];
#endif
    cmatN_transpose_no_alias(tmp, mat, n);
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void cmatN_mul_mat_no_alias(int8_t *restrict dst_mat, const int8_t *restrict mat_a,
                                  const int8_t *restrict mat_b, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst_mat[c * n + r] = 0;
            for (int k = 0; k < n; k++)
                dst_mat[c * n + r] += mat_a[k * n + r] * mat_b[c * n + k];
        }
    }
}

/** dst = a @ b */
static void cmatN_mul_mat(int8_t *dst_mat, const int8_t *mat_a, const int8_t *mat_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    int8_t tmp[MATHC_MAX_SIZE * MATHC_MAX_SIZE];
#else
    int8_t tmp[n * n];
#endif
    cmatN_mul_mat_no_alias(tmp, mat_a, mat_b, n);
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void cmatN_mul_vec_no_alias(int8_t *restrict dst_vec, const int8_t *restrict mat_a,
                                  const int8_t *restrict vec_b, int n) {
    for (int r = 0; r < n; r++) {
        dst_vec[r] = 0;
        for (int c = 0; c < n; c++) {
            dst_vec[r] += mat_a[c * n + r] * vec_b[c];
        }
    }
}

/** dst = a @ b */
static void cmatN_mul_vec(int8_t *dst_vec, const int8_t *mat_a, const int8_t *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    int8_t tmp[MATHC_MAX_SIZE];
#else
    int8_t tmp[n];
#endif
    cmatN_mul_vec_no_alias(tmp, mat_a, vec_b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void cvecN_mul_mat_no_alias(int8_t *restrict dst_vec, const int8_t *restrict vec_a,
                                  const int8_t *restrict mat_b, int n) {
    for (int c = 0; c < n; c++) {
        dst_vec[c] = 0;
        for (int r = 0; r < n; r++) {
            dst_vec[c] += mat_b[c * n + r] * vec_a[r];
        }
    }
}

/** dst = a @ b */
static void cvecN_mul_mat(int8_t *dst_vec, const int8_t *vec_a, const int8_t *mat_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    int8_t tmp[MATHC_MAX_SIZE];
#else
    int8_t tmp[n];
#endif
    cvecN_mul_mat_no_alias(tmp, vec_a, mat_b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** block<block_n*block_n> = mat<n*n>[col:col+block_n, row:row+block_n] */
static void cmatN_get_block(int8_t * restrict dst_block, const int8_t * restrict mat, int row, int col, int8_t block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for(int c=0; c<block_n; c++) {
        for(int r=0; r<block_n; r++) {
            dst_block[c * block_n + r] = mat[c * n + r];
        }
    }
}

/** dst<n*n>[col:col+block_n, row:row+block_n] = block<block_n*block_n> */
static void cmatN_set_block(int8_t * restrict dst_mat, const int8_t * restrict block, int row, int col, int8_t block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for(int c=0; c<block_n; c++) {
        for(int r=0; r<block_n; r++) {
            dst_mat[c * n + r] = block[c * block_n + r];
        }
    }
}

#endif //MATHC_MAT_CMATN_H
