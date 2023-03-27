#ifndef M_VEC_DVECN_H
#define M_VEC_DVECN_H


#ifndef M_MAX_SIZE
#define M_MAX_SIZE 16
#endif

#include <string.h>     // memcmp
#include <stdbool.h>
#include <assert.h>
#include "../sca/double.h"

/** macro to cast a vector into a double vector */
#define dvecN_cast_into(dst, from, n) \
do { \
    for(int dvecN_cast_into_i_=0; dvecN_cast_into_i_<(n); dvecN_cast_into_i_++) \
        (dst)[dvecN_cast_into_i_] = (double) (from)[dvecN_cast_into_i_]; \
} while(0)


/** dst = v / 255 */
static void dvecN_cast_from_uchar_1(double *dst_vec, const unsigned char *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = (double) vec[i] / (double) 255;
}


/** a == b */
static bool dvecN_cmp(const double *a, const double *b, int n) {
    return memcmp(a, b, n * sizeof(double)) == 0;
}

/** dst = v */
static void dvecN_copy(double *dst, const double *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = v[i];
}

/** dst = s */
static void dvecN_set(double *dst, double s, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = s;
}

/** dst = unit_x */
static void dvecN_unit_x(double *dst, int n) {
    dvecN_set(dst, 0, n);
    dst[0] = 1;
}

/** dst = unit_y */
static void dvecN_unit_y(double *dst, int n) {
    dvecN_set(dst, 0, n);
    dst[1] = 1;
}

/** assert(n>=3); dst = unit_z */
static void dvecN_unit_z(double *dst, int n) {
    assert(n >= 3 && "m vec*_unit_z");
    dvecN_set(dst, 0, n);
    dst[2] = 1;
}

/** assert(n>=4); dst = unit_w */
static void dvecN_unit_w(double *dst, int n) {
    assert(n >= 4 && "m vec*_unit_w");
    dvecN_set(dst, 0, n);
    dst[3] = 1;
}

/** dst = -v */
static void dvecN_neg(double *dst, const double *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = -v[i];
}

/** dst = a + b */
static void dvecN_add_vec(double *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b[i];
}

/** dst = a + b */
static void dvecN_add(double *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b;
}

/** dst = a - b */
static void dvecN_sub_vec(double *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] - b[i];
}

/** dst = a - b */
static void dvecN_sub(double *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] - b;
}

/** dst = a * b */
static void dvecN_scale_vec(double *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] * b[i];
}

/** dst = a * b */
static void dvecN_scale(double *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] * b;
}

/** dst = a / b */
static void dvecN_div_vec(double *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] / b[i];
}

/** dst = a / b */
static void dvecN_div(double *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] / b;
}

/** dst = a + b * c */
static void dvecN_add_scaled_vec(double *dst, const double *a, const double *b, const double *c, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b[i] * c[i];
}

/** dst = a + b * c */
static void dvecN_add_scaled(double *dst, const double *a, const double *b, double c, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] + b[i] * c;
}

/** dst = a * M_PI / 180 */
static void dvecN_radians(double *dst, const double *deg, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_radians(deg[i]);
}

/** dst = a * 180 / M_PI */
static void dvecN_degrees(double *dst, const double *rad, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_degrees(rad[i]);
}

/** dst = sin(angle_rad) */
static void dvecN_sin(double *dst, const double *angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_sin(angle_rad[i]);
}

/** dst = cos(angle_rad) */
static void dvecN_cos(double *dst, const double *angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_cos(angle_rad[i]);
}

/** dst = tan(angle_rad) */
static void dvecN_tan(double *dst, const double *angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_tan(angle_rad[i]);
}

/** dst = asin(x) */
static void dvecN_asin(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_asin(x[i]);
}

/** dst = acos(x) */
static void dvecN_acos(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_acos(x[i]);
}

/** dst = atan(x) */
static void dvecN_atan(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_atan(x[i]);
}

/** dst = atan2(y, x) */
static void dvecN_atan2(double *dst, const double *y, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_atan2(y[i], x[i]);
}

/** dst = pow(x, y) */
static void dvecN_pow(double *dst, const double *x, double y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_pow(x[i], y);
}

/** dst = pow(x, y) */
static void dvecN_pow_vec(double *dst, const double *x, const double *y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_pow(x[i], y[i]);
}

/** dst = exp(x) */
static void dvecN_exp(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_exp(x[i]);
}

/** dst = log(x) */
static void dvecN_log(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_log(x[i]);
}

/** dst = exp2(x) */
static void dvecN_exp2(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_exp2(x[i]);
}

/** dst = log2(x) */
static void dvecN_log2(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_log2(x[i]);
}

/** dst = sqrt(x) */
static void dvecN_sqrt(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_sqrt(x[i]);
}

/** dst = 1 / sqrt(x) */
static void dvecN_inversesqrt(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_inversesqrt(x[i]);
}

