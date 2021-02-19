#ifndef MATHC_VEC_UVECN_H
#define MATHC_VEC_UVECN_H

#ifndef MATHC_MAX_SIZE
#ifdef __STDC_NO_VLA__
#define MATHC_MAX_SIZE 16
#endif
#endif

#include <stdbool.h>
#include <math.h>
#include <assert.h>


/** macro to cast a vector unsignedo a unsigned vector */
#define uvecN_cast_into(dst_vec, vec, n) \
do { \
    for(unsigned uvecN_cast_into_i_=0; uvecN_cast_into_i_<(n); uvecN_cast_into_i_++) \
        (dst_vec)[uvecN_cast_into_i_] = (unsigned) (vec)[uvecN_cast_into_i_]; \
} while(0)


/** dst = vec */
static void uvecN_copy(unsigned *dst_vec, const unsigned *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec[i];
}

/** dst = scalar */
static void uvecN_set(unsigned *dst_vec, unsigned scalar, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = scalar;
}

/** dst = a + b */
static void uvecN_add_vec(unsigned *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + vec_b[i];
}

/** dst = a + b */
static void uvecN_add(unsigned *dst_vec, const unsigned *vec_a, unsigned scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + scalar_b;
}

/** dst = a - b */
static void uvecN_sub_vec(unsigned *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - vec_b[i];
}

/** dst = a - b */
static void uvecN_sub(unsigned *dst_vec, const unsigned *vec_a, unsigned scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - scalar_b;
}

/** dst = a * b */
static void uvecN_scale_vec(unsigned *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * vec_b[i];
}

/** dst = a * b */
static void uvecN_scale(unsigned *dst_vec, const unsigned *vec_a, unsigned scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * scalar_b;
}

/** dst = a / b */
static void uvecN_div_vec(unsigned *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / vec_b[i];
}

/** dst = a / b */
static void uvecN_div(unsigned *dst_vec, const unsigned *vec_a, unsigned scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / scalar_b;
}

/** dst = x % y */
static void uvecN_mod(unsigned *dst_vec, const unsigned *vec_x, unsigned y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] % y;
}

/** dst = x % y */
static void uvecN_mod_vec(unsigned *dst_vec, const unsigned *vec_x, const unsigned *vec_y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] % vec_y[i];
}

/** dst = a < b ? a : b */
static void uvecN_min(unsigned *dst_vec, const unsigned *vec_a, unsigned b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b ? vec_a[i] : b;
}

/** dst = a < b ? a : b */
static void uvecN_min_vec(unsigned *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = a > b ? a : b */
static void uvecN_max(unsigned *dst_vec, const unsigned *vec_a, unsigned b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b ? vec_a[i] : b;
}

/** dst = a > b ? a : b */
static void uvecN_max_vec(unsigned *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = x < min ? min : (x > max ? max : x) */
static void uvecN_clamp(unsigned *dst_vec, const unsigned *vec_x, unsigned min, unsigned max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < min ? min : (vec_x[i] > max ? max : vec_x[i]);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void uvecN_clamp_vec(unsigned *dst_vec, const unsigned *vec_x, const unsigned *vec_min, const unsigned *vec_max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_min[i] ? vec_min[i] : (vec_x[i] > vec_max[i] ? vec_max[i] : vec_x[i]);
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned uvecN_sum(const unsigned *vec, int n) {
    unsigned sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec[i];
    return sum;
}

/** returns a dot b */
static unsigned uvecN_dot(const unsigned *vec_a, const unsigned *vec_b, int n) {
    unsigned dot = 0;
    for (int i = 0; i < n; i++)
        dot += vec_a[i] * vec_b[i];
    return dot;
}

/** returns ||vec||_2 */
static float uvecN_norm(const unsigned *vec, int n) {
    return sqrtf(uvecN_dot(vec, vec, n));
}

/** returns length of a vector, see uvecN_norm. Just here to match glsl */
static float uvecN_length(const unsigned *vec, int n) {
    return uvecN_norm(vec, n);
}

/** returns norm(b-a) */
static float uvecN_distance(const unsigned *vec_a, const unsigned *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    unsigned tmp[MATHC_MAX_SIZE];
#else
    unsigned tmp[n];
#endif
    uvecN_sub_vec(tmp, vec_b, vec_a, n);
    return uvecN_norm(tmp, n);
}

/** dst = a < b */
static void uvecN_less_than(bool *dst_vec, const unsigned *vec_a, unsigned b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b;
}

/** dst = a < b */
static void uvecN_less_than_vec(bool *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i];
}

/** dst = a <= b */
static void uvecN_less_than_equal(bool *dst_vec, const unsigned *vec_a, unsigned b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= b;
}

/** dst = a <= b */
static void uvecN_less_than_equal_vec(bool *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= vec_b[i];
}

/** dst = a > b */
static void uvecN_greater_than(bool *dst_vec, const unsigned *vec_a, unsigned b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b;
}

/** dst = a > b */
static void uvecN_greater_than_vec(bool *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i];
}

/** dst = a >= b */
static void uvecN_greater_than_equal(bool *dst_vec, const unsigned *vec_a, unsigned b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= b;
}

/** dst = a >= b */
static void uvecN_greater_than_equal_vec(bool *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= vec_b[i];
}

/** dst = a == b */
static void uvecN_equal(bool *dst_vec, const unsigned *vec_a, unsigned b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == b;
}

/** dst = a == b */
static void uvecN_equal_vec(bool *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == vec_b[i];
}

/** dst = a != b */
static void uvecN_not_equal(bool *dst_vec, const unsigned *vec_a, unsigned b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != b;
}

/** dst = a != b */
static void uvecN_not_equal_vec(bool *dst_vec, const unsigned *vec_a, const unsigned *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != vec_b[i];
}

#endif //MATHC_VEC_UVECN_H
