#ifndef M_MAT_IMATN_H
#define M_MAT_IMATN_H

// restrict
#ifdef __cplusplus
#define restrict __restrict
#endif

#ifndef M_MAX_SIZE
#ifdef __STDC_NO_VLA__
#define M_MAX_SIZE 16
#endif
#endif

#include <assert.h>


/** dst = r==c ? 1 : 0 (identity) */
static void imatN_eye(int *dst, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            dst[r * n + c] = r == c ? 1 : 0;
    }
}

/** dst = m[row][:] */
static void imatN_get_row(int *dst_vec, const int *m, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_vec[c] = m[c * n + row];
}

/** dst = m[:][col] */
static void imatN_get_col(int *dst_vec, const int *m, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_vec[r] = m[col * n + r];
}

/** dst[row][:] = v */
static void imatN_set_row(int *dst, const int *v, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst[c * n + row] = v[c];
}

/** dst[:][col] = v */
static void imatN_set_col(int *dst, const int *v, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst[col * n + r] = v[r];
}

/** dst[row][:] = s */
static void imatN_set_row_sca(int *dst, int s, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst[c * n + row] = s;
}

/** dst[:][col] = s */
static void imatN_set_col_sca(int *dst, int s, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst[col * n + r] = s;
}

/** returns sum of diagonal from upper left to lower right */
static int imatN_trace(const int *mat, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += mat[i * n + i];
    return sum;
}

/** dst = m^t  (restrict data) */
static void imatN_transpose_no_alias(int *restrict dst, const int *restrict m, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst[c * n + r] = m[r * n + c];
        }
    }
}

/** dst = m^t */
static void imatN_transpose(int *dst, const int *m, int n) {
#ifdef M_MAX_SIZE
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE * M_MAX_SIZE];
#else
    int tmp[n * n];
#endif
    imatN_transpose_no_alias(tmp, m, n);
    for (int i = 0; i < n * n; i++)
        dst[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void imatN_mul_mat_no_alias(int *restrict dst, const int *restrict a,
                                   const int *restrict b, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst[c * n + r] = 0;
            for (int k = 0; k < n; k++)
                dst[c * n + r] += a[k * n + r] * b[c * n + k];
        }
    }
}

/** dst = a @ b */
static void imatN_mul_mat(int *dst, const int *a, const int *b, int n) {
#ifdef M_MAX_SIZE
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE * M_MAX_SIZE];
#else
    int tmp[n * n];
#endif
    imatN_mul_mat_no_alias(tmp, a, b, n);
    for (int i = 0; i < n * n; i++)
        dst[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void imatN_mul_vec_no_alias(int *restrict dst_vec, const int *restrict a,
                                   const int *restrict b, int n) {
    for (int r = 0; r < n; r++) {
        dst_vec[r] = 0;
        for (int c = 0; c < n; c++) {
            dst_vec[r] += a[c * n + r] * b[c];
        }
    }
}

/** dst = a @ b */
static void imatN_mul_vec(int *dst_vec, const int *a, const int *b, int n) {
#ifdef M_MAX_SIZE
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE];
#else
    int tmp[n];
#endif
    imatN_mul_vec_no_alias(tmp, a, b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void ivecN_mul_mat_no_alias(int *restrict dst_vec, const int *restrict a,
                                   const int *restrict b, int n) {
    for (int c = 0; c < n; c++) {
        dst_vec[c] = 0;
        for (int r = 0; r < n; r++) {
            dst_vec[c] += b[c * n + r] * a[r];
        }
    }
}

/** dst = a @ b */
static void ivecN_mul_mat(int *dst_vec, const int *a, const int *b, int n) {
#ifdef M_MAX_SIZE
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE];
#else
    int tmp[n];
#endif
    ivecN_mul_mat_no_alias(tmp, a, b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** block<block_n*block_n> = m<n*n>[col:col+block_n, row:row+block_n] */
static void imatN_get_block(int *restrict dst_block, const int *restrict m, int row, int col, int block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for (int c = 0; c < block_n; c++) {
        for (int r = 0; r < block_n; r++) {
            dst_block[c * block_n + r] = m[c * n + r];
        }
    }
}

/** dst<n*n>[col:col+block_n, row:row+block_n] = block<block_n*block_n> */
static void imatN_set_block(int *restrict dst, const int *restrict block, int row, int col, int block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for (int c = 0; c < block_n; c++) {
        for (int r = 0; r < block_n; r++) {
            dst[c * n + r] = block[c * block_n + r];
        }
    }
}

#endif //M_MAT_IMATN_H
