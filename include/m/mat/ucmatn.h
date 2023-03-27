#ifndef M_MAT_UCMATN_H
#define M_MAT_UCMATN_H


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

/** macro to cast a mattor into a unsigned char mattor */
#define ucmatN_cast_into(dst, from, n) \
do { \
    for(int ucmatN_cast_into_i_=0; ucmatN_cast_into_i_<((n)*(n)); ucmatN_cast_into_i_++) \
        (dst)[ucmatN_cast_into_i_] = (unsigned char) (from)[ucmatN_cast_into_i_]; \
} while(0)


/** dst = mat * 255 */
static void ucmatN_cast_from_float_1(unsigned char *dst_mat, const float *mat, int n) {
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = (unsigned char) (mat[i] * 255.0f);
}

/** dst = mat * 255 */
static void ucmatN_cast_from_double_1(unsigned char *dst_mat, const double *mat, int n) {
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = (unsigned char) (mat[i] * 255.0);
}

/** dst = mat * 255 */
static void ucmatN_cast_from_longdouble_1(unsigned char *dst_mat, const long double *mat, int n) {
    for (int i = 0; i < n * n; i++)
        dst_mat[i] = (unsigned char) (mat[i] * 255.0);
}


/** a == b */
static bool ucmatN_cmp(const unsigned char *a, const unsigned char *b, int n) {
    return memcmp(a, b, (n * n) * sizeof(unsigned char)) == 0;
}

/** dst = v */
static void ucmatN_copy(unsigned char *dst, const unsigned char *v, int n) {
    for (int i = 0; i < n * n; i++)
        dst[i] = v[i];
}

/** dst = s */
static void ucmatN_set(unsigned char *dst, unsigned char s, int n) {
    for (int i = 0; i < n * n; i++)
        dst[i] = s;
}


/** dst = r==c ? 1 : 0 (identity) */
static void ucmatN_eye(unsigned char *dst, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            dst[r * n + c] = r == c ? 1 : 0;
    }
}

/** dst = m[row][:] */
static void ucmatN_get_row(unsigned char *dst_vec, const unsigned char *m, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst_vec[c] = m[c * n + row];
}

/** dst = m[:][col] */
static void ucmatN_get_col(unsigned char *dst_vec, const unsigned char *m, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst_vec[r] = m[col * n + r];
}

/** dst[row][:] = v */
static void ucmatN_set_row(unsigned char *dst, const unsigned char *v, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst[c * n + row] = v[c];
}

/** dst[:][col] = v */
static void ucmatN_set_col(unsigned char *dst, const unsigned char *v, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst[col * n + r] = v[r];
}

/** dst[row][:] = s */
static void ucmatN_set_row_sca(unsigned char *dst, unsigned char s, int row, int n) {
    assert(row >= 0 && row < n);
    for (int c = 0; c < n; c++)
        dst[c * n + row] = s;
}

/** dst[:][col] = s */
static void ucmatN_set_col_sca(unsigned char *dst, unsigned char s, int col, int n) {
    assert(col >= 0 && col < n);
    for (int r = 0; r < n; r++)
        dst[col * n + r] = s;
}

/** returns sum of diagonal from upper left to lower right */
static unsigned char ucmatN_trace(const unsigned char *mat, int n) {
    unsigned char sum = 0;
    for (int i = 0; i < n; i++)
        sum += mat[i * n + i];
    return sum;
}

/** dst = m^t  (restrict data) */
static void ucmatN_transpose_no_alias(unsigned char *restrict dst, const unsigned char *restrict m, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst[c * n + r] = m[r * n + c];
        }
    }
}

/** dst = m^t */
static void ucmatN_transpose(unsigned char *dst, const unsigned char *m, int n) {
    assert(n <= M_MAX_SIZE);
    unsigned char tmp[M_MAX_SIZE * M_MAX_SIZE];
    ucmatN_transpose_no_alias(tmp, m, n);
    for (int i = 0; i < n * n; i++)
        dst[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void ucmatN_mul_mat_no_alias(unsigned char *restrict dst, const unsigned char *restrict a,
                                    const unsigned char *restrict b, int n) {
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < n; r++) {
            dst[c * n + r] = 0;
            for (int k = 0; k < n; k++)
                dst[c * n + r] += a[k * n + r] * b[c * n + k];
        }
    }
}

/** dst = a @ b */
static void ucmatN_mul_mat(unsigned char *dst, const unsigned char *a, const unsigned char *b, int n) {
    assert(n <= M_MAX_SIZE);
    unsigned char tmp[M_MAX_SIZE * M_MAX_SIZE];
    ucmatN_mul_mat_no_alias(tmp, a, b, n);
    for (int i = 0; i < n * n; i++)
        dst[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void ucmatN_mul_vec_no_alias(unsigned char *restrict dst_vec, const unsigned char *restrict a,
                                    const unsigned char *restrict b, int n) {
    for (int r = 0; r < n; r++) {
        dst_vec[r] = 0;
        for (int c = 0; c < n; c++) {
            dst_vec[r] += a[c * n + r] * b[c];
        }
    }
}

/** dst = a @ b */
static void ucmatN_mul_vec(unsigned char *dst_vec, const unsigned char *a, const unsigned char *b, int n) {
    assert(n <= M_MAX_SIZE);
    unsigned char tmp[M_MAX_SIZE];
    ucmatN_mul_vec_no_alias(tmp, a, b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** dst = a @ b  (restrict data) */
static void ucvecN_mul_mat_no_alias(unsigned char *restrict dst_vec, const unsigned char *restrict a,
                                    const unsigned char *restrict b, int n) {
    for (int c = 0; c < n; c++) {
        dst_vec[c] = 0;
        for (int r = 0; r < n; r++) {
            dst_vec[c] += b[c * n + r] * a[r];
        }
    }
}

/** dst = a @ b */
static void ucvecN_mul_mat(unsigned char *dst_vec, const unsigned char *a, const unsigned char *b, int n) {
    assert(n <= M_MAX_SIZE);
    unsigned char tmp[M_MAX_SIZE];
    ucvecN_mul_mat_no_alias(tmp, a, b, n);
    for (int i = 0; i < n; i++)
        dst_vec[i] = tmp[i];
}

/** block<block_n*block_n> = m<n*n>[col:col+block_n, row:row+block_n] */
static void
ucmatN_get_block(unsigned char *restrict dst_block, const unsigned char *restrict m, int row, int col, int block_n,
                 int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for (int c = 0; c < block_n; c++) {
        for (int r = 0; r < block_n; r++) {
            dst_block[c * block_n + r] = m[c * n + r];
        }
    }
}

/** dst<n*n>[col:col+block_n, row:row+block_n] = block<block_n*block_n> */
static void
ucmatN_set_block(unsigned char *restrict dst, const unsigned char *restrict block, int row, int col, int block_n,
                 int n) {
    assert(row >= 0 && row + block_n <= n);
    assert(col >= 0 && col + block_n <= n);
    for (int c = 0; c < block_n; c++) {
        for (int r = 0; r < block_n; r++) {
            dst[c * n + r] = block[c * block_n + r];
        }
    }
}

#endif //M_MAT_UCMATN_H
