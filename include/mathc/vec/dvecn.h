#ifndef MATHC_VEC_DVECN_H
#define MATHC_VEC_DVECN_H

#ifndef MATHC_MAX_SIZE
#ifdef __STDC_NO_VLA__
#define MATHC_MAX_SIZE 16
#endif
#endif

#include <stdbool.h>
#include <math.h>
#include <assert.h>


/** macro to cast a vector into a double vector */
#define dvecN_cast_into(dst_vec, vec, n) \
do { \
    for(int dvecN_cast_into_i_=0; dvecN_cast_into_i_<(n); dvecN_cast_into_i_++) \
        (dst_vec)[dvecN_cast_into_i_] = (double) (vec)[dvecN_cast_into_i_]; \
} while(0)


/** dst = vec */
static void dvecN_copy(double *dst_vec, const double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec[i];
}

/** dst = scalar */
static void dvecN_set(double *dst_vec, double scalar, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = scalar;
}

/** dst = -vec */
static void dvecN_neg(double *dst_vec, const double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = -vec[i];
}

/** dst = a + b */
static void dvecN_add_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + vec_b[i];
}

/** dst = a + b */
static void dvecN_add(double *dst_vec, const double *vec_a, double scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] + scalar_b;
}

/** dst = a - b */
static void dvecN_sub_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - vec_b[i];
}

/** dst = a - b */
static void dvecN_sub(double *dst_vec, const double *vec_a, double scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] - scalar_b;
}

/** dst = a * b */
static void dvecN_scale_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * vec_b[i];
}

/** dst = a * b */
static void dvecN_scale(double *dst_vec, const double *vec_a, double scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * scalar_b;
}

/** dst = a / b */
static void dvecN_div_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / vec_b[i];
}

/** dst = a / b */
static void dvecN_div(double *dst_vec, const double *vec_a, double scalar_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] / scalar_b;
}

/** dst = a * M_PI / 180 */
static void dvecN_radians(double *dst_vec, const double *vec_deg, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_deg[i] * M_PI / 180.0;
}

/** dst = a * 180 / M_PI */
static void dvecN_degrees(double *dst_vec, const double *vec_rad, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_rad[i] * 180.0 / M_PI;
}

/** dst = sin(angle_rad) */
static void dvecN_sin(double *dst_vec, const double *vec_angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = sin(vec_angle_rad[i]);
}

/** dst = cos(angle_rad) */
static void dvecN_cos(double *dst_vec, const double *vec_angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = cos(vec_angle_rad[i]);
}

/** dst = tan(angle_rad) */
static void dvecN_tan(double *dst_vec, const double *vec_angle_rad, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = tan(vec_angle_rad[i]);
}

/** dst = asin(x) */
static void dvecN_asin(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = asin(vec_x[i]);
}

/** dst = acos(x) */
static void dvecN_acos(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = acos(vec_x[i]);
}

/** dst = atan(x) */
static void dvecN_atan(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = atan(vec_x[i]);
}

/** dst = atan2(y, x) */
static void dvecN_atan2(double *dst_vec, const double *vec_y, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = atan2(vec_y[i], vec_x[i]);
}

/** dst = pow(x, y) */
static void dvecN_pow(double *dst_vec, const double *vec_x, double y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = pow(vec_x[i], y);
}

/** dst = pow(x, y) */
static void dvecN_pow_vec(double *dst_vec, const double *vec_x, const double *vec_y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = pow(vec_x[i], vec_y[i]);
}

/** dst = exp(x) */
static void dvecN_exp(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = exp(vec_x[i]);
}

/** dst = log(x) */
static void dvecN_log(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = log(vec_x[i]);
}

/** dst = exp2(x) */
static void dvecN_exp2(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = exp2(vec_x[i]);
}

/** dst = log2(x) */
static void dvecN_log2(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = log2(vec_x[i]);
}

/** dst = sqrt(x) */
static void dvecN_sqrt(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = sqrt(vec_x[i]);
}

/** dst = 1 / sqrt(x) */
static void dvecN_inversesqrt(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = 1.0 / sqrt(vec_x[i]);
}

/** dst = abs(x) */
static void dvecN_abs(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = fabs(vec_x[i]);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static void dvecN_sign(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] > 0.0 ? 1.0 : (vec_x[i] < 0.0 ? -1.0 : 0.0);
}

/** dst = floor(x) */
static void dvecN_floor(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = floor(vec_x[i]);
}

/** dst = ceil(x) */
static void dvecN_ceil(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = ceil(vec_x[i]);
}

/** dst = x - floor(x) */
static void dvecN_fract(double *dst_vec, const double *vec_x, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] - floor(vec_x[i]);
}

