#ifndef M_VEC_VECN_H
#define M_VEC_VECN_H


#ifndef M_MAX_SIZE
#define M_MAX_SIZE 16
#endif

#include <string.h>     // memcmp
#include <stdbool.h>
#include <assert.h>
#include "../sca/float.h"

/** macro to cast a vector into a float vector */
#define vecN_cast_into(dst, from, n) \
do { \
    for(int vecN_cast_into_i_=0; vecN_cast_into_i_<(n); vecN_cast_into_i_++) \
        (dst)[vecN_cast_into_i_] = (float) (from)[vecN_cast_into_i_]; \
} while(0)


/** dst = v / 255 */
static void vecN_cast_from_uchar_1(float *dst_vec, const unsigned char *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = (float) vec[i] / (float) 255;
}






/** a == b */
static bool vecN_cmp(const float *a, const float *b, int n) {
    return memcmp(a, b, n * sizeof(float)) == 0;
}

/** dst = v */
static void vecN_copy(float *dst, const float *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = v[i];
}

/** dst = s */
static void vecN_set(float *dst, float s, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = s;
}

/** dst = unit_x */
static void vecN_unit_x(float *dst, int n) {
    vecN_set(dst, 0, n);
    dst[0] = 1;
}

/** dst = unit_y */
static void vecN_unit_y(float *dst, int n) {
    vecN_set(dst, 0, n);
    dst[1] = 1;
}

/** assert(n>=3); dst = unit_z */
static void vecN_unit_z(float *dst, int n) {
    assert(n>=3 && "m vec*_unit_z");
    vecN_set(dst, 0, n);
    dst[2] = 1;
}

/** assert(n>=4); dst = unit_w */
static void vecN_unit_w(float *dst, int n) {
    assert(n>=4 && "m vec*_unit_w");
    vecN_set(dst, 0, n);
    dst[3] = 1;
}

/** dst = -v */
static void vecN_neg(float *dst, const float *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = -v[i];
}

/** dst = a + b */
static void vecN_add_vec(float *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b[i];
}

/** dst = a + b */
static void vecN_add(float *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b;
}

/** dst = a - b */
static void vecN_sub_vec(float *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] - b[i];
}

/** dst = a - b */
static void vecN_sub(float *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] - b;
}

/** dst = a * b */
static void vecN_scale_vec(float *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] * b[i];
}

/** dst = a * b */
static void vecN_scale(float *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] * b;
}

/** dst = a / b */
static void vecN_div_vec(float *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] / b[i];
}

/** dst = a / b */
static void vecN_div(float *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] / b;
}

/** dst = a * M_PI / 180 */
static void vecN_radians(float *dst, const float *deg, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_radians(deg[i]);
}

/** dst = a * 180 / M_PI */
static void vecN_degrees(float *dst, const float *rad, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_degrees(rad[i]);
}

/** dst = sin(angle_rad) */
static void vecN_sin(float *dst, const float *angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_sin(angle_rad[i]);
}

/** dst = cos(angle_rad) */
static void vecN_cos(float *dst, const float *angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_cos(angle_rad[i]);
}

/** dst = tan(angle_rad) */
static void vecN_tan(float *dst, const float *angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_tan(angle_rad[i]);
}

/** dst = asin(x) */
static void vecN_asin(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_asin(x[i]);
}

/** dst = acos(x) */
static void vecN_acos(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_acos(x[i]);
}

/** dst = atan(x) */
static void vecN_atan(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_atan(x[i]);
}

/** dst = atan2(y, x) */
static void vecN_atan2(float *dst, const float *y, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_atan2(y[i], x[i]);
}

/** dst = pow(x, y) */
static void vecN_pow(float *dst, const float *x, float y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_pow(x[i], y);
}

/** dst = pow(x, y) */
static void vecN_pow_vec(float *dst, const float *x, const float *y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_pow(x[i], y[i]);
}

/** dst = exp(x) */
static void vecN_exp(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_exp(x[i]);
}

/** dst = log(x) */
static void vecN_log(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_log(x[i]);
}

/** dst = exp2(x) */
static void vecN_exp2(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_exp2(x[i]);
}

/** dst = log2(x) */
static void vecN_log2(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_log2(x[i]);
}

/** dst = sqrt(x) */
static void vecN_sqrt(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_sqrt(x[i]);
}

/** dst = 1 / sqrt(x) */
static void vecN_inversesqrt(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_inversesqrt(x[i]);
}

