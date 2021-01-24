#ifndef MATHC_VEC_VEC2_H
#define MATHC_VEC_VEC2_H

#include "vecn.h"
#include "../types/float.h"
#include "../types/bool.h"


/** dst = unit_x */
static vec2 vec2_unit_x() {
    return (vec2) {{1, 0}};
}

/** dst = unit_y */
static vec2 vec2_unit_y() {
    return (vec2) {{0, 1}};
}


/** dst = scalar */
static vec2 vec2_set(float scalar) {
    vec2 res;
    vecN_set(res.v, scalar, 2);
    return res;
}


/** dst = -vec */
static vec2 vec2_neg(vec2 vec) {
    vec2 res;
    vecN_neg(res.v, vec.v, 2);
    return res;
}
/** dst = -vec */
static vec2 vec2_neg_v(const float *vec) {
    return vec2_neg(Vec2(vec));
}


/** dst = a + b */
static vec2 vec2_add_vec(vec2 vec_a, vec2 vec_b) {
    vec2 res;
    vecN_add_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a + b */
static vec2 vec2_add_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_add_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a + b */
static vec2 vec2_add(vec2 vec_a, float scalar_b) {
    vec2 res;
    vecN_add(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a + b */
static vec2 vec2_add_v(const float *vec_a, float scalar_b) {
    return vec2_add(Vec2(vec_a), scalar_b);
}


/** dst = a - b */
static vec2 vec2_sub_vec(vec2 vec_a, vec2 vec_b) {
    vec2 res;
    vecN_sub_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a - b */
static vec2 vec2_sub_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_sub_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a - b */
static vec2 vec2_sub(vec2 vec_a, float scalar_b) {
    vec2 res;
    vecN_sub(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a - b */
static vec2 vec2_sub_v(const float *vec_a, float scalar_b) {
    return vec2_sub(Vec2(vec_a), scalar_b);
}


/** dst = a * b */
static vec2 vec2_scale_vec(vec2 vec_a, vec2 vec_b) {
    vec2 res;
    vecN_scale_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a * b */
static vec2 vec2_scale_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_scale_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a * b */
static vec2 vec2_scale(vec2 vec_a, float scalar_b) {
    vec2 res;
    vecN_scale(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a * b */
static vec2 vec2_scale_v(const float *vec_a, float scalar_b) {
    return vec2_scale(Vec2(vec_a), scalar_b);
}


/** dst = a / b */
static vec2 vec2_div_vec(vec2 vec_a, vec2 vec_b) {
    vec2 res;
    vecN_div_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a / b */
static vec2 vec2_div_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_div_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a / b */
static vec2 vec2_div(vec2 vec_a, float scalar_b) {
    vec2 res;
    vecN_div(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a / b */
static vec2 vec2_div_v(const float *vec_a, float scalar_b) {
    return vec2_div(Vec2(vec_a), scalar_b);
}


/** dst = a * M_PI / 180 */
static vec2 vec2_radians(vec2 vec_deg) {
    vec2 res;
    vecN_radians(res.v, vec_deg.v, 2);
    return res;
}
/** dst = a * M_PI / 180 */
static vec2 vec2_radians_v(const float *vec_deg) {
    return vec2_radians(Vec2(vec_deg));
}


/** dst = a * 180 / M_PI */
static vec2 vec2_degrees(vec2 vec_rad) {
    vec2 res;
    vecN_degrees(res.v, vec_rad.v, 2);
    return res;
}
/** dst = a * 180 / M_PI */
static vec2 vec2_degrees_v(const float *vec_rad) {
    return vec2_degrees(Vec2(vec_rad));
}


/** dst = sin(angle_rad) */
static vec2 vec2_sin(vec2 vec_angle_rad) {
    vec2 res;
    vecN_sin(res.v, vec_angle_rad.v, 2);
    return res;
}
/** dst = sin(angle_rad) */
static vec2 vec2_sin_v(const float *vec_angle_rad) {
    return vec2_sin(Vec2(vec_angle_rad));
}


/** dst = cos(angle_rad) */
static vec2 vec2_cos(vec2 vec_angle_rad) {
    vec2 res;
    vecN_cos(res.v, vec_angle_rad.v, 2);
    return res;
}
/** dst = cos(angle_rad) */
static vec2 vec2_cos_v(const float *vec_angle_rad) {
    return vec2_cos(Vec2(vec_angle_rad));
}


/** dst = tan(angle_rad) */
static vec2 vec2_tan(vec2 vec_angle_rad) {
    vec2 res;
    vecN_tan(res.v, vec_angle_rad.v, 2);
    return res;
}
/** dst = tan(angle_rad) */
static vec2 vec2_tan_v(const float *vec_angle_rad) {
    return vec2_tan(Vec2(vec_angle_rad));
}


/** dst = asin(x) */
static vec2 vec2_asin(vec2 vec_x) {
    vec2 res;
    vecN_asin(res.v, vec_x.v, 2);
    return res;
}
/** dst = asin(x) */
static vec2 vec2_asin_v(const float *vec_x) {
    return vec2_asin(Vec2(vec_x));
}


/** dst = acos(x) */
static vec2 vec2_acos(vec2 vec_x) {
    vec2 res;
    vecN_acos(res.v, vec_x.v, 2);
    return res;
}
/** dst = acos(x) */
static vec2 vec2_acos_v(const float *vec_x) {
    return vec2_acos(Vec2(vec_x));
}


/** dst = atan(x) */
static vec2 vec2_atan(vec2 vec_x) {
    vec2 res;
    vecN_atan(res.v, vec_x.v, 2);
    return res;
}
/** dst = atan(x) */
static vec2 vec2_atan_v(const float *vec_x) {
    return vec2_atan(Vec2(vec_x));
}


/** dst = atan2(y, x) */
static vec2 vec2_atan2(vec2 vec_y, vec2 vec_x) {
    vec2 res;
    vecN_atan2(res.v, vec_y.v, vec_x.v, 2);
    return res;
}
/** dst = atan2(y, x) */
static vec2 vec2_atan2_v(const float *vec_y, const float *vec_x) {
    return vec2_atan2(Vec2(vec_y), Vec2(vec_x));
}


/** dst = pow(x, y) */
static vec2 vec2_pow(vec2 vec_x, float y) {
    vec2 res;
    vecN_pow(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = pow(x, y) */
static vec2 vec2_pow_v(const float *vec_x, float y) {
    return vec2_pow(Vec2(vec_x), y);
}


/** dst = pow(x, y) */
static vec2 vec2_pow_vec(vec2 vec_x, vec2 vec_y) {
    vec2 res;
    vecN_pow_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = pow(x, y) */
static vec2 vec2_pow_vec_v(const float *vec_x, const float *vec_y) {
    return vec2_pow_vec(Vec2(vec_x), Vec2(vec_y));
}


/** dst = exp(x) */
static vec2 vec2_exp(vec2 vec_x) {
    vec2 res;
    vecN_exp(res.v, vec_x.v, 2);
    return res;
}
/** dst = exp(x) */
static vec2 vec2_exp_v(const float *vec_x) {
    return vec2_exp(Vec2(vec_x));
}


/** dst = log(x) */
static vec2 vec2_log(vec2 vec_x) {
    vec2 res;
    vecN_log(res.v, vec_x.v, 2);
    return res;
}
/** dst = log(x) */
static vec2 vec2_log_v(const float *vec_x) {
    return vec2_log(Vec2(vec_x));
}


/** dst = exp2(x) */
static vec2 vec2_exp2(vec2 vec_x) {
    vec2 res;
    vecN_exp2(res.v, vec_x.v, 2);
    return res;
}
/** dst = exp2(x) */
static vec2 vec2_exp2_v(const float *vec_x) {
    return vec2_exp2(Vec2(vec_x));
}


/** dst = log2(x) */
static vec2 vec2_log2(vec2 vec_x) {
    vec2 res;
    vecN_log2(res.v, vec_x.v, 2);
    return res;
}
/** dst = log2(x) */
static vec2 vec2_log2_v(const float *vec_x) {
    return vec2_log2(Vec2(vec_x));
}


/** dst = sqrt(x) */
static vec2 vec2_sqrt(vec2 vec_x) {
    vec2 res;
    vecN_sqrt(res.v, vec_x.v, 2);
    return res;
}
/** dst = sqrt(x) */
static vec2 vec2_sqrt_v(const float *vec_x) {
    return vec2_sqrt(Vec2(vec_x));
}


/** dst = 1 / sqrt(x) */
static vec2 vec2_inversesqrt(vec2 vec_x) {
    vec2 res;
    vecN_inversesqrt(res.v, vec_x.v, 2);
    return res;
}
/** dst = 1 / sqrt(x) */
static vec2 vec2_inversesqrt_v(const float *vec_x) {
    return vec2_inversesqrt(Vec2(vec_x));
}


/** dst = abs(x) */
static vec2 vec2_abs(vec2 vec_x) {
    vec2 res;
    vecN_abs(res.v, vec_x.v, 2);
    return res;
}
/** dst = abs(x) */
static vec2 vec2_abs_v(const float *vec_x) {
    return vec2_abs(Vec2(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec2 vec2_sign(vec2 vec_x) {
    vec2 res;
    vecN_sign(res.v, vec_x.v, 2);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec2 vec2_sign_v(const float *vec_x) {
    return vec2_sign(Vec2(vec_x));
}


/** dst = floor(x) */
static vec2 vec2_floor(vec2 vec_x) {
    vec2 res;
    vecN_floor(res.v, vec_x.v, 2);
    return res;
}
/** dst = floor(x) */
static vec2 vec2_floor_v(const float *vec_x) {
    return vec2_floor(Vec2(vec_x));
}


/** dst = ceil(x) */
static vec2 vec2_ceil(vec2 vec_x) {
    vec2 res;
    vecN_ceil(res.v, vec_x.v, 2);
    return res;
}
/** dst = ceil(x) */
static vec2 vec2_ceil_v(const float *vec_x) {
    return vec2_ceil(Vec2(vec_x));
}


/** dst = x - floor(x) */
static vec2 vec2_fract(vec2 vec_x) {
    vec2 res;
    vecN_fract(res.v, vec_x.v, 2);
    return res;
}
/** dst = x - floor(x) */
static vec2 vec2_fract_v(const float *vec_x) {
    return vec2_fract(Vec2(vec_x));
}


/** dst = x - y * floor(x/y) */
static vec2 vec2_mod(vec2 vec_x, float y) {
    vec2 res;
    vecN_mod(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = x - y * floor(x/y) */
static vec2 vec2_mod_v(const float *vec_x, float y) {
    return vec2_mod(Vec2(vec_x), y);
}


/** dst = x - y * floor(x/y) */
static vec2 vec2_mod_vec(vec2 vec_x, vec2 vec_y) {
    vec2 res;
    vecN_mod_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = x - y * floor(x/y) */
static vec2 vec2_mod_vec_v(const float *vec_x, const float *vec_y) {
    return vec2_mod_vec(Vec2(vec_x), Vec2(vec_y));
}


/** dst = a < b ? a : b */
static vec2 vec2_min(vec2 vec_x, float y) {
    vec2 res;
    vecN_min(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a < b ? a : b */
static vec2 vec2_min_v(const float *vec_x, float y) {
    return vec2_min(Vec2(vec_x), y);
}


/** dst = a < b ? a : b */
static vec2 vec2_min_vec(vec2 vec_x, vec2 vec_y) {
    vec2 res;
    vecN_min_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a < b ? a : b */
static vec2 vec2_min_vec_v(const float *vec_x, const float *vec_y) {
    return vec2_min_vec(Vec2(vec_x), Vec2(vec_y));
}


/** dst = a > b ? a : b */
static vec2 vec2_max(vec2 vec_x, float y) {
    vec2 res;
    vecN_max(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a > b ? a : b */
static vec2 vec2_max_v(const float *vec_x, float y) {
    return vec2_max(Vec2(vec_x), y);
}


/** dst = a > b ? a : b */
static vec2 vec2_max_vec(vec2 vec_x, vec2 vec_y) {
    vec2 res;
    vecN_max_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a > b ? a : b */
static vec2 vec2_max_vec_v(const float *vec_x, const float *vec_y) {
    return vec2_max_vec(Vec2(vec_x), Vec2(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec2 vec2_clamp(vec2 vec_x, float min, float max) {
    vec2 res;
    vecN_clamp(res.v, vec_x.v, min, max, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static vec2 vec2_clamp_v(const float *vec_x, float min, float max) {
    return vec2_clamp(Vec2(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec2 vec2_clamp_vec(vec2 vec_x, vec2 vec_min, vec2 vec_max) {
    vec2 res;
    vecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static vec2 vec2_clamp_vec_v(const float *vec_x, const float *vec_min, const float *vec_max) {
    return vec2_clamp_vec(Vec2(vec_x), Vec2(vec_min), Vec2(vec_max));
}


/** dst = a * (1-t) + b * t */
static vec2 vec2_mix(vec2 vec_a, vec2 vec_b, float t) {
    vec2 res;
    vecN_mix(res.v, vec_a.v, vec_b.v, t, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static vec2 vec2_mix_v(const float *vec_a, const float *vec_b, float t) {
    return vec2_mix(Vec2(vec_a), Vec2(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static vec2 vec2_mix_vec(vec2 vec_a, vec2 vec_b, vec2 vec_t) {
    vec2 res;
    vecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t.v, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static vec2 vec2_mix_vec_v(const float *vec_a, const float *vec_b, const float *vec_t) {
    return vec2_mix_vec(Vec2(vec_a), Vec2(vec_b), Vec2(vec_t));
}


/** dst = x < edge ? 0 : 1 */
static vec2 vec2_step(vec2 vec_x, float edge) {
    vec2 res;
    vecN_step(res.v, vec_x.v, edge, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static vec2 vec2_step_v(const float *vec_x, float edge) {
    return vec2_step(Vec2(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static vec2 vec2_step_vec(vec2 vec_x, vec2 vec_edge) {
    vec2 res;
    vecN_step_vec(res.v, vec_x.v, vec_edge.v, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static vec2 vec2_step_vec_v(const float *vec_x, const float *vec_edge) {
    return vec2_step_vec(Vec2(vec_x), Vec2(vec_edge));
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec2 vec2_smoothstep(vec2 vec_x, float edge1, float edge2) {
    vec2 res;
    vecN_smoothstep(res.v, vec_x.v, edge1, edge2, 2);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec2 vec2_smoothstep_v(const float *vec_x, float edge1, float edge2) {
    return vec2_smoothstep(Vec2(vec_x), edge1, edge2);
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec2 vec2_smoothstep_vec(vec2 vec_x, vec2 vec_edge1, vec2 vec_edge2) {
    vec2 res;
    vecN_smoothstep_vec(res.v, vec_x.v, vec_edge1.v, vec_edge2.v, 2);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static vec2 vec2_smoothstep_vec_v(const float *vec_x, const float *vec_edge1, const float *vec_edge2) {
    return vec2_smoothstep_vec(Vec2(vec_x), Vec2(vec_edge1), Vec2(vec_edge2));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static float vec2_sum(vec2 vec) {
    return vecN_sum(vec.v, 2);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static float vec2_sum_v(const float *vec) {
    return vec2_sum(Vec2(vec));
}


/** returns a dot b */
static float vec2_dot(vec2 vec_a, vec2 vec_b) {
    return vecN_dot(vec_a.v, vec_b.v, 2);
}
/** returns a dot b */
static float vec2_dot_v(const float *vec_a, const float *vec_b) {
    return vec2_dot(Vec2(vec_a), Vec2(vec_b));
}


/** returns ||vec||_2 */
static float vec2_norm(vec2 vec) {
    return vecN_norm(vec.v, 2);
}
/** returns ||vec||_2 */
static float vec2_norm_v(const float *vec) {
    return vec2_norm(Vec2(vec));
}


/** returns ||vec||_p */
static float vec2_norm_p(vec2 vec, float p) {
    return vecN_norm_p(vec.v, p, 2);
}
/** returns ||vec||_p */
static float vec2_norm_p_v(const float *vec, float p) {
    return vec2_norm_p(Vec2(vec), p);
}


/** returns ||vec||_1 */
static float vec2_norm_1(vec2 vec) {
    return vecN_norm_1(vec.v, 2);
}
/** returns ||vec||_1 */
static float vec2_norm_1_v(const float *vec) {
    return vec2_norm_1(Vec2(vec));
}


/** returns ||vec||_inf */
static float vec2_norm_inf(vec2 vec) {
    return vecN_norm_inf(vec.v, 2);
}
/** returns ||vec||_inf */
static float vec2_norm_inf_v(const float *vec) {
    return vec2_norm_inf(Vec2(vec));
}


/** dst = vec / norm(vec) */
static vec2 vec2_normalize_unsafe(vec2 vec) {
    vec2 res;
    vecN_normalize_unsafe(res.v, vec.v, 2);
    return res;
}
/** dst = vec / norm(vec) */
static vec2 vec2_normalize_unsafe_v(const float *vec) {
    return vec2_normalize_unsafe(Vec2(vec));
}


/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static vec2 vec2_normalize(vec2 vec) {
    vec2 res;
    vecN_normalize(res.v, vec.v, 2);
    return res;
}
/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static vec2 vec2_normalize_v(const float *vec) {
    return vec2_normalize(Vec2(vec));
}


/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec2_length(vec2 vec) {
    return vecN_length(vec.v, 2);
}
/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec2_length_v(const float *vec) {
    return vec2_length(Vec2(vec));
}


/** returns norm(b-a) */
static float vec2_distance(vec2 vec_a, vec2 vec_b) {
    return vecN_distance(vec_a.v, vec_b.v, 2);
}
/** returns norm(b-a) */
static float vec2_distance_v(const float *vec_a, const float *vec_b) {
    return vec2_distance(Vec2(vec_a), Vec2(vec_b));
}


/** dst = dot(I, Nref) < 0 ? N : -N */
static vec2 vec2_faceforward(vec2 vec_N, vec2 vec_I, vec2 vec_Nref) {
    vec2 res;
    vecN_faceforward(res.v, vec_N.v, vec_I.v, vec_Nref.v, 2);
    return res;
}
/** dst = dot(I, Nref) < 0 ? N : -N */
static vec2 vec2_faceforward_v(const float *vec_N, const float *vec_I, const float *vec_Nref) {
    return vec2_faceforward(Vec2(vec_N), Vec2(vec_I), Vec2(vec_Nref));
}


/** dst = I - 2.0 * N * dot(N,I) */
static vec2 vec2_reflect(vec2 vec_I, vec2 vec_N) {
    vec2 res;
    vecN_reflect(res.v, vec_I.v, vec_N.v, 2);
    return res;
}
/** dst = I - 2.0 * N * dot(N,I) */
static vec2 vec2_reflect_v(const float *vec_I, const float *vec_N) {
    return vec2_reflect(Vec2(vec_I), Vec2(vec_N));
}


static vec2 vec2_refract(vec2 vec_I, vec2 vec_N, float eta) {
    vec2 res;
    vecN_refract(res.v, vec_I.v, vec_N.v, eta, 2);
    return res;
}
static vec2 vec2_refract_v(const float *vec_I, const float *vec_N, float eta) {
    return vec2_refract(Vec2(vec_I), Vec2(vec_N), eta);
}


/** dst = a < b */
static bvec2 vec2_less_than(vec2 vec_a, float b) {
    bvec2 res;
    vecN_less_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a < b */
static bvec2 vec2_less_than_v(const float *vec_a, float b) {
    return vec2_less_than(Vec2(vec_a), b);
}


/** dst = a < b */
static bvec2 vec2_less_than_vec(vec2 vec_a, vec2 vec_b) {
    bvec2 res;
    vecN_less_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a < b */
static bvec2 vec2_less_than_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_less_than_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a <= b */
static bvec2 vec2_less_than_equal(vec2 vec_a, float b) {
    bvec2 res;
    vecN_less_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a <= b */
static bvec2 vec2_less_than_equal_v(const float *vec_a, float b) {
    return vec2_less_than_equal(Vec2(vec_a), b);
}


/** dst = a <= b */
static bvec2 vec2_less_than_equal_vec(vec2 vec_a, vec2 vec_b) {
    bvec2 res;
    vecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a <= b */
static bvec2 vec2_less_than_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_less_than_equal_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a > b */
static bvec2 vec2_greater_than(vec2 vec_a, float b) {
    bvec2 res;
    vecN_greater_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a > b */
static bvec2 vec2_greater_than_v(const float *vec_a, float b) {
    return vec2_greater_than(Vec2(vec_a), b);
}


/** dst = a > b */
static bvec2 vec2_greater_than_vec(vec2 vec_a, vec2 vec_b) {
    bvec2 res;
    vecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a > b */
static bvec2 vec2_greater_than_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_greater_than_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a >= b */
static bvec2 vec2_greater_than_equal(vec2 vec_a, float b) {
    bvec2 res;
    vecN_greater_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a >= b */
static bvec2 vec2_greater_than_equal_v(const float *vec_a, float b) {
    return vec2_greater_than_equal(Vec2(vec_a), b);
}


/** dst = a >= b */
static bvec2 vec2_greater_than_equal_vec(vec2 vec_a, vec2 vec_b) {
    bvec2 res;
    vecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a >= b */
static bvec2 vec2_greater_than_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_greater_than_equal_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a == b */
static bvec2 vec2_equal(vec2 vec_a, float b) {
    bvec2 res;
    vecN_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a == b */
static bvec2 vec2_equal_v(const float *vec_a, float b) {
    return vec2_equal(Vec2(vec_a), b);
}


/** dst = a == b */
static bvec2 vec2_equal_vec(vec2 vec_a, vec2 vec_b) {
    bvec2 res;
    vecN_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a == b */
static bvec2 vec2_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_equal_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a != b */
static bvec2 vec2_not_equal(vec2 vec_a, float b) {
    bvec2 res;
    vecN_not_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a != b */
static bvec2 vec2_not_equal_v(const float *vec_a, float b) {
    return vec2_not_equal(Vec2(vec_a), b);
}


/** dst = a != b */
static bvec2 vec2_not_equal_vec(vec2 vec_a, vec2 vec_b) {
    bvec2 res;
    vecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a != b */
static bvec2 vec2_not_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec2_not_equal_vec(Vec2(vec_a), Vec2(vec_b));
}


/** dst = a == b (+-eps) */
static bvec2 vec2_equal_eps(vec2 vec_a, float b, float eps) {
    bvec2 res;
    vecN_equal_eps(res.v, vec_a.v, b, eps, 2);
    return res;
}
/** dst = a == b (+-eps) */
static bvec2 vec2_equal_eps_v(const float *vec_a, float b, float eps) {
    return vec2_equal_eps(Vec2(vec_a), b, eps);
}


/** dst = a == b (+-eps) */
static bvec2 vec2_equal_eps_vec(vec2 vec_a, vec2 vec_b, float eps) {
    bvec2 res;
    vecN_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 2);
    return res;
}
/** dst = a == b (+-eps) */
static bvec2 vec2_equal_eps_vec_v(const float *vec_a, const float *vec_b, float eps) {
    return vec2_equal_eps_vec(Vec2(vec_a), Vec2(vec_b), eps);
}


/** dst = a != b (+-eps) */
static bvec2 vec2_not_equal_eps(vec2 vec_a, float b, float eps) {
    bvec2 res;
    vecN_not_equal_eps(res.v, vec_a.v, b, eps, 2);
    return res;
}
/** dst = a != b (+-eps) */
static bvec2 vec2_not_equal_eps_v(const float *vec_a, float b, float eps) {
    return vec2_not_equal_eps(Vec2(vec_a), b, eps);
}


/** dst = a != b (+-eps) */
static bvec2 vec2_not_equal_eps_vec(vec2 vec_a, vec2 vec_b, float eps) {
    bvec2 res;
    vecN_not_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 2);
    return res;
}
/** dst = a != b (+-eps) */
static bvec2 vec2_not_equal_eps_vec_v(const float *vec_a, const float *vec_b, float eps) {
    return vec2_not_equal_eps_vec(Vec2(vec_a), Vec2(vec_b), eps);
}

/** dst = isnan(a) */
static bvec2 vec2_isnan(vec2 vec) {
    bvec2 res;
    vecN_isnan(res.v, vec.v, 2);
    return res;
}
/** dst = isnan(a) */
static bvec2 vec2_isnan_v(const float *vec) {
    return vec2_isnan(Vec2(vec));
}

/** dst = isnan(a) */
static bvec2 vec2_not_isnan(vec2 vec) {
    bvec2 res;
    vecN_not_isnan(res.v, vec.v, 2);
    return res;
}
/** dst = isnan(a) */
static bvec2 vec2_not_isnan_v(const float *vec) {
    return vec2_not_isnan(Vec2(vec));
}

#endif //MATHC_VEC_VEC2_H