/** dst = x - y * floor(x/y) */
static void dvecN_mod(double *dst_vec, const double *vec_x, double y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] - y * floor(vec_x[i] / y);
}

/** dst = x - y * floor(x/y) */
static void dvecN_mod_vec(double *dst_vec, const double *vec_x, const double *vec_y, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] - vec_y[i] * floor(vec_x[i] / vec_y[i]);
}

/** dst = a < b ? a : b */
static void dvecN_min(double *dst_vec, const double *vec_a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b ? vec_a[i] : b;
}

/** dst = a < b ? a : b */
static void dvecN_min_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = a > b ? a : b */
static void dvecN_max(double *dst_vec, const double *vec_a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b ? vec_a[i] : b;
}

/** dst = a > b ? a : b */
static void dvecN_max_vec(double *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i] ? vec_a[i] : vec_b[i];
}

/** dst = x < min ? min : (x > max ? max : x) */
static void dvecN_clamp(double *dst_vec, const double *vec_x, double min, double max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < min ? min : (vec_x[i] > max ? max : vec_x[i]);
}

/** dst = x < min ? min : (x > max ? max : x) */
static void dvecN_clamp_vec(double *dst_vec, const double *vec_x, const double *vec_min, const double *vec_max, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_min[i] ? vec_min[i] : (vec_x[i] > vec_max[i] ? vec_max[i] : vec_x[i]);
}

/** dst = a * (1-t) + b * t */
static void dvecN_mix(double *dst_vec, const double *vec_a, const double *vec_b, double t, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * (1.0 - t) + vec_b[i] * t;
}

/** dst = a * (1-t) + b * t */
static void dvecN_mix_vec(double *dst_vec, const double *vec_a, const double *vec_b, const double *vec_t, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] * (1.0 - vec_t[i]) + vec_b[i] * vec_t[i];
}

/** dst = x < edge ? 0 : 1 */
static void dvecN_step(double *dst_vec, const double *vec_x, double edge, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < edge ? 0.0 : 1.0;
}

/** dst = x < edge ? 0 : 1 */
static void dvecN_step_vec(double *dst_vec, const double *vec_x, const double *vec_edge, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_x[i] < vec_edge[i] ? 0.0 : 1.0;
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static void dvecN_smoothstep(double *dst_vec, const double *vec_x, double edge1, double edge2, int n) {
    for (int i = 0; i < n; i++) {
        double x = vec_x[i];
        dst_vec[i] = x < edge1 ? 0.0 : (x > edge2 ? 1.0 : x * x * (3.0 - 2.0 * x));
    }
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static void
dvecN_smoothstep_vec(double *dst_vec, const double *vec_x, const double *vec_edge1, const double *vec_edge2, int n) {
    for (int i = 0; i < n; i++) {
        double x = vec_x[i];
        dst_vec[i] = x < vec_edge1[i] ? 0.0 : (x > vec_edge2[i] ? 1.0 : x * x * (3.0 - 2.0 * x));
    }
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static double dvecN_sum(const double *vec, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec[i];
    return sum;
}

/** returns a dot b */
static double dvecN_dot(const double *vec_a, const double *vec_b, int n) {
    double dot = 0;
    for (int i = 0; i < n; i++)
        dot += vec_a[i] * vec_b[i];
    return dot;
}

/** returns ||vec||_2 */
static double dvecN_norm(const double *vec, int n) {
    return sqrt(dvecN_dot(vec, vec, n));
}

/** returns ||vec||_p */
static double dvecN_norm_p(const double *vec, double p, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += pow(fabs(vec[i]), p);
    }
    return pow(sum, 1.0 / p);
}

/** returns ||vec||_1 */
static double dvecN_norm_1(const double *vec, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += fabs(vec[i]);
    }
    return sum;
}

/** returns ||vec||_inf */
static double dvecN_norm_inf(const double *vec, int n) {
    double max = 0;
    for (int i = 0; i < n; i++) {
        if (max < fabs(vec[i]))
            max = fabs(vec[i]);
    }
    return max;
}

/** dst = vec / norm(vec) */
static void dvecN_normalize_unsafe(double *dst_vec, const double *vec, int n) {
    dvecN_scale(dst_vec, vec, 1.0 / dvecN_norm(vec, n), n);
}

/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static void dvecN_normalize(double *dst_vec, const double *vec, int n) {
    double norm = dvecN_norm(vec, n);
    dvecN_scale(dst_vec, vec, 1.0 / (norm > 0.0 ? norm : 1.0), n);
}

/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvecN_length(const double *vec, int n) {
    return dvecN_norm(vec, n);
}

/** returns norm(b-a) */
static double dvecN_distance(const double *vec_a, const double *vec_b, int n) {
#ifdef MATHC_MAX_SIZE
    assert(n <= MATHC_MAX_SIZE);
    double tmp[MATHC_MAX_SIZE];
#else
    double tmp[n];
#endif
    dvecN_sub_vec(tmp, vec_b, vec_a, n);
    return dvecN_norm(tmp, n);
}

/** dst = dot(I, Nref) < 0 ? N : -N */
static void dvecN_faceforward(double *dst_vec, const double *vec_N, const double *vec_I, const double *vec_Nref, int n) {
    if (dvecN_dot(vec_I, vec_Nref, n) < 0)
        dvecN_copy(dst_vec, vec_N, n);
    else
        dvecN_neg(dst_vec, vec_N, n);
}

/** dst = I - 2.0 * N * dot(N,I) */
static void dvecN_reflect(double *dst_vec, const double *vec_I, const double *vec_N, int n) {
    dvecN_scale(dst_vec, vec_N, 2.0 * dvecN_dot(vec_N, vec_I, n), n);
    dvecN_sub_vec(dst_vec, vec_I, dst_vec, n);
}

static void dvecN_refract(double *dst_vec, const double *vec_I, const double *vec_N, double eta, int n) {
    // implementation from example implementation: https://developer.download.nvidia.com/cg/refract.html
    dvecN_neg(dst_vec, vec_I, n);
    double cosi = dvecN_dot(dst_vec, vec_N, n);
    double cost2 = 1.0 - eta * eta * (1.0 - cosi * cosi);
    dvecN_scale(dst_vec, vec_N, eta * cosi - sqrt(fabs(cost2)), n);
    double t[3];
    dvecN_scale(t, vec_I, eta, n);
    dvecN_add_vec(t, t, dst_vec, n);
    dvecN_scale(dst_vec, t, cost2 > 0.0, n);
}

/** dst = a < b */
static void dvecN_less_than(bool *dst_vec, const double *vec_a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < b;
}

/** dst = a < b */
static void dvecN_less_than_vec(bool *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] < vec_b[i];
}

