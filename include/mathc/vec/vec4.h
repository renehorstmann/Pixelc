#ifndef MATHC_VEC_VEC4_H
#define MATHC_VEC_VEC4_H

#include "vecn.h"
#include "../types/float.h"
#include "../types/bool.h"


/** dst = unit_x */
static vec4 vec4_unit_x() {
    return (vec4) {{1, 0, 0, 0}};
}

/** dst = unit_y */
static vec4 vec4_unit_y() {
    return (vec4) {{0, 1, 0, 0}};
}

/** dst = unit_z */
static vec4 vec4_unit_z() {
    return (vec4) {{0, 0, 1, 0}};
}

/** dst = unit_w */
static vec4 vec4_unit_w() {
    return (vec4) {{0, 0, 0, 1}};
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_double(const double *v) {
    vec4 res;
    vecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_int(const int *v) {
    vec4 res;
    vecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_unsigned(const unsigned *v) {
    vec4 res;
    vecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_char(const signed char *v) {
    vec4 res;
    vecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_uchar(const unsigned char *v) {
    vec4 res;
    vecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (vec4) v */
static vec4 vec4_cast_from_bool(const bool *v) {
    vec4 res;
    vecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = vec / 255 */
static vec4 vec4_cast_from_uchar_1(const unsigned char *v) {
    vec4 res;
    vecN_cast_from_uchar_1(res.v, v, 4);
    return res;
}

/** vec_a == vec_b */
static bool vec4_cmp(vec4 a, vec4 b) {
    return vecN_cmp(a.v, b.v, 4);
}

/** dst = scalar */
static vec4 vec4_set(float scalar) {
    vec4 res;
    vecN_set(res.v, scalar, 4);
    return res;
}


/** dst = -vec */
static vec4 vec4_neg(vec4 vec) {
    vec4 res;
    vecN_neg(res.v, vec.v, 4);
    return res;
}
/** dst = -vec */
static vec4 vec4_neg_v(const float *vec) {
    return vec4_neg(Vec4(vec));
}


/** dst = a + b */
static vec4 vec4_add_vec(vec4 vec_a, vec4 vec_b) {
    vec4 res;
    vecN_add_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a + b */
static vec4 vec4_add_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_add_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a + b */
static vec4 vec4_add(vec4 vec_a, float scalar_b) {
    vec4 res;
    vecN_add(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a + b */
static vec4 vec4_add_v(const float *vec_a, float scalar_b) {
    return vec4_add(Vec4(vec_a), scalar_b);
}


/** dst = a - b */
static vec4 vec4_sub_vec(vec4 vec_a, vec4 vec_b) {
    vec4 res;
    vecN_sub_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a - b */
static vec4 vec4_sub_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_sub_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a - b */
static vec4 vec4_sub(vec4 vec_a, float scalar_b) {
    vec4 res;
    vecN_sub(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a - b */
static vec4 vec4_sub_v(const float *vec_a, float scalar_b) {
    return vec4_sub(Vec4(vec_a), scalar_b);
}


/** dst = a * b */
static vec4 vec4_scale_vec(vec4 vec_a, vec4 vec_b) {
    vec4 res;
    vecN_scale_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a * b */
static vec4 vec4_scale_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_scale_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a * b */
static vec4 vec4_scale(vec4 vec_a, float scalar_b) {
    vec4 res;
    vecN_scale(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a * b */
static vec4 vec4_scale_v(const float *vec_a, float scalar_b) {
    return vec4_scale(Vec4(vec_a), scalar_b);
}


/** dst = a / b */
static vec4 vec4_div_vec(vec4 vec_a, vec4 vec_b) {
    vec4 res;
    vecN_div_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a / b */
static vec4 vec4_div_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_div_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a / b */
static vec4 vec4_div(vec4 vec_a, float scalar_b) {
    vec4 res;
    vecN_div(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a / b */
static vec4 vec4_div_v(const float *vec_a, float scalar_b) {
    return vec4_div(Vec4(vec_a), scalar_b);
}


/** dst = a * M_PI / 180 */
static vec4 vec4_radians(vec4 vec_deg) {
    vec4 res;
    vecN_radians(res.v, vec_deg.v, 4);
    return res;
}
/** dst = a * M_PI / 180 */
static vec4 vec4_radians_v(const float *vec_deg) {
    return vec4_radians(Vec4(vec_deg));
}


/** dst = a * 180 / M_PI */
static vec4 vec4_degrees(vec4 vec_rad) {
    vec4 res;
    vecN_degrees(res.v, vec_rad.v, 4);
    return res;
}
/** dst = a * 180 / M_PI */
static vec4 vec4_degrees_v(const float *vec_rad) {
    return vec4_degrees(Vec4(vec_rad));
}


/** dst = sin(angle_rad) */
static vec4 vec4_sin(vec4 vec_angle_rad) {
    vec4 res;
    vecN_sin(res.v, vec_angle_rad.v, 4);
    return res;
}
/** dst = sin(angle_rad) */
static vec4 vec4_sin_v(const float *vec_angle_rad) {
    return vec4_sin(Vec4(vec_angle_rad));
}


/** dst = cos(angle_rad) */
static vec4 vec4_cos(vec4 vec_angle_rad) {
    vec4 res;
    vecN_cos(res.v, vec_angle_rad.v, 4);
    return res;
}
/** dst = cos(angle_rad) */
static vec4 vec4_cos_v(const float *vec_angle_rad) {
    return vec4_cos(Vec4(vec_angle_rad));
}


/** dst = tan(angle_rad) */
static vec4 vec4_tan(vec4 vec_angle_rad) {
    vec4 res;
    vecN_tan(res.v, vec_angle_rad.v, 4);
    return res;
}
/** dst = tan(angle_rad) */
static vec4 vec4_tan_v(const float *vec_angle_rad) {
    return vec4_tan(Vec4(vec_angle_rad));
}


/** dst = asin(x) */
static vec4 vec4_asin(vec4 vec_x) {
    vec4 res;
    vecN_asin(res.v, vec_x.v, 4);
    return res;
}
/** dst = asin(x) */
static vec4 vec4_asin_v(const float *vec_x) {
    return vec4_asin(Vec4(vec_x));
}


/** dst = acos(x) */
static vec4 vec4_acos(vec4 vec_x) {
    vec4 res;
    vecN_acos(res.v, vec_x.v, 4);
    return res;
}
/** dst = acos(x) */
static vec4 vec4_acos_v(const float *vec_x) {
    return vec4_acos(Vec4(vec_x));
}


/** dst = atan(x) */
static vec4 vec4_atan(vec4 vec_x) {
    vec4 res;
    vecN_atan(res.v, vec_x.v, 4);
    return res;
}
/** dst = atan(x) */
static vec4 vec4_atan_v(const float *vec_x) {
    return vec4_atan(Vec4(vec_x));
}


/** dst = atan2(y, x) */
static vec4 vec4_atan2(vec4 vec_y, vec4 vec_x) {
    vec4 res;
    vecN_atan2(res.v, vec_y.v, vec_x.v, 4);
    return res;
}
/** dst = atan2(y, x) */
static vec4 vec4_atan2_v(const float *vec_y, const float *vec_x) {
    return vec4_atan2(Vec4(vec_y), Vec4(vec_x));
}


/** dst = pow(x, y) */
static vec4 vec4_pow(vec4 vec_x, float y) {
    vec4 res;
    vecN_pow(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = pow(x, y) */
static vec4 vec4_pow_v(const float *vec_x, float y) {
    return vec4_pow(Vec4(vec_x), y);
}


/** dst = pow(x, y) */
static vec4 vec4_pow_vec(vec4 vec_x, vec4 vec_y) {
    vec4 res;
    vecN_pow_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = pow(x, y) */
static vec4 vec4_pow_vec_v(const float *vec_x, const float *vec_y) {
    return vec4_pow_vec(Vec4(vec_x), Vec4(vec_y));
}


/** dst = exp(x) */
static vec4 vec4_exp(vec4 vec_x) {
    vec4 res;
    vecN_exp(res.v, vec_x.v, 4);
    return res;
}
/** dst = exp(x) */
static vec4 vec4_exp_v(const float *vec_x) {
    return vec4_exp(Vec4(vec_x));
}


/** dst = log(x) */
static vec4 vec4_log(vec4 vec_x) {
    vec4 res;
    vecN_log(res.v, vec_x.v, 4);
    return res;
}
/** dst = log(x) */
static vec4 vec4_log_v(const float *vec_x) {
    return vec4_log(Vec4(vec_x));
}


/** dst = exp2(x) */
static vec4 vec4_exp2(vec4 vec_x) {
    vec4 res;
    vecN_exp2(res.v, vec_x.v, 4);
    return res;
}
/** dst = exp2(x) */
static vec4 vec4_exp2_v(const float *vec_x) {
    return vec4_exp2(Vec4(vec_x));
}


/** dst = log2(x) */
static vec4 vec4_log2(vec4 vec_x) {
    vec4 res;
    vecN_log2(res.v, vec_x.v, 4);
    return res;
}
/** dst = log2(x) */
static vec4 vec4_log2_v(const float *vec_x) {
    return vec4_log2(Vec4(vec_x));
}


/** dst = sqrt(x) */
static vec4 vec4_sqrt(vec4 vec_x) {
    vec4 res;
    vecN_sqrt(res.v, vec_x.v, 4);
    return res;
}
/** dst = sqrt(x) */
static vec4 vec4_sqrt_v(const float *vec_x) {
    return vec4_sqrt(Vec4(vec_x));
}


/** dst = 1 / sqrt(x) */
static vec4 vec4_inversesqrt(vec4 vec_x) {
    vec4 res;
    vecN_inversesqrt(res.v, vec_x.v, 4);
    return res;
}
/** dst = 1 / sqrt(x) */
static vec4 vec4_inversesqrt_v(const float *vec_x) {
    return vec4_inversesqrt(Vec4(vec_x));
}


/** dst = abs(x) */
static vec4 vec4_abs(vec4 vec_x) {
    vec4 res;
    vecN_abs(res.v, vec_x.v, 4);
    return res;
}
/** dst = abs(x) */
static vec4 vec4_abs_v(const float *vec_x) {
    return vec4_abs(Vec4(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec4 vec4_sign(vec4 vec_x) {
    vec4 res;
    vecN_sign(res.v, vec_x.v, 4);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec4 vec4_sign_v(const float *vec_x) {
    return vec4_sign(Vec4(vec_x));
}


/** dst = floor(x) */
static vec4 vec4_floor(vec4 vec_x) {
    vec4 res;
    vecN_floor(res.v, vec_x.v, 4);
    return res;
}
/** dst = floor(x) */
static vec4 vec4_floor_v(const float *vec_x) {
    return vec4_floor(Vec4(vec_x));
}


/** dst = ceil(x) */
static vec4 vec4_ceil(vec4 vec_x) {
    vec4 res;
    vecN_ceil(res.v, vec_x.v, 4);
    return res;
}
/** dst = ceil(x) */
static vec4 vec4_ceil_v(const float *vec_x) {
    return vec4_ceil(Vec4(vec_x));
}


/** dst = x - floor(x) */
static vec4 vec4_fract(vec4 vec_x) {
    vec4 res;
    vecN_fract(res.v, vec_x.v, 4);
    return res;
}
/** dst = x - floor(x) */
static vec4 vec4_fract_v(const float *vec_x) {
    return vec4_fract(Vec4(vec_x));
}


/** dst = x - y * floor(x/y) */
static vec4 vec4_mod(vec4 vec_x, float y) {
    vec4 res;
    vecN_mod(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = x - y * floor(x/y) */
static vec4 vec4_mod_v(const float *vec_x, float y) {
    return vec4_mod(Vec4(vec_x), y);
}


/** dst = x - y * floor(x/y) */
static vec4 vec4_mod_vec(vec4 vec_x, vec4 vec_y) {
    vec4 res;
    vecN_mod_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = x - y * floor(x/y) */
static vec4 vec4_mod_vec_v(const float *vec_x, const float *vec_y) {
    return vec4_mod_vec(Vec4(vec_x), Vec4(vec_y));
}


/** dst = a < b ? a : b */
static vec4 vec4_min(vec4 vec_x, float y) {
    vec4 res;
    vecN_min(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a < b ? a : b */
static vec4 vec4_min_v(const float *vec_x, float y) {
    return vec4_min(Vec4(vec_x), y);
}


/** dst = a < b ? a : b */
static vec4 vec4_min_vec(vec4 vec_x, vec4 vec_y) {
    vec4 res;
    vecN_min_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a < b ? a : b */
static vec4 vec4_min_vec_v(const float *vec_x, const float *vec_y) {
    return vec4_min_vec(Vec4(vec_x), Vec4(vec_y));
}


/** dst = a > b ? a : b */
static vec4 vec4_max(vec4 vec_x, float y) {
    vec4 res;
    vecN_max(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a > b ? a : b */
static vec4 vec4_max_v(const float *vec_x, float y) {
    return vec4_max(Vec4(vec_x), y);
}


/** dst = a > b ? a : b */
static vec4 vec4_max_vec(vec4 vec_x, vec4 vec_y) {
    vec4 res;
    vecN_max_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a > b ? a : b */
static vec4 vec4_max_vec_v(const float *vec_x, const float *vec_y) {
    return vec4_max_vec(Vec4(vec_x), Vec4(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec4 vec4_clamp(vec4 vec_x, float min, float max) {
    vec4 res;
    vecN_clamp(res.v, vec_x.v, min, max, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static vec4 vec4_clamp_v(const float *vec_x, float min, float max) {
    return vec4_clamp(Vec4(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec4 vec4_clamp_vec(vec4 vec_x, vec4 vec_min, vec4 vec_max) {
    vec4 res;
    vecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static vec4 vec4_clamp_vec_v(const float *vec_x, const float *vec_min, const float *vec_max) {
    return vec4_clamp_vec(Vec4(vec_x), Vec4(vec_min), Vec4(vec_max));
}


/** dst = a * (1-t) + b * t */
static vec4 vec4_mix(vec4 vec_a, vec4 vec_b, float t) {
    vec4 res;
    vecN_mix(res.v, vec_a.v, vec_b.v, t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static vec4 vec4_mix_v(const float *vec_a, const float *vec_b, float t) {
    return vec4_mix(Vec4(vec_a), Vec4(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static vec4 vec4_mix_vec(vec4 vec_a, vec4 vec_b, vec4 vec_t) {
    vec4 res;
    vecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t.v, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static vec4 vec4_mix_vec_v(const float *vec_a, const float *vec_b, const float *vec_t) {
    return vec4_mix_vec(Vec4(vec_a), Vec4(vec_b), Vec4(vec_t));
}


/** dst = x < edge ? 0 : 1 */
static vec4 vec4_step(vec4 vec_x, float edge) {
    vec4 res;
    vecN_step(res.v, vec_x.v, edge, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static vec4 vec4_step_v(const float *vec_x, float edge) {
    return vec4_step(Vec4(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static vec4 vec4_step_vec(vec4 vec_x, vec4 vec_edge) {
    vec4 res;
    vecN_step_vec(res.v, vec_x.v, vec_edge.v, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static vec4 vec4_step_vec_v(const float *vec_x, const float *vec_edge) {
    return vec4_step_vec(Vec4(vec_x), Vec4(vec_edge));
}


/** dst = x < edge1 ? 0 : (x > edge4 ? 1 : x * x * (4 - 4 * x)) Hermite polynomials */
static vec4 vec4_smoothstep(vec4 vec_x, float edge1, float edge4) {
    vec4 res;
    vecN_smoothstep(res.v, vec_x.v, edge1, edge4, 4);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge4 ? 1 : x * x * (4 - 4 * x)) Hermite polynomials */
static vec4 vec4_smoothstep_v(const float *vec_x, float edge1, float edge4) {
    return vec4_smoothstep(Vec4(vec_x), edge1, edge4);
}


/** dst = x < edge1 ? 0 : (x > edge4 ? 1 : x * x * (4 - 4 * x)) Hermite polynomials */
static vec4 vec4_smoothstep_vec(vec4 vec_x, vec4 vec_edge1, vec4 vec_edge4) {
    vec4 res;
    vecN_smoothstep_vec(res.v, vec_x.v, vec_edge1.v, vec_edge4.v, 4);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge4 ? 1 : x * x * (4 - 4 * x)) Hermite polynomials */
static vec4 vec4_smoothstep_vec_v(const float *vec_x, const float *vec_edge1, const float *vec_edge4) {
    return vec4_smoothstep_vec(Vec4(vec_x), Vec4(vec_edge1), Vec4(vec_edge4));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static float vec4_sum(vec4 vec) {
    return vecN_sum(vec.v, 4);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static float vec4_sum_v(const float *vec) {
    return vec4_sum(Vec4(vec));
}


/** returns a dot b */
static float vec4_dot(vec4 vec_a, vec4 vec_b) {
    return vecN_dot(vec_a.v, vec_b.v, 4);
}
/** returns a dot b */
static float vec4_dot_v(const float *vec_a, const float *vec_b) {
    return vec4_dot(Vec4(vec_a), Vec4(vec_b));
}


/** returns ||vec||_4 */
static float vec4_norm(vec4 vec) {
    return vecN_norm(vec.v, 4);
}
/** returns ||vec||_4 */
static float vec4_norm_v(const float *vec) {
    return vec4_norm(Vec4(vec));
}


/** returns ||vec||_p */
static float vec4_norm_p(vec4 vec, float p) {
    return vecN_norm_p(vec.v, p, 4);
}
/** returns ||vec||_p */
static float vec4_norm_p_v(const float *vec, float p) {
    return vec4_norm_p(Vec4(vec), p);
}


/** returns ||vec||_1 */
static float vec4_norm_1(vec4 vec) {
    return vecN_norm_1(vec.v, 4);
}
/** returns ||vec||_1 */
static float vec4_norm_1_v(const float *vec) {
    return vec4_norm_1(Vec4(vec));
}


/** returns ||vec||_inf */
static float vec4_norm_inf(vec4 vec) {
    return vecN_norm_inf(vec.v, 4);
}
/** returns ||vec||_inf */
static float vec4_norm_inf_v(const float *vec) {
    return vec4_norm_inf(Vec4(vec));
}


/** dst = vec / norm(vec) */
static vec4 vec4_normalize_unsafe(vec4 vec) {
    vec4 res;
    vecN_normalize_unsafe(res.v, vec.v, 4);
    return res;
}
/** dst = vec / norm(vec) */
static vec4 vec4_normalize_unsafe_v(const float *vec) {
    return vec4_normalize_unsafe(Vec4(vec));
}


/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static vec4 vec4_normalize(vec4 vec) {
    vec4 res;
    vecN_normalize(res.v, vec.v, 4);
    return res;
}
/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static vec4 vec4_normalize_v(const float *vec) {
    return vec4_normalize(Vec4(vec));
}


/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec4_length(vec4 vec) {
    return vecN_length(vec.v, 4);
}
/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec4_length_v(const float *vec) {
    return vec4_length(Vec4(vec));
}


/** returns norm(b-a) */
static float vec4_distance(vec4 vec_a, vec4 vec_b) {
    return vecN_distance(vec_a.v, vec_b.v, 4);
}
/** returns norm(b-a) */
static float vec4_distance_v(const float *vec_a, const float *vec_b) {
    return vec4_distance(Vec4(vec_a), Vec4(vec_b));
}


/** dst = dot(I, Nref) < 0 ? N : -N */
static vec4 vec4_faceforward(vec4 vec_N, vec4 vec_I, vec4 vec_Nref) {
    vec4 res;
    vecN_faceforward(res.v, vec_N.v, vec_I.v, vec_Nref.v, 4);
    return res;
}
/** dst = dot(I, Nref) < 0 ? N : -N */
static vec4 vec4_faceforward_v(const float *vec_N, const float *vec_I, const float *vec_Nref) {
    return vec4_faceforward(Vec4(vec_N), Vec4(vec_I), Vec4(vec_Nref));
}


/** dst = I - 4.0 * N * dot(N,I) */
static vec4 vec4_reflect(vec4 vec_I, vec4 vec_N) {
    vec4 res;
    vecN_reflect(res.v, vec_I.v, vec_N.v, 4);
    return res;
}
/** dst = I - 4.0 * N * dot(N,I) */
static vec4 vec4_reflect_v(const float *vec_I, const float *vec_N) {
    return vec4_reflect(Vec4(vec_I), Vec4(vec_N));
}


static vec4 vec4_refract(vec4 vec_I, vec4 vec_N, float eta) {
    vec4 res;
    vecN_refract(res.v, vec_I.v, vec_N.v, eta, 4);
    return res;
}
static vec4 vec4_refract_v(const float *vec_I, const float *vec_N, float eta) {
    return vec4_refract(Vec4(vec_I), Vec4(vec_N), eta);
}


/** dst = a < b */
static bvec4 vec4_less_than(vec4 vec_a, float b) {
    bvec4 res;
    vecN_less_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a < b */
static bvec4 vec4_less_than_v(const float *vec_a, float b) {
    return vec4_less_than(Vec4(vec_a), b);
}


/** dst = a < b */
static bvec4 vec4_less_than_vec(vec4 vec_a, vec4 vec_b) {
    bvec4 res;
    vecN_less_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a < b */
static bvec4 vec4_less_than_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_less_than_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a <= b */
static bvec4 vec4_less_than_equal(vec4 vec_a, float b) {
    bvec4 res;
    vecN_less_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a <= b */
static bvec4 vec4_less_than_equal_v(const float *vec_a, float b) {
    return vec4_less_than_equal(Vec4(vec_a), b);
}


/** dst = a <= b */
static bvec4 vec4_less_than_equal_vec(vec4 vec_a, vec4 vec_b) {
    bvec4 res;
    vecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a <= b */
static bvec4 vec4_less_than_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_less_than_equal_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a > b */
static bvec4 vec4_greater_than(vec4 vec_a, float b) {
    bvec4 res;
    vecN_greater_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a > b */
static bvec4 vec4_greater_than_v(const float *vec_a, float b) {
    return vec4_greater_than(Vec4(vec_a), b);
}


/** dst = a > b */
static bvec4 vec4_greater_than_vec(vec4 vec_a, vec4 vec_b) {
    bvec4 res;
    vecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a > b */
static bvec4 vec4_greater_than_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_greater_than_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a >= b */
static bvec4 vec4_greater_than_equal(vec4 vec_a, float b) {
    bvec4 res;
    vecN_greater_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a >= b */
static bvec4 vec4_greater_than_equal_v(const float *vec_a, float b) {
    return vec4_greater_than_equal(Vec4(vec_a), b);
}


/** dst = a >= b */
static bvec4 vec4_greater_than_equal_vec(vec4 vec_a, vec4 vec_b) {
    bvec4 res;
    vecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a >= b */
static bvec4 vec4_greater_than_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_greater_than_equal_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a == b */
static bvec4 vec4_equal(vec4 vec_a, float b) {
    bvec4 res;
    vecN_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a == b */
static bvec4 vec4_equal_v(const float *vec_a, float b) {
    return vec4_equal(Vec4(vec_a), b);
}


/** dst = a == b */
static bvec4 vec4_equal_vec(vec4 vec_a, vec4 vec_b) {
    bvec4 res;
    vecN_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a == b */
static bvec4 vec4_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_equal_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a != b */
static bvec4 vec4_not_equal(vec4 vec_a, float b) {
    bvec4 res;
    vecN_not_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a != b */
static bvec4 vec4_not_equal_v(const float *vec_a, float b) {
    return vec4_not_equal(Vec4(vec_a), b);
}


/** dst = a != b */
static bvec4 vec4_not_equal_vec(vec4 vec_a, vec4 vec_b) {
    bvec4 res;
    vecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a != b */
static bvec4 vec4_not_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec4_not_equal_vec(Vec4(vec_a), Vec4(vec_b));
}


/** dst = a == b (+-eps) */
static bvec4 vec4_equal_eps(vec4 vec_a, float b, float eps) {
    bvec4 res;
    vecN_equal_eps(res.v, vec_a.v, b, eps, 4);
    return res;
}
/** dst = a == b (+-eps) */
static bvec4 vec4_equal_eps_v(const float *vec_a, float b, float eps) {
    return vec4_equal_eps(Vec4(vec_a), b, eps);
}


/** dst = a == b (+-eps) */
static bvec4 vec4_equal_eps_vec(vec4 vec_a, vec4 vec_b, float eps) {
    bvec4 res;
    vecN_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 4);
    return res;
}
/** dst = a == b (+-eps) */
static bvec4 vec4_equal_eps_vec_v(const float *vec_a, const float *vec_b, float eps) {
    return vec4_equal_eps_vec(Vec4(vec_a), Vec4(vec_b), eps);
}


/** dst = a != b (+-eps) */
static bvec4 vec4_not_equal_eps(vec4 vec_a, float b, float eps) {
    bvec4 res;
    vecN_not_equal_eps(res.v, vec_a.v, b, eps, 4);
    return res;
}
/** dst = a != b (+-eps) */
static bvec4 vec4_not_equal_eps_v(const float *vec_a, float b, float eps) {
    return vec4_not_equal_eps(Vec4(vec_a), b, eps);
}


/** dst = a != b (+-eps) */
static bvec4 vec4_not_equal_eps_vec(vec4 vec_a, vec4 vec_b, float eps) {
    bvec4 res;
    vecN_not_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 4);
    return res;
}
/** dst = a != b (+-eps) */
static bvec4 vec4_not_equal_eps_vec_v(const float *vec_a, const float *vec_b, float eps) {
    return vec4_not_equal_eps_vec(Vec4(vec_a), Vec4(vec_b), eps);
}

/** dst = isnan(a) */
static bvec4 vec4_isnan(vec4 vec) {
    bvec4 res;
    vecN_isnan(res.v, vec.v, 4);
    return res;
}
/** dst = isnan(a) */
static bvec4 vec4_isnan_v(const float *vec) {
    return vec4_isnan(Vec4(vec));
}

/** dst = isnan(a) */
static bvec4 vec4_not_isnan(vec4 vec) {
    bvec4 res;
    vecN_not_isnan(res.v, vec.v, 4);
    return res;
}
/** dst = isnan(a) */
static bvec4 vec4_not_isnan_v(const float *vec) {
    return vec4_not_isnan(Vec4(vec));
}



//
// in addition to vec2:
//


/** dst = a x b , dst.w = 0 */
static vec4 vec4_cross(vec4 vec_a, vec4 vec_b) {
    vec4 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    res.w = 0;
    return res;
}
/** dst = a x b , dst.w = 0 */
static vec4 vec4_cross_v(const float *vec_a, const float *vec_b) {
    return vec4_cross(Vec4(vec_a), Vec4(vec_b));
}


#endif //MATHC_VEC_VEC4_H
