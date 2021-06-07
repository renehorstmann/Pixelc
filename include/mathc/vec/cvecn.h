#ifndef MATHC_VEC_CVECN_H
#define MATHC_VEC_CVECN_H

#ifndef MATHC_MAX_SIZE
#ifdef __STDC_NO_VLA__
#define MATHC_MAX_SIZE 16
#endif
#endif

#include <string.h>     // memcmp
#include <stdlib.h>     // abs
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>



/** macro to cast a vector into a int8_t vector */
#define cvecN_cast_into(dst_vec, vec, n) \
do { \
    for(int cvecN_cast_into_i_=0; cvecN_cast_into_i_<(n); cvecN_cast_into_i_++) \
        (dst_vec)[cvecN_cast_into_i_] = (int8_t) (vec)[cvecN_cast_into_i_]; \
} while(0)

/** vec_a == vec_b */
static bool cvecN_cmp(const int8_t *vec_a, const int8_t *vec_b, int n) {
    return memcmp(vec_a, vec_b, n * sizeof(int8_t)) == 0;
}

/** dst = vec */
static void cvecN_copy(int8_t *dst_vec, const int8_t *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec[i];
}

/** dst = scalar */
static void cvecN_set(int8_t *dst_vec, int8_t scalar, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = scalar;
}

/** dst = -vec */
static void cvecN_neg(int8_t *dst_vec, const int8_t *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = -vec[i];
}

/** dst = a + b */
static void cvecN_add_vec(int8_t *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + vec_b[i];
}

/** dst = a + b */
static void cvecN_add(int8_t *dst_vec, const int8_t *vec_a, int8_t scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + scalar_b;
}

/** dst = a - b */
static void cvecN_sub_vec(int8_t *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - vec_b[i];
}

/** dst = a - b */
static void cvecN_sub(int8_t *dst_vec, const int8_t *vec_a, int8_t scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - scalar_b;
}

/** dst = a * b */
static void cvecN_scale_vec(int8_t *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * vec_b[i];
}

/** dst = a * b */
static void cvecN_scale(int8_t *dst_vec, const int8_t *vec_a, int8_t scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * scalar_b;
}

/** dst = a / b */
static void cvecN_div_vec(int8_t *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / vec_b[i];
}

/** dst = a / b */
static void cvecN_div(int8_t *dst_vec, const int8_t *vec_a, int8_t scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / scalar_b;
}

/** dst = abs(x) */
static void cvecN_abs(int8_t *dst_vec, const int8_t *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = abs(vec_x[i]);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static void cvecN_sign(int8_t *dst_vec, const int8_t *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] > 0 ? 1 : (vec_x[i] < 0 ? -1 : 0);
}

/** dst = x % y */
static void cvecN_mod(int8_t *dst_vec, const int8_t *vec_x, int8_t y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] % y;
}

/** dst = x % y */
static void cvecN_mod_vec(int8_t *dst_vec, const int8_t *vec_x, const int8_t *vec_y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] % vec_y[i];
}

/** dst = a < b ? a : b */
static void cvecN_min(int8_t *dst_vec, const int8_t *vec_a, int8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b ? vec_a[i] : b;
}

