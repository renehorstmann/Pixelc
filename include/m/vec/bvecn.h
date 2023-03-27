#ifndef M_VEC_BVECN_H
#define M_VEC_BVECN_H

#include <string.h>     // memcmp
#include <assert.h>
#include <stdbool.h>

/** vec_a == vec_b */
static bool bvecN_cmp(const bool *vec_a, const bool *vec_b, int n) {
    return memcmp(vec_a, vec_b, n * sizeof(bool)) == 0;
}

/** dst = vec */
static void bvecN_copy(bool *dst, const bool *vec, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = vec[i];
}

/** dst = scalar */
static void bvecN_set(bool *dst, bool set, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = set;
}

/** dst = unit_x */
static void bvecN_unit_x(bool *dst, int n) {
    bvecN_set(dst, false, n);
    dst[0] = true;
}

/** dst = unit_y */
static void bvecN_unit_y(bool *dst, int n) {
    bvecN_set(dst, false, n);
    dst[1] = true;
}

/** assert(n>=3); dst = unit_z */
static void bvecN_unit_z(bool *dst, int n) {
    assert(n >= 3 && "m bvec*_unit_z");
    bvecN_set(dst, false, n);
    dst[2] = true;
}

/** assert(n>=4); dst = unit_w */
static void bvecN_unit_w(bool *dst, int n) {
    assert(n >= 4 && "m bvec*_unit_w");
    bvecN_set(dst, false, n);
    dst[3] = true;
}

/** dst = !vec */
static void bvecN_not(bool *dst, const bool *vec, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = !vec[i];
}

/** dst = a || b */
static void bvecN_or(bool *dst, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = vec_a[i] || vec_b[i];
}

/** dst = !(a || b) */
static void bvecN_nor(bool *dst, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = !(vec_a[i] || vec_b[i]);
}

/** dst = a ^ b */
static void bvecN_xor(bool *dst, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = vec_a[i] ^ vec_b[i];
}

/** dst = !(a ^ b) */
static void bvecN_nxor(bool *dst, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = !(vec_a[i] ^ vec_b[i]);
}

/** dst = a && b */
static void bvecN_and(bool *dst, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = vec_a[i] && vec_b[i];
}

/** dst = !(a && b) */
static void bvecN_nand(bool *dst, const bool *vec_a, const bool *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = !(vec_a[i] && vec_b[i]);
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
    return bvecN_sum(vec, n) == n;
}

#endif //M_VEC_BVECN_H
