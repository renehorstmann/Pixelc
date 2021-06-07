#ifndef MATHC_VEC_UCVECN_H
#define MATHC_VEC_UCVECN_H

#ifndef MATHC_MAX_SIZE
#ifdef __STDC_NO_VLA__
#define MATHC_MAX_SIZE 16
#endif
#endif

#include <string.h>     // memcmp
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>



/** macro to cast a vector to a uint8_t vector */
#define ucvecN_cast_into(dst_vec, vec, n) \
do { \
    for(int ucvecN_cast_into_i_=0; ucvecN_cast_into_i_<(n); ucvecN_cast_into_i_++) \
        (dst_vec)[ucvecN_cast_into_i_] = (uint8_t) (vec)[ucvecN_cast_into_i_]; \
} while(0)


/** dst = vec * 255 */
static void ucvecN_cast_from_float_1(uint8_t *dst_vec, const float *vec, int n) {
    for(int i = 0; i < n; i++)
        dst_vec[i] = (uint8_t) (vec[i] * 255.0f);
}

/** dst = vec * 255 */
static void ucvecN_cast_from_double_1(uint8_t *dst_vec, const double *vec, int n) {
    for(int i = 0; i < n; i++)
        dst_vec[i] = (uint8_t) (vec[i] * 255.0);
}

/** vec_a == vec_b */
static bool ucvecN_cmp(const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    return memcmp(vec_a, vec_b, n * sizeof(uint8_t)) == 0;
}


/** dst = vec */
static void ucvecN_copy(uint8_t *dst_vec, const uint8_t *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec[i];
}

/** dst = scalar */
static void ucvecN_set(uint8_t *dst_vec, uint8_t scalar, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = scalar;
}

/** dst = a + b */
static void ucvecN_add_vec(uint8_t *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + vec_b[i];
}

/** dst = a + b */
static void ucvecN_add(uint8_t *dst_vec, const uint8_t *vec_a, uint8_t scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + scalar_b;
}

/** dst = a - b */
static void ucvecN_sub_vec(uint8_t *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - vec_b[i];
}

/** dst = a - b */
static void ucvecN_sub(uint8_t *dst_vec, const uint8_t *vec_a, uint8_t scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - scalar_b;
}

/** dst = a * b */
static void ucvecN_scale_vec(uint8_t *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * vec_b[i];
}

/** dst = a * b */
static void ucvecN_scale(uint8_t *dst_vec, const uint8_t *vec_a, uint8_t scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * scalar_b;
}

/** dst = a / b */
static void ucvecN_div_vec(uint8_t *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / vec_b[i];
}

/** dst = a / b */
static void ucvecN_div(uint8_t *dst_vec, const uint8_t *vec_a, uint8_t scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / scalar_b;
}

/** dst = x % y */
static void ucvecN_mod(uint8_t *dst_vec, const uint8_t *vec_x, uint8_t y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] % y;
}

/** dst = x % y */
static void ucvecN_mod_vec(uint8_t *dst_vec, const uint8_t *vec_x, const uint8_t *vec_y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] % vec_y[i];
}

/** dst = a < b ? a : b */
static void ucvecN_min(uint8_t *dst_vec, const uint8_t *vec_a, uint8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b ? vec_a[i] : b;
}

/** dst = a < b ? a : b */
static void ucvecN_min_vec(uint8_t *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = a > b ? a : b */
static void ucvecN_max(uint8_t *dst_vec, const uint8_t *vec_a, uint8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b ? vec_a[i] : b;
}

/** dst = a > b ? a : b */
static void ucvecN_max_vec(uint8_t *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = x < min ? min : (x > max ? max : x) */
static void ucvecN_clamp(uint8_t *dst_vec, const uint8_t *vec_x, uint8_t min, uint8_t max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < min ? min : (vec_x[i] > max ? max : vec_x[i]);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void ucvecN_clamp_vec(uint8_t *dst_vec, const uint8_t *vec_x, const uint8_t *vec_min, const uint8_t *vec_max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_min[i] ? vec_min[i] : (vec_x[i] > vec_max[i] ? vec_max[i] : vec_x[i]);
}

/** dst = a * (1-t) + b * t */
static void ucvecN_mix(uint8_t *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, float t, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * (1.0f - t) + vec_b[i] * t;
}

/** dst = a * (1-t) + b * t */
static void ucvecN_mix_vec(uint8_t *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, const float *vec_t, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * (1.0f - vec_t[i]) + vec_b[i] * vec_t[i];
}

/** dst = x < edge ? 0 : 1 */
static void ucvecN_step(uint8_t *dst_vec, const uint8_t *vec_x, uint8_t edge, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < edge ? 0 : 1;
}

/** dst = x < edge ? 0 : 1 */
static void ucvecN_step_vec(uint8_t *dst_vec, const uint8_t *vec_x, const uint8_t *vec_edge, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_edge[i] ? 0 : 1;
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static uint8_t ucvecN_sum(const uint8_t *vec, int n) {
    uint8_t sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec[i];
    return sum;
}

/** returns a dot b */
static uint8_t ucvecN_dot(const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    uint8_t dot = 0;
    for (int i = 0; i < n; i++)
        dot += vec_a[i] * vec_b[i];
    return dot;
}

/** returns ||vec||_2 */
static float ucvecN_norm(const uint8_t *vec, int n) {
    return sqrtf(ucvecN_dot(vec, vec, n));
}

/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static float ucvecN_length(const uint8_t *vec, int n) {
    return ucvecN_norm(vec, n);
}

/** returns norm(b-a) */
static float ucvecN_distance(const uint8_t *vec_a, const uint8_t *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    uint8_t tmp[MATHC_MAX_SIZE];
#else
    uint8_t tmp[n];
#endif
    ucvecN_sub_vec(tmp, vec_b, vec_a, n);
    return ucvecN_norm(tmp, n);
}

/** dst = a < b */
static void ucvecN_less_than(bool *dst_vec, const uint8_t *vec_a, uint8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b;
}

/** dst = a < b */
static void ucvecN_less_than_vec(bool *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i];
}

/** dst = a <= b */
static void ucvecN_less_than_equal(bool *dst_vec, const uint8_t *vec_a, uint8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= b;
}

/** dst = a <= b */
static void ucvecN_less_than_equal_vec(bool *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= vec_b[i];
}

/** dst = a > b */
static void ucvecN_greater_than(bool *dst_vec, const uint8_t *vec_a, uint8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b;
}

/** dst = a > b */
static void ucvecN_greater_than_vec(bool *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i];
}

/** dst = a >= b */
static void ucvecN_greater_than_equal(bool *dst_vec, const uint8_t *vec_a, uint8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= b;
}

/** dst = a >= b */
static void ucvecN_greater_than_equal_vec(bool *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= vec_b[i];
}

/** dst = a == b */
static void ucvecN_equal(bool *dst_vec, const uint8_t *vec_a, uint8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == b;
}

/** dst = a == b */
static void ucvecN_equal_vec(bool *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == vec_b[i];
}

/** dst = a != b */
static void ucvecN_not_equal(bool *dst_vec, const uint8_t *vec_a, uint8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != b;
}

/** dst = a != b */
static void ucvecN_not_equal_vec(bool *dst_vec, const uint8_t *vec_a, const uint8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != vec_b[i];
}

#endif //MATHC_VEC_UCVECN_H
