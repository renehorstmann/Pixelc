#ifndef M_MAT_IMATN_H
#define M_MAT_IMATN_H


// restrict
#ifdef __cplusplus
#define restrict __restrict
#endif

#ifndef M_MAX_SIZE
#define M_MAX_SIZE 16
#endif

#include <string.h>     // memcmp
#include <assert.h>
#include <stdbool.h>

/** macro to cast a mattor into a int mattor */
#define imatN_cast_into(dst, from, n) \
do { \
    for(int imatN_cast_into_i_=0; imatN_cast_into_i_<((n)*(n)); imatN_cast_into_i_++) \
        (dst)[imatN_cast_into_i_] = (int) (from)[imatN_cast_into_i_]; \
} while(0)


/** dst = mat * 255 */
static void imatN_cast_from_float_1(int *dst_mat, const float *mat, int n) {
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = (int) (mat[i] * 255.0f);
}

/** dst = mat * 255 */
static void imatN_cast_from_double_1(int *dst_mat, const double *mat, int n) {
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = (int) (mat[i] * 255.0);
}

/** dst = mat * 255 */
static void imatN_cast_from_longdouble_1(int *dst_mat, const long double *mat, int n) {
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = (int) (mat[i] * 255.0);
}


/** a == b */
static bool imatN_cmp(const int *a, const int *b, int n) {
    return memcmp(a, b, (n * n) * sizeof(int)) == 0;
}

/** dst = v */
static void imatN_copy(int *dst, const int *v, int n) {
    for (int i = 0; i < n * n; i++)
        dst[i] = v[i];
}

/** dst = s */
static void imatN_set(int *dst, int s, int n) {
    for (int i = 0; i < n * n; i++)
        dst[i] = s;
}


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
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE * M_MAX_SIZE];
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
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE * M_MAX_SIZE];
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
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE];
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
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE];
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