/** dst = a < b ? a : b */
static void cvecN_min_vec(int8_t *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = a > b ? a : b */
static void cvecN_max(int8_t *dst_vec, const int8_t *vec_a, int8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b ? vec_a[i] : b;
}

/** dst = a > b ? a : b */
static void cvecN_max_vec(int8_t *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = x < min ? min : (x > max ? max : x) */
static void cvecN_clamp(int8_t *dst_vec, const int8_t *vec_x, int8_t min, int8_t max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < min ? min : (vec_x[i] > max ? max : vec_x[i]);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void cvecN_clamp_vec(int8_t *dst_vec, const int8_t *vec_x, const int8_t *vec_min, const int8_t *vec_max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_min[i] ? vec_min[i] : (vec_x[i] > vec_max[i] ? vec_max[i] : vec_x[i]);
}

/** dst = a * (1-t) + b * t */
static void cvecN_mix(int8_t *dst_vec, const int8_t *vec_a, const int8_t *vec_b, float t, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * (1.0f - t) + vec_b[i] * t;
}

/** dst = a * (1-t) + b * t */
static void cvecN_mix_vec(int8_t *dst_vec, const int8_t *vec_a, const int8_t *vec_b, const float *vec_t, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * (1.0f - vec_t[i]) + vec_b[i] * vec_t[i];
}

/** dst = x < edge ? 0 : 1 */
static void cvecN_step(int8_t *dst_vec, const int8_t *vec_x, int8_t edge, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < edge ? 0 : 1;
}

/** dst = x < edge ? 0 : 1 */
static void cvecN_step_vec(int8_t *dst_vec, const int8_t *vec_x, const int8_t *vec_edge, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_edge[i] ? 0 : 1;
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int cvecN_sum(const int8_t *vec, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec[i];
    return sum;
}

/** returns a dot b */
static int cvecN_dot(const int8_t *vec_a, const int8_t *vec_b, int n) {
    int dot = 0;
    for (int i = 0; i < n; i++)
        dot += vec_a[i] * vec_b[i];
    return dot;
}

/** returns ||vec||_2 */
static float cvecN_norm(const int8_t *vec, int n) {
    return sqrtf(cvecN_dot(vec, vec, n));
}

/** returns ||vec||_p */
static float cvecN_norm_p(const int8_t *vec, float p, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += powf(abs(vec[i]), p);
    }
    return powf(sum, 1.0f / p);
}

/** returns ||vec||_1 */
static int cvecN_norm_1(const int8_t *vec, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += abs(vec[i]);
    }
    return sum;
}

/** returns ||vec||_inf */
static int cvecN_norm_inf(const int8_t *vec, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (max < abs(vec[i]))
            max = abs(vec[i]);
    }
    return max;
}

/** returns length of a vector, see cvecN_norm. Just here to match glsl */
static float cvecN_length(const int8_t *vec, int n) {
    return cvecN_norm(vec, n);
}

/** returns norm(b-a) */
static float cvecN_distance(const int8_t *vec_a, const int8_t *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    int8_t tmp[MATHC_MAX_SIZE];
#else
    int8_t tmp[n];
#endif
    cvecN_sub_vec(tmp, vec_b, vec_a, n);
    return cvecN_norm(tmp, n);
}

/** dst = a < b */
static void cvecN_less_than(bool *dst_vec, const int8_t *vec_a, int8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b;
}

/** dst = a < b */
static void cvecN_less_than_vec(bool *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i];
}

/** dst = a <= b */
static void cvecN_less_than_equal(bool *dst_vec, const int8_t *vec_a, int8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= b;
}

/** dst = a <= b */
static void cvecN_less_than_equal_vec(bool *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= vec_b[i];
}

/** dst = a > b */
static void cvecN_greater_than(bool *dst_vec, const int8_t *vec_a, int8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b;
}

/** dst = a > b */
static void cvecN_greater_than_vec(bool *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i];
}

/** dst = a >= b */
static void cvecN_greater_than_equal(bool *dst_vec, const int8_t *vec_a, int8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= b;
}

/** dst = a >= b */
static void cvecN_greater_than_equal_vec(bool *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= vec_b[i];
}

/** dst = a == b */
static void cvecN_equal(bool *dst_vec, const int8_t *vec_a, int8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == b;
}

/** dst = a == b */
static void cvecN_equal_vec(bool *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == vec_b[i];
}

/** dst = a != b */
static void cvecN_not_equal(bool *dst_vec, const int8_t *vec_a, int8_t b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != b;
}

/** dst = a != b */
static void cvecN_not_equal_vec(bool *dst_vec, const int8_t *vec_a, const int8_t *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != vec_b[i];
}

#endif //MATHC_VEC_CVECN_H
