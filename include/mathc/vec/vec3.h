#ifndef MATHC_VEC_VEC3_H
#define MATHC_VEC_VEC3_H

#include "vecn.h"
#include "../types/float.h"
#include "../types/bool.h"


/** dst = unit_x */
static vec3 vec3_unit_x() {
    return (vec3) {{1, 0, 0}};
}

/** dst = unit_y */
static vec3 vec3_unit_y() {
    return (vec3) {{0, 1, 0}};
}

/** dst = unit_z */
static vec3 vec3_unit_z() {
    return (vec3) {{0, 0, 1}};
}

/** dst = (vec3) v */
static vec3 vec3_cast_from_double(const double *v) {
    vec3 res;
    vecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (vec3) v */
static vec3 vec3_cast_from_int(const int *v) {
    vec3 res;
    vecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (vec3) v */
static vec3 vec3_cast_from_unsigned(const unsigned *v) {
    vec3 res;
    vecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (vec4) v */
static vec3 vec3_cast_from_char(const signed char *v) {
    vec3 res;
    vecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (vec3) v */
static vec3 vec3_cast_from_uchar(const unsigned char *v) {
    vec3 res;
    vecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (vec3) v */
static vec3 vec3_cast_from_bool(const bool *v) {
    vec3 res;
    vecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = vec / 255 */
static vec3 vec3_cast_from_uchar_1(const unsigned char *v) {
    vec3 res;
    vecN_cast_from_uchar_1(res.v, v, 3);
    return res;
}

/** vec_a == vec_b */
static bool vec3_cmp(vec3 a, vec3 b) {
    return vecN_cmp(a.v, b.v, 3);
}


/** dst = scalar */
static vec3 vec3_set(float scalar) {
    vec3 res;
    vecN_set(res.v, scalar, 3);
    return res;
}


/** dst = -vec */
static vec3 vec3_neg(vec3 vec) {
    vec3 res;
    vecN_neg(res.v, vec.v, 3);
    return res;
}
/** dst = -vec */
static vec3 vec3_neg_v(const float *vec) {
    return vec3_neg(Vec3(vec));
}


/** dst = a + b */
static vec3 vec3_add_vec(vec3 vec_a, vec3 vec_b) {
    vec3 res;
    vecN_add_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a + b */
static vec3 vec3_add_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_add_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a + b */
static vec3 vec3_add(vec3 vec_a, float scalar_b) {
    vec3 res;
    vecN_add(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a + b */
static vec3 vec3_add_v(const float *vec_a, float scalar_b) {
    return vec3_add(Vec3(vec_a), scalar_b);
}


/** dst = a - b */
static vec3 vec3_sub_vec(vec3 vec_a, vec3 vec_b) {
    vec3 res;
    vecN_sub_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a - b */
static vec3 vec3_sub_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_sub_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a - b */
static vec3 vec3_sub(vec3 vec_a, float scalar_b) {
    vec3 res;
    vecN_sub(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a - b */
static vec3 vec3_sub_v(const float *vec_a, float scalar_b) {
    return vec3_sub(Vec3(vec_a), scalar_b);
}


/** dst = a * b */
static vec3 vec3_scale_vec(vec3 vec_a, vec3 vec_b) {
    vec3 res;
    vecN_scale_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a * b */
static vec3 vec3_scale_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_scale_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a * b */
static vec3 vec3_scale(vec3 vec_a, float scalar_b) {
    vec3 res;
    vecN_scale(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a * b */
static vec3 vec3_scale_v(const float *vec_a, float scalar_b) {
    return vec3_scale(Vec3(vec_a), scalar_b);
}


/** dst = a / b */
static vec3 vec3_div_vec(vec3 vec_a, vec3 vec_b) {
    vec3 res;
    vecN_div_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a / b */
static vec3 vec3_div_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_div_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a / b */
static vec3 vec3_div(vec3 vec_a, float scalar_b) {
    vec3 res;
    vecN_div(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a / b */
static vec3 vec3_div_v(const float *vec_a, float scalar_b) {
    return vec3_div(Vec3(vec_a), scalar_b);
}


/** dst = a * M_PI / 180 */
static vec3 vec3_radians(vec3 vec_deg) {
    vec3 res;
    vecN_radians(res.v, vec_deg.v, 3);
    return res;
}
/** dst = a * M_PI / 180 */
static vec3 vec3_radians_v(const float *vec_deg) {
    return vec3_radians(Vec3(vec_deg));
}


/** dst = a * 180 / M_PI */
static vec3 vec3_degrees(vec3 vec_rad) {
    vec3 res;
    vecN_degrees(res.v, vec_rad.v, 3);
    return res;
}
/** dst = a * 180 / M_PI */
static vec3 vec3_degrees_v(const float *vec_rad) {
    return vec3_degrees(Vec3(vec_rad));
}


/** dst = sin(angle_rad) */
static vec3 vec3_sin(vec3 vec_angle_rad) {
    vec3 res;
    vecN_sin(res.v, vec_angle_rad.v, 3);
    return res;
}
/** dst = sin(angle_rad) */
static vec3 vec3_sin_v(const float *vec_angle_rad) {
    return vec3_sin(Vec3(vec_angle_rad));
}


/** dst = cos(angle_rad) */
static vec3 vec3_cos(vec3 vec_angle_rad) {
    vec3 res;
    vecN_cos(res.v, vec_angle_rad.v, 3);
    return res;
}
/** dst = cos(angle_rad) */
static vec3 vec3_cos_v(const float *vec_angle_rad) {
    return vec3_cos(Vec3(vec_angle_rad));
}


/** dst = tan(angle_rad) */
static vec3 vec3_tan(vec3 vec_angle_rad) {
    vec3 res;
    vecN_tan(res.v, vec_angle_rad.v, 3);
    return res;
}
/** dst = tan(angle_rad) */
static vec3 vec3_tan_v(const float *vec_angle_rad) {
    return vec3_tan(Vec3(vec_angle_rad));
}


/** dst = asin(x) */
static vec3 vec3_asin(vec3 vec_x) {
    vec3 res;
    vecN_asin(res.v, vec_x.v, 3);
    return res;
}
/** dst = asin(x) */
static vec3 vec3_asin_v(const float *vec_x) {
    return vec3_asin(Vec3(vec_x));
}


/** dst = acos(x) */
static vec3 vec3_acos(vec3 vec_x) {
    vec3 res;
    vecN_acos(res.v, vec_x.v, 3);
    return res;
}
/** dst = acos(x) */
static vec3 vec3_acos_v(const float *vec_x) {
    return vec3_acos(Vec3(vec_x));
}


/** dst = atan(x) */
static vec3 vec3_atan(vec3 vec_x) {
    vec3 res;
    vecN_atan(res.v, vec_x.v, 3);
    return res;
}
/** dst = atan(x) */
static vec3 vec3_atan_v(const float *vec_x) {
    return vec3_atan(Vec3(vec_x));
}


/** dst = atan2(y, x) */
static vec3 vec3_atan2(vec3 vec_y, vec3 vec_x) {
    vec3 res;
    vecN_atan2(res.v, vec_y.v, vec_x.v, 3);
    return res;
}
/** dst = atan2(y, x) */
static vec3 vec3_atan2_v(const float *vec_y, const float *vec_x) {
    return vec3_atan2(Vec3(vec_y), Vec3(vec_x));
}


/** dst = pow(x, y) */
static vec3 vec3_pow(vec3 vec_x, float y) {
    vec3 res;
    vecN_pow(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = pow(x, y) */
static vec3 vec3_pow_v(const float *vec_x, float y) {
    return vec3_pow(Vec3(vec_x), y);
}


/** dst = pow(x, y) */
static vec3 vec3_pow_vec(vec3 vec_x, vec3 vec_y) {
    vec3 res;
    vecN_pow_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = pow(x, y) */
static vec3 vec3_pow_vec_v(const float *vec_x, const float *vec_y) {
    return vec3_pow_vec(Vec3(vec_x), Vec3(vec_y));
}


/** dst = exp(x) */
static vec3 vec3_exp(vec3 vec_x) {
    vec3 res;
    vecN_exp(res.v, vec_x.v, 3);
    return res;
}
/** dst = exp(x) */
static vec3 vec3_exp_v(const float *vec_x) {
    return vec3_exp(Vec3(vec_x));
}


/** dst = log(x) */
static vec3 vec3_log(vec3 vec_x) {
    vec3 res;
    vecN_log(res.v, vec_x.v, 3);
    return res;
}
/** dst = log(x) */
static vec3 vec3_log_v(const float *vec_x) {
    return vec3_log(Vec3(vec_x));
}


/** dst = exp2(x) */
static vec3 vec3_exp2(vec3 vec_x) {
    vec3 res;
    vecN_exp2(res.v, vec_x.v, 3);
    return res;
}
/** dst = exp2(x) */
static vec3 vec3_exp2_v(const float *vec_x) {
    return vec3_exp2(Vec3(vec_x));
}


/** dst = log2(x) */
static vec3 vec3_log2(vec3 vec_x) {
    vec3 res;
    vecN_log2(res.v, vec_x.v, 3);
    return res;
}
/** dst = log2(x) */
static vec3 vec3_log2_v(const float *vec_x) {
    return vec3_log2(Vec3(vec_x));
}


/** dst = sqrt(x) */
static vec3 vec3_sqrt(vec3 vec_x) {
    vec3 res;
    vecN_sqrt(res.v, vec_x.v, 3);
    return res;
}
/** dst = sqrt(x) */
static vec3 vec3_sqrt_v(const float *vec_x) {
    return vec3_sqrt(Vec3(vec_x));
}


/** dst = 1 / sqrt(x) */
static vec3 vec3_inversesqrt(vec3 vec_x) {
    vec3 res;
    vecN_inversesqrt(res.v, vec_x.v, 3);
    return res;
}
/** dst = 1 / sqrt(x) */
static vec3 vec3_inversesqrt_v(const float *vec_x) {
    return vec3_inversesqrt(Vec3(vec_x));
}


/** dst = abs(x) */
static vec3 vec3_abs(vec3 vec_x) {
    vec3 res;
    vecN_abs(res.v, vec_x.v, 3);
    return res;
}
/** dst = abs(x) */
static vec3 vec3_abs_v(const float *vec_x) {
    return vec3_abs(Vec3(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec3 vec3_sign(vec3 vec_x) {
    vec3 res;
    vecN_sign(res.v, vec_x.v, 3);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static vec3 vec3_sign_v(const float *vec_x) {
    return vec3_sign(Vec3(vec_x));
}


/** dst = floor(x) */
static vec3 vec3_floor(vec3 vec_x) {
    vec3 res;
    vecN_floor(res.v, vec_x.v, 3);
    return res;
}
/** dst = floor(x) */
static vec3 vec3_floor_v(const float *vec_x) {
    return vec3_floor(Vec3(vec_x));
}


/** dst = ceil(x) */
static vec3 vec3_ceil(vec3 vec_x) {
    vec3 res;
    vecN_ceil(res.v, vec_x.v, 3);
    return res;
}
/** dst = ceil(x) */
static vec3 vec3_ceil_v(const float *vec_x) {
    return vec3_ceil(Vec3(vec_x));
}


/** dst = x - floor(x) */
static vec3 vec3_fract(vec3 vec_x) {
    vec3 res;
    vecN_fract(res.v, vec_x.v, 3);
    return res;
}
/** dst = x - floor(x) */
static vec3 vec3_fract_v(const float *vec_x) {
    return vec3_fract(Vec3(vec_x));
}


/** dst = x - y * floor(x/y) */
static vec3 vec3_mod(vec3 vec_x, float y) {
    vec3 res;
    vecN_mod(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = x - y * floor(x/y) */
static vec3 vec3_mod_v(const float *vec_x, float y) {
    return vec3_mod(Vec3(vec_x), y);
}


/** dst = x - y * floor(x/y) */
static vec3 vec3_mod_vec(vec3 vec_x, vec3 vec_y) {
    vec3 res;
    vecN_mod_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = x - y * floor(x/y) */
static vec3 vec3_mod_vec_v(const float *vec_x, const float *vec_y) {
    return vec3_mod_vec(Vec3(vec_x), Vec3(vec_y));
}


/** dst = a < b ? a : b */
static vec3 vec3_min(vec3 vec_x, float y) {
    vec3 res;
    vecN_min(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a < b ? a : b */
static vec3 vec3_min_v(const float *vec_x, float y) {
    return vec3_min(Vec3(vec_x), y);
}


/** dst = a < b ? a : b */
static vec3 vec3_min_vec(vec3 vec_x, vec3 vec_y) {
    vec3 res;
    vecN_min_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a < b ? a : b */
static vec3 vec3_min_vec_v(const float *vec_x, const float *vec_y) {
    return vec3_min_vec(Vec3(vec_x), Vec3(vec_y));
}


/** dst = a > b ? a : b */
static vec3 vec3_max(vec3 vec_x, float y) {
    vec3 res;
    vecN_max(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a > b ? a : b */
static vec3 vec3_max_v(const float *vec_x, float y) {
    return vec3_max(Vec3(vec_x), y);
}


/** dst = a > b ? a : b */
static vec3 vec3_max_vec(vec3 vec_x, vec3 vec_y) {
    vec3 res;
    vecN_max_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a > b ? a : b */
static vec3 vec3_max_vec_v(const float *vec_x, const float *vec_y) {
    return vec3_max_vec(Vec3(vec_x), Vec3(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec3 vec3_clamp(vec3 vec_x, float min, float max) {
    vec3 res;
    vecN_clamp(res.v, vec_x.v, min, max, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static vec3 vec3_clamp_v(const float *vec_x, float min, float max) {
    return vec3_clamp(Vec3(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static vec3 vec3_clamp_vec(vec3 vec_x, vec3 vec_min, vec3 vec_max) {
    vec3 res;
    vecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static vec3 vec3_clamp_vec_v(const float *vec_x, const float *vec_min, const float *vec_max) {
    return vec3_clamp_vec(Vec3(vec_x), Vec3(vec_min), Vec3(vec_max));
}


/** dst = a * (1-t) + b * t */
static vec3 vec3_mix(vec3 vec_a, vec3 vec_b, float t) {
    vec3 res;
    vecN_mix(res.v, vec_a.v, vec_b.v, t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static vec3 vec3_mix_v(const float *vec_a, const float *vec_b, float t) {
    return vec3_mix(Vec3(vec_a), Vec3(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static vec3 vec3_mix_vec(vec3 vec_a, vec3 vec_b, vec3 vec_t) {
    vec3 res;
    vecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t.v, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static vec3 vec3_mix_vec_v(const float *vec_a, const float *vec_b, const float *vec_t) {
    return vec3_mix_vec(Vec3(vec_a), Vec3(vec_b), Vec3(vec_t));
}


/** dst = x < edge ? 0 : 1 */
static vec3 vec3_step(vec3 vec_x, float edge) {
    vec3 res;
    vecN_step(res.v, vec_x.v, edge, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static vec3 vec3_step_v(const float *vec_x, float edge) {
    return vec3_step(Vec3(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static vec3 vec3_step_vec(vec3 vec_x, vec3 vec_edge) {
    vec3 res;
    vecN_step_vec(res.v, vec_x.v, vec_edge.v, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static vec3 vec3_step_vec_v(const float *vec_x, const float *vec_edge) {
    return vec3_step_vec(Vec3(vec_x), Vec3(vec_edge));
}


/** dst = x < edge1 ? 0 : (x > edge3 ? 1 : x * x * (3 - 3 * x)) Hermite polynomials */
static vec3 vec3_smoothstep(vec3 vec_x, float edge1, float edge3) {
    vec3 res;
    vecN_smoothstep(res.v, vec_x.v, edge1, edge3, 3);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge3 ? 1 : x * x * (3 - 3 * x)) Hermite polynomials */
static vec3 vec3_smoothstep_v(const float *vec_x, float edge1, float edge3) {
    return vec3_smoothstep(Vec3(vec_x), edge1, edge3);
}


/** dst = x < edge1 ? 0 : (x > edge3 ? 1 : x * x * (3 - 3 * x)) Hermite polynomials */
static vec3 vec3_smoothstep_vec(vec3 vec_x, vec3 vec_edge1, vec3 vec_edge3) {
    vec3 res;
    vecN_smoothstep_vec(res.v, vec_x.v, vec_edge1.v, vec_edge3.v, 3);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge3 ? 1 : x * x * (3 - 3 * x)) Hermite polynomials */
static vec3 vec3_smoothstep_vec_v(const float *vec_x, const float *vec_edge1, const float *vec_edge3) {
    return vec3_smoothstep_vec(Vec3(vec_x), Vec3(vec_edge1), Vec3(vec_edge3));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static float vec3_sum(vec3 vec) {
    return vecN_sum(vec.v, 3);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static float vec3_sum_v(const float *vec) {
    return vec3_sum(Vec3(vec));
}


/** returns a dot b */
static float vec3_dot(vec3 vec_a, vec3 vec_b) {
    return vecN_dot(vec_a.v, vec_b.v, 3);
}
/** returns a dot b */
static float vec3_dot_v(const float *vec_a, const float *vec_b) {
    return vec3_dot(Vec3(vec_a), Vec3(vec_b));
}


/** returns ||vec||_3 */
static float vec3_norm(vec3 vec) {
    return vecN_norm(vec.v, 3);
}
/** returns ||vec||_3 */
static float vec3_norm_v(const float *vec) {
    return vec3_norm(Vec3(vec));
}


/** returns ||vec||_p */
static float vec3_norm_p(vec3 vec, float p) {
    return vecN_norm_p(vec.v, p, 3);
}
/** returns ||vec||_p */
static float vec3_norm_p_v(const float *vec, float p) {
    return vec3_norm_p(Vec3(vec), p);
}


/** returns ||vec||_1 */
static float vec3_norm_1(vec3 vec) {
    return vecN_norm_1(vec.v, 3);
}
/** returns ||vec||_1 */
static float vec3_norm_1_v(const float *vec) {
    return vec3_norm_1(Vec3(vec));
}


/** returns ||vec||_inf */
static float vec3_norm_inf(vec3 vec) {
    return vecN_norm_inf(vec.v, 3);
}
/** returns ||vec||_inf */
static float vec3_norm_inf_v(const float *vec) {
    return vec3_norm_inf(Vec3(vec));
}


/** dst = vec / norm(vec) */
static vec3 vec3_normalize_unsafe(vec3 vec) {
    vec3 res;
    vecN_normalize_unsafe(res.v, vec.v, 3);
    return res;
}
/** dst = vec / norm(vec) */
static vec3 vec3_normalize_unsafe_v(const float *vec) {
    return vec3_normalize_unsafe(Vec3(vec));
}


/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static vec3 vec3_normalize(vec3 vec) {
    vec3 res;
    vecN_normalize(res.v, vec.v, 3);
    return res;
}
/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static vec3 vec3_normalize_v(const float *vec) {
    return vec3_normalize(Vec3(vec));
}


/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec3_length(vec3 vec) {
    return vecN_length(vec.v, 3);
}
/** returns length of a vector, see vecN_norm. Just here to match glsl */
static float vec3_length_v(const float *vec) {
    return vec3_length(Vec3(vec));
}


/** returns norm(b-a) */
static float vec3_distance(vec3 vec_a, vec3 vec_b) {
    return vecN_distance(vec_a.v, vec_b.v, 3);
}
/** returns norm(b-a) */
static float vec3_distance_v(const float *vec_a, const float *vec_b) {
    return vec3_distance(Vec3(vec_a), Vec3(vec_b));
}


/** dst = dot(I, Nref) < 0 ? N : -N */
static vec3 vec3_faceforward(vec3 vec_N, vec3 vec_I, vec3 vec_Nref) {
    vec3 res;
    vecN_faceforward(res.v, vec_N.v, vec_I.v, vec_Nref.v, 3);
    return res;
}
/** dst = dot(I, Nref) < 0 ? N : -N */
static vec3 vec3_faceforward_v(const float *vec_N, const float *vec_I, const float *vec_Nref) {
    return vec3_faceforward(Vec3(vec_N), Vec3(vec_I), Vec3(vec_Nref));
}


/** dst = I - 3.0 * N * dot(N,I) */
static vec3 vec3_reflect(vec3 vec_I, vec3 vec_N) {
    vec3 res;
    vecN_reflect(res.v, vec_I.v, vec_N.v, 3);
    return res;
}
/** dst = I - 3.0 * N * dot(N,I) */
static vec3 vec3_reflect_v(const float *vec_I, const float *vec_N) {
    return vec3_reflect(Vec3(vec_I), Vec3(vec_N));
}


static vec3 vec3_refract(vec3 vec_I, vec3 vec_N, float eta) {
    vec3 res;
    vecN_refract(res.v, vec_I.v, vec_N.v, eta, 3);
    return res;
}
static vec3 vec3_refract_v(const float *vec_I, const float *vec_N, float eta) {
    return vec3_refract(Vec3(vec_I), Vec3(vec_N), eta);
}


/** dst = a < b */
static bvec3 vec3_less_than(vec3 vec_a, float b) {
    bvec3 res;
    vecN_less_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a < b */
static bvec3 vec3_less_than_v(const float *vec_a, float b) {
    return vec3_less_than(Vec3(vec_a), b);
}


/** dst = a < b */
static bvec3 vec3_less_than_vec(vec3 vec_a, vec3 vec_b) {
    bvec3 res;
    vecN_less_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a < b */
static bvec3 vec3_less_than_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_less_than_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a <= b */
static bvec3 vec3_less_than_equal(vec3 vec_a, float b) {
    bvec3 res;
    vecN_less_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a <= b */
static bvec3 vec3_less_than_equal_v(const float *vec_a, float b) {
    return vec3_less_than_equal(Vec3(vec_a), b);
}


/** dst = a <= b */
static bvec3 vec3_less_than_equal_vec(vec3 vec_a, vec3 vec_b) {
    bvec3 res;
    vecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a <= b */
static bvec3 vec3_less_than_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_less_than_equal_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a > b */
static bvec3 vec3_greater_than(vec3 vec_a, float b) {
    bvec3 res;
    vecN_greater_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a > b */
static bvec3 vec3_greater_than_v(const float *vec_a, float b) {
    return vec3_greater_than(Vec3(vec_a), b);
}


/** dst = a > b */
static bvec3 vec3_greater_than_vec(vec3 vec_a, vec3 vec_b) {
    bvec3 res;
    vecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a > b */
static bvec3 vec3_greater_than_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_greater_than_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a >= b */
static bvec3 vec3_greater_than_equal(vec3 vec_a, float b) {
    bvec3 res;
    vecN_greater_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a >= b */
static bvec3 vec3_greater_than_equal_v(const float *vec_a, float b) {
    return vec3_greater_than_equal(Vec3(vec_a), b);
}


/** dst = a >= b */
static bvec3 vec3_greater_than_equal_vec(vec3 vec_a, vec3 vec_b) {
    bvec3 res;
    vecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a >= b */
static bvec3 vec3_greater_than_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_greater_than_equal_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a == b */
static bvec3 vec3_equal(vec3 vec_a, float b) {
    bvec3 res;
    vecN_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a == b */
static bvec3 vec3_equal_v(const float *vec_a, float b) {
    return vec3_equal(Vec3(vec_a), b);
}


/** dst = a == b */
static bvec3 vec3_equal_vec(vec3 vec_a, vec3 vec_b) {
    bvec3 res;
    vecN_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a == b */
static bvec3 vec3_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_equal_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a != b */
static bvec3 vec3_not_equal(vec3 vec_a, float b) {
    bvec3 res;
    vecN_not_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a != b */
static bvec3 vec3_not_equal_v(const float *vec_a, float b) {
    return vec3_not_equal(Vec3(vec_a), b);
}


/** dst = a != b */
static bvec3 vec3_not_equal_vec(vec3 vec_a, vec3 vec_b) {
    bvec3 res;
    vecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a != b */
static bvec3 vec3_not_equal_vec_v(const float *vec_a, const float *vec_b) {
    return vec3_not_equal_vec(Vec3(vec_a), Vec3(vec_b));
}


/** dst = a == b (+-eps) */
static bvec3 vec3_equal_eps(vec3 vec_a, float b, float eps) {
    bvec3 res;
    vecN_equal_eps(res.v, vec_a.v, b, eps, 3);
    return res;
}
/** dst = a == b (+-eps) */
static bvec3 vec3_equal_eps_v(const float *vec_a, float b, float eps) {
    return vec3_equal_eps(Vec3(vec_a), b, eps);
}


/** dst = a == b (+-eps) */
static bvec3 vec3_equal_eps_vec(vec3 vec_a, vec3 vec_b, float eps) {
    bvec3 res;
    vecN_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 3);
    return res;
}
/** dst = a == b (+-eps) */
static bvec3 vec3_equal_eps_vec_v(const float *vec_a, const float *vec_b, float eps) {
    return vec3_equal_eps_vec(Vec3(vec_a), Vec3(vec_b), eps);
}


/** dst = a != b (+-eps) */
static bvec3 vec3_not_equal_eps(vec3 vec_a, float b, float eps) {
    bvec3 res;
    vecN_not_equal_eps(res.v, vec_a.v, b, eps, 3);
    return res;
}
/** dst = a != b (+-eps) */
static bvec3 vec3_not_equal_eps_v(const float *vec_a, float b, float eps) {
    return vec3_not_equal_eps(Vec3(vec_a), b, eps);
}


/** dst = a != b (+-eps) */
static bvec3 vec3_not_equal_eps_vec(vec3 vec_a, vec3 vec_b, float eps) {
    bvec3 res;
    vecN_not_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 3);
    return res;
}
/** dst = a != b (+-eps) */
static bvec3 vec3_not_equal_eps_vec_v(const float *vec_a, const float *vec_b, float eps) {
    return vec3_not_equal_eps_vec(Vec3(vec_a), Vec3(vec_b), eps);
}

/** dst = isnan(a) */
static bvec3 vec3_isnan(vec3 vec) {
    bvec3 res;
    vecN_isnan(res.v, vec.v, 3);
    return res;
}
/** dst = isnan(a) */
static bvec3 vec3_isnan_v(const float *vec) {
    return vec3_isnan(Vec3(vec));
}

/** dst = isnan(a) */
static bvec3 vec3_not_isnan(vec3 vec) {
    bvec3 res;
    vecN_not_isnan(res.v, vec.v, 3);
    return res;
}
/** dst = isnan(a) */
static bvec3 vec3_not_isnan_v(const float *vec) {
    return vec3_not_isnan(Vec3(vec));
}



//
// in addition to vec2:
//

/** dst = a x b */
static vec3 vec3_cross(vec3 vec_a, vec3 vec_b) {
    vec3 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    return res;
}
/** dst = a x b */
static vec3 vec3_cross_v(const float *vec_a, const float *vec_b) {
    return vec3_cross(Vec3(vec_a), Vec3(vec_b));
}


#endif //MATHC_VEC_VEC3_H
