#ifndef MATHC_VEC_BVECN_H
#define MATHC_VEC_BVECN_H

#include <stdbool.h>

/** dst = vec */
static void bvecN_copy(bool *dst_vec, const bool *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec[i];
}

/** dst = scalar */
static void bvecN_set(bool *dst_vec, bool set, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = set;
}

/** dst = !vec */
static void bvecN_not(bool *dst_vec, const bool *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = !vec[i];
}

/** dst = a || b */
static void bvecN_or(bool *dst_vec, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] || vec_b[i];
}

/** dst = !(a || b) */
static void bvecN_nor(bool *dst_vec, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = !(vec_a[i] || vec_b[i]);
}

/** dst = a ^ b */
static void bvecN_xor(bool *dst_vec, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] ^ vec_b[i];
}

/** dst = !(a ^ b) */
static void bvecN_nxor(bool *dst_vec, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = !(vec_a[i] ^ vec_b[i]);
}

/** dst = a && b */
static void bvecN_and(bool *dst_vec, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] && vec_b[i];
}

/** dst = !(a && b) */
static void bvecN_nand(bool *dst_vec, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = !(vec_a[i] && vec_b[i]);
}

/** returns the sum of true values */
static int bvecN_sum(const bool *vec, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += !!vec[i];    // to get 1 for anything and 0 for 0
    return sum;
}

/** returns sum(vec) > 0 */
static bool bvecN_any(const bool *vec, int n) {
    return bvecN_sum(vec, n) > 0;
}

/** returns sum(vec) == n */
static bool bvecN_all(const bool *vec, int n) {
    return bvecN_sum(vec, n) == 3;
}

#endif //MATHC_VEC_BVECN_H
