#ifndef M_VEC_DVEC4_H
#define M_VEC_DVEC4_H


#include "dvecn.h"
#include "../types/dvec4.h"
#include "../types/bvec4.h"


/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_float(const float *cast) {
    dvec4 res;
    dvecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_double(const double *cast) {
    dvec4 res;
    dvecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_int(const int *cast) {
    dvec4 res;
    dvecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_uchar(const unsigned char *cast) {
    dvec4 res;
    dvecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = v / 255 */
static dvec4 dvec4_cast_from_uchar_1(const unsigned char *cast) {
    dvec4 res;
    dvecN_cast_from_uchar_1(res.v, cast, 4);
    return res;
}




/** a == b */
static bool dvec4_cmp(dvec4 a, dvec4 b) {
    return dvecN_cmp(a.v, b.v, 4);
}


/** dst = s */
static dvec4 dvec4_set(double s) {
    dvec4 res;
    dvecN_set(res.v, s, 4);
    return res;
}

/** dst = v0, v1, ... */
static dvec4 dvec4_new(double v0, double v1
         , double v2
         , double v3
) {
    dvec4 self;
    self.v0 = v0;
    self.v1 = v1;
    self.v2 = v2;
    self.v3 = v3;
    return self;
}

/** dst = unit_x */
static dvec4 dvec4_unit_x() {
    dvec4 res;
    dvecN_unit_x(res.v, 4);
    return res;
}


/** dst = unit_y */
static dvec4 dvec4_unit_y() {
    dvec4 res;
    dvecN_unit_y(res.v, 4);
    return res;
}


/** dst = unit_z */
static dvec4 dvec4_unit_z() {
    dvec4 res;
    dvecN_unit_z(res.v, 4);
    return res;
}


/** dst = unit_w */
static dvec4 dvec4_unit_w() {
    dvec4 res;
    dvecN_unit_w(res.v, 4);
    return res;
}


/** dst = -v */
static dvec4 dvec4_neg(dvec4 v) {
    dvec4 res;
    dvecN_neg(res.v, v.v, 4);
    return res;
}


/** dst = a + b */
static dvec4 dvec4_add_vec(dvec4 a, dvec4 b) {
    dvec4 res;
    dvecN_add_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a + b */
static dvec4 dvec4_add(dvec4 a, double b) {
    dvec4 res;
    dvecN_add(res.v, a.v, b, 4);
    return res;
}


/** dst = a - b */
static dvec4 dvec4_sub_vec(dvec4 a, dvec4 b) {
    dvec4 res;
    dvecN_sub_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a - b */
static dvec4 dvec4_sub(dvec4 a, double b) {
    dvec4 res;
    dvecN_sub(res.v, a.v, b, 4);
    return res;
}


/** dst = a * b */
static dvec4 dvec4_scale_vec(dvec4 a, dvec4 b) {
    dvec4 res;
    dvecN_scale_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a * b */
static dvec4 dvec4_scale(dvec4 a, double b) {
    dvec4 res;
    dvecN_scale(res.v, a.v, b, 4);
    return res;
}


/** dst = a / b */
static dvec4 dvec4_div_vec(dvec4 a, dvec4 b) {
    dvec4 res;
    dvecN_div_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a / b */
static dvec4 dvec4_div(dvec4 a, double b) {
    dvec4 res;
    dvecN_div(res.v, a.v, b, 4);
    return res;
}


/** dst = a * M_PI / 180 */
static dvec4 dvec4_radians(dvec4 deg) {
    dvec4 res;
    dvecN_radians(res.v, deg.v, 4);
    return res;
}


/** dst = a * 180 / M_PI */
static dvec4 dvec4_degrees(dvec4 rad) {
    dvec4 res;
    dvecN_degrees(res.v, rad.v, 4);
    return res;
}


/** dst = sin(angle_rad) */
static dvec4 dvec4_sin(dvec4 angle_rad) {
    dvec4 res;
    dvecN_sin(res.v, angle_rad.v, 4);
    return res;
}


/** dst = cos(angle_rad) */
static dvec4 dvec4_cos(dvec4 angle_rad) {
    dvec4 res;
    dvecN_cos(res.v, angle_rad.v, 4);
    return res;
}


/** dst = tan(angle_rad) */
static dvec4 dvec4_tan(dvec4 angle_rad) {
    dvec4 res;
    dvecN_tan(res.v, angle_rad.v, 4);
    return res;
}


/** dst = asin(x) */
static dvec4 dvec4_asin(dvec4 x) {
    dvec4 res;
    dvecN_asin(res.v, x.v, 4);
    return res;
}


/** dst = acos(x) */
static dvec4 dvec4_acos(dvec4 x) {
    dvec4 res;
    dvecN_acos(res.v, x.v, 4);
    return res;
}


/** dst = atan(x) */
static dvec4 dvec4_atan(dvec4 x) {
    dvec4 res;
    dvecN_atan(res.v, x.v, 4);
    return res;
}


/** dst = atan2(y, x) */
static dvec4 dvec4_atan2(dvec4 y, dvec4 x) {
    dvec4 res;
    dvecN_atan2(res.v, y.v, x.v, 4);
    return res;
}


/** dst = pow(x, y) */
static dvec4 dvec4_pow(dvec4 x, double y) {
    dvec4 res;
    dvecN_pow(res.v, x.v, y, 4);
    return res;
}


/** dst = pow(x, y) */
static dvec4 dvec4_pow_vec(dvec4 x, dvec4 y) {
    dvec4 res;
    dvecN_pow_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = exp(x) */
static dvec4 dvec4_exp(dvec4 x) {
    dvec4 res;
    dvecN_exp(res.v, x.v, 4);
    return res;
}


/** dst = log(x) */
static dvec4 dvec4_log(dvec4 x) {
    dvec4 res;
    dvecN_log(res.v, x.v, 4);
    return res;
}


/** dst = exp2(x) */
static dvec4 dvec4_exp2(dvec4 x) {
    dvec4 res;
    dvecN_exp2(res.v, x.v, 4);
    return res;
}


/** dst = log2(x) */
static dvec4 dvec4_log2(dvec4 x) {
    dvec4 res;
    dvecN_log2(res.v, x.v, 4);
    return res;
}


/** dst = sqrt(x) */
static dvec4 dvec4_sqrt(dvec4 x) {
    dvec4 res;
    dvecN_sqrt(res.v, x.v, 4);
    return res;
}


/** dst = 1 / sqrt(x) */
static dvec4 dvec4_inversesqrt(dvec4 x) {
    dvec4 res;
    dvecN_inversesqrt(res.v, x.v, 4);
    return res;
}


/** dst = abs(x) */
static dvec4 dvec4_abs(dvec4 x) {
    dvec4 res;
    dvecN_abs(res.v, x.v, 4);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec4 dvec4_sign(dvec4 x) {
    dvec4 res;
    dvecN_sign(res.v, x.v, 4);
    return res;
}


/** dst = floor(x) */
static dvec4 dvec4_floor(dvec4 x) {
    dvec4 res;
    dvecN_floor(res.v, x.v, 4);
    return res;
}


/** dst = ceil(x) */
static dvec4 dvec4_ceil(dvec4 x) {
    dvec4 res;
    dvecN_ceil(res.v, x.v, 4);
    return res;
}


/** dst = x - floor(x) */
static dvec4 dvec4_fract(dvec4 x) {
    dvec4 res;
    dvecN_fract(res.v, x.v, 4);
    return res;
}


/** dst = x - y * floor(x/y) */
static dvec4 dvec4_mod(dvec4 x, double y) {
    dvec4 res;
    dvecN_mod(res.v, x.v, y, 4);
    return res;
}


/** dst = x - y * floor(x/y) */
static dvec4 dvec4_mod_vec(dvec4 x, dvec4 y) {
    dvec4 res;
    dvecN_mod_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = a < b ? a : b */
static dvec4 dvec4_min(dvec4 x, double y) {
    dvec4 res;
    dvecN_min(res.v, x.v, y, 4);
    return res;
}


/** dst = a < b ? a : b */
static dvec4 dvec4_min_vec(dvec4 x, dvec4 y) {
    dvec4 res;
    dvecN_min_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = a > b ? a : b */
static dvec4 dvec4_max(dvec4 x, double y) {
    dvec4 res;
    dvecN_max(res.v, x.v, y, 4);
    return res;
}


/** dst = a > b ? a : b */
static dvec4 dvec4_max_vec(dvec4 x, dvec4 y) {
    dvec4 res;
    dvecN_max_vec(res.v, x.v, y.v, 4);
    return res;
}


/** returns the index of the min v value */
static int dvec4_min_index(dvec4 vec) {
    return dvecN_min_index(vec.v, 4);
}


/** returns the index of the max v value */
static int dvec4_max_index(dvec4 vec) {
    return dvecN_max_index(vec.v, 4);
}

/** dst = x < min ? min : (x > max ? max : x) */
static dvec4 dvec4_clamp(dvec4 x, double min, double max) {
    dvec4 res;
    dvecN_clamp(res.v, x.v, min, max, 4);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec4 dvec4_clamp_vec(dvec4 x, dvec4 min, dvec4 max) {
    dvec4 res;
    dvecN_clamp_vec(res.v, x.v, min.v, max.v, 4);
    return res;
}


/** dst = a * (1-t) + b * t */
static dvec4 dvec4_mix(dvec4 a, dvec4 b, double t) {
    dvec4 res;
    dvecN_mix(res.v, a.v, b.v, t, 4);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static dvec4 dvec4_step(dvec4 x, double edge) {
    dvec4 res;
    dvecN_step(res.v, x.v, edge, 4);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static dvec4 dvec4_step_vec(dvec4 x, dvec4 edge) {
    dvec4 res;
    dvecN_step_vec(res.v, x.v, edge.v, 4);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec4 dvec4_smoothstep(dvec4 x, double edge1, double edge2) {
    dvec4 res;
    dvecN_smoothstep(res.v, x.v, edge1, edge2, 4);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec4 dvec4_smoothstep_vec(dvec4 x, dvec4 edge1, dvec4 edge2) {
    dvec4 res;
    dvecN_smoothstep_vec(res.v, x.v, edge1.v, edge2.v, 4);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static double dvec4_sum(dvec4 v) {
    return dvecN_sum(v.v, 4);
}


/** returns a dot b */
static double dvec4_dot(dvec4 a, dvec4 b) {
    return dvecN_dot(a.v, b.v, 4);
}


/** dst = a x b , dst.w... = 0 */
static dvec4 dvec4_cross(dvec4 a, dvec4 b) {
    dvec4 res;
    dvecN_cross(res.v, a.v, b.v, 4);
    return res;
}


/** returns ||v||_4 */
static double dvec4_norm(dvec4 v) {
    return dvecN_norm(v.v, 4);
}


/** returns ||v||_p */
static double dvec4_norm_p(dvec4 v, double p) {
    return dvecN_norm_p(v.v, p, 4);
}


/** returns ||v||_1 */
static double dvec4_norm_1(dvec4 v) {
    return dvecN_norm_1(v.v, 4);
}


/** returns ||v||_inf */
static double dvec4_norm_inf(dvec4 v) {
    return dvecN_norm_inf(v.v, 4);
}


/** dst = v / norm(v) */
static dvec4 dvec4_normalize_unsafe(dvec4 v) {
    dvec4 res;
    dvecN_normalize_unsafe(res.v, v.v, 4);
    return res;
}


/** dst = v / (norm(v) > 0 ? norm(v) : 1) */
static dvec4 dvec4_normalize(dvec4 v) {
    dvec4 res;
    dvecN_normalize(res.v, v.v, 4);
    return res;
}


/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec4_length(dvec4 v) {
    return dvecN_length(v.v, 4);
}


/** returns norm(b-a) */
static double dvec4_distance(dvec4 a, dvec4 b) {
    return dvecN_distance(a.v, b.v, 4);
}


/** returns dot(b-a) */
static double dvec4_sqr_distance(dvec4 a, dvec4 b) {
    return dvecN_sqr_distance(a.v, b.v, 4);
}


/** dst = dot(i, nref) < 0 ? N : -N */
static dvec4 dvec4_faceforward(dvec4 n, dvec4 i, dvec4 nref) {
    dvec4 res;
    dvecN_faceforward(res.v, n.v, i.v, nref.v, 4);
    return res;
}


/** dst = i - 2.0 * n * dot(n,i) */
static dvec4 dvec4_reflect(dvec4 i, dvec4 n) {
    dvec4 res;
    dvecN_reflect(res.v, i.v, n.v, 4);
    return res;
}


static dvec4 dvec4_refract(dvec4 i, dvec4 n, double eta) {
    dvec4 res;
    dvecN_refract(res.v, i.v, n.v, eta, 4);
    return res;
}


/** dst = a < b */
static bvec4 dvec4_less_than(dvec4 a, double b) {
    bvec4 res;
    dvecN_less_than(res.v, a.v, b, 4);
    return res;
}


/** dst = a < b */
static bvec4 dvec4_less_than_vec(dvec4 a, dvec4 b) {
    bvec4 res;
    dvecN_less_than_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a <= b */
static bvec4 dvec4_less_than_equal(dvec4 a, double b) {
    bvec4 res;
    dvecN_less_than_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a <= b */
static bvec4 dvec4_less_than_equal_vec(dvec4 a, dvec4 b) {
    bvec4 res;
    dvecN_less_than_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a > b */
static bvec4 dvec4_greater_than(dvec4 a, double b) {
    bvec4 res;
    dvecN_greater_than(res.v, a.v, b, 4);
    return res;
}


/** dst = a > b */
static bvec4 dvec4_greater_than_vec(dvec4 a, dvec4 b) {
    bvec4 res;
    dvecN_greater_than_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a >= b */
static bvec4 dvec4_greater_than_equal(dvec4 a, double b) {
    bvec4 res;
    dvecN_greater_than_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a >= b */
static bvec4 dvec4_greater_than_equal_vec(dvec4 a, dvec4 b) {
    bvec4 res;
    dvecN_greater_than_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a == b */
static bvec4 dvec4_equal(dvec4 a, double b) {
    bvec4 res;
    dvecN_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a == b */
static bvec4 dvec4_equal_vec(dvec4 a, dvec4 b) {
    bvec4 res;
    dvecN_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a != b */
static bvec4 dvec4_not_equal(dvec4 a, double b) {
    bvec4 res;
    dvecN_not_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a != b */
static bvec4 dvec4_not_equal_vec(dvec4 a, dvec4 b) {
    bvec4 res;
    dvecN_not_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a == b (+-eps) */
static bvec4 dvec4_equal_eps(dvec4 a, double b, double eps) {
    bvec4 res;
    dvecN_equal_eps(res.v, a.v, b, eps, 4);
    return res;
}


/** dst = a == b (+-eps) */
static bvec4 dvec4_equal_eps_vec(dvec4 a, dvec4 b, double eps) {
    bvec4 res;
    dvecN_equal_eps_vec(res.v, a.v, b.v, eps, 4);
    return res;
}


/** dst = a != b (+-eps) */
static bvec4 dvec4_not_equal_eps(dvec4 a, double b, double eps) {
    bvec4 res;
    dvecN_not_equal_eps(res.v, a.v, b, eps, 4);
    return res;
}


/** dst = a != b (+-eps) */
static bvec4 dvec4_not_equal_eps_vec(dvec4 a, dvec4 b, double eps) {
    bvec4 res;
    dvecN_not_equal_eps_vec(res.v, a.v, b.v, eps, 4);
    return res;
}


/** dst = isnan(v) */
static bvec4 dvec4_isnan(dvec4 v) {
    bvec4 res;
    dvecN_isnan(res.v, v.v, 4);
    return res;
}


/** dst = !isnan(v) */
static bvec4 dvec4_not_isnan(dvec4 v) {
    bvec4 res;
    dvecN_not_isnan(res.v, v.v, 4);
    return res;
}


/** dst = isinf(v) */
static bvec4 dvec4_isinf(dvec4 v) {
    bvec4 res;
    dvecN_isinf(res.v, v.v, 4);
    return res;
}


/** dst = !isinf(v) */
static bvec4 dvec4_not_isinf(dvec4 v) {
    bvec4 res;
    dvecN_not_isinf(res.v, v.v, 4);
    return res;
}

#endif //M_VEC_DVEC4_H
