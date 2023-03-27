#ifndef M_VEC_UCVECN_H
#define M_VEC_UCVECN_H


#ifndef M_MAX_SIZE
#define M_MAX_SIZE 16
#endif

#include <string.h>     // memcmp
#include <stdbool.h>
#include <assert.h>
#include "../sca/uchar.h"

/** macro to cast a vector into a unsigned char vector */
#define ucvecN_cast_into(dst, from, n) \
do { \
    for(int ucvecN_cast_into_i_=0; ucvecN_cast_into_i_<(n); ucvecN_cast_into_i_++) \
        (dst)[ucvecN_cast_into_i_] = (unsigned char) (from)[ucvecN_cast_into_i_]; \
} while(0)


/** dst = vec * 255 */
static void ucvecN_cast_from_float_1(unsigned char *dst_vec, const float *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = (unsigned char) (vec[i] * 255.0f);
}

/** dst = vec * 255 */
static void ucvecN_cast_from_double_1(unsigned char *dst_vec, const double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = (unsigned char) (vec[i] * 255.0);
}

/** dst = vec * 255 */
static void ucvecN_cast_from_longdouble_1(unsigned char *dst_vec, const long double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = (unsigned char) (vec[i] * 255.0);
}


/** a == b */
static bool ucvecN_cmp(const unsigned char *a, const unsigned char *b, int n) {
    return memcmp(a, b, n * sizeof(unsigned char)) == 0;
}

/** dst = v */
static void ucvecN_copy(unsigned char *dst, const unsigned char *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = v[i];
}

/** dst = s */
static void ucvecN_set(unsigned char *dst, unsigned char s, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = s;
}

/** dst = unit_x */
static void ucvecN_unit_x(unsigned char *dst, int n) {
    ucvecN_set(dst, 0, n);
    dst[0] = 1;
}

/** dst = unit_y */
static void ucvecN_unit_y(unsigned char *dst, int n) {
    ucvecN_set(dst, 0, n);
    dst[1] = 1;
}

/** assert(n>=3); dst = unit_z */
static void ucvecN_unit_z(unsigned char *dst, int n) {
    assert(n >= 3 && "m vec*_unit_z");
    ucvecN_set(dst, 0, n);
    dst[2] = 1;
}

/** assert(n>=4); dst = unit_w */
static void ucvecN_unit_w(unsigned char *dst, int n) {
    assert(n >= 4 && "m vec*_unit_w");
    ucvecN_set(dst, 0, n);
    dst[3] = 1;
}


/** dst = a + b */
static void ucvecN_add_vec(unsigned char *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b[i];
}

/** dst = a + b */
static void ucvecN_add(unsigned char *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b;
}

/** dst = a - b */
static void ucvecN_sub_vec(unsigned char *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] - b[i];
}

/** dst = a - b */
static void ucvecN_sub(unsigned char *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] - b;
}

/** dst = a * b */
static void ucvecN_scale_vec(unsigned char *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] * b[i];
}

/** dst = a * b */
static void ucvecN_scale(unsigned char *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] * b;
}

/** dst = a / b */
static void ucvecN_div_vec(unsigned char *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] / b[i];
}

/** dst = a / b */
static void ucvecN_div(unsigned char *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] / b;
}

/** dst = a + b * c */
static void
ucvecN_add_scaled_vec(unsigned char *dst, const unsigned char *a, const unsigned char *b, const unsigned char *c,
                      int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b[i] * c[i];
}

/** dst = a + b * c */
static void
ucvecN_add_scaled(unsigned char *dst, const unsigned char *a, const unsigned char *b, unsigned char c, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b[i] * c;
}


/** dst = pow(x, y) */
static void ucvecN_pow(unsigned char *dst, const unsigned char *x, unsigned char y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_pow(x[i], y);
}

/** dst = pow(x, y) */
static void ucvecN_pow_vec(unsigned char *dst, const unsigned char *x, const unsigned char *y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_pow(x[i], y[i]);
}

/** dst = exp(x) */
static void ucvecN_exp(unsigned char *dst, const unsigned char *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_exp(x[i]);
}

/** dst = log(x) */
static void ucvecN_log(unsigned char *dst, const unsigned char *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_log(x[i]);
}

/** dst = exp2(x) */
static void ucvecN_exp2(unsigned char *dst, const unsigned char *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_exp2(x[i]);
}

/** dst = log2(x) */
static void ucvecN_log2(unsigned char *dst, const unsigned char *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_log2(x[i]);
}

/** dst = sqrt(x) */
static void ucvecN_sqrt(unsigned char *dst, const unsigned char *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_sqrt(x[i]);
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static void ucvecN_mod(unsigned char *dst, const unsigned char *x, unsigned char y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_mod(x[i], y);
}

/** dst = (x % y + y) % y (always positive, if y>0) **/
static void ucvecN_mod_vec(unsigned char *dst, const unsigned char *x, const unsigned char *y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_mod(x[i], y[i]);
}

/** dst = a < b ? a : b */
static void ucvecN_min(unsigned char *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_min(a[i], b);
}

/** dst = a < b ? a : b */
static void ucvecN_min_vec(unsigned char *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_min(a[i], b[i]);
}

/** dst = a > b ? a : b */
static void ucvecN_max(unsigned char *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_max(a[i], b);
}

/** dst = a > b ? a : b */
static void ucvecN_max_vec(unsigned char *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_max(a[i], b[i]);
}

/** returns the index of the min v value */
static int ucvecN_min_index(const unsigned char *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] < v[idx])
            idx = i;
    }
    return idx;
}

