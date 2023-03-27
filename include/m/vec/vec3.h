#ifndef M_VEC_VEC3_H
#define M_VEC_VEC3_H


#include "vecn.h"
#include "../types/vec3.h"
#include "../types/bvec3.h"


/** dst = (vec3) v */
static vec3 vec3_cast_from_float(const float *cast) {
    vec3 res;
    vecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (vec3) v */
static vec3 vec3_cast_from_double(const double *cast) {
    vec3 res;
    vecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (vec3) v */
static vec3 vec3_cast_from_int(const int *cast) {
    vec3 res;
    vecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (vec3) v */
static vec3 vec3_cast_from_uchar(const unsigned char *cast) {
    vec3 res;
    vecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = v / 255 */
static vec3 vec3_cast_from_uchar_1(const unsigned char *cast) {
    vec3 res;
    vecN_cast_from_uchar_1(res.v, cast, 3);
    return res;
}


/** a == b */
static bool vec3_cmp(vec3 a, vec3 b) {
    return vecN_cmp(a.v, b.v, 3);
}


/** dst = s */
static vec3 vec3_set(float s) {
    vec3 res;
    vecN_set(res.v, s, 3);
    return res;
}

/** dst = v0, v1, ... */
static vec3 vec3_new(float v0, float v1, float v2
) {
    vec3 self;
    self.v0 = v0;
    self.v1 = v1;
    self.v2 = v2;
    return self;
}

/** dst = unit_x */
static vec3 vec3_unit_x() {
    vec3 res;
    vecN_unit_x(res.v, 3);
    return res;
}


/** dst = unit_y */
static vec3 vec3_unit_y() {
    vec3 res;
    vecN_unit_y(res.v, 3);
    return res;
}


/** dst = unit_z */
static vec3 vec3_unit_z() {
    vec3 res;
    vecN_unit_z(res.v, 3);
    return res;
}


/** dst = -v */
static vec3 vec3_neg(vec3 v) {
    vec3 res;
    vecN_neg(res.v, v.v, 3);
    return res;
}


/** dst = a + b */
static vec3 vec3_add_vec(vec3 a, vec3 b) {
    vec3 res;
    vecN_add_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a + b */
static vec3 vec3_add(vec3 a, float b) {
    vec3 res;
    vecN_add(res.v, a.v, b, 3);
    return res;
}


/** dst = a - b */
static vec3 vec3_sub_vec(vec3 a, vec3 b) {
    vec3 res;
    vecN_sub_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a - b */
static vec3 vec3_sub(vec3 a, float b) {
    vec3 res;
    vecN_sub(res.v, a.v, b, 3);
    return res;
}


/** dst = a * b */
static vec3 vec3_scale_vec(vec3 a, vec3 b) {
    vec3 res;
    vecN_scale_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a * b */
static vec3 vec3_scale(vec3 a, float b) {
    vec3 res;
    vecN_scale(res.v, a.v, b, 3);
    return res;
}


/** dst = a / b */
static vec3 vec3_div_vec(vec3 a, vec3 b) {
    vec3 res;
    vecN_div_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a / b */
static vec3 vec3_div(vec3 a, float b) {
    vec3 res;
    vecN_div(res.v, a.v, b, 3);
    return res;
}

/** dst = a + b * c */
static vec3 vec3_add_scaled_vec(vec3 a, vec3 b, vec3 c) {
    vec3 res;
    vecN_add_scaled_vec(res.v, a.v, b.v, c.v, 3);
    return res;
}

/** dst = a + b * c */
static vec3 vec3_add_scaled(vec3 a, vec3 b, float c) {
    vec3 res;
    vecN_add_scaled(res.v, a.v, b.v, c, 3);
    return res;
}


/** dst = a * M_PI / 180 */
static vec3 vec3_radians(vec3 deg) {
    vec3 res;
    vecN_radians(res.v, deg.v, 3);
    return res;
}


/** dst = a * 180 / M_PI */
static vec3 vec3_degrees(vec3 rad) {
    vec3 res;
    vecN_degrees(res.v, rad.v, 3);
    return res;
}


/** dst = sin(angle_rad) */
static vec3 vec3_sin(vec3 angle_rad) {
    vec3 res;
    vecN_sin(res.v, angle_rad.v, 3);
    return res;
}


/** dst = cos(angle_rad) */
static vec3 vec3_cos(vec3 angle_rad) {
    vec3 res;
    vecN_cos(res.v, angle_rad.v, 3);
    return res;
}


/** dst = tan(angle_rad) */
static vec3 vec3_tan(vec3 angle_rad) {
    vec3 res;
    vecN_tan(res.v, angle_rad.v, 3);
    return res;
}


/** dst = asin(x) */
static vec3 vec3_asin(vec3 x) {
    vec3 res;
    vecN_asin(res.v, x.v, 3);
    return res;
}


/** dst = acos(x) */
static vec3 vec3_acos(vec3 x) {
    vec3 res;
    vecN_acos(res.v, x.v, 3);
    return res;
}


/** dst = atan(x) */
static vec3 vec3_atan(vec3 x) {
    vec3 res;
    vecN_atan(res.v, x.v, 3);
    return res;
}


/** dst = atan2(y, x) */
static vec3 vec3_atan2(vec3 y, vec3 x) {
    vec3 res;
    vecN_atan2(res.v, y.v, x.v, 3);
    return res;
}


/** dst = pow(x, y) */
static vec3 vec3_pow(vec3 x, float y) {
    vec3 res;
    vecN_pow(res.v, x.v, y, 3);
    return res;
}


/** dst = pow(x, y) */
static vec3 vec3_pow_vec(vec3 x, vec3 y) {
    vec3 res;
    vecN_pow_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = exp(x) */
static vec3 vec3_exp(vec3 x) {
    vec3 res;
    vecN_exp(res.v, x.v, 3);
    return res;
}


/** dst = log(x) */
static vec3 vec3_log(vec3 x) {
    vec3 res;
    vecN_log(res.v, x.v, 3);
    return res;
}


/** dst = exp2(x) */
static vec3 vec3_exp2(vec3 x) {
    vec3 res;
    vecN_exp2(res.v, x.v, 3);
    return res;
}


/** dst = log2(x) */
static vec3 vec3_log2(vec3 x) {
    vec3 res;
    vecN_log2(res.v, x.v, 3);
    return res;
}


/** dst = sqrt(x) */
static vec3 vec3_sqrt(vec3 x) {
    vec3 res;
    vecN_sqrt(res.v, x.v, 3);
    return res;
}


/** dst = 1 / sqrt(x) */
static vec3 vec3_inversesqrt(vec3 x) {
    vec3 res;
    vecN_inversesqrt(res.v, x.v, 3);
    return res;
}


/** dst = abs(x) */
static vec3 vec3_abs(vec3 x) {
    vec3 res;
    vecN_abs(res.v, x.v, 3);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec3 vec3_sign(vec3 x) {
    vec3 res;
    vecN_sign(res.v, x.v, 3);
    return res;
}


/** dst = floor(x) */
static vec3 vec3_floor(vec3 x) {
    vec3 res;
    vecN_floor(res.v, x.v, 3);
    return res;
}


/** dst = ceil(x) */
static vec3 vec3_ceil(vec3 x) {
    vec3 res;
    vecN_ceil(res.v, x.v, 3);
    return res;
}


/** dst = x - floor(x) */
static vec3 vec3_fract(vec3 x) {
    vec3 res;
    vecN_fract(res.v, x.v, 3);
    return res;
}


/** dst = x - y * floor(x/y) */
static vec3 vec3_mod(vec3 x, float y) {
    vec3 res;
    vecN_mod(res.v, x.v, y, 3);
    return res;
}


/** dst = x - y * floor(x/y) */
static vec3 vec3_mod_vec(vec3 x, vec3 y) {
    vec3 res;
    vecN_mod_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = a < b ? a : b */
static vec3 vec3_min(vec3 x, float y) {
    vec3 res;
    vecN_min(res.v, x.v, y, 3);
    return res;
}


/** dst = a < b ? a : b */
static vec3 vec3_min_vec(vec3 x, vec3 y) {
    vec3 res;
    vecN_min_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = a > b ? a : b */
static vec3 vec3_max(vec3 x, float y) {
    vec3 res;
    vecN_max(res.v, x.v, y, 3);
    return res;
}


/** dst = a > b ? a : b */
static vec3 vec3_max_vec(vec3 x, vec3 y) {
    vec3 res;
    vecN_max_vec(res.v, x.v, y.v, 3);
    return res;
}


/** returns the index of the min v value */
static int vec3_min_index(vec3 vec) {
    return vecN_min_index(vec.v, 3);
}


/** returns the index of the max v value */
static int vec3_max_index(vec3 vec) {
    return vecN_max_index(vec.v, 3);
}

/** dst = x < min ? min : (x > max ? max : x) */
static vec3 vec3_clamp(vec3 x, float min, float max) {
    vec3 res;
    vecN_clamp(res.v, x.v, min, max, 3);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec3 vec3_clamp_vec(vec3 x, vec3 min, vec3 max) {
    vec3 res;
    vecN_clamp_vec(res.v, x.v, min.v, max.v, 3);
    return res;
}


/** dst = a * (1-t) + b * t */
static vec3 vec3_mix(vec3 a, vec3 b, float t) {
    vec3 res;
    vecN_mix(res.v, a.v, b.v, t, 3);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static vec3 vec3_step(vec3 x, float edge) {
    vec3 res;
    vecN_step(res.v, x.v, edge, 3);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static vec3 vec3_step_vec(vec3 x, vec3 edge) {
    vec3 res;
    vecN_step_vec(res.v, x.v, edge.v, 3);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec3 vec3_smoothstep(vec3 x, float edge1, float edge2) {
    vec3 res;
    vecN_smoothstep(res.v, x.v, edge1, edge2, 3);
    return res;
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec3 vec3_smoothstep_vec(vec3 x, vec3 edge1, vec3 edge2) {
    vec3 res;
    vecN_smoothstep_vec(res.v, x.v, edge1.v, edge2.v, 3);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static float vec3_sum(vec3 v) {
    return vecN_sum(v.v, 3);
}


/** returns a dot b */
static float vec3_dot(vec3 a, vec3 b) {
    return vecN_dot(a.v, b.v, 3);
}


/** dst = a x b , dst.w... = 0 */
static vec3 vec3_cross(vec3 a, vec3 b) {
    vec3 res;
    vecN_cross(res.v, a.v, b.v, 3);
    return res;
}


/** returns ||v||_3 */
static float vec3_norm(vec3 v) {
    return vecN_norm(v.v, 3);
}


/** returns ||v||_p */
static float vec3_norm_p(vec3 v, float p) {
    return vecN_norm_p(v.v, p, 3);
}


/** returns ||v||_1 */
static float vec3_norm_1(vec3 v) {
    return vecN_norm_1(v.v, 3);
}


/** returns ||v||_inf */
static float vec3_norm_inf(vec3 v) {
    return vecN_norm_inf(v.v, 3);
}


/** dst = v / norm(v) */
static vec3 vec3_normalize_unsafe(vec3 v) {
    vec3 res;
    vecN_normalize_unsafe(res.v, v.v, 3);
    return res;
}


/** dst = v / (norm(v) > 0 ? norm(v) : 1) */
static vec3 vec3_normalize(vec3 v) {
    vec3 res;
    vecN_normalize(res.v, v.v, 3);
    return res;
}

/** dst = normalize(cross(a, b)) */
static vec3 vec3_cross_normalized(vec3 a, vec3 b) {
    vec3 res;
    vecN_cross_normalized(res.v, a.v, b.v, 3);
    return res;
}


/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec3_length(vec3 v) {
    return vecN_length(v.v, 3);
}


/** returns norm(b-a) */
static float vec3_distance(vec3 a, vec3 b) {
    return vecN_distance(a.v, b.v, 3);
}


/** returns dot(b-a) */
static float vec3_sqr_distance(vec3 a, vec3 b) {
    return vecN_sqr_distance(a.v, b.v, 3);
}


/** dst = dot(i, nref) < 0 ? N : -N */
static vec3 vec3_faceforward(vec3 n, vec3 i, vec3 nref) {
    vec3 res;
    vecN_faceforward(res.v, n.v, i.v, nref.v, 3);
    return res;
}


/** dst = i - 2.0 * n * dot(n,i) */
static vec3 vec3_reflect(vec3 i, vec3 n) {
    vec3 res;
    vecN_reflect(res.v, i.v, n.v, 3);
    return res;
}


static vec3 vec3_refract(vec3 i, vec3 n, float eta) {
    vec3 res;
    vecN_refract(res.v, i.v, n.v, eta, 3);
    return res;
}


/** dst = a < b */
static bvec3 vec3_less_than(vec3 a, float b) {
    bvec3 res;
    vecN_less_than(res.v, a.v, b, 3);
    return res;
}


/** dst = a < b */
static bvec3 vec3_less_than_vec(vec3 a, vec3 b) {
    bvec3 res;
    vecN_less_than_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a <= b */
static bvec3 vec3_less_than_equal(vec3 a, float b) {
    bvec3 res;
    vecN_less_than_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a <= b */
static bvec3 vec3_less_than_equal_vec(vec3 a, vec3 b) {
    bvec3 res;
    vecN_less_than_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a > b */
static bvec3 vec3_greater_than(vec3 a, float b) {
    bvec3 res;
    vecN_greater_than(res.v, a.v, b, 3);
    return res;
}


/** dst = a > b */
static bvec3 vec3_greater_than_vec(vec3 a, vec3 b) {
    bvec3 res;
    vecN_greater_than_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a >= b */
static bvec3 vec3_greater_than_equal(vec3 a, float b) {
    bvec3 res;
    vecN_greater_than_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a >= b */
static bvec3 vec3_greater_than_equal_vec(vec3 a, vec3 b) {
    bvec3 res;
    vecN_greater_than_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a == b */
static bvec3 vec3_equal(vec3 a, float b) {
    bvec3 res;
    vecN_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a == b */
static bvec3 vec3_equal_vec(vec3 a, vec3 b) {
    bvec3 res;
    vecN_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a != b */
static bvec3 vec3_not_equal(vec3 a, float b) {
    bvec3 res;
    vecN_not_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a != b */
static bvec3 vec3_not_equal_vec(vec3 a, vec3 b) {
    bvec3 res;
    vecN_not_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a == b (+-eps) */
static bvec3 vec3_equal_eps(vec3 a, float b, float eps) {
    bvec3 res;
    vecN_equal_eps(res.v, a.v, b, eps, 3);
    return res;
}


/** dst = a == b (+-eps) */
static bvec3 vec3_equal_eps_vec(vec3 a, vec3 b, float eps) {
    bvec3 res;
    vecN_equal_eps_vec(res.v, a.v, b.v, eps, 3);
    return res;
}


/** dst = a != b (+-eps) */
static bvec3 vec3_not_equal_eps(vec3 a, float b, float eps) {
    bvec3 res;
    vecN_not_equal_eps(res.v, a.v, b, eps, 3);
    return res;
}


/** dst = a != b (+-eps) */
static bvec3 vec3_not_equal_eps_vec(vec3 a, vec3 b, float eps) {
    bvec3 res;
    vecN_not_equal_eps_vec(res.v, a.v, b.v, eps, 3);
    return res;
}


/** dst = isnan(v) */
static bvec3 vec3_isnan(vec3 v) {
    bvec3 res;
    vecN_isnan(res.v, v.v, 3);
    return res;
}


/** dst = !isnan(v) */
static bvec3 vec3_not_isnan(vec3 v) {
    bvec3 res;
    vecN_not_isnan(res.v, v.v, 3);
    return res;
}


/** dst = isinf(v) */
static bvec3 vec3_isinf(vec3 v) {
    bvec3 res;
    vecN_isinf(res.v, v.v, 3);
    return res;
}


/** dst = !isinf(v) */
static bvec3 vec3_not_isinf(vec3 v) {
    bvec3 res;
    vecN_not_isinf(res.v, v.v, 3);
    return res;
}

#endif //M_VEC_VEC3_H
