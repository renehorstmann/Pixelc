#ifndef M_VEC_DVEC3_H
#define M_VEC_DVEC3_H


#include "dvecn.h"
#include "../types/dvec3.h"
#include "../types/bvec3.h"

// macro to create a dvec3
#define dvec3_(x, y \
, z\
) (dvec3) {{(x), (y)\
, (z)\
}}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_float(const float *cast) {
    dvec3 res;
    dvecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_double(const double *cast) {
    dvec3 res;
    dvecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_int(const int *cast) {
    dvec3 res;
    dvecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_uchar(const unsigned char *cast) {
    dvec3 res;
    dvecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = v / 255 */
static dvec3 dvec3_cast_from_uchar_1(const unsigned char *cast) {
    dvec3 res;
    dvecN_cast_from_uchar_1(res.v, cast, 3);
    return res;
}


/** a == b */
static bool dvec3_cmp(dvec3 a, dvec3 b) {
    return dvecN_cmp(a.v, b.v, 3);
}


/** dst = s */
static dvec3 dvec3_set(double s) {
    dvec3 res;
    dvecN_set(res.v, s, 3);
    return res;
}

/** dst = v0, v1, ... */
static dvec3 dvec3_new(double v0, double v1, double v2
) {
    dvec3 self;
    self.v0 = v0;
    self.v1 = v1;
    self.v2 = v2;
    return self;
}

/** dst = unit_x */
static dvec3 dvec3_unit_x() {
    dvec3 res;
    dvecN_unit_x(res.v, 3);
    return res;
}


/** dst = unit_y */
static dvec3 dvec3_unit_y() {
    dvec3 res;
    dvecN_unit_y(res.v, 3);
    return res;
}


/** dst = unit_z */
static dvec3 dvec3_unit_z() {
    dvec3 res;
    dvecN_unit_z(res.v, 3);
    return res;
}


/** dst = -v */
static dvec3 dvec3_neg(dvec3 v) {
    dvec3 res;
    dvecN_neg(res.v, v.v, 3);
    return res;
}


/** dst = a + b */
static dvec3 dvec3_add_vec(dvec3 a, dvec3 b) {
    dvec3 res;
    dvecN_add_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a + b */
static dvec3 dvec3_add(dvec3 a, double b) {
    dvec3 res;
    dvecN_add(res.v, a.v, b, 3);
    return res;
}


/** dst = a - b */
static dvec3 dvec3_sub_vec(dvec3 a, dvec3 b) {
    dvec3 res;
    dvecN_sub_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a - b */
static dvec3 dvec3_sub(dvec3 a, double b) {
    dvec3 res;
    dvecN_sub(res.v, a.v, b, 3);
    return res;
}


/** dst = a * b */
static dvec3 dvec3_scale_vec(dvec3 a, dvec3 b) {
    dvec3 res;
    dvecN_scale_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a * b */
static dvec3 dvec3_scale(dvec3 a, double b) {
    dvec3 res;
    dvecN_scale(res.v, a.v, b, 3);
    return res;
}


/** dst = a / b */
static dvec3 dvec3_div_vec(dvec3 a, dvec3 b) {
    dvec3 res;
    dvecN_div_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a / b */
static dvec3 dvec3_div(dvec3 a, double b) {
    dvec3 res;
    dvecN_div(res.v, a.v, b, 3);
    return res;
}

/** dst = a + b * c */
static dvec3 dvec3_add_scaled_vec(dvec3 a, dvec3 b, dvec3 c) {
    dvec3 res;
    dvecN_add_scaled_vec(res.v, a.v, b.v, c.v, 3);
    return res;
}

/** dst = a + b * c */
static dvec3 dvec3_add_scaled(dvec3 a, dvec3 b, double c) {
    dvec3 res;
    dvecN_add_scaled(res.v, a.v, b.v, c, 3);
    return res;
}


/** dst = a * M_PI / 180 */
static dvec3 dvec3_radians(dvec3 deg) {
    dvec3 res;
    dvecN_radians(res.v, deg.v, 3);
    return res;
}


/** dst = a * 180 / M_PI */
static dvec3 dvec3_degrees(dvec3 rad) {
    dvec3 res;
    dvecN_degrees(res.v, rad.v, 3);
    return res;
}


/** dst = sin(angle_rad) */
static dvec3 dvec3_sin(dvec3 angle_rad) {
    dvec3 res;
    dvecN_sin(res.v, angle_rad.v, 3);
    return res;
}


/** dst = cos(angle_rad) */
static dvec3 dvec3_cos(dvec3 angle_rad) {
    dvec3 res;
    dvecN_cos(res.v, angle_rad.v, 3);
    return res;
}


/** dst = tan(angle_rad) */
static dvec3 dvec3_tan(dvec3 angle_rad) {
    dvec3 res;
    dvecN_tan(res.v, angle_rad.v, 3);
    return res;
}


/** dst = asin(x) */
static dvec3 dvec3_asin(dvec3 x) {
    dvec3 res;
    dvecN_asin(res.v, x.v, 3);
    return res;
}


/** dst = acos(x) */
static dvec3 dvec3_acos(dvec3 x) {
    dvec3 res;
    dvecN_acos(res.v, x.v, 3);
    return res;
}


/** dst = atan(x) */
static dvec3 dvec3_atan(dvec3 x) {
    dvec3 res;
    dvecN_atan(res.v, x.v, 3);
    return res;
}


/** dst = atan2(y, x) */
static dvec3 dvec3_atan2(dvec3 y, dvec3 x) {
    dvec3 res;
    dvecN_atan2(res.v, y.v, x.v, 3);
    return res;
}


/** dst = pow(x, y) */
static dvec3 dvec3_pow(dvec3 x, double y) {
    dvec3 res;
    dvecN_pow(res.v, x.v, y, 3);
    return res;
}


/** dst = pow(x, y) */
static dvec3 dvec3_pow_vec(dvec3 x, dvec3 y) {
    dvec3 res;
    dvecN_pow_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = exp(x) */
static dvec3 dvec3_exp(dvec3 x) {
    dvec3 res;
    dvecN_exp(res.v, x.v, 3);
    return res;
}


/** dst = log(x) */
static dvec3 dvec3_log(dvec3 x) {
    dvec3 res;
    dvecN_log(res.v, x.v, 3);
    return res;
}


/** dst = exp2(x) */
static dvec3 dvec3_exp2(dvec3 x) {
    dvec3 res;
    dvecN_exp2(res.v, x.v, 3);
    return res;
}


/** dst = log2(x) */
static dvec3 dvec3_log2(dvec3 x) {
    dvec3 res;
    dvecN_log2(res.v, x.v, 3);
    return res;
}


/** dst = sqrt(x) */
static dvec3 dvec3_sqrt(dvec3 x) {
    dvec3 res;
    dvecN_sqrt(res.v, x.v, 3);
    return res;
}


/** dst = 1 / sqrt(x) */
static dvec3 dvec3_inversesqrt(dvec3 x) {
    dvec3 res;
    dvecN_inversesqrt(res.v, x.v, 3);
    return res;
}


/** dst = abs(x) */
static dvec3 dvec3_abs(dvec3 x) {
    dvec3 res;
    dvecN_abs(res.v, x.v, 3);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec3 dvec3_sign(dvec3 x) {
    dvec3 res;
    dvecN_sign(res.v, x.v, 3);
    return res;
}


/** dst = floor(x) */
static dvec3 dvec3_floor(dvec3 x) {
    dvec3 res;
    dvecN_floor(res.v, x.v, 3);
    return res;
}


/** dst = ceil(x) */
static dvec3 dvec3_ceil(dvec3 x) {
    dvec3 res;
    dvecN_ceil(res.v, x.v, 3);
    return res;
}


/** dst = x - floor(x) */
static dvec3 dvec3_fract(dvec3 x) {
    dvec3 res;
    dvecN_fract(res.v, x.v, 3);
    return res;
}


/** dst = x - y * floor(x/y) */
static dvec3 dvec3_mod(dvec3 x, double y) {
    dvec3 res;
    dvecN_mod(res.v, x.v, y, 3);
    return res;
}


/** dst = x - y * floor(x/y) */
static dvec3 dvec3_mod_vec(dvec3 x, dvec3 y) {
    dvec3 res;
    dvecN_mod_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = a < b ? a : b */
static dvec3 dvec3_min(dvec3 x, double y) {
    dvec3 res;
    dvecN_min(res.v, x.v, y, 3);
    return res;
}


/** dst = a < b ? a : b */
static dvec3 dvec3_min_vec(dvec3 x, dvec3 y) {
    dvec3 res;
    dvecN_min_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = a > b ? a : b */
static dvec3 dvec3_max(dvec3 x, double y) {
    dvec3 res;
    dvecN_max(res.v, x.v, y, 3);
    return res;
}


/** dst = a > b ? a : b */
static dvec3 dvec3_max_vec(dvec3 x, dvec3 y) {
    dvec3 res;
    dvecN_max_vec(res.v, x.v, y.v, 3);
    return res;
}


/** returns the index of the min v value */
static int dvec3_min_index(dvec3 vec) {
    return dvecN_min_index(vec.v, 3);
}


/** returns the index of the max v value */
static int dvec3_max_index(dvec3 vec) {
    return dvecN_max_index(vec.v, 3);
}

/** dst = x < min ? min : (x > max ? max : x) */
static dvec3 dvec3_clamp(dvec3 x, double min, double max) {
    dvec3 res;
    dvecN_clamp(res.v, x.v, min, max, 3);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec3 dvec3_clamp_vec(dvec3 x, dvec3 min, dvec3 max) {
    dvec3 res;
    dvecN_clamp_vec(res.v, x.v, min.v, max.v, 3);
    return res;
}


/** dst = a * (1-t) + b * t */
static dvec3 dvec3_mix(dvec3 a, dvec3 b, float t) {
    dvec3 res;
    dvecN_mix(res.v, a.v, b.v, t, 3);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static dvec3 dvec3_step(dvec3 x, double edge) {
    dvec3 res;
    dvecN_step(res.v, x.v, edge, 3);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static dvec3 dvec3_step_vec(dvec3 x, dvec3 edge) {
    dvec3 res;
    dvecN_step_vec(res.v, x.v, edge.v, 3);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec3 dvec3_smoothstep(dvec3 x, double edge1, double edge2) {
    dvec3 res;
    dvecN_smoothstep(res.v, x.v, edge1, edge2, 3);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec3 dvec3_smoothstep_vec(dvec3 x, dvec3 edge1, dvec3 edge2) {
    dvec3 res;
    dvecN_smoothstep_vec(res.v, x.v, edge1.v, edge2.v, 3);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static double dvec3_sum(dvec3 v) {
    return dvecN_sum(v.v, 3);
}


/** returns a dot b */
static double dvec3_dot(dvec3 a, dvec3 b) {
    return dvecN_dot(a.v, b.v, 3);
}


/** dst = a x b , dst.w... = 0 */
static dvec3 dvec3_cross(dvec3 a, dvec3 b) {
    dvec3 res;
    dvecN_cross(res.v, a.v, b.v, 3);
    return res;
}


/** returns ||v||_3 */
static double dvec3_norm(dvec3 v) {
    return dvecN_norm(v.v, 3);
}


/** returns ||v||_p */
static double dvec3_norm_p(dvec3 v, double p) {
    return dvecN_norm_p(v.v, p, 3);
}


/** returns ||v||_1 */
static double dvec3_norm_1(dvec3 v) {
    return dvecN_norm_1(v.v, 3);
}


/** returns ||v||_inf */
static double dvec3_norm_inf(dvec3 v) {
    return dvecN_norm_inf(v.v, 3);
}


/** dst = v / norm(v) */
static dvec3 dvec3_normalize_unsafe(dvec3 v) {
    dvec3 res;
    dvecN_normalize_unsafe(res.v, v.v, 3);
    return res;
}


/** dst = v / (norm(v) > 0 ? norm(v) : 1) */
static dvec3 dvec3_normalize(dvec3 v) {
    dvec3 res;
    dvecN_normalize(res.v, v.v, 3);
    return res;
}

/** dst = normalize(cross(a, b)) */
static dvec3 dvec3_cross_normalized(dvec3 a, dvec3 b) {
    dvec3 res;
    dvecN_cross_normalized(res.v, a.v, b.v, 3);
    return res;
}


/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec3_length(dvec3 v) {
    return dvecN_length(v.v, 3);
}


/** returns norm(b-a) */
static double dvec3_distance(dvec3 a, dvec3 b) {
    return dvecN_distance(a.v, b.v, 3);
}


/** returns dot(b-a) */
static double dvec3_sqr_distance(dvec3 a, dvec3 b) {
    return dvecN_sqr_distance(a.v, b.v, 3);
}


/** dst = dot(i, nref) < 0 ? N : -N */
static dvec3 dvec3_faceforward(dvec3 n, dvec3 i, dvec3 nref) {
    dvec3 res;
    dvecN_faceforward(res.v, n.v, i.v, nref.v, 3);
    return res;
}


/** dst = i - 2.0 * n * dot(n,i) */
static dvec3 dvec3_reflect(dvec3 i, dvec3 n) {
    dvec3 res;
    dvecN_reflect(res.v, i.v, n.v, 3);
    return res;
}


static dvec3 dvec3_refract(dvec3 i, dvec3 n, double eta) {
    dvec3 res;
    dvecN_refract(res.v, i.v, n.v, eta, 3);
    return res;
}


/** dst = a < b */
static bvec3 dvec3_less_than(dvec3 a, double b) {
    bvec3 res;
    dvecN_less_than(res.v, a.v, b, 3);
    return res;
}


/** dst = a < b */
static bvec3 dvec3_less_than_vec(dvec3 a, dvec3 b) {
    bvec3 res;
    dvecN_less_than_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a <= b */
static bvec3 dvec3_less_than_equal(dvec3 a, double b) {
    bvec3 res;
    dvecN_less_than_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a <= b */
static bvec3 dvec3_less_than_equal_vec(dvec3 a, dvec3 b) {
    bvec3 res;
    dvecN_less_than_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a > b */
static bvec3 dvec3_greater_than(dvec3 a, double b) {
    bvec3 res;
    dvecN_greater_than(res.v, a.v, b, 3);
    return res;
}


/** dst = a > b */
static bvec3 dvec3_greater_than_vec(dvec3 a, dvec3 b) {
    bvec3 res;
    dvecN_greater_than_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a >= b */
static bvec3 dvec3_greater_than_equal(dvec3 a, double b) {
    bvec3 res;
    dvecN_greater_than_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a >= b */
static bvec3 dvec3_greater_than_equal_vec(dvec3 a, dvec3 b) {
    bvec3 res;
    dvecN_greater_than_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a == b */
static bvec3 dvec3_equal(dvec3 a, double b) {
    bvec3 res;
    dvecN_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a == b */
static bvec3 dvec3_equal_vec(dvec3 a, dvec3 b) {
    bvec3 res;
    dvecN_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a != b */
static bvec3 dvec3_not_equal(dvec3 a, double b) {
    bvec3 res;
    dvecN_not_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a != b */
static bvec3 dvec3_not_equal_vec(dvec3 a, dvec3 b) {
    bvec3 res;
    dvecN_not_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a == b (+-eps) */
static bvec3 dvec3_equal_eps(dvec3 a, double b, double eps) {
    bvec3 res;
    dvecN_equal_eps(res.v, a.v, b, eps, 3);
    return res;
}


/** dst = a == b (+-eps) */
static bvec3 dvec3_equal_eps_vec(dvec3 a, dvec3 b, double eps) {
    bvec3 res;
    dvecN_equal_eps_vec(res.v, a.v, b.v, eps, 3);
    return res;
}


/** dst = a != b (+-eps) */
static bvec3 dvec3_not_equal_eps(dvec3 a, double b, double eps) {
    bvec3 res;
    dvecN_not_equal_eps(res.v, a.v, b, eps, 3);
    return res;
}


/** dst = a != b (+-eps) */
static bvec3 dvec3_not_equal_eps_vec(dvec3 a, dvec3 b, double eps) {
    bvec3 res;
    dvecN_not_equal_eps_vec(res.v, a.v, b.v, eps, 3);
    return res;
}


/** dst = isnan(v) */
static bvec3 dvec3_isnan(dvec3 v) {
    bvec3 res;
    dvecN_isnan(res.v, v.v, 3);
    return res;
}


/** dst = !isnan(v) */
static bvec3 dvec3_not_isnan(dvec3 v) {
    bvec3 res;
    dvecN_not_isnan(res.v, v.v, 3);
    return res;
}


/** dst = isinf(v) */
static bvec3 dvec3_isinf(dvec3 v) {
    bvec3 res;
    dvecN_isinf(res.v, v.v, 3);
    return res;
}


/** dst = !isinf(v) */
static bvec3 dvec3_not_isinf(dvec3 v) {
    bvec3 res;
    dvecN_not_isinf(res.v, v.v, 3);
    return res;
}

#endif //M_VEC_DVEC3_H