/** dst = a <= b */
static void dvecN_less_than_equal(bool *dst_vec, const double *vec_a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= b;
}

/** dst = a <= b */
static void dvecN_less_than_equal_vec(bool *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] <= vec_b[i];
}

/** dst = a > b */
static void dvecN_greater_than(bool *dst_vec, const double *vec_a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > b;
}

/** dst = a > b */
static void dvecN_greater_than_vec(bool *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] > vec_b[i];
}

/** dst = a >= b */
static void dvecN_greater_than_equal(bool *dst_vec, const double *vec_a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= b;
}

/** dst = a >= b */
static void dvecN_greater_than_equal_vec(bool *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] >= vec_b[i];
}

/** dst = a == b */
static void dvecN_equal(bool *dst_vec, const double *vec_a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == b;
}

/** dst = a == b */
static void dvecN_equal_vec(bool *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] == vec_b[i];
}

/** dst = a != b */
static void dvecN_not_equal(bool *dst_vec, const double *vec_a, double b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != b;
}

/** dst = a != b */
static void dvecN_not_equal_vec(bool *dst_vec, const double *vec_a, const double *vec_b, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = vec_a[i] != vec_b[i];
}

/** dst = a == b (+-eps) */
static void dvecN_equal_eps(bool *dst_vec, const double *vec_a, double b, double eps, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = fabs(vec_a[i] - b) <= eps;
}

/** dst = a == b (+-eps) */
static void dvecN_equal_eps_vec(bool *dst_vec, const double *vec_a, const double *vec_b, double eps, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = fabs(vec_a[i] - vec_b[i]) <= eps;
}

/** dst = a != b (+-eps) */
static void dvecN_not_equal_eps(bool *dst_vec, const double *vec_a, double b, double eps, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = fabs(vec_a[i] - b) > eps;
}

/** dst = a != b (+-eps) */
static void dvecN_not_equal_eps_vec(bool *dst_vec, const double *vec_a, const double *vec_b, double eps, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = fabs(vec_a[i] - vec_b[i]) > eps;
}

/** dst = isnan(vec) */
static void dvecN_isnan(bool *dst_vec, const double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = isnan(vec[i]);
}

/** dst = isnan(vec) */
static void dvecN_not_isnan(bool *dst_vec, const double *vec, int n) {
    for (int i = 0; i < n; i++)
        dst_vec[i] = !isnan(vec[i]);
}

#endif //MATHC_VEC_DVECN_H