/** dst = abs(x) */
static void dvecN_abs(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_abs(x[i]);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static void dvecN_sign(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_sign(x[i]);
}

/** dst = floor(x) */
static void dvecN_floor(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_floor(x[i]);
}

/** dst = ceil(x) */
static void dvecN_ceil(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_ceil(x[i]);
}

/** dst = x - floor(x) */
static void dvecN_fract(double *dst, const double *x, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_fract(x[i]);
}

/** dst = x - y * floor(x/y) */
static void dvecN_mod(double *dst, const double *x, double y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_mod(x[i], y);
}

/** dst = x - y * floor(x/y) */
static void dvecN_mod_vec(double *dst, const double *x, const double *y, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_mod(x[i], y[i]);
}

/** dst = a < b ? a : b */
static void dvecN_min(double *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_min(a[i], b);
}

/** dst = a < b ? a : b */
static void dvecN_min_vec(double *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_min(a[i], b[i]);
}

/** dst = a > b ? a : b */
static void dvecN_max(double *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_max(a[i], b);
}

/** dst = a > b ? a : b */
static void dvecN_max_vec(double *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_max(a[i], b[i]);
}

/** returns the index of the min v value */
static int dvecN_min_index(const double *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] < v[idx])
            idx = i;
    }
    return idx;
}

/** returns the index of the max v value */
static int dvecN_max_index(const double *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] > v[idx])
            idx = i;
    }
    return idx;
}

/** dst = x < min ? min : (x > max ? max : x) */
static void dvecN_clamp(double *dst, const double *x, double min, double max, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_clamp(x[i], min, max);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void dvecN_clamp_vec(double *dst, const double *x, const double *min, const double *max, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_clamp(x[i], min[i], max[i]);
}

/** dst = a * (1-t) + b * t */
static void dvecN_mix(double *dst, const double *a, const double *b, float t, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_mix(a[i], b[i], t);
}

/** dst = a * (1-t) + b * t */
static void dvecN_mix_vec(double *dst, const double *a, const double *b, const float *t, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_mix(a[i], b[i], t[i]);
}

/** dst = x < edge ? 0 : 1 */
static void dvecN_step(double *dst, const double *x, double edge, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_step(x[i], edge);
}

/** dst = x < edge ? 0 : 1 */
static void dvecN_step_vec(double *dst, const double *x, const double *edge, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_step(x[i], edge[i]);
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static void dvecN_smoothstep(double *dst, const double *x, double edge1, double edge2, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_smoothstep(x[i], edge1, edge2);
    }
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static void
dvecN_smoothstep_vec(double *dst, const double *x, const double *edge1, const double *edge2, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_smoothstep(x[i], edge1[i], edge2[i]);
    }
}

/** returns v[0] + v[1] + ... + v[n-1] */
static double dvecN_sum(const double *v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += v[i];
    return sum;
}

/** returns a dot b */
static double dvecN_dot(const double *a, const double *b, int n) {
    double dot = 0;
    for (int i = 0; i < n; i++)
        dot += a[i] * b[i];
    return dot;
}

/** assert(n>=3) ; dst = a x b , dst.w... = 0 */
static void dvecN_cross(double *dst, const double *a, const double *b, int n) {
    assert(n >= 3 && "m vec*_cross only in 3D");
    dst[0] = a[1] * b[2] - a[2] * b[1];
    dst[1] = a[2] * b[0] - a[0] * b[2];
    dst[2] = a[0] * b[1] - a[1] * b[0];
    for (int i = 3; i < n; i++)
        dst[i] = 0;
}

/** returns ||v||_2 */
static double dvecN_norm(const double *v, int n) {
    return dsca_sqrt(dvecN_dot(v, v, n));
}

/** returns ||v||_p */
static double dvecN_norm_p(const double *v, double p, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += dsca_pow(dsca_abs(v[i]), p);
    }
    return dsca_pow(sum, (double) 1 / p);
}

/** returns ||v||_1 */
static double dvecN_norm_1(const double *v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += dsca_abs(v[i]);
    }
    return sum;
}

/** returns ||v||_inf */
static double dvecN_norm_inf(const double *v, int n) {
    double max = 0;
    for (int i = 0; i < n; i++) {
        if (max < dsca_abs(v[i]))
            max = dsca_abs(v[i]);
    }
    return max;
}

/** dst = v / norm(v) */
static void dvecN_normalize_unsafe(double *dst, const double *v, int n) {
    dvecN_scale(dst, v, (double) 1 / dvecN_norm(v, n), n);
}

/** dst = v / (norm(v) > 0 ? norm(v) : 1) */
static void dvecN_normalize(double *dst, const double *v, int n) {
    double norm = dvecN_norm(v, n);
    dvecN_scale(dst, v, (double) 1 / (norm > (double) 0 ? norm : (double) 1), n);
}

