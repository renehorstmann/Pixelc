#ifndef M_VEC_IVECN_H
#define M_VEC_IVECN_H


#ifndef M_MAX_SIZE
#define M_MAX_SIZE 16
#endif

#include <string.h>     // memcmp
#include <stdbool.h>
#include <assert.h>
#include "../sca/int.h"

/** macro to cast a vector into a int vector */
#define ivecN_cast_into(dst, from, n) \
do { \
    for(int ivecN_cast_into_i_=0; ivecN_cast_into_i_<(n); ivecN_cast_into_i_++) \
        (dst)[ivecN_cast_into_i_] = (int) (from)[ivecN_cast_into_i_]; \
} while(0)




/** dst = vec * 255 */
static void ivecN_cast_from_float_1(int *dst_vec, const float *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = (int) (vec[i] * 255.0f);
}

/** dst = vec * 255 */
static void ivecN_cast_from_double_1(int *dst_vec, const double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = (int) (vec[i] * 255.0);
}

/** dst = vec * 255 */
static void ivecN_cast_from_longdouble_1(int *dst_vec, const long double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = (int) (vec[i] * 255.0);
}


/** a == b */
static bool ivecN_cmp(const int *a, const int *b, int n) {
    return memcmp(a, b, n * sizeof(int)) == 0;
}

/** dst = v */
static void ivecN_copy(int *dst, const int *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = v[i];
}

/** dst = s */
static void ivecN_set(int *dst, int s, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = s;
}

/** dst = unit_x */
static void ivecN_unit_x(int *dst, int n) {
    ivecN_set(dst, 0, n);
    dst[0] = 1;
}

/** dst = unit_y */
static void ivecN_unit_y(int *dst, int n) {
    ivecN_set(dst, 0, n);
    dst[1] = 1;
}

/** assert(n>=3); dst = unit_z */
static void ivecN_unit_z(int *dst, int n) {
    assert(n>=3 && "m vec*_unit_z");
    ivecN_set(dst, 0, n);
    dst[2] = 1;
}

/** assert(n>=4); dst = unit_w */
static void ivecN_unit_w(int *dst, int n) {
    assert(n>=4 && "m vec*_unit_w");
    ivecN_set(dst, 0, n);
    dst[3] = 1;
}

/** dst = -v */
static void ivecN_neg(int *dst, const int *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = -v[i];
}

/** dst = a + b */
static void ivecN_add_vec(int *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b[i];
}

/** dst = a + b */
static void ivecN_add(int *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b;
}

/** dst = a - b */
static void ivecN_sub_vec(int *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] - b[i];
}

/** dst = a - b */
static void ivecN_sub(int *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] - b;
}

/** dst = a * b */
static void ivecN_scale_vec(int *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] * b[i];
}

/** dst = a * b */
static void ivecN_scale(int *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] * b;
}

/** dst = a / b */
static void ivecN_div_vec(int *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] / b[i];
}

/** dst = a / b */
static void ivecN_div(int *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] / b;
}










/** dst = pow(x, y) */
static void ivecN_pow(int *dst, const int *x, int y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_pow(x[i], y);
}

/** dst = pow(x, y) */
static void ivecN_pow_vec(int *dst, const int *x, const int *y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_pow(x[i], y[i]);
}

/** dst = exp(x) */
static void ivecN_exp(int *dst, const int *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_exp(x[i]);
}

/** dst = log(x) */
static void ivecN_log(int *dst, const int *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_log(x[i]);
}

/** dst = exp2(x) */
static void ivecN_exp2(int *dst, const int *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_exp2(x[i]);
}

/** dst = log2(x) */
static void ivecN_log2(int *dst, const int *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_log2(x[i]);
}

/** dst = sqrt(x) */
static void ivecN_sqrt(int *dst, const int *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_sqrt(x[i]);
}


/** dst = abs(x) */
static void ivecN_abs(int *dst, const int *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_abs(x[i]);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static void ivecN_sign(int *dst, const int *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_sign(x[i]);
}




/** dst = (x % y + y) % y (always positive, if y>0) **/
static void ivecN_mod(int *dst, const int *x, int y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_mod(x[i], y);
}

/** dst = (x % y + y) % y (always positive, if y>0) **/
static void ivecN_mod_vec(int *dst, const int *x, const int *y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_mod(x[i], y[i]);
}

/** dst = a < b ? a : b */
static void ivecN_min(int *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_min(a[i], b);
}

/** dst = a < b ? a : b */
static void ivecN_min_vec(int *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_min(a[i], b[i]);
}

/** dst = a > b ? a : b */
static void ivecN_max(int *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_max(a[i], b);
}

/** dst = a > b ? a : b */
static void ivecN_max_vec(int *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_max(a[i], b[i]);
}

/** returns the index of the min v value */
static int ivecN_min_index(const int *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] < v[idx])
            idx = i;
    }
    return idx;
}

