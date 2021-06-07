#ifndef MATHC_MAT_UCMATN_H
#define MATHC_MAT_UCMATN_H

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
static void ucmatN_eye(unsigned char *dst_mat, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            dst_mat[r * n + c] = r == c ? 1 : 0;
    }
}

/** dst = mat[row][:] */
static void ucmatN_get_row(unsigned char *dst_vec, const unsigned char *mat, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_vec[c] = mat[c * n + row];
}

/** dst = mat[:][col] */
static void ucmatN_get_col(unsigned char *dst_vec, const unsigned char *mat, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_vec[r] = mat[col * n + r];
}

/** dst[row][:] = vec */
static void ucmatN_set_row(unsigned char *dst_mat, const unsigned char *vec, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_mat[c * n + row] = vec[c];
}

/** dst[:][col] = vec */
static void ucmatN_set_col(unsigned char *dst_mat, const unsigned char *vec, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_mat[col * n + r] = vec[r];
}

/** dst[row][:] = scalar */
static void ucmatN_set_row_sca(unsigned char *dst_mat, unsigned char scalar, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_mat[c * n + row] = scalar;
}

/** dst[:][col] = scalar */
static void ucmatN_set_col_sca(unsigned char *dst_mat, unsigned char scalar, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_mat[col * n + r] = scalar;
}

/** returns sum of diagonal form upper left to lower right */
static unsigned ucmatN_trace(const unsigned char *mat, int n) {
    unsigned sum = 0;
    for(int i=0; i<n; i++)
        sum += mat[i*n + i];
    return sum;
}

/** dst = mat^t  (restrict data) */
static void ucmatN_transpose_no_alias(unsigned char *restrict dst_mat, const unsigned char *restrict mat, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst_mat[c * n + r] = mat[r * n + c];
        }
    }
}

/** dst = mat^t */
static void ucmatN_transpose(unsigned char *dst_mat, const unsigned char *mat, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned char tmp[MATHC_MAX_SIZE * MATHC_MAX_SIZE];
#else
    unsigned char tmp[n * n];
#endif
    ucmatN_transpose_no_alias(tmp, mat, n);
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void ucmatN_mul_mat_no_alias(unsigned char *restrict dst_mat, const unsigned char *restrict mat_a,
                                  const unsigned char *restrict mat_b, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst_mat[c * n + r] = 0;
            for (int k = 0; k < n; k++)
                dst_mat[c * n + r] += mat_a[k * n + r] * mat_b[c * n + k];
        }
    }
}

/** dst = a @ b */
static void ucmatN_mul_mat(unsigned char *dst_mat, const unsigned char *mat_a, const unsigned char *mat_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned char tmp[MATHC_MAX_SIZE * MATHC_MAX_SIZE];
#else
    unsigned char tmp[n * n];
#endif
    ucmatN_mul_mat_no_alias(tmp, mat_a, mat_b, n);
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void ucmatN_mul_vec_no_alias(unsigned char *restrict dst_vec, const unsigned char *restrict mat_a,
                                  const unsigned char *restrict vec_b, int n) {
    for (int r = 0; r < n; r++) {
        dst_vec[r] = 0;
        for (int c = 0; c < n; c++) {
            dst_vec[r] += mat_a[c * n + r] * vec_b[c];
        }
    }
}

/** dst = a @ b */
static void ucmatN_mul_vec(unsigned char *dst_vec, const unsigned char *mat_a, const unsigned char *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned char tmp[MATHC_MAX_SIZE];
#else
    unsigned char tmp[n];
#endif
    ucmatN_mul_vec_no_alias(tmp, mat_a, vec_b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void ucvecN_mul_mat_no_alias(unsigned char *restrict dst_vec, const unsigned char *restrict vec_a,
                                  const unsigned char *restrict mat_b, int n) {
    for (int c = 0; c < n; c++) {
        dst_vec[c] = 0;
        for (int r = 0; r < n; r++) {
            dst_vec[c] += mat_b[c * n + r] * vec_a[r];
        }
    }
}

/** dst = a @ b */
static void ucvecN_mul_mat(unsigned char *dst_vec, const unsigned char *vec_a, const unsigned char *mat_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned char tmp[MATHC_MAX_SIZE];
#else
    unsigned char tmp[n];
#endif
    ucvecN_mul_mat_no_alias(tmp, vec_a, mat_b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** block<block_n*block_n> = mat<n*n>[col:col+block_n, row:row+block_n] */
static void ucmatN_get_block(unsigned char * restrict dst_block, const unsigned char * restrict mat, int row, int col, unsigned char block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for(int c=0; c<block_n; c++) {
        for(int r=0; r<block_n; r++) {
            dst_block[c * block_n + r] = mat[c * n + r];
        }
    }
}

/** dst<n*n>[col:col+block_n, row:row+block_n] = block<block_n*block_n> */
static void ucmatN_set_block(unsigned char * restrict dst_mat, const unsigned char * restrict block, int row, int col, unsigned char block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for(int c=0; c<block_n; c++) {
        for(int r=0; r<block_n; r++) {
            dst_mat[c * n + r] = block[c * block_n + r];
        }
    }
}

#endif //MATHC_MAT_UCMATN_H
