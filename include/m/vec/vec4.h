#ifndef M_VEC_VEC4_H
#define M_VEC_VEC4_H


#include "vecn.h"
#include "../types/vec4.h"
#include "../types/bvec4.h"


/** dst = (vec4) v */
static vec4 vec4_cast_from_float(const float *cast) {
    vec4 res;
    vecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_double(const double *cast) {
    vec4 res;
    vecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_int(const int *cast) {
    vec4 res;
    vecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_uchar(const unsigned char *cast) {
    vec4 res;
    vecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = v / 255 */
static vec4 vec4_cast_from_uchar_1(const unsigned char *cast) {
    vec4 res;
    vecN_cast_from_uchar_1(res.v, cast, 4);
    return res;
}


/** a == b */
static bool vec4_cmp(vec4 a, vec4 b) {
    return vecN_cmp(a.v, b.v, 4);
}


/** dst = s */
static vec4 vec4_set(float s) {
    vec4 res;
    vecN_set(res.v, s, 4);
    return res;
}

/** dst = v0, v1, ... */
static vec4 vec4_new(float v0, float v1, float v2, float v3
) {
    vec4 self;
    self.v0 = v0;
    self.v1 = v1;
    self.v2 = v2;
    self.v3 = v3;
    return self;
}

/** dst = unit_x */
static vec4 vec4_unit_x() {
    vec4 res;
    vecN_unit_x(res.v, 4);
    return res;
}


/** dst = unit_y */
static vec4 vec4_unit_y() {
    vec4 res;
    vecN_unit_y(res.v, 4);
    return res;
}


/** dst = unit_z */
static vec4 vec4_unit_z() {
    vec4 res;
    vecN_unit_z(res.v, 4);
    return res;
}


/** dst = unit_w */
static vec4 vec4_unit_w() {
    vec4 res;
    vecN_unit_w(res.v, 4);
    return res;
}


/** dst = -v */
static vec4 vec4_neg(vec4 v) {
    vec4 res;
    vecN_neg(res.v, v.v, 4);
    return res;
}


/** dst = a + b */
static vec4 vec4_add_vec(vec4 a, vec4 b) {
    vec4 res;
    vecN_add_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a + b */
static vec4 vec4_add(vec4 a, float b) {
    vec4 res;
    vecN_add(res.v, a.v, b, 4);
    return res;
}


/** dst = a - b */
static vec4 vec4_sub_vec(vec4 a, vec4 b) {
    vec4 res;
    vecN_sub_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a - b */
static vec4 vec4_sub(vec4 a, float b) {
    vec4 res;
    vecN_sub(res.v, a.v, b, 4);
    return res;
}


/** dst = a * b */
static vec4 vec4_scale_vec(vec4 a, vec4 b) {
    vec4 res;
    vecN_scale_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a * b */
static vec4 vec4_scale(vec4 a, float b) {
    vec4 res;
    vecN_scale(res.v, a.v, b, 4);
    return res;
}


/** dst = a / b */
static vec4 vec4_div_vec(vec4 a, vec4 b) {
    vec4 res;
    vecN_div_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a / b */
static vec4 vec4_div(vec4 a, float b) {
    vec4 res;
    vecN_div(res.v, a.v, b, 4);
    return res;
}

/** dst = a + b * c */
static vec4 vec4_add_scaled_vec(vec4 a, vec4 b, vec4 c) {
    vec4 res;
    vecN_add_scaled_vec(res.v, a.v, b.v, c.v, 4);
    return res;
}

/** dst = a + b * c */
static vec4 vec4_add_scaled(vec4 a, vec4 b, float c) {
    vec4 res;
    vecN_add_scaled(res.v, a.v, b.v, c, 4);
    return res;
}


/** dst = a * M_PI / 180 */
static vec4 vec4_radians(vec4 deg) {
    vec4 res;
    vecN_radians(res.v, deg.v, 4);
    return res;
}


/** dst = a * 180 / M_PI */
static vec4 vec4_degrees(vec4 rad) {
    vec4 res;
    vecN_degrees(res.v, rad.v, 4);
    return res;
}


/** dst = sin(angle_rad) */
static vec4 vec4_sin(vec4 angle_rad) {
    vec4 res;
    vecN_sin(res.v, angle_rad.v, 4);
    return res;
}


/** dst = cos(angle_rad) */
static vec4 vec4_cos(vec4 angle_rad) {
    vec4 res;
    vecN_cos(res.v, angle_rad.v, 4);
    return res;
}


/** dst = tan(angle_rad) */
static vec4 vec4_tan(vec4 angle_rad) {
    vec4 res;
    vecN_tan(res.v, angle_rad.v, 4);
    return res;
}


/** dst = asin(x) */
static vec4 vec4_asin(vec4 x) {
    vec4 res;
    vecN_asin(res.v, x.v, 4);
    return res;
}


/** dst = acos(x) */
static vec4 vec4_acos(vec4 x) {
    vec4 res;
    vecN_acos(res.v, x.v, 4);
    return res;
}


/** dst = atan(x) */
static vec4 vec4_atan(vec4 x) {
    vec4 res;
    vecN_atan(res.v, x.v, 4);
    return res;
}


/** dst = atan2(y, x) */
static vec4 vec4_atan2(vec4 y, vec4 x) {
    vec4 res;
    vecN_atan2(res.v, y.v, x.v, 4);
    return res;
}


/** dst = pow(x, y) */
static vec4 vec4_pow(vec4 x, float y) {
    vec4 res;
    vecN_pow(res.v, x.v, y, 4);
    return res;
}


/** dst = pow(x, y) */
static vec4 vec4_pow_vec(vec4 x, vec4 y) {
    vec4 res;
    vecN_pow_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = exp(x) */
static vec4 vec4_exp(vec4 x) {
    vec4 res;
    vecN_exp(res.v, x.v, 4);
    return res;
}


/** dst = log(x) */
static vec4 vec4_log(vec4 x) {
    vec4 res;
    vecN_log(res.v, x.v, 4);
    return res;
}


/** dst = exp2(x) */
static vec4 vec4_exp2(vec4 x) {
    vec4 res;
    vecN_exp2(res.v, x.v, 4);
    return res;
}


/** dst = log2(x) */
static vec4 vec4_log2(vec4 x) {
    vec4 res;
    vecN_log2(res.v, x.v, 4);
    return res;
}


/** dst = sqrt(x) */
static vec4 vec4_sqrt(vec4 x) {
    vec4 res;
    vecN_sqrt(res.v, x.v, 4);
    return res;
}


/** dst = 1 / sqrt(x) */
static vec4 vec4_inversesqrt(vec4 x) {
    vec4 res;
    vecN_inversesqrt(res.v, x.v, 4);
    return res;
}


/** dst = abs(x) */
static vec4 vec4_abs(vec4 x) {
    vec4 res;
    vecN_abs(res.v, x.v, 4);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec4 vec4_sign(vec4 x) {
    vec4 res;
    vecN_sign(res.v, x.v, 4);
    return res;
}


/** dst = floor(x) */
static vec4 vec4_floor(vec4 x) {
    vec4 res;
    vecN_floor(res.v, x.v, 4);
    return res;
}


/** dst = ceil(x) */
static vec4 vec4_ceil(vec4 x) {
    vec4 res;
    vecN_ceil(res.v, x.v, 4);
    return res;
}


/** dst = x - floor(x) */
static vec4 vec4_fract(vec4 x) {
    vec4 res;
    vecN_fract(res.v, x.v, 4);
    return res;
}


/** dst = x - y * floor(x/y) */
static vec4 vec4_mod(vec4 x, float y) {
    vec4 res;
    vecN_mod(res.v, x.v, y, 4);
    return res;
}


/** dst = x - y * floor(x/y) */
static vec4 vec4_mod_vec(vec4 x, vec4 y) {
    vec4 res;
    vecN_mod_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = a < b ? a : b */
static vec4 vec4_min(vec4 x, float y) {
    vec4 res;
    vecN_min(res.v, x.v, y, 4);
    return res;
}


/** dst = a < b ? a : b */
static vec4 vec4_min_vec(vec4 x, vec4 y) {
    vec4 res;
    vecN_min_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = a > b ? a : b */
static vec4 vec4_max(vec4 x, float y) {
    vec4 res;
    vecN_max(res.v, x.v, y, 4);
    return res;
}


/** dst = a > b ? a : b */
static vec4 vec4_max_vec(vec4 x, vec4 y) {
    vec4 res;
    vecN_max_vec(res.v, x.v, y.v, 4);
    return res;
}


/** returns the index of the min v value */
static int vec4_min_index(vec4 vec) {
    return vecN_min_index(vec.v, 4);
}


/** returns the index of the max v value */
static int vec4_max_index(vec4 vec) {
    return vecN_max_index(vec.v, 4);
}

/** dst = x < min ? min : (x > max ? max : x) */
static vec4 vec4_clamp(vec4 x, float min, float max) {
    vec4 res;
    vecN_clamp(res.v, x.v, min, max, 4);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec4 vec4_clamp_vec(vec4 x, vec4 min, vec4 max) {
    vec4 res;
    vecN_clamp_vec(res.v, x.v, min.v, max.v, 4);
    return res;
}


/** dst = a * (1-t) + b * t */
static vec4 vec4_mix(vec4 a, vec4 b, float t) {
    vec4 res;
    vecN_mix(res.v, a.v, b.v, t, 4);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static vec4 vec4_step(vec4 x, float edge) {
    vec4 res;
    vecN_step(res.v, x.v, edge, 4);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static vec4 vec4_step_vec(vec4 x, vec4 edge) {
    vec4 res;
    vecN_step_vec(res.v, x.v, edge.v, 4);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec4 vec4_smoothstep(vec4 x, float edge1, float edge2) {
    vec4 res;
    vecN_smoothstep(res.v, x.v, edge1, edge2, 4);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec4 vec4_smoothstep_vec(vec4 x, vec4 edge1, vec4 edge2) {
    vec4 res;
    vecN_smoothstep_vec(res.v, x.v, edge1.v, edge2.v, 4);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static float vec4_sum(vec4 v) {
    return vecN_sum(v.v, 4);
}


/** returns a dot b */
static float vec4_dot(vec4 a, vec4 b) {
    return vecN_dot(a.v, b.v, 4);
}


/** dst = a x b , dst.w... = 0 */
static vec4 vec4_cross(vec4 a, vec4 b) {
    vec4 res;
    vecN_cross(res.v, a.v, b.v, 4);
    return res;
}


/** returns ||v||_4 */
static float vec4_norm(vec4 v) {
    return vecN_norm(v.v, 4);
}


/** returns ||v||_p */
static float vec4_norm_p(vec4 v, float p) {
    return vecN_norm_p(v.v, p, 4);
}


/** returns ||v||_1 */
static float vec4_norm_1(vec4 v) {
    return vecN_norm_1(v.v, 4);
}


/** returns ||v||_inf */
static float vec4_norm_inf(vec4 v) {
    return vecN_norm_inf(v.v, 4);
}


/** dst = v / norm(v) */
static vec4 vec4_normalize_unsafe(vec4 v) {
    vec4 res;
    vecN_normalize_unsafe(res.v, v.v, 4);
    return res;
}


/** dst = v / (norm(v) > 0 ? norm(v) : 1) */
static vec4 vec4_normalize(vec4 v) {
    vec4 res;
    vecN_normalize(res.v, v.v, 4);
    return res;
}

/** dst = normalize(cross(a, b)) */
static vec4 vec4_cross_normalized(vec4 a, vec4 b) {
    vec4 res;
    vecN_cross_normalized(res.v, a.v, b.v, 4);
    return res;
}


/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec4_length(vec4 v) {
    return vecN_length(v.v, 4);
}


/** returns norm(b-a) */
static float vec4_distance(vec4 a, vec4 b) {
    return vecN_distance(a.v, b.v, 4);
}


/** returns dot(b-a) */
static float vec4_sqr_distance(vec4 a, vec4 b) {
    return vecN_sqr_distance(a.v, b.v, 4);
}


/** dst = dot(i, nref) < 0 ? N : -N */
static vec4 vec4_faceforward(vec4 n, vec4 i, vec4 nref) {
    vec4 res;
    vecN_faceforward(res.v, n.v, i.v, nref.v, 4);
    return res;
}


/** dst = i - 2.0 * n * dot(n,i) */
static vec4 vec4_reflect(vec4 i, vec4 n) {
    vec4 res;
    vecN_reflect(res.v, i.v, n.v, 4);
    return res;
}


static vec4 vec4_refract(vec4 i, vec4 n, float eta) {
    vec4 res;
    vecN_refract(res.v, i.v, n.v, eta, 4);
    return res;
}


/** dst = a < b */
static bvec4 vec4_less_than(vec4 a, float b) {
    bvec4 res;
    vecN_less_than(res.v, a.v, b, 4);
    return res;
}


/** dst = a < b */
static bvec4 vec4_less_than_vec(vec4 a, vec4 b) {
    bvec4 res;
    vecN_less_than_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a <= b */
static bvec4 vec4_less_than_equal(vec4 a, float b) {
    bvec4 res;
    vecN_less_than_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a <= b */
static bvec4 vec4_less_than_equal_vec(vec4 a, vec4 b) {
    bvec4 res;
    vecN_less_than_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a > b */
static bvec4 vec4_greater_than(vec4 a, float b) {
    bvec4 res;
    vecN_greater_than(res.v, a.v, b, 4);
    return res;
}


/** dst = a > b */
static bvec4 vec4_greater_than_vec(vec4 a, vec4 b) {
    bvec4 res;
    vecN_greater_than_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a >= b */
static bvec4 vec4_greater_than_equal(vec4 a, float b) {
    bvec4 res;
    vecN_greater_than_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a >= b */
static bvec4 vec4_greater_than_equal_vec(vec4 a, vec4 b) {
    bvec4 res;
    vecN_greater_than_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a == b */
static bvec4 vec4_equal(vec4 a, float b) {
    bvec4 res;
    vecN_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a == b */
static bvec4 vec4_equal_vec(vec4 a, vec4 b) {
    bvec4 res;
    vecN_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a != b */
static bvec4 vec4_not_equal(vec4 a, float b) {
    bvec4 res;
    vecN_not_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a != b */
static bvec4 vec4_not_equal_vec(vec4 a, vec4 b) {
    bvec4 res;
    vecN_not_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a == b (+-eps) */
static bvec4 vec4_equal_eps(vec4 a, float b, float eps) {
    bvec4 res;
    vecN_equal_eps(res.v, a.v, b, eps, 4);
    return res;
}


/** dst = a == b (+-eps) */
static bvec4 vec4_equal_eps_vec(vec4 a, vec4 b, float eps) {
    bvec4 res;
    vecN_equal_eps_vec(res.v, a.v, b.v, eps, 4);
    return res;
}


/** dst = a != b (+-eps) */
static bvec4 vec4_not_equal_eps(vec4 a, float b, float eps) {
    bvec4 res;
    vecN_not_equal_eps(res.v, a.v, b, eps, 4);
    return res;
}


/** dst = a != b (+-eps) */
static bvec4 vec4_not_equal_eps_vec(vec4 a, vec4 b, float eps) {
    bvec4 res;
    vecN_not_equal_eps_vec(res.v, a.v, b.v, eps, 4);
    return res;
}


/** dst = isnan(v) */
static bvec4 vec4_isnan(vec4 v) {
    bvec4 res;
    vecN_isnan(res.v, v.v, 4);
    return res;
}


/** dst = !isnan(v) */
static bvec4 vec4_not_isnan(vec4 v) {
    bvec4 res;
    vecN_not_isnan(res.v, v.v, 4);
    return res;
}


/** dst = isinf(v) */
static bvec4 vec4_isinf(vec4 v) {
    bvec4 res;
    vecN_isinf(res.v, v.v, 4);
    return res;
}


/** dst = !isinf(v) */
static bvec4 vec4_not_isinf(vec4 v) {
    bvec4 res;
    vecN_not_isinf(res.v, v.v, 4);
    return res;
}

#endif //M_VEC_VEC4_H
