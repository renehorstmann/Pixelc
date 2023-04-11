#ifndef M_VEC_VEC2_H
#define M_VEC_VEC2_H


#include "vecn.h"
#include "../types/vec2.h"
#include "../types/bvec2.h"

// macro to create a vec2
#define vec2_(x, y \
) (vec2) {{(x), (y)\
}}

/** dst = (vec2) v */
static vec2 vec2_cast_from_float(const float *cast) {
    vec2 res;
    vecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (vec2) v */
static vec2 vec2_cast_from_double(const double *cast) {
    vec2 res;
    vecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (vec2) v */
static vec2 vec2_cast_from_int(const int *cast) {
    vec2 res;
    vecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (vec2) v */
static vec2 vec2_cast_from_uchar(const unsigned char *cast) {
    vec2 res;
    vecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = v / 255 */
static vec2 vec2_cast_from_uchar_1(const unsigned char *cast) {
    vec2 res;
    vecN_cast_from_uchar_1(res.v, cast, 2);
    return res;
}


/** a == b */
static bool vec2_cmp(vec2 a, vec2 b) {
    return vecN_cmp(a.v, b.v, 2);
}


/** dst = s */
static vec2 vec2_set(float s) {
    vec2 res;
    vecN_set(res.v, s, 2);
    return res;
}

/** dst = v0, v1, ... */
static vec2 vec2_new(float v0, float v1
) {
    vec2 self;
    self.v0 = v0;
    self.v1 = v1;
    return self;
}

/** dst = unit_x */
static vec2 vec2_unit_x() {
    vec2 res;
    vecN_unit_x(res.v, 2);
    return res;
}


/** dst = unit_y */
static vec2 vec2_unit_y() {
    vec2 res;
    vecN_unit_y(res.v, 2);
    return res;
}


/** dst = -v */
static vec2 vec2_neg(vec2 v) {
    vec2 res;
    vecN_neg(res.v, v.v, 2);
    return res;
}


/** dst = a + b */
static vec2 vec2_add_vec(vec2 a, vec2 b) {
    vec2 res;
    vecN_add_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a + b */
static vec2 vec2_add(vec2 a, float b) {
    vec2 res;
    vecN_add(res.v, a.v, b, 2);
    return res;
}


/** dst = a - b */
static vec2 vec2_sub_vec(vec2 a, vec2 b) {
    vec2 res;
    vecN_sub_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a - b */
static vec2 vec2_sub(vec2 a, float b) {
    vec2 res;
    vecN_sub(res.v, a.v, b, 2);
    return res;
}


/** dst = a * b */
static vec2 vec2_scale_vec(vec2 a, vec2 b) {
    vec2 res;
    vecN_scale_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a * b */
static vec2 vec2_scale(vec2 a, float b) {
    vec2 res;
    vecN_scale(res.v, a.v, b, 2);
    return res;
}


/** dst = a / b */
static vec2 vec2_div_vec(vec2 a, vec2 b) {
    vec2 res;
    vecN_div_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a / b */
static vec2 vec2_div(vec2 a, float b) {
    vec2 res;
    vecN_div(res.v, a.v, b, 2);
    return res;
}

/** dst = a + b * c */
static vec2 vec2_add_scaled_vec(vec2 a, vec2 b, vec2 c) {
    vec2 res;
    vecN_add_scaled_vec(res.v, a.v, b.v, c.v, 2);
    return res;
}

/** dst = a + b * c */
static vec2 vec2_add_scaled(vec2 a, vec2 b, float c) {
    vec2 res;
    vecN_add_scaled(res.v, a.v, b.v, c, 2);
    return res;
}


/** dst = a * M_PI / 180 */
static vec2 vec2_radians(vec2 deg) {
    vec2 res;
    vecN_radians(res.v, deg.v, 2);
    return res;
}


/** dst = a * 180 / M_PI */
static vec2 vec2_degrees(vec2 rad) {
    vec2 res;
    vecN_degrees(res.v, rad.v, 2);
    return res;
}


/** dst = sin(angle_rad) */
static vec2 vec2_sin(vec2 angle_rad) {
    vec2 res;
    vecN_sin(res.v, angle_rad.v, 2);
    return res;
}


/** dst = cos(angle_rad) */
static vec2 vec2_cos(vec2 angle_rad) {
    vec2 res;
    vecN_cos(res.v, angle_rad.v, 2);
    return res;
}


/** dst = tan(angle_rad) */
static vec2 vec2_tan(vec2 angle_rad) {
    vec2 res;
    vecN_tan(res.v, angle_rad.v, 2);
    return res;
}


/** dst = asin(x) */
static vec2 vec2_asin(vec2 x) {
    vec2 res;
    vecN_asin(res.v, x.v, 2);
    return res;
}


/** dst = acos(x) */
static vec2 vec2_acos(vec2 x) {
    vec2 res;
    vecN_acos(res.v, x.v, 2);
    return res;
}


/** dst = atan(x) */
static vec2 vec2_atan(vec2 x) {
    vec2 res;
    vecN_atan(res.v, x.v, 2);
    return res;
}


/** dst = atan2(y, x) */
static vec2 vec2_atan2(vec2 y, vec2 x) {
    vec2 res;
    vecN_atan2(res.v, y.v, x.v, 2);
    return res;
}


/** dst = pow(x, y) */
static vec2 vec2_pow(vec2 x, float y) {
    vec2 res;
    vecN_pow(res.v, x.v, y, 2);
    return res;
}


/** dst = pow(x, y) */
static vec2 vec2_pow_vec(vec2 x, vec2 y) {
    vec2 res;
    vecN_pow_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = exp(x) */
static vec2 vec2_exp(vec2 x) {
    vec2 res;
    vecN_exp(res.v, x.v, 2);
    return res;
}


/** dst = log(x) */
static vec2 vec2_log(vec2 x) {
    vec2 res;
    vecN_log(res.v, x.v, 2);
    return res;
}


/** dst = exp2(x) */
static vec2 vec2_exp2(vec2 x) {
    vec2 res;
    vecN_exp2(res.v, x.v, 2);
    return res;
}


/** dst = log2(x) */
static vec2 vec2_log2(vec2 x) {
    vec2 res;
    vecN_log2(res.v, x.v, 2);
    return res;
}


/** dst = sqrt(x) */
static vec2 vec2_sqrt(vec2 x) {
    vec2 res;
    vecN_sqrt(res.v, x.v, 2);
    return res;
}


/** dst = 1 / sqrt(x) */
static vec2 vec2_inversesqrt(vec2 x) {
    vec2 res;
    vecN_inversesqrt(res.v, x.v, 2);
    return res;
}


/** dst = abs(x) */
static vec2 vec2_abs(vec2 x) {
    vec2 res;
    vecN_abs(res.v, x.v, 2);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec2 vec2_sign(vec2 x) {
    vec2 res;
    vecN_sign(res.v, x.v, 2);
    return res;
}


/** dst = floor(x) */
static vec2 vec2_floor(vec2 x) {
    vec2 res;
    vecN_floor(res.v, x.v, 2);
    return res;
}


/** dst = ceil(x) */
static vec2 vec2_ceil(vec2 x) {
    vec2 res;
    vecN_ceil(res.v, x.v, 2);
    return res;
}


/** dst = x - floor(x) */
static vec2 vec2_fract(vec2 x) {
    vec2 res;
    vecN_fract(res.v, x.v, 2);
    return res;
}


/** dst = x - y * floor(x/y) */
static vec2 vec2_mod(vec2 x, float y) {
    vec2 res;
    vecN_mod(res.v, x.v, y, 2);
    return res;
}


/** dst = x - y * floor(x/y) */
static vec2 vec2_mod_vec(vec2 x, vec2 y) {
    vec2 res;
    vecN_mod_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = a < b ? a : b */
static vec2 vec2_min(vec2 x, float y) {
    vec2 res;
    vecN_min(res.v, x.v, y, 2);
    return res;
}


/** dst = a < b ? a : b */
static vec2 vec2_min_vec(vec2 x, vec2 y) {
    vec2 res;
    vecN_min_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = a > b ? a : b */
static vec2 vec2_max(vec2 x, float y) {
    vec2 res;
    vecN_max(res.v, x.v, y, 2);
    return res;
}


/** dst = a > b ? a : b */
static vec2 vec2_max_vec(vec2 x, vec2 y) {
    vec2 res;
    vecN_max_vec(res.v, x.v, y.v, 2);
    return res;
}


/** returns the index of the min v value */
static int vec2_min_index(vec2 vec) {
    return vecN_min_index(vec.v, 2);
}


/** returns the index of the max v value */
static int vec2_max_index(vec2 vec) {
    return vecN_max_index(vec.v, 2);
}

/** dst = x < min ? min : (x > max ? max : x) */
static vec2 vec2_clamp(vec2 x, float min, float max) {
    vec2 res;
    vecN_clamp(res.v, x.v, min, max, 2);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec2 vec2_clamp_vec(vec2 x, vec2 min, vec2 max) {
    vec2 res;
    vecN_clamp_vec(res.v, x.v, min.v, max.v, 2);
    return res;
}


/** dst = a * (1-t) + b * t */
static vec2 vec2_mix(vec2 a, vec2 b, float t) {
    vec2 res;
    vecN_mix(res.v, a.v, b.v, t, 2);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static vec2 vec2_step(vec2 x, float edge) {
    vec2 res;
    vecN_step(res.v, x.v, edge, 2);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static vec2 vec2_step_vec(vec2 x, vec2 edge) {
    vec2 res;
    vecN_step_vec(res.v, x.v, edge.v, 2);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec2 vec2_smoothstep(vec2 x, float edge1, float edge2) {
    vec2 res;
    vecN_smoothstep(res.v, x.v, edge1, edge2, 2);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec2 vec2_smoothstep_vec(vec2 x, vec2 edge1, vec2 edge2) {
    vec2 res;
    vecN_smoothstep_vec(res.v, x.v, edge1.v, edge2.v, 2);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static float vec2_sum(vec2 v) {
    return vecN_sum(v.v, 2);
}


/** returns a dot b */
static float vec2_dot(vec2 a, vec2 b) {
    return vecN_dot(a.v, b.v, 2);
}


/** dst = a x b , dst.w... = 0 */
static vec2 vec2_cross(vec2 a, vec2 b) {
    vec2 res;
    vecN_cross(res.v, a.v, b.v, 2);
    return res;
}


/** returns ||v||_2 */
static float vec2_norm(vec2 v) {
    return vecN_norm(v.v, 2);
}


/** returns ||v||_p */
static float vec2_norm_p(vec2 v, float p) {
    return vecN_norm_p(v.v, p, 2);
}


/** returns ||v||_1 */
static float vec2_norm_1(vec2 v) {
    return vecN_norm_1(v.v, 2);
}


/** returns ||v||_inf */
static float vec2_norm_inf(vec2 v) {
    return vecN_norm_inf(v.v, 2);
}


/** dst = v / norm(v) */
static vec2 vec2_normalize_unsafe(vec2 v) {
    vec2 res;
    vecN_normalize_unsafe(res.v, v.v, 2);
    return res;
}


/** dst = v / (norm(v) > 0 ? norm(v) : 1) */
static vec2 vec2_normalize(vec2 v) {
    vec2 res;
    vecN_normalize(res.v, v.v, 2);
    return res;
}

/** dst = normalize(cross(a, b)) */
static vec2 vec2_cross_normalized(vec2 a, vec2 b) {
    vec2 res;
    vecN_cross_normalized(res.v, a.v, b.v, 2);
    return res;
}


/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec2_length(vec2 v) {
    return vecN_length(v.v, 2);
}


/** returns norm(b-a) */
static float vec2_distance(vec2 a, vec2 b) {
    return vecN_distance(a.v, b.v, 2);
}


/** returns dot(b-a) */
static float vec2_sqr_distance(vec2 a, vec2 b) {
    return vecN_sqr_distance(a.v, b.v, 2);
}


/** dst = dot(i, nref) < 0 ? N : -N */
static vec2 vec2_faceforward(vec2 n, vec2 i, vec2 nref) {
    vec2 res;
    vecN_faceforward(res.v, n.v, i.v, nref.v, 2);
    return res;
}


/** dst = i - 2.0 * n * dot(n,i) */
static vec2 vec2_reflect(vec2 i, vec2 n) {
    vec2 res;
    vecN_reflect(res.v, i.v, n.v, 2);
    return res;
}


static vec2 vec2_refract(vec2 i, vec2 n, float eta) {
    vec2 res;
    vecN_refract(res.v, i.v, n.v, eta, 2);
    return res;
}


/** dst = a < b */
static bvec2 vec2_less_than(vec2 a, float b) {
    bvec2 res;
    vecN_less_than(res.v, a.v, b, 2);
    return res;
}


/** dst = a < b */
static bvec2 vec2_less_than_vec(vec2 a, vec2 b) {
    bvec2 res;
    vecN_less_than_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a <= b */
static bvec2 vec2_less_than_equal(vec2 a, float b) {
    bvec2 res;
    vecN_less_than_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a <= b */
static bvec2 vec2_less_than_equal_vec(vec2 a, vec2 b) {
    bvec2 res;
    vecN_less_than_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a > b */
static bvec2 vec2_greater_than(vec2 a, float b) {
    bvec2 res;
    vecN_greater_than(res.v, a.v, b, 2);
    return res;
}


/** dst = a > b */
static bvec2 vec2_greater_than_vec(vec2 a, vec2 b) {
    bvec2 res;
    vecN_greater_than_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a >= b */
static bvec2 vec2_greater_than_equal(vec2 a, float b) {
    bvec2 res;
    vecN_greater_than_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a >= b */
static bvec2 vec2_greater_than_equal_vec(vec2 a, vec2 b) {
    bvec2 res;
    vecN_greater_than_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a == b */
static bvec2 vec2_equal(vec2 a, float b) {
    bvec2 res;
    vecN_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a == b */
static bvec2 vec2_equal_vec(vec2 a, vec2 b) {
    bvec2 res;
    vecN_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a != b */
static bvec2 vec2_not_equal(vec2 a, float b) {
    bvec2 res;
    vecN_not_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a != b */
static bvec2 vec2_not_equal_vec(vec2 a, vec2 b) {
    bvec2 res;
    vecN_not_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a == b (+-eps) */
static bvec2 vec2_equal_eps(vec2 a, float b, float eps) {
    bvec2 res;
    vecN_equal_eps(res.v, a.v, b, eps, 2);
    return res;
}


/** dst = a == b (+-eps) */
static bvec2 vec2_equal_eps_vec(vec2 a, vec2 b, float eps) {
    bvec2 res;
    vecN_equal_eps_vec(res.v, a.v, b.v, eps, 2);
    return res;
}


/** dst = a != b (+-eps) */
static bvec2 vec2_not_equal_eps(vec2 a, float b, float eps) {
    bvec2 res;
    vecN_not_equal_eps(res.v, a.v, b, eps, 2);
    return res;
}


/** dst = a != b (+-eps) */
static bvec2 vec2_not_equal_eps_vec(vec2 a, vec2 b, float eps) {
    bvec2 res;
    vecN_not_equal_eps_vec(res.v, a.v, b.v, eps, 2);
    return res;
}


/** dst = isnan(v) */
static bvec2 vec2_isnan(vec2 v) {
    bvec2 res;
    vecN_isnan(res.v, v.v, 2);
    return res;
}


/** dst = !isnan(v) */
static bvec2 vec2_not_isnan(vec2 v) {
    bvec2 res;
    vecN_not_isnan(res.v, v.v, 2);
    return res;
}


/** dst = isinf(v) */
static bvec2 vec2_isinf(vec2 v) {
    bvec2 res;
    vecN_isinf(res.v, v.v, 2);
    return res;
}


/** dst = !isinf(v) */
static bvec2 vec2_not_isinf(vec2 v) {
    bvec2 res;
    vecN_not_isinf(res.v, v.v, 2);
    return res;
}

#endif //M_VEC_VEC2_H
