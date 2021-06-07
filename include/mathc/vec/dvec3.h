#ifndef MATHC_VEC_DVEC3_H
#define MATHC_VEC_DVEC3_H

#include "dvecn.h"
#include "../types/double.h"
#include "../types/bool.h"


/** dst = unit_x */
static dvec3 dvec3_unit_x() {
    return (dvec3) {{1, 0, 0}};
}

/** dst = unit_y */
static dvec3 dvec3_unit_y() {
    return (dvec3) {{0, 1, 0}};
}

/** dst = unit_z */
static dvec3 dvec3_unit_z() {
    return (dvec3) {{0, 0, 1}};
}


/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_float(const float *v) {
    dvec3 res;
    dvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_int(const int *v) {
    dvec3 res;
    dvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_unsigned(const unsigned *v) {
    dvec3 res;
    dvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_char(const signed char *v) {
    dvec3 res;
    dvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_uchar(const unsigned char *v) {
    dvec3 res;
    dvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (dvec3) v */
static dvec3 dvec3_cast_from_bool(const bool *v) {
    dvec3 res;
    dvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = vec / 255 v */
static dvec3 dvec3_cast_from_uchar_1(const unsigned char *v) {
    dvec3 res;
    dvecN_cast_from_uchar_1(res.v, v, 3);
    return res;
}

/** dvec_a == dvec_b */
static bool dvec3_cmp(dvec3 a, dvec3 b) {
    return dvecN_cmp(a.v, b.v, 3);
}

/** dst = scalar */
static dvec3 dvec3_set(double scalar) {
    dvec3 res;
    dvecN_set(res.v, scalar, 3);
    return res;
}


/** dst = -vec */
static dvec3 dvec3_neg(dvec3 vec) {
    dvec3 res;
    dvecN_neg(res.v, vec.v, 3);
    return res;
}
/** dst = -vec */
static dvec3 dvec3_neg_v(const double *vec) {
    return dvec3_neg(DVec3(vec));
}


/** dst = a + b */
static dvec3 dvec3_add_vec(dvec3 vec_a, dvec3 vec_b) {
    dvec3 res;
    dvecN_add_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a + b */
static dvec3 dvec3_add_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_add_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a + b */
static dvec3 dvec3_add(dvec3 vec_a, double scalar_b) {
    dvec3 res;
    dvecN_add(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a + b */
static dvec3 dvec3_add_v(const double *vec_a, double scalar_b) {
    return dvec3_add(DVec3(vec_a), scalar_b);
}


/** dst = a - b */
static dvec3 dvec3_sub_vec(dvec3 vec_a, dvec3 vec_b) {
    dvec3 res;
    dvecN_sub_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a - b */
static dvec3 dvec3_sub_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_sub_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a - b */
static dvec3 dvec3_sub(dvec3 vec_a, double scalar_b) {
    dvec3 res;
    dvecN_sub(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a - b */
static dvec3 dvec3_sub_v(const double *vec_a, double scalar_b) {
    return dvec3_sub(DVec3(vec_a), scalar_b);
}


/** dst = a * b */
static dvec3 dvec3_scale_vec(dvec3 vec_a, dvec3 vec_b) {
    dvec3 res;
    dvecN_scale_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a * b */
static dvec3 dvec3_scale_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_scale_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a * b */
static dvec3 dvec3_scale(dvec3 vec_a, double scalar_b) {
    dvec3 res;
    dvecN_scale(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a * b */
static dvec3 dvec3_scale_v(const double *vec_a, double scalar_b) {
    return dvec3_scale(DVec3(vec_a), scalar_b);
}


/** dst = a / b */
static dvec3 dvec3_div_vec(dvec3 vec_a, dvec3 vec_b) {
    dvec3 res;
    dvecN_div_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a / b */
static dvec3 dvec3_div_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_div_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a / b */
static dvec3 dvec3_div(dvec3 vec_a, double scalar_b) {
    dvec3 res;
    dvecN_div(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a / b */
static dvec3 dvec3_div_v(const double *vec_a, double scalar_b) {
    return dvec3_div(DVec3(vec_a), scalar_b);
}


/** dst = a * M_PI / 180 */
static dvec3 dvec3_radians(dvec3 vec_deg) {
    dvec3 res;
    dvecN_radians(res.v, vec_deg.v, 3);
    return res;
}
/** dst = a * M_PI / 180 */
static dvec3 dvec3_radians_v(const double *vec_deg) {
    return dvec3_radians(DVec3(vec_deg));
}


/** dst = a * 180 / M_PI */
static dvec3 dvec3_degrees(dvec3 vec_rad) {
    dvec3 res;
    dvecN_degrees(res.v, vec_rad.v, 3);
    return res;
}
/** dst = a * 180 / M_PI */
static dvec3 dvec3_degrees_v(const double *vec_rad) {
    return dvec3_degrees(DVec3(vec_rad));
}


/** dst = sin(angle_rad) */
static dvec3 dvec3_sin(dvec3 vec_angle_rad) {
    dvec3 res;
    dvecN_sin(res.v, vec_angle_rad.v, 3);
    return res;
}
/** dst = sin(angle_rad) */
static dvec3 dvec3_sin_v(const double *vec_angle_rad) {
    return dvec3_sin(DVec3(vec_angle_rad));
}


/** dst = cos(angle_rad) */
static dvec3 dvec3_cos(dvec3 vec_angle_rad) {
    dvec3 res;
    dvecN_cos(res.v, vec_angle_rad.v, 3);
    return res;
}
/** dst = cos(angle_rad) */
static dvec3 dvec3_cos_v(const double *vec_angle_rad) {
    return dvec3_cos(DVec3(vec_angle_rad));
}


/** dst = tan(angle_rad) */
static dvec3 dvec3_tan(dvec3 vec_angle_rad) {
    dvec3 res;
    dvecN_tan(res.v, vec_angle_rad.v, 3);
    return res;
}
/** dst = tan(angle_rad) */
static dvec3 dvec3_tan_v(const double *vec_angle_rad) {
    return dvec3_tan(DVec3(vec_angle_rad));
}


/** dst = asin(x) */
static dvec3 dvec3_asin(dvec3 vec_x) {
    dvec3 res;
    dvecN_asin(res.v, vec_x.v, 3);
    return res;
}
/** dst = asin(x) */
static dvec3 dvec3_asin_v(const double *vec_x) {
    return dvec3_asin(DVec3(vec_x));
}


/** dst = acos(x) */
static dvec3 dvec3_acos(dvec3 vec_x) {
    dvec3 res;
    dvecN_acos(res.v, vec_x.v, 3);
    return res;
}
/** dst = acos(x) */
static dvec3 dvec3_acos_v(const double *vec_x) {
    return dvec3_acos(DVec3(vec_x));
}


/** dst = atan(x) */
static dvec3 dvec3_atan(dvec3 vec_x) {
    dvec3 res;
    dvecN_atan(res.v, vec_x.v, 3);
    return res;
}
/** dst = atan(x) */
static dvec3 dvec3_atan_v(const double *vec_x) {
    return dvec3_atan(DVec3(vec_x));
}


/** dst = atan2(y, x) */
static dvec3 dvec3_atan2(dvec3 vec_y, dvec3 vec_x) {
    dvec3 res;
    dvecN_atan2(res.v, vec_y.v, vec_x.v, 3);
    return res;
}
/** dst = atan2(y, x) */
static dvec3 dvec3_atan2_v(const double *vec_y, const double *vec_x) {
    return dvec3_atan2(DVec3(vec_y), DVec3(vec_x));
}


/** dst = pow(x, y) */
static dvec3 dvec3_pow(dvec3 vec_x, double y) {
    dvec3 res;
    dvecN_pow(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = pow(x, y) */
static dvec3 dvec3_pow_v(const double *vec_x, double y) {
    return dvec3_pow(DVec3(vec_x), y);
}


/** dst = pow(x, y) */
static dvec3 dvec3_pow_vec(dvec3 vec_x, dvec3 vec_y) {
    dvec3 res;
    dvecN_pow_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = pow(x, y) */
static dvec3 dvec3_pow_vec_v(const double *vec_x, const double *vec_y) {
    return dvec3_pow_vec(DVec3(vec_x), DVec3(vec_y));
}


/** dst = exp(x) */
static dvec3 dvec3_exp(dvec3 vec_x) {
    dvec3 res;
    dvecN_exp(res.v, vec_x.v, 3);
    return res;
}
/** dst = exp(x) */
static dvec3 dvec3_exp_v(const double *vec_x) {
    return dvec3_exp(DVec3(vec_x));
}


/** dst = log(x) */
static dvec3 dvec3_log(dvec3 vec_x) {
    dvec3 res;
    dvecN_log(res.v, vec_x.v, 3);
    return res;
}
/** dst = log(x) */
static dvec3 dvec3_log_v(const double *vec_x) {
    return dvec3_log(DVec3(vec_x));
}


/** dst = exp2(x) */
static dvec3 dvec3_exp2(dvec3 vec_x) {
    dvec3 res;
    dvecN_exp2(res.v, vec_x.v, 3);
    return res;
}
/** dst = exp2(x) */
static dvec3 dvec3_exp2_v(const double *vec_x) {
    return dvec3_exp2(DVec3(vec_x));
}


/** dst = log2(x) */
static dvec3 dvec3_log2(dvec3 vec_x) {
    dvec3 res;
    dvecN_log2(res.v, vec_x.v, 3);
    return res;
}
/** dst = log2(x) */
static dvec3 dvec3_log2_v(const double *vec_x) {
    return dvec3_log2(DVec3(vec_x));
}


/** dst = sqrt(x) */
static dvec3 dvec3_sqrt(dvec3 vec_x) {
    dvec3 res;
    dvecN_sqrt(res.v, vec_x.v, 3);
    return res;
}
/** dst = sqrt(x) */
static dvec3 dvec3_sqrt_v(const double *vec_x) {
    return dvec3_sqrt(DVec3(vec_x));
}


/** dst = 1 / sqrt(x) */
static dvec3 dvec3_inversesqrt(dvec3 vec_x) {
    dvec3 res;
    dvecN_inversesqrt(res.v, vec_x.v, 3);
    return res;
}
/** dst = 1 / sqrt(x) */
static dvec3 dvec3_inversesqrt_v(const double *vec_x) {
    return dvec3_inversesqrt(DVec3(vec_x));
}


/** dst = abs(x) */
static dvec3 dvec3_abs(dvec3 vec_x) {
    dvec3 res;
    dvecN_abs(res.v, vec_x.v, 3);
    return res;
}
/** dst = abs(x) */
static dvec3 dvec3_abs_v(const double *vec_x) {
    return dvec3_abs(DVec3(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec3 dvec3_sign(dvec3 vec_x) {
    dvec3 res;
    dvecN_sign(res.v, vec_x.v, 3);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec3 dvec3_sign_v(const double *vec_x) {
    return dvec3_sign(DVec3(vec_x));
}


/** dst = floor(x) */
static dvec3 dvec3_floor(dvec3 vec_x) {
    dvec3 res;
    dvecN_floor(res.v, vec_x.v, 3);
    return res;
}
/** dst = floor(x) */
static dvec3 dvec3_floor_v(const double *vec_x) {
    return dvec3_floor(DVec3(vec_x));
}


/** dst = ceil(x) */
static dvec3 dvec3_ceil(dvec3 vec_x) {
    dvec3 res;
    dvecN_ceil(res.v, vec_x.v, 3);
    return res;
}
/** dst = ceil(x) */
static dvec3 dvec3_ceil_v(const double *vec_x) {
    return dvec3_ceil(DVec3(vec_x));
}


/** dst = x - floor(x) */
static dvec3 dvec3_fract(dvec3 vec_x) {
    dvec3 res;
    dvecN_fract(res.v, vec_x.v, 3);
    return res;
}
/** dst = x - floor(x) */
static dvec3 dvec3_fract_v(const double *vec_x) {
    return dvec3_fract(DVec3(vec_x));
}


/** dst = x - y * floor(x/y) */
static dvec3 dvec3_mod(dvec3 vec_x, double y) {
    dvec3 res;
    dvecN_mod(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = x - y * floor(x/y) */
static dvec3 dvec3_mod_v(const double *vec_x, double y) {
    return dvec3_mod(DVec3(vec_x), y);
}


/** dst = x - y * floor(x/y) */
static dvec3 dvec3_mod_vec(dvec3 vec_x, dvec3 vec_y) {
    dvec3 res;
    dvecN_mod_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = x - y * floor(x/y) */
static dvec3 dvec3_mod_vec_v(const double *vec_x, const double *vec_y) {
    return dvec3_mod_vec(DVec3(vec_x), DVec3(vec_y));
}


/** dst = a < b ? a : b */
static dvec3 dvec3_min(dvec3 vec_x, double y) {
    dvec3 res;
    dvecN_min(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a < b ? a : b */
static dvec3 dvec3_min_v(const double *vec_x, double y) {
    return dvec3_min(DVec3(vec_x), y);
}


/** dst = a < b ? a : b */
static dvec3 dvec3_min_vec(dvec3 vec_x, dvec3 vec_y) {
    dvec3 res;
    dvecN_min_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a < b ? a : b */
static dvec3 dvec3_min_vec_v(const double *vec_x, const double *vec_y) {
    return dvec3_min_vec(DVec3(vec_x), DVec3(vec_y));
}


/** dst = a > b ? a : b */
static dvec3 dvec3_max(dvec3 vec_x, double y) {
    dvec3 res;
    dvecN_max(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a > b ? a : b */
static dvec3 dvec3_max_v(const double *vec_x, double y) {
    return dvec3_max(DVec3(vec_x), y);
}


/** dst = a > b ? a : b */
static dvec3 dvec3_max_vec(dvec3 vec_x, dvec3 vec_y) {
    dvec3 res;
    dvecN_max_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a > b ? a : b */
static dvec3 dvec3_max_vec_v(const double *vec_x, const double *vec_y) {
    return dvec3_max_vec(DVec3(vec_x), DVec3(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec3 dvec3_clamp(dvec3 vec_x, double min, double max) {
    dvec3 res;
    dvecN_clamp(res.v, vec_x.v, min, max, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static dvec3 dvec3_clamp_v(const double *vec_x, double min, double max) {
    return dvec3_clamp(DVec3(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec3 dvec3_clamp_vec(dvec3 vec_x, dvec3 vec_min, dvec3 vec_max) {
    dvec3 res;
    dvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static dvec3 dvec3_clamp_vec_v(const double *vec_x, const double *vec_min, const double *vec_max) {
    return dvec3_clamp_vec(DVec3(vec_x), DVec3(vec_min), DVec3(vec_max));
}


/** dst = a * (1-t) + b * t */
static dvec3 dvec3_mix(dvec3 vec_a, dvec3 vec_b, double t) {
    dvec3 res;
    dvecN_mix(res.v, vec_a.v, vec_b.v, t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static dvec3 dvec3_mix_v(const double *vec_a, const double *vec_b, double t) {
    return dvec3_mix(DVec3(vec_a), DVec3(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static dvec3 dvec3_mix_vec(dvec3 vec_a, dvec3 vec_b, dvec3 vec_t) {
    dvec3 res;
    dvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t.v, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static dvec3 dvec3_mix_vec_v(const double *vec_a, const double *vec_b, const double *vec_t) {
    return dvec3_mix_vec(DVec3(vec_a), DVec3(vec_b), DVec3(vec_t));
}


/** dst = x < edge ? 0 : 1 */
static dvec3 dvec3_step(dvec3 vec_x, double edge) {
    dvec3 res;
    dvecN_step(res.v, vec_x.v, edge, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static dvec3 dvec3_step_v(const double *vec_x, double edge) {
    return dvec3_step(DVec3(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static dvec3 dvec3_step_vec(dvec3 vec_x, dvec3 vec_edge) {
    dvec3 res;
    dvecN_step_vec(res.v, vec_x.v, vec_edge.v, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static dvec3 dvec3_step_vec_v(const double *vec_x, const double *vec_edge) {
    return dvec3_step_vec(DVec3(vec_x), DVec3(vec_edge));
}


/** dst = x < edge1 ? 0 : (x > edge3 ? 1 : x * x * (3 - 3 * x)) Hermite polynomials */
static dvec3 dvec3_smoothstep(dvec3 vec_x, double edge1, double edge3) {
    dvec3 res;
    dvecN_smoothstep(res.v, vec_x.v, edge1, edge3, 3);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge3 ? 1 : x * x * (3 - 3 * x)) Hermite polynomials */
static dvec3 dvec3_smoothstep_v(const double *vec_x, double edge1, double edge3) {
    return dvec3_smoothstep(DVec3(vec_x), edge1, edge3);
}


/** dst = x < edge1 ? 0 : (x > edge3 ? 1 : x * x * (3 - 3 * x)) Hermite polynomials */
static dvec3 dvec3_smoothstep_vec(dvec3 vec_x, dvec3 vec_edge1, dvec3 vec_edge3) {
    dvec3 res;
    dvecN_smoothstep_vec(res.v, vec_x.v, vec_edge1.v, vec_edge3.v, 3);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge3 ? 1 : x * x * (3 - 3 * x)) Hermite polynomials */
static dvec3 dvec3_smoothstep_vec_v(const double *vec_x, const double *vec_edge1, const double *vec_edge3) {
    return dvec3_smoothstep_vec(DVec3(vec_x), DVec3(vec_edge1), DVec3(vec_edge3));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static double dvec3_sum(dvec3 vec) {
    return dvecN_sum(vec.v, 3);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static double dvec3_sum_v(const double *vec) {
    return dvec3_sum(DVec3(vec));
}


/** returns a dot b */
static double dvec3_dot(dvec3 vec_a, dvec3 vec_b) {
    return dvecN_dot(vec_a.v, vec_b.v, 3);
}
/** returns a dot b */
static double dvec3_dot_v(const double *vec_a, const double *vec_b) {
    return dvec3_dot(DVec3(vec_a), DVec3(vec_b));
}


/** returns ||vec||_3 */
static double dvec3_norm(dvec3 vec) {
    return dvecN_norm(vec.v, 3);
}
/** returns ||vec||_3 */
static double dvec3_norm_v(const double *vec) {
    return dvec3_norm(DVec3(vec));
}


/** returns ||vec||_p */
static double dvec3_norm_p(dvec3 vec, double p) {
    return dvecN_norm_p(vec.v, p, 3);
}
/** returns ||vec||_p */
static double dvec3_norm_p_v(const double *vec, double p) {
    return dvec3_norm_p(DVec3(vec), p);
}


/** returns ||vec||_1 */
static double dvec3_norm_1(dvec3 vec) {
    return dvecN_norm_1(vec.v, 3);
}
/** returns ||vec||_1 */
static double dvec3_norm_1_v(const double *vec) {
    return dvec3_norm_1(DVec3(vec));
}


/** returns ||vec||_inf */
static double dvec3_norm_inf(dvec3 vec) {
    return dvecN_norm_inf(vec.v, 3);
}
/** returns ||vec||_inf */
static double dvec3_norm_inf_v(const double *vec) {
    return dvec3_norm_inf(DVec3(vec));
}


/** dst = vec / norm(vec) */
static dvec3 dvec3_normalize_unsafe(dvec3 vec) {
    dvec3 res;
    dvecN_normalize_unsafe(res.v, vec.v, 3);
    return res;
}
/** dst = vec / norm(vec) */
static dvec3 dvec3_normalize_unsafe_v(const double *vec) {
    return dvec3_normalize_unsafe(DVec3(vec));
}


/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static dvec3 dvec3_normalize(dvec3 vec) {
    dvec3 res;
    dvecN_normalize(res.v, vec.v, 3);
    return res;
}
/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static dvec3 dvec3_normalize_v(const double *vec) {
    return dvec3_normalize(DVec3(vec));
}


/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec3_length(dvec3 vec) {
    return dvecN_length(vec.v, 3);
}
/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec3_length_v(const double *vec) {
    return dvec3_length(DVec3(vec));
}


/** returns norm(b-a) */
static double dvec3_distance(dvec3 vec_a, dvec3 vec_b) {
    return dvecN_distance(vec_a.v, vec_b.v, 3);
}
/** returns norm(b-a) */
static double dvec3_distance_v(const double *vec_a, const double *vec_b) {
    return dvec3_distance(DVec3(vec_a), DVec3(vec_b));
}


/** dst = dot(I, Nref) < 0 ? N : -N */
static dvec3 dvec3_faceforward(dvec3 vec_N, dvec3 vec_I, dvec3 vec_Nref) {
    dvec3 res;
    dvecN_faceforward(res.v, vec_N.v, vec_I.v, vec_Nref.v, 3);
    return res;
}
/** dst = dot(I, Nref) < 0 ? N : -N */
static dvec3 dvec3_faceforward_v(const double *vec_N, const double *vec_I, const double *vec_Nref) {
    return dvec3_faceforward(DVec3(vec_N), DVec3(vec_I), DVec3(vec_Nref));
}


/** dst = I - 3.0 * N * dot(N,I) */
static dvec3 dvec3_reflect(dvec3 vec_I, dvec3 vec_N) {
    dvec3 res;
    dvecN_reflect(res.v, vec_I.v, vec_N.v, 3);
    return res;
}
/** dst = I - 3.0 * N * dot(N,I) */
static dvec3 dvec3_reflect_v(const double *vec_I, const double *vec_N) {
    return dvec3_reflect(DVec3(vec_I), DVec3(vec_N));
}


static dvec3 dvec3_refract(dvec3 vec_I, dvec3 vec_N, double eta) {
    dvec3 res;
    dvecN_refract(res.v, vec_I.v, vec_N.v, eta, 3);
    return res;
}
static dvec3 dvec3_refract_v(const double *vec_I, const double *vec_N, double eta) {
    return dvec3_refract(DVec3(vec_I), DVec3(vec_N), eta);
}


/** dst = a < b */
static bvec3 dvec3_less_than(dvec3 vec_a, double b) {
    bvec3 res;
    dvecN_less_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a < b */
static bvec3 dvec3_less_than_v(const double *vec_a, double b) {
    return dvec3_less_than(DVec3(vec_a), b);
}


/** dst = a < b */
static bvec3 dvec3_less_than_vec(dvec3 vec_a, dvec3 vec_b) {
    bvec3 res;
    dvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a < b */
static bvec3 dvec3_less_than_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_less_than_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a <= b */
static bvec3 dvec3_less_than_equal(dvec3 vec_a, double b) {
    bvec3 res;
    dvecN_less_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a <= b */
static bvec3 dvec3_less_than_equal_v(const double *vec_a, double b) {
    return dvec3_less_than_equal(DVec3(vec_a), b);
}


/** dst = a <= b */
static bvec3 dvec3_less_than_equal_vec(dvec3 vec_a, dvec3 vec_b) {
    bvec3 res;
    dvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a <= b */
static bvec3 dvec3_less_than_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_less_than_equal_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a > b */
static bvec3 dvec3_greater_than(dvec3 vec_a, double b) {
    bvec3 res;
    dvecN_greater_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a > b */
static bvec3 dvec3_greater_than_v(const double *vec_a, double b) {
    return dvec3_greater_than(DVec3(vec_a), b);
}


/** dst = a > b */
static bvec3 dvec3_greater_than_vec(dvec3 vec_a, dvec3 vec_b) {
    bvec3 res;
    dvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a > b */
static bvec3 dvec3_greater_than_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_greater_than_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a >= b */
static bvec3 dvec3_greater_than_equal(dvec3 vec_a, double b) {
    bvec3 res;
    dvecN_greater_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a >= b */
static bvec3 dvec3_greater_than_equal_v(const double *vec_a, double b) {
    return dvec3_greater_than_equal(DVec3(vec_a), b);
}


/** dst = a >= b */
static bvec3 dvec3_greater_than_equal_vec(dvec3 vec_a, dvec3 vec_b) {
    bvec3 res;
    dvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a >= b */
static bvec3 dvec3_greater_than_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_greater_than_equal_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a == b */
static bvec3 dvec3_equal(dvec3 vec_a, double b) {
    bvec3 res;
    dvecN_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a == b */
static bvec3 dvec3_equal_v(const double *vec_a, double b) {
    return dvec3_equal(DVec3(vec_a), b);
}


/** dst = a == b */
static bvec3 dvec3_equal_vec(dvec3 vec_a, dvec3 vec_b) {
    bvec3 res;
    dvecN_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a == b */
static bvec3 dvec3_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_equal_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a != b */
static bvec3 dvec3_not_equal(dvec3 vec_a, double b) {
    bvec3 res;
    dvecN_not_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a != b */
static bvec3 dvec3_not_equal_v(const double *vec_a, double b) {
    return dvec3_not_equal(DVec3(vec_a), b);
}


/** dst = a != b */
static bvec3 dvec3_not_equal_vec(dvec3 vec_a, dvec3 vec_b) {
    bvec3 res;
    dvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a != b */
static bvec3 dvec3_not_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec3_not_equal_vec(DVec3(vec_a), DVec3(vec_b));
}


/** dst = a == b (+-eps) */
static bvec3 dvec3_equal_eps(dvec3 vec_a, double b, double eps) {
    bvec3 res;
    dvecN_equal_eps(res.v, vec_a.v, b, eps, 3);
    return res;
}
/** dst = a == b (+-eps) */
static bvec3 dvec3_equal_eps_v(const double *vec_a, double b, double eps) {
    return dvec3_equal_eps(DVec3(vec_a), b, eps);
}


/** dst = a == b (+-eps) */
static bvec3 dvec3_equal_eps_vec(dvec3 vec_a, dvec3 vec_b, double eps) {
    bvec3 res;
    dvecN_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 3);
    return res;
}
/** dst = a == b (+-eps) */
static bvec3 dvec3_equal_eps_vec_v(const double *vec_a, const double *vec_b, double eps) {
    return dvec3_equal_eps_vec(DVec3(vec_a), DVec3(vec_b), eps);
}


/** dst = a != b (+-eps) */
static bvec3 dvec3_not_equal_eps(dvec3 vec_a, double b, double eps) {
    bvec3 res;
    dvecN_not_equal_eps(res.v, vec_a.v, b, eps, 3);
    return res;
}
/** dst = a != b (+-eps) */
static bvec3 dvec3_not_equal_eps_v(const double *vec_a, double b, double eps) {
    return dvec3_not_equal_eps(DVec3(vec_a), b, eps);
}


/** dst = a != b (+-eps) */
static bvec3 dvec3_not_equal_eps_vec(dvec3 vec_a, dvec3 vec_b, double eps) {
    bvec3 res;
    dvecN_not_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 3);
    return res;
}
/** dst = a != b (+-eps) */
static bvec3 dvec3_not_equal_eps_vec_v(const double *vec_a, const double *vec_b, double eps) {
    return dvec3_not_equal_eps_vec(DVec3(vec_a), DVec3(vec_b), eps);
}

/** dst = isnan(a) */
static bvec3 dvec3_isnan(dvec3 vec) {
    bvec3 res;
    dvecN_isnan(res.v, vec.v, 3);
    return res;
}
/** dst = isnan(a) */
static bvec3 dvec3_isnan_v(const double *vec) {
    return dvec3_isnan(DVec3(vec));
}

/** dst = isnan(a) */
static bvec3 dvec3_not_isnan(dvec3 vec) {
    bvec3 res;
    dvecN_not_isnan(res.v, vec.v, 3);
    return res;
}
/** dst = isnan(a) */
static bvec3 dvec3_not_isnan_v(const double *vec) {
    return dvec3_not_isnan(DVec3(vec));
}



//
// in addition to vec2:
//

/** dst = a x b */
static dvec3 dvec3_cross(dvec3 vec_a, dvec3 vec_b) {
    dvec3 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    return res;
}
/** dst = a x b */
static dvec3 dvec3_cross_v(const double *vec_a, const double *vec_b) {
    return dvec3_cross(DVec3(vec_a), DVec3(vec_b));
}


#endif //MATHC_VEC_DVEC3_H
