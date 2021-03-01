#ifndef MATHC_VEC_UCVECN_H
#define MATHC_VEC_UCVECN_H

#ifndef MATHC_MAX_SIZE
#ifdef __STDC_NO_VLA__
#define MATHC_MAX_SIZE 16
#endif
#endif

#include <string.h>     // memcmp
#include <stdbool.h>
#include <math.h>
#include <assert.h>


typedef unsigned char uchar;


/** macro to cast a vector ucharo a uchar vector */
#define ucvecN_cast_into(dst_vec, vec, n) \
do { \
    for(int ucvecN_cast_into_i_=0; ucvecN_cast_into_i_<(n); ucvecN_cast_into_i_++) \
        (dst_vec)[ucvecN_cast_into_i_] = (uchar) (vec)[ucvecN_cast_into_i_]; \
} while(0)


/** dst = vec * 255 */
static void ucvecN_cast_from_float_1(uchar *dst_vec, const float *vec, int n) {
    for(int i = 0; i < n; i++)
        dst_vec[i] = (uchar) (vec[i] * 255.0f);
}

/** dst = vec * 255 */
static void ucvecN_cast_from_double_1(uchar *dst_vec, const double *vec, int n) {
    for(int i = 0; i < n; i++)
        dst_vec[i] = (uchar) (vec[i] * 255.0);
}

/** vec_a == vec_b */
static bool ucvecN_cmp(const uchar *vec_a, const uchar *vec_b, int n) {
    return memcmp(vec_a, vec_b, n * sizeof(uchar)) == 0;
}


/** dst = vec */
static void ucvecN_copy(uchar *dst_vec, const uchar *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec[i];
}

/** dst = scalar */
static void ucvecN_set(uchar *dst_vec, uchar scalar, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = scalar;
}

/** dst = a + b */
static void ucvecN_add_vec(uchar *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + vec_b[i];
}

/** dst = a + b */
static void ucvecN_add(uchar *dst_vec, const uchar *vec_a, uchar scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + scalar_b;
}

/** dst = a - b */
static void ucvecN_sub_vec(uchar *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - vec_b[i];
}

/** dst = a - b */
static void ucvecN_sub(uchar *dst_vec, const uchar *vec_a, uchar scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - scalar_b;
}

/** dst = a * b */
static void ucvecN_scale_vec(uchar *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * vec_b[i];
}

/** dst = a * b */
static void ucvecN_scale(uchar *dst_vec, const uchar *vec_a, uchar scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * scalar_b;
}

/** dst = a / b */
static void ucvecN_div_vec(uchar *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / vec_b[i];
}

/** dst = a / b */
static void ucvecN_div(uchar *dst_vec, const uchar *vec_a, uchar scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / scalar_b;
}

/** dst = x % y */
static void ucvecN_mod(uchar *dst_vec, const uchar *vec_x, uchar y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] % y;
}

/** dst = x % y */
static void ucvecN_mod_vec(uchar *dst_vec, const uchar *vec_x, const uchar *vec_y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] % vec_y[i];
}

/** dst = a < b ? a : b */
static void ucvecN_min(uchar *dst_vec, const uchar *vec_a, uchar b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b ? vec_a[i] : b;
}

/** dst = a < b ? a : b */
static void ucvecN_min_vec(uchar *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = a > b ? a : b */
static void ucvecN_max(uchar *dst_vec, const uchar *vec_a, uchar b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b ? vec_a[i] : b;
}

/** dst = a > b ? a : b */
static void ucvecN_max_vec(uchar *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = x < min ? min : (x > max ? max : x) */
static void ucvecN_clamp(uchar *dst_vec, const uchar *vec_x, uchar min, uchar max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < min ? min : (vec_x[i] > max ? max : vec_x[i]);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void ucvecN_clamp_vec(uchar *dst_vec, const uchar *vec_x, const uchar *vec_min, const uchar *vec_max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_min[i] ? vec_min[i] : (vec_x[i] > vec_max[i] ? vec_max[i] : vec_x[i]);
}

/** dst = a * (1-t) + b * t */
static void ucvecN_mix(uchar *dst_vec, const uchar *vec_a, const uchar *vec_b, float t, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * (1.0f - t) + vec_b[i] * t;
}

/** dst = a * (1-t) + b * t */
static void ucvecN_mix_vec(uchar *dst_vec, const uchar *vec_a, const uchar *vec_b, const float *vec_t, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * (1.0f - vec_t[i]) + vec_b[i] * vec_t[i];
}

/** dst = x < edge ? 0 : 1 */
static void ucvecN_step(uchar *dst_vec, const uchar *vec_x, uchar edge, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < edge ? 0 : 1;
}

/** dst = x < edge ? 0 : 1 */
static void ucvecN_step_vec(uchar *dst_vec, const uchar *vec_x, const uchar *vec_edge, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_edge[i] ? 0 : 1;
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static uchar ucvecN_sum(const uchar *vec, int n) {
    uchar sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec[i];
    return sum;
}

/** returns a dot b */
static uchar ucvecN_dot(const uchar *vec_a, const uchar *vec_b, int n) {
    uchar dot = 0;
    for (int i = 0; i < n; i++)
        dot += vec_a[i] * vec_b[i];
    return dot;
}

/** returns ||vec||_2 */
static float ucvecN_norm(const uchar *vec, int n) {
    return sqrtf(ucvecN_dot(vec, vec, n));
}

/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static float ucvecN_length(const uchar *vec, int n) {
    return ucvecN_norm(vec, n);
}

/** returns norm(b-a) */
static float ucvecN_distance(const uchar *vec_a, const uchar *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    uchar tmp[MATHC_MAX_SIZE];
#else
    uchar tmp[n];
#endif
    ucvecN_sub_vec(tmp, vec_b, vec_a, n);
    return ucvecN_norm(tmp, n);
}

/** dst = a < b */
static void ucvecN_less_than(bool *dst_vec, const uchar *vec_a, uchar b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b;
}

/** dst = a < b */
static void ucvecN_less_than_vec(bool *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i];
}

/** dst = a <= b */
static void ucvecN_less_than_equal(bool *dst_vec, const uchar *vec_a, uchar b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= b;
}

/** dst = a <= b */
static void ucvecN_less_than_equal_vec(bool *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= vec_b[i];
}

/** dst = a > b */
static void ucvecN_greater_than(bool *dst_vec, const uchar *vec_a, uchar b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b;
}

/** dst = a > b */
static void ucvecN_greater_than_vec(bool *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i];
}

/** dst = a >= b */
static void ucvecN_greater_than_equal(bool *dst_vec, const uchar *vec_a, uchar b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= b;
}

/** dst = a >= b */
static void ucvecN_greater_than_equal_vec(bool *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= vec_b[i];
}

/** dst = a == b */
static void ucvecN_equal(bool *dst_vec, const uchar *vec_a, uchar b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == b;
}

/** dst = a == b */
static void ucvecN_equal_vec(bool *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == vec_b[i];
}

/** dst = a != b */
static void ucvecN_not_equal(bool *dst_vec, const uchar *vec_a, uchar b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != b;
}

/** dst = a != b */
static void ucvecN_not_equal_vec(bool *dst_vec, const uchar *vec_a, const uchar *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != vec_b[i];
}

#endif //MATHC_VEC_UCVECN_H
