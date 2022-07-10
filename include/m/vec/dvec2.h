#ifndef M_VEC_DVEC2_H
#define M_VEC_DVEC2_H


#include "dvecn.h"
#include "../types/dvec2.h"
#include "../types/bvec2.h"


/** dst = (dvec2) v */
static dvec2 dvec2_cast_from_float(const float *cast) {
    dvec2 res;
    dvecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (dvec2) v */
static dvec2 dvec2_cast_from_double(const double *cast) {
    dvec2 res;
    dvecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (dvec2) v */
static dvec2 dvec2_cast_from_int(const int *cast) {
    dvec2 res;
    dvecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (dvec2) v */
static dvec2 dvec2_cast_from_uchar(const unsigned char *cast) {
    dvec2 res;
    dvecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = v / 255 */
static dvec2 dvec2_cast_from_uchar_1(const unsigned char *cast) {
    dvec2 res;
    dvecN_cast_from_uchar_1(res.v, cast, 2);
    return res;
}


/** a == b */
static bool dvec2_cmp(dvec2 a, dvec2 b) {
    return dvecN_cmp(a.v, b.v, 2);
}


/** dst = s */
static dvec2 dvec2_set(double s) {
    dvec2 res;
    dvecN_set(res.v, s, 2);
    return res;
}


/** dst = v0, v1, ... */
static dvec2 dvec2_new(double v0, double v1
) {
    return (dvec2) {v0, v1
    };
}

/** dst = unit_x */
static dvec2 dvec2_unit_x() {
    dvec2 res;
    dvecN_unit_x(res.v, 2);
    return res;
}


/** dst = unit_y */
static dvec2 dvec2_unit_y() {
    dvec2 res;
    dvecN_unit_y(res.v, 2);
    return res;
}


/** dst = -v */
static dvec2 dvec2_neg(dvec2 v) {
    dvec2 res;
    dvecN_neg(res.v, v.v, 2);
    return res;
}


/** dst = a + b */
static dvec2 dvec2_add_vec(dvec2 a, dvec2 b) {
    dvec2 res;
    dvecN_add_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a + b */
static dvec2 dvec2_add(dvec2 a, double b) {
    dvec2 res;
    dvecN_add(res.v, a.v, b, 2);
    return res;
}


/** dst = a - b */
static dvec2 dvec2_sub_vec(dvec2 a, dvec2 b) {
    dvec2 res;
    dvecN_sub_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a - b */
static dvec2 dvec2_sub(dvec2 a, double b) {
    dvec2 res;
    dvecN_sub(res.v, a.v, b, 2);
    return res;
}


/** dst = a * b */
static dvec2 dvec2_scale_vec(dvec2 a, dvec2 b) {
    dvec2 res;
    dvecN_scale_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a * b */
static dvec2 dvec2_scale(dvec2 a, double b) {
    dvec2 res;
    dvecN_scale(res.v, a.v, b, 2);
    return res;
}


/** dst = a / b */
static dvec2 dvec2_div_vec(dvec2 a, dvec2 b) {
    dvec2 res;
    dvecN_div_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a / b */
static dvec2 dvec2_div(dvec2 a, double b) {
    dvec2 res;
    dvecN_div(res.v, a.v, b, 2);
    return res;
}


/** dst = a * M_PI / 180 */
static dvec2 dvec2_radians(dvec2 deg) {
    dvec2 res;
    dvecN_radians(res.v, deg.v, 2);
    return res;
}


/** dst = a * 180 / M_PI */
static dvec2 dvec2_degrees(dvec2 rad) {
    dvec2 res;
    dvecN_degrees(res.v, rad.v, 2);
    return res;
}


/** dst = sin(angle_rad) */
static dvec2 dvec2_sin(dvec2 angle_rad) {
    dvec2 res;
    dvecN_sin(res.v, angle_rad.v, 2);
    return res;
}


/** dst = cos(angle_rad) */
static dvec2 dvec2_cos(dvec2 angle_rad) {
    dvec2 res;
    dvecN_cos(res.v, angle_rad.v, 2);
    return res;
}


/** dst = tan(angle_rad) */
static dvec2 dvec2_tan(dvec2 angle_rad) {
    dvec2 res;
    dvecN_tan(res.v, angle_rad.v, 2);
    return res;
}


/** dst = asin(x) */
static dvec2 dvec2_asin(dvec2 x) {
    dvec2 res;
    dvecN_asin(res.v, x.v, 2);
    return res;
}


/** dst = acos(x) */
static dvec2 dvec2_acos(dvec2 x) {
    dvec2 res;
    dvecN_acos(res.v, x.v, 2);
    return res;
}


/** dst = atan(x) */
static dvec2 dvec2_atan(dvec2 x) {
    dvec2 res;
    dvecN_atan(res.v, x.v, 2);
    return res;
}


/** dst = atan2(y, x) */
static dvec2 dvec2_atan2(dvec2 y, dvec2 x) {
    dvec2 res;
    dvecN_atan2(res.v, y.v, x.v, 2);
    return res;
}


/** dst = pow(x, y) */
static dvec2 dvec2_pow(dvec2 x, double y) {
    dvec2 res;
    dvecN_pow(res.v, x.v, y, 2);
    return res;
}


/** dst = pow(x, y) */
static dvec2 dvec2_pow_vec(dvec2 x, dvec2 y) {
    dvec2 res;
    dvecN_pow_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = exp(x) */
static dvec2 dvec2_exp(dvec2 x) {
    dvec2 res;
    dvecN_exp(res.v, x.v, 2);
    return res;
}


/** dst = log(x) */
static dvec2 dvec2_log(dvec2 x) {
    dvec2 res;
    dvecN_log(res.v, x.v, 2);
    return res;
}


/** dst = exp2(x) */
static dvec2 dvec2_exp2(dvec2 x) {
    dvec2 res;
    dvecN_exp2(res.v, x.v, 2);
    return res;
}


/** dst = log2(x) */
static dvec2 dvec2_log2(dvec2 x) {
    dvec2 res;
    dvecN_log2(res.v, x.v, 2);
    return res;
}


/** dst = sqrt(x) */
static dvec2 dvec2_sqrt(dvec2 x) {
    dvec2 res;
    dvecN_sqrt(res.v, x.v, 2);
    return res;
}


/** dst = 1 / sqrt(x) */
static dvec2 dvec2_inversesqrt(dvec2 x) {
    dvec2 res;
    dvecN_inversesqrt(res.v, x.v, 2);
    return res;
}


/** dst = abs(x) */
static dvec2 dvec2_abs(dvec2 x) {
    dvec2 res;
    dvecN_abs(res.v, x.v, 2);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec2 dvec2_sign(dvec2 x) {
    dvec2 res;
    dvecN_sign(res.v, x.v, 2);
    return res;
}


/** dst = floor(x) */
static dvec2 dvec2_floor(dvec2 x) {
    dvec2 res;
    dvecN_floor(res.v, x.v, 2);
    return res;
}


/** dst = ceil(x) */
static dvec2 dvec2_ceil(dvec2 x) {
    dvec2 res;
    dvecN_ceil(res.v, x.v, 2);
    return res;
}


/** dst = x - floor(x) */
static dvec2 dvec2_fract(dvec2 x) {
    dvec2 res;
    dvecN_fract(res.v, x.v, 2);
    return res;
}


/** dst = x - y * floor(x/y) */
static dvec2 dvec2_mod(dvec2 x, double y) {
    dvec2 res;
    dvecN_mod(res.v, x.v, y, 2);
    return res;
}


/** dst = x - y * floor(x/y) */
static dvec2 dvec2_mod_vec(dvec2 x, dvec2 y) {
    dvec2 res;
    dvecN_mod_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = a < b ? a : b */
static dvec2 dvec2_min(dvec2 x, double y) {
    dvec2 res;
    dvecN_min(res.v, x.v, y, 2);
    return res;
}


/** dst = a < b ? a : b */
static dvec2 dvec2_min_vec(dvec2 x, dvec2 y) {
    dvec2 res;
    dvecN_min_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = a > b ? a : b */
static dvec2 dvec2_max(dvec2 x, double y) {
    dvec2 res;
    dvecN_max(res.v, x.v, y, 2);
    return res;
}


/** dst = a > b ? a : b */
static dvec2 dvec2_max_vec(dvec2 x, dvec2 y) {
    dvec2 res;
    dvecN_max_vec(res.v, x.v, y.v, 2);
    return res;
}


/** returns the index of the min v value */
static int dvec2_min_index(dvec2 vec) {
    return dvecN_min_index(vec.v, 2);
}


/** returns the index of the max v value */
static int dvec2_max_index(dvec2 vec) {
    return dvecN_max_index(vec.v, 2);
}

/** dst = x < min ? min : (x > max ? max : x) */
static dvec2 dvec2_clamp(dvec2 x, double min, double max) {
    dvec2 res;
    dvecN_clamp(res.v, x.v, min, max, 2);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec2 dvec2_clamp_vec(dvec2 x, dvec2 min, dvec2 max) {
    dvec2 res;
    dvecN_clamp_vec(res.v, x.v, min.v, max.v, 2);
    return res;
}


/** dst = a * (1-t) + b * t */
static dvec2 dvec2_mix(dvec2 a, dvec2 b, float t) {
    dvec2 res;
    dvecN_mix(res.v, a.v, b.v, t, 2);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static dvec2 dvec2_step(dvec2 x, double edge) {
    dvec2 res;
    dvecN_step(res.v, x.v, edge, 2);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static dvec2 dvec2_step_vec(dvec2 x, dvec2 edge) {
    dvec2 res;
    dvecN_step_vec(res.v, x.v, edge.v, 2);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec2 dvec2_smoothstep(dvec2 x, double edge1, double edge2) {
    dvec2 res;
    dvecN_smoothstep(res.v, x.v, edge1, edge2, 2);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec2 dvec2_smoothstep_vec(dvec2 x, dvec2 edge1, dvec2 edge2) {
    dvec2 res;
    dvecN_smoothstep_vec(res.v, x.v, edge1.v, edge2.v, 2);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static double dvec2_sum(dvec2 v) {
    return dvecN_sum(v.v, 2);
}


/** returns a dot b */
static double dvec2_dot(dvec2 a, dvec2 b) {
    return dvecN_dot(a.v, b.v, 2);
}


/** dst = a x b , dst.w... = 0 */
static dvec2 dvec2_cross(dvec2 a, dvec2 b) {
    dvec2 res;
    dvecN_cross(res.v, a.v, b.v, 2);
    return res;
}


/** returns ||v||_2 */
static double dvec2_norm(dvec2 v) {
    return dvecN_norm(v.v, 2);
}


/** returns ||v||_p */
static double dvec2_norm_p(dvec2 v, double p) {
    return dvecN_norm_p(v.v, p, 2);
}


/** returns ||v||_1 */
static double dvec2_norm_1(dvec2 v) {
    return dvecN_norm_1(v.v, 2);
}


/** returns ||v||_inf */
static double dvec2_norm_inf(dvec2 v) {
    return dvecN_norm_inf(v.v, 2);
}


/** dst = v / norm(v) */
static dvec2 dvec2_normalize_unsafe(dvec2 v) {
    dvec2 res;
    dvecN_normalize_unsafe(res.v, v.v, 2);
    return res;
}


/** dst = v / (norm(v) > 0 ? norm(v) : 1) */
static dvec2 dvec2_normalize(dvec2 v) {
    dvec2 res;
    dvecN_normalize(res.v, v.v, 2);
    return res;
}


/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec2_length(dvec2 v) {
    return dvecN_length(v.v, 2);
}


/** returns norm(b-a) */
static double dvec2_distance(dvec2 a, dvec2 b) {
    return dvecN_distance(a.v, b.v, 2);
}


/** returns dot(b-a) */
static double dvec2_sqr_distance(dvec2 a, dvec2 b) {
    return dvecN_sqr_distance(a.v, b.v, 2);
}


/** dst = dot(i, nref) < 0 ? N : -N */
static dvec2 dvec2_faceforward(dvec2 n, dvec2 i, dvec2 nref) {
    dvec2 res;
    dvecN_faceforward(res.v, n.v, i.v, nref.v, 2);
    return res;
}


/** dst = i - 2.0 * n * dot(n,i) */
static dvec2 dvec2_reflect(dvec2 i, dvec2 n) {
    dvec2 res;
    dvecN_reflect(res.v, i.v, n.v, 2);
    return res;
}


static dvec2 dvec2_refract(dvec2 i, dvec2 n, double eta) {
    dvec2 res;
    dvecN_refract(res.v, i.v, n.v, eta, 2);
    return res;
}


/** dst = a < b */
static bvec2 dvec2_less_than(dvec2 a, double b) {
    bvec2 res;
    dvecN_less_than(res.v, a.v, b, 2);
    return res;
}


/** dst = a < b */
static bvec2 dvec2_less_than_vec(dvec2 a, dvec2 b) {
    bvec2 res;
    dvecN_less_than_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a <= b */
static bvec2 dvec2_less_than_equal(dvec2 a, double b) {
    bvec2 res;
    dvecN_less_than_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a <= b */
static bvec2 dvec2_less_than_equal_vec(dvec2 a, dvec2 b) {
    bvec2 res;
    dvecN_less_than_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a > b */
static bvec2 dvec2_greater_than(dvec2 a, double b) {
    bvec2 res;
    dvecN_greater_than(res.v, a.v, b, 2);
    return res;
}


/** dst = a > b */
static bvec2 dvec2_greater_than_vec(dvec2 a, dvec2 b) {
    bvec2 res;
    dvecN_greater_than_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a >= b */
static bvec2 dvec2_greater_than_equal(dvec2 a, double b) {
    bvec2 res;
    dvecN_greater_than_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a >= b */
static bvec2 dvec2_greater_than_equal_vec(dvec2 a, dvec2 b) {
    bvec2 res;
    dvecN_greater_than_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a == b */
static bvec2 dvec2_equal(dvec2 a, double b) {
    bvec2 res;
    dvecN_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a == b */
static bvec2 dvec2_equal_vec(dvec2 a, dvec2 b) {
    bvec2 res;
    dvecN_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a != b */
static bvec2 dvec2_not_equal(dvec2 a, double b) {
    bvec2 res;
    dvecN_not_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a != b */
static bvec2 dvec2_not_equal_vec(dvec2 a, dvec2 b) {
    bvec2 res;
    dvecN_not_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a == b (+-eps) */
static bvec2 dvec2_equal_eps(dvec2 a, double b, double eps) {
    bvec2 res;
    dvecN_equal_eps(res.v, a.v, b, eps, 2);
    return res;
}


/** dst = a == b (+-eps) */
static bvec2 dvec2_equal_eps_vec(dvec2 a, dvec2 b, double eps) {
    bvec2 res;
    dvecN_equal_eps_vec(res.v, a.v, b.v, eps, 2);
    return res;
}


/** dst = a != b (+-eps) */
static bvec2 dvec2_not_equal_eps(dvec2 a, double b, double eps) {
    bvec2 res;
    dvecN_not_equal_eps(res.v, a.v, b, eps, 2);
    return res;
}


/** dst = a != b (+-eps) */
static bvec2 dvec2_not_equal_eps_vec(dvec2 a, dvec2 b, double eps) {
    bvec2 res;
    dvecN_not_equal_eps_vec(res.v, a.v, b.v, eps, 2);
    return res;
}


/** dst = isnan(v) */
static bvec2 dvec2_isnan(dvec2 v) {
    bvec2 res;
    dvecN_isnan(res.v, v.v, 2);
    return res;
}


/** dst = !isnan(v) */
static bvec2 dvec2_not_isnan(dvec2 v) {
    bvec2 res;
    dvecN_not_isnan(res.v, v.v, 2);
    return res;
}


/** dst = isinf(v) */
static bvec2 dvec2_isinf(dvec2 v) {
    bvec2 res;
    dvecN_isinf(res.v, v.v, 2);
    return res;
}


/** dst = !isinf(v) */
static bvec2 dvec2_not_isinf(dvec2 v) {
    bvec2 res;
    dvecN_not_isinf(res.v, v.v, 2);
    return res;
}

#endif //M_VEC_DVEC2_H