/** returns the index of the max v value */
static int ivecN_max_index(const int *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] > v[idx])
            idx = i;
    }
    return idx;
}

/** dst = x < min ? min : (x > max ? max : x) */
static void ivecN_clamp(int *dst, const int *x, int min, int max, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_clamp(x[i], min, max);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void ivecN_clamp_vec(int *dst, const int *x, const int *min, const int *max, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_clamp(x[i], min[i], max[i]);
}

/** dst = a * (1-t) + b * t */
static void ivecN_mix(int *dst, const int *a, const int *b, float t, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_mix(a[i], b[i], t);
}

/** dst = a * (1-t) + b * t */
static void ivecN_mix_vec(int *dst, const int *a, const int *b, const float *t, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_mix(a[i], b[i], t[i]);
}

/** dst = x < edge ? 0 : 1 */
static void ivecN_step(int *dst, const int *x, int edge, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_step(x[i], edge);
}

/** dst = x < edge ? 0 : 1 */
static void ivecN_step_vec(int *dst, const int *x, const int *edge, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = isca_step(x[i], edge[i]);
}



/** returns v[0] + v[1] + ... + v[n-1] */
static int ivecN_sum(const int *v, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += v[i];
    return sum;
}

/** returns a dot b */
static int ivecN_dot(const int *a, const int *b, int n) {
    int dot = 0;
    for (int i = 0; i < n; i++)
        dot += a[i] * b[i];
    return dot;
}

/** assert(n>=3) ; dst = a x b , dst.w... = 0 */
static void ivecN_cross(int *dst, const int *a, const int *b, int n) {
    assert(n>=3 && "m vec*_cross only in 3D");
    dst[0] = a[1] * b[2] - a[2] * b[1];
    dst[1] = a[2] * b[0] - a[0] * b[2];
    dst[2] = a[0] * b[1] - a[1] * b[0];
    for(int i=3; i<n; i++)
        dst[i] = 0;
}

/** returns ||v||_2 */
static int ivecN_norm(const int *v, int n) {
    return isca_sqrt(ivecN_dot(v, v, n));
}

/** returns ||v||_p */
static int ivecN_norm_p(const int *v, int p, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += isca_pow(isca_abs(v[i]), p);
    }
    return isca_pow(sum, (int) 1 / p);
}

/** returns ||v||_1 */
static int ivecN_norm_1(const int *v, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += isca_abs(v[i]);
    }
    return sum;
}

/** returns ||v||_inf */
static int ivecN_norm_inf(const int *v, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (max < isca_abs(v[i]))
            max = isca_abs(v[i]);
    }
    return max;
}



/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static int ivecN_length(const int *v, int n) {
    return ivecN_norm(v, n);
}

/** returns norm(b-a) */
static int ivecN_distance(const int *a, const int *b, int n) {
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE];
    ivecN_sub_vec(tmp, b, a, n);
    return ivecN_norm(tmp, n);
}

/** returns dot(b-a) */
static int ivecN_sqr_distance(const int *a, const int *b, int n) {
    assert(n <= M_MAX_SIZE);
    int tmp[M_MAX_SIZE];
    ivecN_sub_vec(tmp, b, a, n);
    return ivecN_dot(tmp, tmp, n);
}




/** dst = a < b */
static void ivecN_less_than(bool *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] < b;
}

/** dst = a < b */
static void ivecN_less_than_vec(bool *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] < b[i];
}

/** dst = a <= b */
static void ivecN_less_than_equal(bool *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] <= b;
}

/** dst = a <= b */
static void ivecN_less_than_equal_vec(bool *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] <= b[i];
}

/** dst = a > b */
static void ivecN_greater_than(bool *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] > b;
}

/** dst = a > b */
static void ivecN_greater_than_vec(bool *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] > b[i];
}

/** dst = a >= b */
static void ivecN_greater_than_equal(bool *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] >= b;
}

/** dst = a >= b */
static void ivecN_greater_than_equal_vec(bool *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] >= b[i];
}

/** dst = a == b */
static void ivecN_equal(bool *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] == b;
}

/** dst = a == b */
static void ivecN_equal_vec(bool *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] == b[i];
}

/** dst = a != b */
static void ivecN_not_equal(bool *dst, const int *a, int b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] != b;
}

/** dst = a != b */
static void ivecN_not_equal_vec(bool *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] != b[i];
}









#endif //M_VEC_IVECN_H