/** returns the index of the max v value */
static int ucvecN_max_index(const unsigned char *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] > v[idx])
            idx = i;
    }
    return idx;
}

/** dst = x < min ? min : (x > max ? max : x) */
static void ucvecN_clamp(unsigned char *dst, const unsigned char *x, unsigned char min, unsigned char max, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_clamp(x[i], min, max);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void
ucvecN_clamp_vec(unsigned char *dst, const unsigned char *x, const unsigned char *min, const unsigned char *max,
                 int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_clamp(x[i], min[i], max[i]);
}

/** dst = a * (1-t) + b * t */
static void ucvecN_mix(unsigned char *dst, const unsigned char *a, const unsigned char *b, float t, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_mix(a[i], b[i], t);
}

/** dst = a * (1-t) + b * t */
static void ucvecN_mix_vec(unsigned char *dst, const unsigned char *a, const unsigned char *b, const float *t, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_mix(a[i], b[i], t[i]);
}

/** dst = x < edge ? 0 : 1 */
static void ucvecN_step(unsigned char *dst, const unsigned char *x, unsigned char edge, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_step(x[i], edge);
}

/** dst = x < edge ? 0 : 1 */
static void ucvecN_step_vec(unsigned char *dst, const unsigned char *x, const unsigned char *edge, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = ucsca_step(x[i], edge[i]);
}


/** returns v[0] + v[1] + ... + v[n-1] */
static unsigned char ucvecN_sum(const unsigned char *v, int n) {
    unsigned char sum = 0;
    for (int i = 0; i < n; i++)
        sum += v[i];
    return sum;
}

/** returns a dot b */
static unsigned char ucvecN_dot(const unsigned char *a, const unsigned char *b, int n) {
    unsigned char dot = 0;
    for (int i = 0; i < n; i++)
        dot += a[i] * b[i];
    return dot;
}

/** assert(n>=3) ; dst = a x b , dst.w... = 0 */
static void ucvecN_cross(unsigned char *dst, const unsigned char *a, const unsigned char *b, int n) {
    assert(n >= 3 && "m vec*_cross only in 3D");
    dst[0] = a[1] * b[2] - a[2] * b[1];
    dst[1] = a[2] * b[0] - a[0] * b[2];
    dst[2] = a[0] * b[1] - a[1] * b[0];
    for (int i = 3; i < n; i++)
        dst[i] = 0;
}

/** returns ||v||_2 */
static unsigned char ucvecN_norm(const unsigned char *v, int n) {
    return ucsca_sqrt(ucvecN_dot(v, v, n));
}


/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static unsigned char ucvecN_length(const unsigned char *v, int n) {
    return ucvecN_norm(v, n);
}

/** returns norm(b-a) */
static unsigned char ucvecN_distance(const unsigned char *a, const unsigned char *b, int n) {
    assert(n <= M_MAX_SIZE);
    unsigned char tmp[M_MAX_SIZE];
    ucvecN_sub_vec(tmp, b, a, n);
    return ucvecN_norm(tmp, n);
}

/** returns dot(b-a) */
static unsigned char ucvecN_sqr_distance(const unsigned char *a, const unsigned char *b, int n) {
    assert(n <= M_MAX_SIZE);
    unsigned char tmp[M_MAX_SIZE];
    ucvecN_sub_vec(tmp, b, a, n);
    return ucvecN_dot(tmp, tmp, n);
}


/** dst = a < b */
static void ucvecN_less_than(bool *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] < b;
}

/** dst = a < b */
static void ucvecN_less_than_vec(bool *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] < b[i];
}

/** dst = a <= b */
static void ucvecN_less_than_equal(bool *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] <= b;
}

/** dst = a <= b */
static void ucvecN_less_than_equal_vec(bool *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] <= b[i];
}

/** dst = a > b */
static void ucvecN_greater_than(bool *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] > b;
}

/** dst = a > b */
static void ucvecN_greater_than_vec(bool *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] > b[i];
}

/** dst = a >= b */
static void ucvecN_greater_than_equal(bool *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] >= b;
}

/** dst = a >= b */
static void ucvecN_greater_than_equal_vec(bool *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] >= b[i];
}

/** dst = a == b */
static void ucvecN_equal(bool *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] == b;
}

/** dst = a == b */
static void ucvecN_equal_vec(bool *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] == b[i];
}

/** dst = a != b */
static void ucvecN_not_equal(bool *dst, const unsigned char *a, unsigned char b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] != b;
}

/** dst = a != b */
static void ucvecN_not_equal_vec(bool *dst, const unsigned char *a, const unsigned char *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] != b[i];
}


#endif //M_VEC_UCVECN_H
