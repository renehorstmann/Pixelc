#ifndef MATHC_MAT_UMATN_H
#define MATHC_MAT_UMATN_H

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
static void umatN_eye(unsigned *dst_mat, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            dst_mat[r * n + c] = r == c ? 1 : 0;
    }
}

/** dst = mat[row][:] */
static void umatN_get_row(unsigned *dst_vec, const unsigned *mat, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_vec[c] = mat[c * n + row];
}

/** dst = mat[:][col] */
static void umatN_get_col(unsigned *dst_vec, const unsigned *mat, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_vec[r] = mat[col * n + r];
}

/** dst[row][:] = vec */
static void umatN_set_row(unsigned *dst_mat, const unsigned *vec, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_mat[c * n + row] = vec[c];
}

/** dst[:][col] = vec */
static void umatN_set_col(unsigned *dst_mat, const unsigned *vec, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_mat[col * n + r] = vec[r];
}

/** dst[row][:] = scalar */
static void umatN_set_row_sca(unsigned *dst_mat, unsigned scalar, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_mat[c * n + row] = scalar;
}

/** dst[:][col] = scalar */
static void umatN_set_col_sca(unsigned *dst_mat, unsigned scalar, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_mat[col * n + r] = scalar;
}

/** returns sum of diagonal form upper left to lower right */
static unsigned umatN_trace(const unsigned *mat, int n) {
    unsigned sum = 0;
    for(int i=0; i<n; i++)
        sum += mat[i*n + i];
    return sum;
}

/** dst = mat^t  (restrict data) */
static void umatN_transpose_no_alias(unsigned *restrict dst_mat, const unsigned *restrict mat, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst_mat[c * n + r] = mat[r * n + c];
        }
    }
}

/** dst = mat^t */
static void umatN_transpose(unsigned *dst_mat, const unsigned *mat, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned tmp[MATHC_MAX_SIZE * MATHC_MAX_SIZE];
#else
    unsigned tmp[n * n];
#endif
    umatN_transpose_no_alias(tmp, mat, n);
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void umatN_mul_mat_no_alias(unsigned *restrict dst_mat, const unsigned *restrict mat_a,
                                  const unsigned *restrict mat_b, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst_mat[c * n + r] = 0;
            for (int k = 0; k < n; k++)
                dst_mat[c * n + r] += mat_a[k * n + r] * mat_b[c * n + k];
        }
    }
}

/** dst = a @ b */
static void umatN_mul_mat(unsigned *dst_mat, const unsigned *mat_a, const unsigned *mat_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned tmp[MATHC_MAX_SIZE * MATHC_MAX_SIZE];
#else
    unsigned tmp[n * n];
#endif
    umatN_mul_mat_no_alias(tmp, mat_a, mat_b, n);
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void umatN_mul_vec_no_alias(unsigned *restrict dst_vec, const unsigned *restrict mat_a,
                                  const unsigned *restrict vec_b, int n) {
    for (int r = 0; r < n; r++) {
        dst_vec[r] = 0;
        for (int c = 0; c < n; c++) {
            dst_vec[r] += mat_a[c * n + r] * vec_b[c];
        }
    }
}

/** dst = a @ b */
static void umatN_mul_vec(unsigned *dst_vec, const unsigned *mat_a, const unsigned *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned tmp[MATHC_MAX_SIZE];
#else
    unsigned tmp[n];
#endif
    umatN_mul_vec_no_alias(tmp, mat_a, vec_b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void uvecN_mul_mat_no_alias(unsigned *restrict dst_vec, const unsigned *restrict vec_a,
                                  const unsigned *restrict mat_b, int n) {
    for (int c = 0; c < n; c++) {
        dst_vec[c] = 0;
        for (int r = 0; r < n; r++) {
            dst_vec[c] += mat_b[c * n + r] * vec_a[r];
        }
    }
}

/** dst = a @ b */
static void uvecN_mul_mat(unsigned *dst_vec, const unsigned *vec_a, const unsigned *mat_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned tmp[MATHC_MAX_SIZE];
#else
    unsigned tmp[n];
#endif
    uvecN_mul_mat_no_alias(tmp, vec_a, mat_b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** block<block_n*block_n> = mat<n*n>[col:col+block_n, row:row+block_n] */
static void umatN_get_block(unsigned * restrict dst_block, const unsigned * restrict mat, int row, int col, unsigned block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for(int c=0; c<block_n; c++) {
        for(int r=0; r<block_n; r++) {
            dst_block[c * block_n + r] = mat[c * n + r];
        }
    }
}

/** dst<n*n>[col:col+block_n, row:row+block_n] = block<block_n*block_n> */
static void umatN_set_block(unsigned * restrict dst_mat, const unsigned * restrict block, int row, int col, unsigned block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for(int c=0; c<block_n; c++) {
        for(int r=0; r<block_n; r++) {
            dst_mat[c * n + r] = block[c * block_n + r];
        }
    }
}

#endif //MATHC_MAT_UMATN_H