/** dst = abs(x) */
static void vecN_abs(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_abs(x[i]);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static void vecN_sign(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_sign(x[i]);
}

/** dst = floor(x) */
static void vecN_floor(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_floor(x[i]);
}

/** dst = ceil(x) */
static void vecN_ceil(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_ceil(x[i]);
}

/** dst = x - floor(x) */
static void vecN_fract(float *dst, const float *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_fract(x[i]);
}

/** dst = x - y * floor(x/y) */
static void vecN_mod(float *dst, const float *x, float y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_mod(x[i], y);
}

/** dst = x - y * floor(x/y) */
static void vecN_mod_vec(float *dst, const float *x, const float *y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_mod(x[i], y[i]);
}

/** dst = a < b ? a : b */
static void vecN_min(float *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_min(a[i], b);
}

/** dst = a < b ? a : b */
static void vecN_min_vec(float *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_min(a[i], b[i]);
}

/** dst = a > b ? a : b */
static void vecN_max(float *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_max(a[i], b);
}

/** dst = a > b ? a : b */
static void vecN_max_vec(float *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_max(a[i], b[i]);
}

/** returns the index of the min v value */
static int vecN_min_index(const float *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] < v[idx])
            idx = i;
    }
    return idx;
}

/** returns the index of the max v value */
static int vecN_max_index(const float *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] > v[idx])
            idx = i;
    }
    return idx;
}

/** dst = x < min ? min : (x > max ? max : x) */
static void vecN_clamp(float *dst, const float *x, float min, float max, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_clamp(x[i], min, max);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void vecN_clamp_vec(float *dst, const float *x, const float *min, const float *max, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_clamp(x[i], min[i], max[i]);
}

/** dst = a * (1-t) + b * t */
static void vecN_mix(float *dst, const float *a, const float *b, float t, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_mix(a[i], b[i], t);
}

/** dst = a * (1-t) + b * t */
static void vecN_mix_vec(float *dst, const float *a, const float *b, const float *t, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_mix(a[i], b[i], t[i]);
}

/** dst = x < edge ? 0 : 1 */
static void vecN_step(float *dst, const float *x, float edge, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_step(x[i], edge);
}

/** dst = x < edge ? 0 : 1 */
static void vecN_step_vec(float *dst, const float *x, const float *edge, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_step(x[i], edge[i]);
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static void vecN_smoothstep(float *dst, const float *x, float edge1, float edge2, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_smoothstep(x[i], edge1, edge2);
    }
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static void
vecN_smoothstep_vec(float *dst, const float *x, const float *edge1, const float *edge2, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_smoothstep(x[i], edge1[i], edge2[i]);
    }
}

/** returns v[0] + v[1] + ... + v[n-1] */
static float vecN_sum(const float *v, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += v[i];
    return sum;
}

/** returns a dot b */
static float vecN_dot(const float *a, const float *b, int n) {
    float dot = 0;
    for (int i = 0; i < n; i++)
        dot += a[i] * b[i];
    return dot;
}

/** assert(n>=3) ; dst = a x b , dst.w... = 0 */
static void vecN_cross(float *dst, const float *a, const float *b, int n) {
    assert(n>=3 && "m vec*_cross only in 3D");
    dst[0] = a[1] * b[2] - a[2] * b[1];
    dst[1] = a[2] * b[0] - a[0] * b[2];
    dst[2] = a[0] * b[1] - a[1] * b[0];
    for(int i=3; i<n; i++)
        dst[i] = 0;
}

/** returns ||v||_2 */
static float vecN_norm(const float *v, int n) {
    return sca_sqrt(vecN_dot(v, v, n));
}

/** returns ||v||_p */
static float vecN_norm_p(const float *v, float p, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += sca_pow(sca_abs(v[i]), p);
    }
    return sca_pow(sum, (float) 1 / p);
}

/** returns ||v||_1 */
static float vecN_norm_1(const float *v, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += sca_abs(v[i]);
    }
    return sum;
}

/** returns ||v||_inf */
static float vecN_norm_inf(const float *v, int n) {
    float max = 0;
    for (int i = 0; i < n; i++) {
        if (max < sca_abs(v[i]))
            max = sca_abs(v[i]);
    }
    return max;
}

/** dst = v / norm(v) */
static void vecN_normalize_unsafe(float *dst, const float *v, int n) {
    vecN_scale(dst, v, (float) 1 / vecN_norm(v, n), n);
}

/** dst = v / (norm(v) > 0 ? norm(v) : 1) */
static void vecN_normalize(float *dst, const float *v, int n) {
    float norm = vecN_norm(v, n);
    vecN_scale(dst, v, (float) 1 / (norm > (float) 0 ? norm : (float) 1), n);
}

