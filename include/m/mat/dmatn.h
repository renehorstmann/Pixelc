#ifndef M_MAT_DMATN_H
#define M_MAT_DMATN_H


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

/** macro to cast a mattor into a double mattor */
#define dmatN_cast_into(dst, from, n) \
do { \
    for(int dmatN_cast_into_i_=0; dmatN_cast_into_i_<((n)*(n)); dmatN_cast_into_i_++) \
        (dst)[dmatN_cast_into_i_] = (double) (from)[dmatN_cast_into_i_]; \
} while(0)


/** dst = v / 255 */
static void dmatN_cast_from_uchar_1(double *dst_mat, const unsigned char *mat, int n) {
    for (int i = 0; i < n*n; i++)
        dst_mat[i] = (double) mat[i] / (double) 255;
}






/** a == b */
static bool dmatN_cmp(const double *a, const double *b, int n) {
    return memcmp(a, b, (n*n) * sizeof(double)) == 0;
}

/** dst = v */
static void dmatN_copy(double *dst, const double *v, int n) {
    for (int i = 0; i < n*n; i++)
        dst[i] = v[i];
}

/** dst = s */
static void dmatN_set(double *dst, double s, int n) {
    for (int i = 0; i < n*n; i++)
        dst[i] = s;
}


/** dst = r==c ? 1 : 0 (identity) */
static void dmatN_eye(double *dst, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            dst[r * n + c] = r == c ? 1 : 0;
    }
}

/** dst = m[row][:] */
static void dmatN_get_row(double *dst_vec, const double *m, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_vec[c] = m[c * n + row];
}

/** dst = m[:][col] */
static void dmatN_get_col(double *dst_vec, const double *m, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_vec[r] = m[col * n + r];
}

/** dst[row][:] = v */
static void dmatN_set_row(double *dst, const double *v, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst[c * n + row] = v[c];
}

/** dst[:][col] = v */
static void dmatN_set_col(double *dst, const double *v, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst[col * n + r] = v[r];
}

/** dst[row][:] = s */
static void dmatN_set_row_sca(double *dst, double s, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst[c * n + row] = s;
}

/** dst[:][col] = s */
static void dmatN_set_col_sca(double *dst, double s, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst[col * n + r] = s;
}

/** returns sum of diagonal from upper left to lower right */
static double dmatN_trace(const double *mat, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += mat[i * n + i];
    return sum;
}

/** dst = m^t  (restrict data) */
static void dmatN_transpose_no_alias(double *restrict dst, const double *restrict m, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst[c * n + r] = m[r * n + c];
        }
    }
}

/** dst = m^t */
static void dmatN_transpose(double *dst, const double *m, int n) {
    assert(n <= M_MAX_SIZE);
    double tmp[M_MAX_SIZE * M_MAX_SIZE];
    dmatN_transpose_no_alias(tmp, m, n);
    for (int i = 0; i < n * n; i++)
        dst[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void dmatN_mul_mat_no_alias(double *restrict dst, const double *restrict a,
                                  const double *restrict b, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst[c * n + r] = 0;
            for (int k = 0; k < n; k++)
                dst[c * n + r] += a[k * n + r] * b[c * n + k];
        }
    }
}

/** dst = a @ b */
static void dmatN_mul_mat(double *dst, const double *a, const double *b, int n) {
    assert(n <= M_MAX_SIZE);
    double tmp[M_MAX_SIZE * M_MAX_SIZE];
    dmatN_mul_mat_no_alias(tmp, a, b, n);
    for (int i = 0; i < n * n; i++)
        dst[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void dmatN_mul_vec_no_alias(double *restrict dst_vec, const double *restrict a,
                                  const double *restrict b, int n) {
    for (int r = 0; r < n; r++) {
        dst_vec[r] = 0;
        for (int c = 0; c < n; c++) {
            dst_vec[r] += a[c * n + r] * b[c];
        }
    }
}

/** dst = a @ b */
static void dmatN_mul_vec(double *dst_vec, const double *a, const double *b, int n) {
    assert(n <= M_MAX_SIZE);
    double tmp[M_MAX_SIZE];
    dmatN_mul_vec_no_alias(tmp, a, b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void dvecN_mul_mat_no_alias(double *restrict dst_vec, const double *restrict a,
                                  const double *restrict b, int n) {
    for (int c = 0; c < n; c++) {
        dst_vec[c] = 0;
        for (int r = 0; r < n; r++) {
            dst_vec[c] += b[c * n + r] * a[r];
        }
    }
}

/** dst = a @ b */
static void dvecN_mul_mat(double *dst_vec, const double *a, const double *b, int n) {
    assert(n <= M_MAX_SIZE);
    double tmp[M_MAX_SIZE];
    dvecN_mul_mat_no_alias(tmp, a, b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** block<block_n*block_n> = m<n*n>[col:col+block_n, row:row+block_n] */
static void dmatN_get_block(double *restrict dst_block, const double *restrict m, int row, int col, int block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for (int c = 0; c < block_n; c++) {
        for (int r = 0; r < block_n; r++) {
            dst_block[c * block_n + r] = m[c * n + r];
        }
    }
}

/** dst<n*n>[col:col+block_n, row:row+block_n] = block<block_n*block_n> */
static void dmatN_set_block(double *restrict dst, const double *restrict block, int row, int col, int block_n, int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for (int c = 0; c < block_n; c++) {
        for (int r = 0; r < block_n; r++) {
            dst[c * n + r] = block[c * block_n + r];
        }
    }
}

#endif //M_MAT_DMATN_H