/** dst = normalize(cross(a, b)) */
static void dvecN_cross_normalized(double *dst, const double *a, const double *b, int n) {
    dvecN_cross(dst, a, b, n);
    dvecN_normalize(dst, dst, n);
}

/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvecN_length(const double *v, int n) {
    return dvecN_norm(v, n);
}

/** returns norm(b-a) */
static double dvecN_distance(const double *a, const double *b, int n) {
    assert(n <= M_MAX_SIZE);
    double tmp[M_MAX_SIZE];
    dvecN_sub_vec(tmp, b, a, n);
    return dvecN_norm(tmp, n);
}

/** returns dot(b-a) */
static double dvecN_sqr_distance(const double *a, const double *b, int n) {
    assert(n <= M_MAX_SIZE);
    double tmp[M_MAX_SIZE];
    dvecN_sub_vec(tmp, b, a, n);
    return dvecN_dot(tmp, tmp, n);
}

/** dst = dot(i_v, nref_v) < 0 ? n_v : -n_v */
static void dvecN_faceforward(double *dst, const double *n_v, const double *i_v, const double *nref_v, int n) {
    if (dvecN_dot(i_v, nref_v, n) < 0)
        dvecN_copy(dst, n_v, n);
    else
        dvecN_neg(dst, n_v, n);
}

/** dst = i_v - 2.0 * n_v * dot(n_v,i_v) */
static void dvecN_reflect(double *dst, const double *i_v, const double *n_v, int n) {
    dvecN_scale(dst, n_v, (double) 2 * dvecN_dot(n_v, i_v, n), n);
    dvecN_sub_vec(dst, i_v, dst, n);
}

static void dvecN_refract(double *dst, const double *i_v, const double *n_v, double eta, int n) {
    // implementation from example implementation: https://developer.download.nvidia.com/cg/refract.html
    dvecN_neg(dst, i_v, n);
    double cosi = dvecN_dot(dst, n_v, n);
    double cost2 = (double) 1 - eta * eta * ((double) 1 - cosi * cosi);
    dvecN_scale(dst, n_v, eta * cosi - dsca_sqrt(dsca_abs(cost2)), n);
    double t[3];
    dvecN_scale(t, i_v, eta, n);
    dvecN_add_vec(t, t, dst, n);
    dvecN_scale(dst, t, cost2 > (double) 0, n);
}

/** dst = a < b */
static void dvecN_less_than(bool *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] < b;
}

/** dst = a < b */
static void dvecN_less_than_vec(bool *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] < b[i];
}

/** dst = a <= b */
static void dvecN_less_than_equal(bool *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] <= b;
}

/** dst = a <= b */
static void dvecN_less_than_equal_vec(bool *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] <= b[i];
}

/** dst = a > b */
static void dvecN_greater_than(bool *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] > b;
}

/** dst = a > b */
static void dvecN_greater_than_vec(bool *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] > b[i];
}

/** dst = a >= b */
static void dvecN_greater_than_equal(bool *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] >= b;
}

/** dst = a >= b */
static void dvecN_greater_than_equal_vec(bool *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] >= b[i];
}

/** dst = a == b */
static void dvecN_equal(bool *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] == b;
}

/** dst = a == b */
static void dvecN_equal_vec(bool *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] == b[i];
}

/** dst = a != b */
static void dvecN_not_equal(bool *dst, const double *a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] != b;
}

/** dst = a != b */
static void dvecN_not_equal_vec(bool *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = a[i] != b[i];
}

/** dst = a == b (+-eps) */
static void dvecN_equal_eps(bool *dst, const double *a, double b, double eps, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_abs(a[i] - b) <= eps;
}

/** dst = a == b (+-eps) */
static void dvecN_equal_eps_vec(bool *dst, const double *a, const double *b, double eps, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_abs(a[i] - b[i]) <= eps;
}

/** dst = a != b (+-eps) */
static void dvecN_not_equal_eps(bool *dst, const double *a, double b, double eps, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_abs(a[i] - b) > eps;
}

/** dst = a != b (+-eps) */
static void dvecN_not_equal_eps_vec(bool *dst, const double *a, const double *b, double eps, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_abs(a[i] - b[i]) > eps;
}

/** dst = isnan(v) */
static void dvecN_isnan(bool *dst, const double *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_isnan(v[i]);
}

/** dst = !isnan(v) */
static void dvecN_not_isnan(bool *dst, const double *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = !dsca_isnan(v[i]);
}

/** dst = isinf(v) */
static void dvecN_isinf(bool *dst, const double *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = dsca_isinf(v[i]);
}

/** dst = !isinf(v) */
static void dvecN_not_isinf(bool *dst, const double *v, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = !dsca_isinf(v[i]);
}

#endif //M_VEC_DVECN_H