/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vecN_length(const float *v, int n) {
    return vecN_norm(v, n);
}

/** returns norm(b-a) */
static float vecN_distance(const float *a, const float *b, int n) {
    assert(n <= M_MAX_SIZE);
    float tmp[M_MAX_SIZE];
    vecN_sub_vec(tmp, b, a, n);
    return vecN_norm(tmp, n);
}

/** returns dot(b-a) */
static float vecN_sqr_distance(const float *a, const float *b, int n) {
    assert(n <= M_MAX_SIZE);
    float tmp[M_MAX_SIZE];
    vecN_sub_vec(tmp, b, a, n);
    return vecN_dot(tmp, tmp, n);
}

/** dst = dot(i_v, nref_v) < 0 ? n_v : -n_v */
static void vecN_faceforward(float *dst, const float *n_v, const float *i_v, const float *nref_v, int n) {
    if (vecN_dot(i_v, nref_v, n) < 0)
        vecN_copy(dst, n_v, n);
    else
        vecN_neg(dst, n_v, n);
}

/** dst = i_v - 2.0 * n_v * dot(n_v,i_v) */
static void vecN_reflect(float *dst, const float *i_v, const float *n_v, int n) {
    vecN_scale(dst, n_v, (float) 2 * vecN_dot(n_v, i_v, n), n);
    vecN_sub_vec(dst, i_v, dst, n);
}

static void vecN_refract(float *dst, const float *i_v, const float *n_v, float eta, int n) {
    // implementation from example implementation: https://developer.download.nvidia.com/cg/refract.html
    vecN_neg(dst, i_v, n);
    float cosi = vecN_dot(dst, n_v, n);
    float cost2 = (float) 1 - eta * eta * ((float) 1 - cosi * cosi);
    vecN_scale(dst, n_v, eta * cosi - sca_sqrt(sca_abs(cost2)), n);
    float t[3];
    vecN_scale(t, i_v, eta, n);
    vecN_add_vec(t, t, dst, n);
    vecN_scale(dst, t, cost2 > (float) 0, n);
}

/** dst = a < b */
static void vecN_less_than(bool *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] < b;
}

/** dst = a < b */
static void vecN_less_than_vec(bool *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] < b[i];
}

/** dst = a <= b */
static void vecN_less_than_equal(bool *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] <= b;
}

/** dst = a <= b */
static void vecN_less_than_equal_vec(bool *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] <= b[i];
}

/** dst = a > b */
static void vecN_greater_than(bool *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] > b;
}

/** dst = a > b */
static void vecN_greater_than_vec(bool *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] > b[i];
}

/** dst = a >= b */
static void vecN_greater_than_equal(bool *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] >= b;
}

/** dst = a >= b */
static void vecN_greater_than_equal_vec(bool *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] >= b[i];
}

/** dst = a == b */
static void vecN_equal(bool *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] == b;
}

/** dst = a == b */
static void vecN_equal_vec(bool *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] == b[i];
}

/** dst = a != b */
static void vecN_not_equal(bool *dst, const float *a, float b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] != b;
}

/** dst = a != b */
static void vecN_not_equal_vec(bool *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] != b[i];
}

/** dst = a == b (+-eps) */
static void vecN_equal_eps(bool *dst, const float *a, float b, float eps, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_abs(a[i] - b) <= eps;
}

/** dst = a == b (+-eps) */
static void vecN_equal_eps_vec(bool *dst, const float *a, const float *b, float eps, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_abs(a[i] - b[i]) <= eps;
}

/** dst = a != b (+-eps) */
static void vecN_not_equal_eps(bool *dst, const float *a, float b, float eps, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_abs(a[i] - b) > eps;
}

/** dst = a != b (+-eps) */
static void vecN_not_equal_eps_vec(bool *dst, const float *a, const float *b, float eps, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_abs(a[i] - b[i]) > eps;
}

/** dst = isnan(v) */
static void vecN_isnan(bool *dst, const float *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_isnan(v[i]);
}

/** dst = !isnan(v) */
static void vecN_not_isnan(bool *dst, const float *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = !sca_isnan(v[i]);
}

/** dst = isinf(v) */
static void vecN_isinf(bool *dst, const float *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = sca_isinf(v[i]);
}

/** dst = !isinf(v) */
static void vecN_not_isinf(bool *dst, const float *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = !sca_isinf(v[i]);
}

#endif //M_VEC_VECN_H
