#ifndef MATHC_VEC_DVEC2_H
#define MATHC_VEC_DVEC2_H

#include "dvecn.h"
#include "../types/double.h"
#include "../types/bool.h"


/** dst = unit_x */
static dvec2 dvec2_unit_x() {
    return (dvec2) {{1, 0}};
}

/** dst = unit_y */
static dvec2 dvec2_unit_y() {
    return (dvec2) {{0, 1}};
}


/** dst = scalar */
static dvec2 dvec2_set(double scalar) {
    dvec2 res;
    dvecN_set(res.v, scalar, 2);
    return res;
}


/** dst = -vec */
static dvec2 dvec2_neg(dvec2 vec) {
    dvec2 res;
    dvecN_neg(res.v, vec.v, 2);
    return res;
}
/** dst = -vec */
static dvec2 dvec2_neg_v(const double *vec) {
    return dvec2_neg(DVec2(vec));
}


/** dst = a + b */
static dvec2 dvec2_add_vec(dvec2 vec_a, dvec2 vec_b) {
    dvec2 res;
    dvecN_add_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a + b */
static dvec2 dvec2_add_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_add_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a + b */
static dvec2 dvec2_add(dvec2 vec_a, double scalar_b) {
    dvec2 res;
    dvecN_add(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a + b */
static dvec2 dvec2_add_v(const double *vec_a, double scalar_b) {
    return dvec2_add(DVec2(vec_a), scalar_b);
}


/** dst = a - b */
static dvec2 dvec2_sub_vec(dvec2 vec_a, dvec2 vec_b) {
    dvec2 res;
    dvecN_sub_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a - b */
static dvec2 dvec2_sub_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_sub_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a - b */
static dvec2 dvec2_sub(dvec2 vec_a, double scalar_b) {
    dvec2 res;
    dvecN_sub(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a - b */
static dvec2 dvec2_sub_v(const double *vec_a, double scalar_b) {
    return dvec2_sub(DVec2(vec_a), scalar_b);
}


/** dst = a * b */
static dvec2 dvec2_scale_vec(dvec2 vec_a, dvec2 vec_b) {
    dvec2 res;
    dvecN_scale_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a * b */
static dvec2 dvec2_scale_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_scale_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a * b */
static dvec2 dvec2_scale(dvec2 vec_a, double scalar_b) {
    dvec2 res;
    dvecN_scale(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a * b */
static dvec2 dvec2_scale_v(const double *vec_a, double scalar_b) {
    return dvec2_scale(DVec2(vec_a), scalar_b);
}


/** dst = a / b */
static dvec2 dvec2_div_vec(dvec2 vec_a, dvec2 vec_b) {
    dvec2 res;
    dvecN_div_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a / b */
static dvec2 dvec2_div_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_div_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a / b */
static dvec2 dvec2_div(dvec2 vec_a, double scalar_b) {
    dvec2 res;
    dvecN_div(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a / b */
static dvec2 dvec2_div_v(const double *vec_a, double scalar_b) {
    return dvec2_div(DVec2(vec_a), scalar_b);
}


/** dst = a * M_PI / 180 */
static dvec2 dvec2_radians(dvec2 vec_deg) {
    dvec2 res;
    dvecN_radians(res.v, vec_deg.v, 2);
    return res;
}
/** dst = a * M_PI / 180 */
static dvec2 dvec2_radians_v(const double *vec_deg) {
    return dvec2_radians(DVec2(vec_deg));
}


/** dst = a * 180 / M_PI */
static dvec2 dvec2_degrees(dvec2 vec_rad) {
    dvec2 res;
    dvecN_degrees(res.v, vec_rad.v, 2);
    return res;
}
/** dst = a * 180 / M_PI */
static dvec2 dvec2_degrees_v(const double *vec_rad) {
    return dvec2_degrees(DVec2(vec_rad));
}


/** dst = sin(angle_rad) */
static dvec2 dvec2_sin(dvec2 vec_angle_rad) {
    dvec2 res;
    dvecN_sin(res.v, vec_angle_rad.v, 2);
    return res;
}
/** dst = sin(angle_rad) */
static dvec2 dvec2_sin_v(const double *vec_angle_rad) {
    return dvec2_sin(DVec2(vec_angle_rad));
}


/** dst = cos(angle_rad) */
static dvec2 dvec2_cos(dvec2 vec_angle_rad) {
    dvec2 res;
    dvecN_cos(res.v, vec_angle_rad.v, 2);
    return res;
}
/** dst = cos(angle_rad) */
static dvec2 dvec2_cos_v(const double *vec_angle_rad) {
    return dvec2_cos(DVec2(vec_angle_rad));
}


/** dst = tan(angle_rad) */
static dvec2 dvec2_tan(dvec2 vec_angle_rad) {
    dvec2 res;
    dvecN_tan(res.v, vec_angle_rad.v, 2);
    return res;
}
/** dst = tan(angle_rad) */
static dvec2 dvec2_tan_v(const double *vec_angle_rad) {
    return dvec2_tan(DVec2(vec_angle_rad));
}


/** dst = asin(x) */
static dvec2 dvec2_asin(dvec2 vec_x) {
    dvec2 res;
    dvecN_asin(res.v, vec_x.v, 2);
    return res;
}
/** dst = asin(x) */
static dvec2 dvec2_asin_v(const double *vec_x) {
    return dvec2_asin(DVec2(vec_x));
}


/** dst = acos(x) */
static dvec2 dvec2_acos(dvec2 vec_x) {
    dvec2 res;
    dvecN_acos(res.v, vec_x.v, 2);
    return res;
}
/** dst = acos(x) */
static dvec2 dvec2_acos_v(const double *vec_x) {
    return dvec2_acos(DVec2(vec_x));
}


/** dst = atan(x) */
static dvec2 dvec2_atan(dvec2 vec_x) {
    dvec2 res;
    dvecN_atan(res.v, vec_x.v, 2);
    return res;
}
/** dst = atan(x) */
static dvec2 dvec2_atan_v(const double *vec_x) {
    return dvec2_atan(DVec2(vec_x));
}


/** dst = atan2(y, x) */
static dvec2 dvec2_atan2(dvec2 vec_y, dvec2 vec_x) {
    dvec2 res;
    dvecN_atan2(res.v, vec_y.v, vec_x.v, 2);
    return res;
}
/** dst = atan2(y, x) */
static dvec2 dvec2_atan2_v(const double *vec_y, const double *vec_x) {
    return dvec2_atan2(DVec2(vec_y), DVec2(vec_x));
}


/** dst = pow(x, y) */
static dvec2 dvec2_pow(dvec2 vec_x, double y) {
    dvec2 res;
    dvecN_pow(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = pow(x, y) */
static dvec2 dvec2_pow_v(const double *vec_x, double y) {
    return dvec2_pow(DVec2(vec_x), y);
}


/** dst = pow(x, y) */
static dvec2 dvec2_pow_vec(dvec2 vec_x, dvec2 vec_y) {
    dvec2 res;
    dvecN_pow_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = pow(x, y) */
static dvec2 dvec2_pow_vec_v(const double *vec_x, const double *vec_y) {
    return dvec2_pow_vec(DVec2(vec_x), DVec2(vec_y));
}


/** dst = exp(x) */
static dvec2 dvec2_exp(dvec2 vec_x) {
    dvec2 res;
    dvecN_exp(res.v, vec_x.v, 2);
    return res;
}
/** dst = exp(x) */
static dvec2 dvec2_exp_v(const double *vec_x) {
    return dvec2_exp(DVec2(vec_x));
}


/** dst = log(x) */
static dvec2 dvec2_log(dvec2 vec_x) {
    dvec2 res;
    dvecN_log(res.v, vec_x.v, 2);
    return res;
}
/** dst = log(x) */
static dvec2 dvec2_log_v(const double *vec_x) {
    return dvec2_log(DVec2(vec_x));
}


/** dst = exp2(x) */
static dvec2 dvec2_exp2(dvec2 vec_x) {
    dvec2 res;
    dvecN_exp2(res.v, vec_x.v, 2);
    return res;
}
/** dst = exp2(x) */
static dvec2 dvec2_exp2_v(const double *vec_x) {
    return dvec2_exp2(DVec2(vec_x));
}


/** dst = log2(x) */
static dvec2 dvec2_log2(dvec2 vec_x) {
    dvec2 res;
    dvecN_log2(res.v, vec_x.v, 2);
    return res;
}
/** dst = log2(x) */
static dvec2 dvec2_log2_v(const double *vec_x) {
    return dvec2_log2(DVec2(vec_x));
}


/** dst = sqrt(x) */
static dvec2 dvec2_sqrt(dvec2 vec_x) {
    dvec2 res;
    dvecN_sqrt(res.v, vec_x.v, 2);
    return res;
}
/** dst = sqrt(x) */
static dvec2 dvec2_sqrt_v(const double *vec_x) {
    return dvec2_sqrt(DVec2(vec_x));
}


/** dst = 1 / sqrt(x) */
static dvec2 dvec2_inversesqrt(dvec2 vec_x) {
    dvec2 res;
    dvecN_inversesqrt(res.v, vec_x.v, 2);
    return res;
}
/** dst = 1 / sqrt(x) */
static dvec2 dvec2_inversesqrt_v(const double *vec_x) {
    return dvec2_inversesqrt(DVec2(vec_x));
}


/** dst = abs(x) */
static dvec2 dvec2_abs(dvec2 vec_x) {
    dvec2 res;
    dvecN_abs(res.v, vec_x.v, 2);
    return res;
}
/** dst = abs(x) */
static dvec2 dvec2_abs_v(const double *vec_x) {
    return dvec2_abs(DVec2(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec2 dvec2_sign(dvec2 vec_x) {
    dvec2 res;
    dvecN_sign(res.v, vec_x.v, 2);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec2 dvec2_sign_v(const double *vec_x) {
    return dvec2_sign(DVec2(vec_x));
}


/** dst = floor(x) */
static dvec2 dvec2_floor(dvec2 vec_x) {
    dvec2 res;
    dvecN_floor(res.v, vec_x.v, 2);
    return res;
}
/** dst = floor(x) */
static dvec2 dvec2_floor_v(const double *vec_x) {
    return dvec2_floor(DVec2(vec_x));
}


/** dst = ceil(x) */
static dvec2 dvec2_ceil(dvec2 vec_x) {
    dvec2 res;
    dvecN_ceil(res.v, vec_x.v, 2);
    return res;
}
/** dst = ceil(x) */
static dvec2 dvec2_ceil_v(const double *vec_x) {
    return dvec2_ceil(DVec2(vec_x));
}


/** dst = x - floor(x) */
static dvec2 dvec2_fract(dvec2 vec_x) {
    dvec2 res;
    dvecN_fract(res.v, vec_x.v, 2);
    return res;
}
/** dst = x - floor(x) */
static dvec2 dvec2_fract_v(const double *vec_x) {
    return dvec2_fract(DVec2(vec_x));
}


/** dst = x - y * floor(x/y) */
static dvec2 dvec2_mod(dvec2 vec_x, double y) {
    dvec2 res;
    dvecN_mod(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = x - y * floor(x/y) */
static dvec2 dvec2_mod_v(const double *vec_x, double y) {
    return dvec2_mod(DVec2(vec_x), y);
}


/** dst = x - y * floor(x/y) */
static dvec2 dvec2_mod_vec(dvec2 vec_x, dvec2 vec_y) {
    dvec2 res;
    dvecN_mod_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = x - y * floor(x/y) */
static dvec2 dvec2_mod_vec_v(const double *vec_x, const double *vec_y) {
    return dvec2_mod_vec(DVec2(vec_x), DVec2(vec_y));
}


/** dst = a < b ? a : b */
static dvec2 dvec2_min(dvec2 vec_x, double y) {
    dvec2 res;
    dvecN_min(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a < b ? a : b */
static dvec2 dvec2_min_v(const double *vec_x, double y) {
    return dvec2_min(DVec2(vec_x), y);
}


/** dst = a < b ? a : b */
static dvec2 dvec2_min_vec(dvec2 vec_x, dvec2 vec_y) {
    dvec2 res;
    dvecN_min_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a < b ? a : b */
static dvec2 dvec2_min_vec_v(const double *vec_x, const double *vec_y) {
    return dvec2_min_vec(DVec2(vec_x), DVec2(vec_y));
}


/** dst = a > b ? a : b */
static dvec2 dvec2_max(dvec2 vec_x, double y) {
    dvec2 res;
    dvecN_max(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a > b ? a : b */
static dvec2 dvec2_max_v(const double *vec_x, double y) {
    return dvec2_max(DVec2(vec_x), y);
}


/** dst = a > b ? a : b */
static dvec2 dvec2_max_vec(dvec2 vec_x, dvec2 vec_y) {
    dvec2 res;
    dvecN_max_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a > b ? a : b */
static dvec2 dvec2_max_vec_v(const double *vec_x, const double *vec_y) {
    return dvec2_max_vec(DVec2(vec_x), DVec2(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec2 dvec2_clamp(dvec2 vec_x, double min, double max) {
    dvec2 res;
    dvecN_clamp(res.v, vec_x.v, min, max, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static dvec2 dvec2_clamp_v(const double *vec_x, double min, double max) {
    return dvec2_clamp(DVec2(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec2 dvec2_clamp_vec(dvec2 vec_x, dvec2 vec_min, dvec2 vec_max) {
    dvec2 res;
    dvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static dvec2 dvec2_clamp_vec_v(const double *vec_x, const double *vec_min, const double *vec_max) {
    return dvec2_clamp_vec(DVec2(vec_x), DVec2(vec_min), DVec2(vec_max));
}


/** dst = a * (1-t) + b * t */
static dvec2 dvec2_mix(dvec2 vec_a, dvec2 vec_b, double t) {
    dvec2 res;
    dvecN_mix(res.v, vec_a.v, vec_b.v, t, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static dvec2 dvec2_mix_v(const double *vec_a, const double *vec_b, double t) {
    return dvec2_mix(DVec2(vec_a), DVec2(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static dvec2 dvec2_mix_vec(dvec2 vec_a, dvec2 vec_b, dvec2 vec_t) {
    dvec2 res;
    dvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t.v, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static dvec2 dvec2_mix_vec_v(const double *vec_a, const double *vec_b, const double *vec_t) {
    return dvec2_mix_vec(DVec2(vec_a), DVec2(vec_b), DVec2(vec_t));
}


/** dst = x < edge ? 0 : 1 */
static dvec2 dvec2_step(dvec2 vec_x, double edge) {
    dvec2 res;
    dvecN_step(res.v, vec_x.v, edge, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static dvec2 dvec2_step_v(const double *vec_x, double edge) {
    return dvec2_step(DVec2(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static dvec2 dvec2_step_vec(dvec2 vec_x, dvec2 vec_edge) {
    dvec2 res;
    dvecN_step_vec(res.v, vec_x.v, vec_edge.v, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static dvec2 dvec2_step_vec_v(const double *vec_x, const double *vec_edge) {
    return dvec2_step_vec(DVec2(vec_x), DVec2(vec_edge));
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec2 dvec2_smoothstep(dvec2 vec_x, double edge1, double edge2) {
    dvec2 res;
    dvecN_smoothstep(res.v, vec_x.v, edge1, edge2, 2);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec2 dvec2_smoothstep_v(const double *vec_x, double edge1, double edge2) {
    return dvec2_smoothstep(DVec2(vec_x), edge1, edge2);
}


/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec2 dvec2_smoothstep_vec(dvec2 vec_x, dvec2 vec_edge1, dvec2 vec_edge2) {
    dvec2 res;
    dvecN_smoothstep_vec(res.v, vec_x.v, vec_edge1.v, vec_edge2.v, 2);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static dvec2 dvec2_smoothstep_vec_v(const double *vec_x, const double *vec_edge1, const double *vec_edge2) {
    return dvec2_smoothstep_vec(DVec2(vec_x), DVec2(vec_edge1), DVec2(vec_edge2));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static double dvec2_sum(dvec2 vec) {
    return dvecN_sum(vec.v, 2);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static double dvec2_sum_v(const double *vec) {
    return dvec2_sum(DVec2(vec));
}


/** returns a dot b */
static double dvec2_dot(dvec2 vec_a, dvec2 vec_b) {
    return dvecN_dot(vec_a.v, vec_b.v, 2);
}
/** returns a dot b */
static double dvec2_dot_v(const double *vec_a, const double *vec_b) {
    return dvec2_dot(DVec2(vec_a), DVec2(vec_b));
}


/** returns ||vec||_2 */
static double dvec2_norm(dvec2 vec) {
    return dvecN_norm(vec.v, 2);
}
/** returns ||vec||_2 */
static double dvec2_norm_v(const double *vec) {
    return dvec2_norm(DVec2(vec));
}


/** returns ||vec||_p */
static double dvec2_norm_p(dvec2 vec, double p) {
    return dvecN_norm_p(vec.v, p, 2);
}
/** returns ||vec||_p */
static double dvec2_norm_p_v(const double *vec, double p) {
    return dvec2_norm_p(DVec2(vec), p);
}


/** returns ||vec||_1 */
static double dvec2_norm_1(dvec2 vec) {
    return dvecN_norm_1(vec.v, 2);
}
/** returns ||vec||_1 */
static double dvec2_norm_1_v(const double *vec) {
    return dvec2_norm_1(DVec2(vec));
}


/** returns ||vec||_inf */
static double dvec2_norm_inf(dvec2 vec) {
    return dvecN_norm_inf(vec.v, 2);
}
/** returns ||vec||_inf */
static double dvec2_norm_inf_v(const double *vec) {
    return dvec2_norm_inf(DVec2(vec));
}


/** dst = vec / norm(vec) */
static dvec2 dvec2_normalize_unsafe(dvec2 vec) {
    dvec2 res;
    dvecN_normalize_unsafe(res.v, vec.v, 2);
    return res;
}
/** dst = vec / norm(vec) */
static dvec2 dvec2_normalize_unsafe_v(const double *vec) {
    return dvec2_normalize_unsafe(DVec2(vec));
}


/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static dvec2 dvec2_normalize(dvec2 vec) {
    dvec2 res;
    dvecN_normalize(res.v, vec.v, 2);
    return res;
}
/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static dvec2 dvec2_normalize_v(const double *vec) {
    return dvec2_normalize(DVec2(vec));
}


/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec2_length(dvec2 vec) {
    return dvecN_length(vec.v, 2);
}
/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec2_length_v(const double *vec) {
    return dvec2_length(DVec2(vec));
}


/** returns norm(b-a) */
static double dvec2_distance(dvec2 vec_a, dvec2 vec_b) {
    return dvecN_distance(vec_a.v, vec_b.v, 2);
}
/** returns norm(b-a) */
static double dvec2_distance_v(const double *vec_a, const double *vec_b) {
    return dvec2_distance(DVec2(vec_a), DVec2(vec_b));
}


/** dst = dot(I, Nref) < 0 ? N : -N */
static dvec2 dvec2_faceforward(dvec2 vec_N, dvec2 vec_I, dvec2 vec_Nref) {
    dvec2 res;
    dvecN_faceforward(res.v, vec_N.v, vec_I.v, vec_Nref.v, 2);
    return res;
}
/** dst = dot(I, Nref) < 0 ? N : -N */
static dvec2 dvec2_faceforward_v(const double *vec_N, const double *vec_I, const double *vec_Nref) {
    return dvec2_faceforward(DVec2(vec_N), DVec2(vec_I), DVec2(vec_Nref));
}


/** dst = I - 2.0 * N * dot(N,I) */
static dvec2 dvec2_reflect(dvec2 vec_I, dvec2 vec_N) {
    dvec2 res;
    dvecN_reflect(res.v, vec_I.v, vec_N.v, 2);
    return res;
}
/** dst = I - 2.0 * N * dot(N,I) */
static dvec2 dvec2_reflect_v(const double *vec_I, const double *vec_N) {
    return dvec2_reflect(DVec2(vec_I), DVec2(vec_N));
}


static dvec2 dvec2_refract(dvec2 vec_I, dvec2 vec_N, double eta) {
    dvec2 res;
    dvecN_refract(res.v, vec_I.v, vec_N.v, eta, 2);
    return res;
}
static dvec2 dvec2_refract_v(const double *vec_I, const double *vec_N, double eta) {
    return dvec2_refract(DVec2(vec_I), DVec2(vec_N), eta);
}


/** dst = a < b */
static bvec2 dvec2_less_than(dvec2 vec_a, double b) {
    bvec2 res;
    dvecN_less_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a < b */
static bvec2 dvec2_less_than_v(const double *vec_a, double b) {
    return dvec2_less_than(DVec2(vec_a), b);
}


/** dst = a < b */
static bvec2 dvec2_less_than_vec(dvec2 vec_a, dvec2 vec_b) {
    bvec2 res;
    dvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a < b */
static bvec2 dvec2_less_than_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_less_than_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a <= b */
static bvec2 dvec2_less_than_equal(dvec2 vec_a, double b) {
    bvec2 res;
    dvecN_less_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a <= b */
static bvec2 dvec2_less_than_equal_v(const double *vec_a, double b) {
    return dvec2_less_than_equal(DVec2(vec_a), b);
}


/** dst = a <= b */
static bvec2 dvec2_less_than_equal_vec(dvec2 vec_a, dvec2 vec_b) {
    bvec2 res;
    dvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a <= b */
static bvec2 dvec2_less_than_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_less_than_equal_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a > b */
static bvec2 dvec2_greater_than(dvec2 vec_a, double b) {
    bvec2 res;
    dvecN_greater_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a > b */
static bvec2 dvec2_greater_than_v(const double *vec_a, double b) {
    return dvec2_greater_than(DVec2(vec_a), b);
}


/** dst = a > b */
static bvec2 dvec2_greater_than_vec(dvec2 vec_a, dvec2 vec_b) {
    bvec2 res;
    dvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a > b */
static bvec2 dvec2_greater_than_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_greater_than_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a >= b */
static bvec2 dvec2_greater_than_equal(dvec2 vec_a, double b) {
    bvec2 res;
    dvecN_greater_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a >= b */
static bvec2 dvec2_greater_than_equal_v(const double *vec_a, double b) {
    return dvec2_greater_than_equal(DVec2(vec_a), b);
}


/** dst = a >= b */
static bvec2 dvec2_greater_than_equal_vec(dvec2 vec_a, dvec2 vec_b) {
    bvec2 res;
    dvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a >= b */
static bvec2 dvec2_greater_than_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_greater_than_equal_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a == b */
static bvec2 dvec2_equal(dvec2 vec_a, double b) {
    bvec2 res;
    dvecN_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a == b */
static bvec2 dvec2_equal_v(const double *vec_a, double b) {
    return dvec2_equal(DVec2(vec_a), b);
}


/** dst = a == b */
static bvec2 dvec2_equal_vec(dvec2 vec_a, dvec2 vec_b) {
    bvec2 res;
    dvecN_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a == b */
static bvec2 dvec2_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_equal_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a != b */
static bvec2 dvec2_not_equal(dvec2 vec_a, double b) {
    bvec2 res;
    dvecN_not_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a != b */
static bvec2 dvec2_not_equal_v(const double *vec_a, double b) {
    return dvec2_not_equal(DVec2(vec_a), b);
}


/** dst = a != b */
static bvec2 dvec2_not_equal_vec(dvec2 vec_a, dvec2 vec_b) {
    bvec2 res;
    dvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a != b */
static bvec2 dvec2_not_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec2_not_equal_vec(DVec2(vec_a), DVec2(vec_b));
}


/** dst = a == b (+-eps) */
static bvec2 dvec2_equal_eps(dvec2 vec_a, double b, double eps) {
    bvec2 res;
    dvecN_equal_eps(res.v, vec_a.v, b, eps, 2);
    return res;
}
/** dst = a == b (+-eps) */
static bvec2 dvec2_equal_eps_v(const double *vec_a, double b, double eps) {
    return dvec2_equal_eps(DVec2(vec_a), b, eps);
}


/** dst = a == b (+-eps) */
static bvec2 dvec2_equal_eps_vec(dvec2 vec_a, dvec2 vec_b, double eps) {
    bvec2 res;
    dvecN_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 2);
    return res;
}
/** dst = a == b (+-eps) */
static bvec2 dvec2_equal_eps_vec_v(const double *vec_a, const double *vec_b, double eps) {
    return dvec2_equal_eps_vec(DVec2(vec_a), DVec2(vec_b), eps);
}


/** dst = a != b (+-eps) */
static bvec2 dvec2_not_equal_eps(dvec2 vec_a, double b, double eps) {
    bvec2 res;
    dvecN_not_equal_eps(res.v, vec_a.v, b, eps, 2);
    return res;
}
/** dst = a != b (+-eps) */
static bvec2 dvec2_not_equal_eps_v(const double *vec_a, double b, double eps) {
    return dvec2_not_equal_eps(DVec2(vec_a), b, eps);
}


/** dst = a != b (+-eps) */
static bvec2 dvec2_not_equal_eps_vec(dvec2 vec_a, dvec2 vec_b, double eps) {
    bvec2 res;
    dvecN_not_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 2);
    return res;
}
/** dst = a != b (+-eps) */
static bvec2 dvec2_not_equal_eps_vec_v(const double *vec_a, const double *vec_b, double eps) {
    return dvec2_not_equal_eps_vec(DVec2(vec_a), DVec2(vec_b), eps);
}

/** dst = isnan(a) */
static bvec2 dvec2_isnan(dvec2 vec) {
    bvec2 res;
    dvecN_isnan(res.v, vec.v, 2);
    return res;
}
/** dst = isnan(a) */
static bvec2 dvec2_isnan_v(const double *vec) {
    return dvec2_isnan(DVec2(vec));
}

/** dst = isnan(a) */
static bvec2 dvec2_not_isnan(dvec2 vec) {
    bvec2 res;
    dvecN_not_isnan(res.v, vec.v, 2);
    return res;
}
/** dst = isnan(a) */
static bvec2 dvec2_not_isnan_v(const double *vec) {
    return dvec2_not_isnan(DVec2(vec));
}

#endif //MATHC_VEC_DVEC2_H
