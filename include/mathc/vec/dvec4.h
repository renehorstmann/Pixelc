#ifndef MATHC_VEC_DVEC4_H
#define MATHC_VEC_DVEC4_H

#include "dvecn.h"
#include "../types/double.h"
#include "../types/bool.h"


/** dst = unit_x */
static dvec4 dvec4_unit_x() {
    return (dvec4) {{1, 0, 0, 0}};
}

/** dst = unit_y */
static dvec4 dvec4_unit_y() {
    return (dvec4) {{0, 1, 0, 0}};
}

/** dst = unit_z */
static dvec4 dvec4_unit_z() {
    return (dvec4) {{0, 0, 1, 0}};
}

/** dst = unit_w */
static dvec4 dvec4_unit_w() {
    return (dvec4) {{0, 0, 0, 1}};
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_float(const float *v) {
    dvec4 res;
    dvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_int(const int *v) {
    dvec4 res;
    dvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_unsigned(const unsigned *v) {
    dvec4 res;
    dvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_char(const signed char *v) {
    dvec4 res;
    dvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_uchar(const unsigned char *v) {
    dvec4 res;
    dvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (dvec4) v */
static dvec4 dvec4_cast_from_bool(const bool *v) {
    dvec4 res;
    dvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = vec / 255 v */
static dvec4 dvec4_cast_from_uchar_1(const unsigned char *v) {
    dvec4 res;
    dvecN_cast_from_uchar_1(res.v, v, 4);
    return res;
}

/** dvec_a == dvec_b */
static bool dvec4_cmp(dvec4 a, dvec4 b) {
    return dvecN_cmp(a.v, b.v, 4);
}


/** dst = scalar */
static dvec4 dvec4_set(double scalar) {
    dvec4 res;
    dvecN_set(res.v, scalar, 4);
    return res;
}


/** dst = -vec */
static dvec4 dvec4_neg(dvec4 vec) {
    dvec4 res;
    dvecN_neg(res.v, vec.v, 4);
    return res;
}
/** dst = -vec */
static dvec4 dvec4_neg_v(const double *vec) {
    return dvec4_neg(DVec4(vec));
}


/** dst = a + b */
static dvec4 dvec4_add_vec(dvec4 vec_a, dvec4 vec_b) {
    dvec4 res;
    dvecN_add_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a + b */
static dvec4 dvec4_add_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_add_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a + b */
static dvec4 dvec4_add(dvec4 vec_a, double scalar_b) {
    dvec4 res;
    dvecN_add(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a + b */
static dvec4 dvec4_add_v(const double *vec_a, double scalar_b) {
    return dvec4_add(DVec4(vec_a), scalar_b);
}


/** dst = a - b */
static dvec4 dvec4_sub_vec(dvec4 vec_a, dvec4 vec_b) {
    dvec4 res;
    dvecN_sub_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a - b */
static dvec4 dvec4_sub_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_sub_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a - b */
static dvec4 dvec4_sub(dvec4 vec_a, double scalar_b) {
    dvec4 res;
    dvecN_sub(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a - b */
static dvec4 dvec4_sub_v(const double *vec_a, double scalar_b) {
    return dvec4_sub(DVec4(vec_a), scalar_b);
}


/** dst = a * b */
static dvec4 dvec4_scale_vec(dvec4 vec_a, dvec4 vec_b) {
    dvec4 res;
    dvecN_scale_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a * b */
static dvec4 dvec4_scale_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_scale_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a * b */
static dvec4 dvec4_scale(dvec4 vec_a, double scalar_b) {
    dvec4 res;
    dvecN_scale(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a * b */
static dvec4 dvec4_scale_v(const double *vec_a, double scalar_b) {
    return dvec4_scale(DVec4(vec_a), scalar_b);
}


/** dst = a / b */
static dvec4 dvec4_div_vec(dvec4 vec_a, dvec4 vec_b) {
    dvec4 res;
    dvecN_div_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a / b */
static dvec4 dvec4_div_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_div_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a / b */
static dvec4 dvec4_div(dvec4 vec_a, double scalar_b) {
    dvec4 res;
    dvecN_div(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a / b */
static dvec4 dvec4_div_v(const double *vec_a, double scalar_b) {
    return dvec4_div(DVec4(vec_a), scalar_b);
}


/** dst = a * M_PI / 180 */
static dvec4 dvec4_radians(dvec4 vec_deg) {
    dvec4 res;
    dvecN_radians(res.v, vec_deg.v, 4);
    return res;
}
/** dst = a * M_PI / 180 */
static dvec4 dvec4_radians_v(const double *vec_deg) {
    return dvec4_radians(DVec4(vec_deg));
}


/** dst = a * 180 / M_PI */
static dvec4 dvec4_degrees(dvec4 vec_rad) {
    dvec4 res;
    dvecN_degrees(res.v, vec_rad.v, 4);
    return res;
}
/** dst = a * 180 / M_PI */
static dvec4 dvec4_degrees_v(const double *vec_rad) {
    return dvec4_degrees(DVec4(vec_rad));
}


/** dst = sin(angle_rad) */
static dvec4 dvec4_sin(dvec4 vec_angle_rad) {
    dvec4 res;
    dvecN_sin(res.v, vec_angle_rad.v, 4);
    return res;
}
/** dst = sin(angle_rad) */
static dvec4 dvec4_sin_v(const double *vec_angle_rad) {
    return dvec4_sin(DVec4(vec_angle_rad));
}


/** dst = cos(angle_rad) */
static dvec4 dvec4_cos(dvec4 vec_angle_rad) {
    dvec4 res;
    dvecN_cos(res.v, vec_angle_rad.v, 4);
    return res;
}
/** dst = cos(angle_rad) */
static dvec4 dvec4_cos_v(const double *vec_angle_rad) {
    return dvec4_cos(DVec4(vec_angle_rad));
}


/** dst = tan(angle_rad) */
static dvec4 dvec4_tan(dvec4 vec_angle_rad) {
    dvec4 res;
    dvecN_tan(res.v, vec_angle_rad.v, 4);
    return res;
}
/** dst = tan(angle_rad) */
static dvec4 dvec4_tan_v(const double *vec_angle_rad) {
    return dvec4_tan(DVec4(vec_angle_rad));
}


/** dst = asin(x) */
static dvec4 dvec4_asin(dvec4 vec_x) {
    dvec4 res;
    dvecN_asin(res.v, vec_x.v, 4);
    return res;
}
/** dst = asin(x) */
static dvec4 dvec4_asin_v(const double *vec_x) {
    return dvec4_asin(DVec4(vec_x));
}


/** dst = acos(x) */
static dvec4 dvec4_acos(dvec4 vec_x) {
    dvec4 res;
    dvecN_acos(res.v, vec_x.v, 4);
    return res;
}
/** dst = acos(x) */
static dvec4 dvec4_acos_v(const double *vec_x) {
    return dvec4_acos(DVec4(vec_x));
}


/** dst = atan(x) */
static dvec4 dvec4_atan(dvec4 vec_x) {
    dvec4 res;
    dvecN_atan(res.v, vec_x.v, 4);
    return res;
}
/** dst = atan(x) */
static dvec4 dvec4_atan_v(const double *vec_x) {
    return dvec4_atan(DVec4(vec_x));
}


/** dst = atan2(y, x) */
static dvec4 dvec4_atan2(dvec4 vec_y, dvec4 vec_x) {
    dvec4 res;
    dvecN_atan2(res.v, vec_y.v, vec_x.v, 4);
    return res;
}
/** dst = atan2(y, x) */
static dvec4 dvec4_atan2_v(const double *vec_y, const double *vec_x) {
    return dvec4_atan2(DVec4(vec_y), DVec4(vec_x));
}


/** dst = pow(x, y) */
static dvec4 dvec4_pow(dvec4 vec_x, double y) {
    dvec4 res;
    dvecN_pow(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = pow(x, y) */
static dvec4 dvec4_pow_v(const double *vec_x, double y) {
    return dvec4_pow(DVec4(vec_x), y);
}


/** dst = pow(x, y) */
static dvec4 dvec4_pow_vec(dvec4 vec_x, dvec4 vec_y) {
    dvec4 res;
    dvecN_pow_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = pow(x, y) */
static dvec4 dvec4_pow_vec_v(const double *vec_x, const double *vec_y) {
    return dvec4_pow_vec(DVec4(vec_x), DVec4(vec_y));
}


/** dst = exp(x) */
static dvec4 dvec4_exp(dvec4 vec_x) {
    dvec4 res;
    dvecN_exp(res.v, vec_x.v, 4);
    return res;
}
/** dst = exp(x) */
static dvec4 dvec4_exp_v(const double *vec_x) {
    return dvec4_exp(DVec4(vec_x));
}


/** dst = log(x) */
static dvec4 dvec4_log(dvec4 vec_x) {
    dvec4 res;
    dvecN_log(res.v, vec_x.v, 4);
    return res;
}
/** dst = log(x) */
static dvec4 dvec4_log_v(const double *vec_x) {
    return dvec4_log(DVec4(vec_x));
}


/** dst = exp2(x) */
static dvec4 dvec4_exp2(dvec4 vec_x) {
    dvec4 res;
    dvecN_exp2(res.v, vec_x.v, 4);
    return res;
}
/** dst = exp2(x) */
static dvec4 dvec4_exp2_v(const double *vec_x) {
    return dvec4_exp2(DVec4(vec_x));
}


/** dst = log2(x) */
static dvec4 dvec4_log2(dvec4 vec_x) {
    dvec4 res;
    dvecN_log2(res.v, vec_x.v, 4);
    return res;
}
/** dst = log2(x) */
static dvec4 dvec4_log2_v(const double *vec_x) {
    return dvec4_log2(DVec4(vec_x));
}


/** dst = sqrt(x) */
static dvec4 dvec4_sqrt(dvec4 vec_x) {
    dvec4 res;
    dvecN_sqrt(res.v, vec_x.v, 4);
    return res;
}
/** dst = sqrt(x) */
static dvec4 dvec4_sqrt_v(const double *vec_x) {
    return dvec4_sqrt(DVec4(vec_x));
}


/** dst = 1 / sqrt(x) */
static dvec4 dvec4_inversesqrt(dvec4 vec_x) {
    dvec4 res;
    dvecN_inversesqrt(res.v, vec_x.v, 4);
    return res;
}
/** dst = 1 / sqrt(x) */
static dvec4 dvec4_inversesqrt_v(const double *vec_x) {
    return dvec4_inversesqrt(DVec4(vec_x));
}


/** dst = abs(x) */
static dvec4 dvec4_abs(dvec4 vec_x) {
    dvec4 res;
    dvecN_abs(res.v, vec_x.v, 4);
    return res;
}
/** dst = abs(x) */
static dvec4 dvec4_abs_v(const double *vec_x) {
    return dvec4_abs(DVec4(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec4 dvec4_sign(dvec4 vec_x) {
    dvec4 res;
    dvecN_sign(res.v, vec_x.v, 4);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static dvec4 dvec4_sign_v(const double *vec_x) {
    return dvec4_sign(DVec4(vec_x));
}


/** dst = floor(x) */
static dvec4 dvec4_floor(dvec4 vec_x) {
    dvec4 res;
    dvecN_floor(res.v, vec_x.v, 4);
    return res;
}
/** dst = floor(x) */
static dvec4 dvec4_floor_v(const double *vec_x) {
    return dvec4_floor(DVec4(vec_x));
}


/** dst = ceil(x) */
static dvec4 dvec4_ceil(dvec4 vec_x) {
    dvec4 res;
    dvecN_ceil(res.v, vec_x.v, 4);
    return res;
}
/** dst = ceil(x) */
static dvec4 dvec4_ceil_v(const double *vec_x) {
    return dvec4_ceil(DVec4(vec_x));
}


/** dst = x - floor(x) */
static dvec4 dvec4_fract(dvec4 vec_x) {
    dvec4 res;
    dvecN_fract(res.v, vec_x.v, 4);
    return res;
}
/** dst = x - floor(x) */
static dvec4 dvec4_fract_v(const double *vec_x) {
    return dvec4_fract(DVec4(vec_x));
}


/** dst = x - y * floor(x/y) */
static dvec4 dvec4_mod(dvec4 vec_x, double y) {
    dvec4 res;
    dvecN_mod(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = x - y * floor(x/y) */
static dvec4 dvec4_mod_v(const double *vec_x, double y) {
    return dvec4_mod(DVec4(vec_x), y);
}


/** dst = x - y * floor(x/y) */
static dvec4 dvec4_mod_vec(dvec4 vec_x, dvec4 vec_y) {
    dvec4 res;
    dvecN_mod_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = x - y * floor(x/y) */
static dvec4 dvec4_mod_vec_v(const double *vec_x, const double *vec_y) {
    return dvec4_mod_vec(DVec4(vec_x), DVec4(vec_y));
}


/** dst = a < b ? a : b */
static dvec4 dvec4_min(dvec4 vec_x, double y) {
    dvec4 res;
    dvecN_min(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a < b ? a : b */
static dvec4 dvec4_min_v(const double *vec_x, double y) {
    return dvec4_min(DVec4(vec_x), y);
}


/** dst = a < b ? a : b */
static dvec4 dvec4_min_vec(dvec4 vec_x, dvec4 vec_y) {
    dvec4 res;
    dvecN_min_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a < b ? a : b */
static dvec4 dvec4_min_vec_v(const double *vec_x, const double *vec_y) {
    return dvec4_min_vec(DVec4(vec_x), DVec4(vec_y));
}


/** dst = a > b ? a : b */
static dvec4 dvec4_max(dvec4 vec_x, double y) {
    dvec4 res;
    dvecN_max(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a > b ? a : b */
static dvec4 dvec4_max_v(const double *vec_x, double y) {
    return dvec4_max(DVec4(vec_x), y);
}


/** dst = a > b ? a : b */
static dvec4 dvec4_max_vec(dvec4 vec_x, dvec4 vec_y) {
    dvec4 res;
    dvecN_max_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a > b ? a : b */
static dvec4 dvec4_max_vec_v(const double *vec_x, const double *vec_y) {
    return dvec4_max_vec(DVec4(vec_x), DVec4(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec4 dvec4_clamp(dvec4 vec_x, double min, double max) {
    dvec4 res;
    dvecN_clamp(res.v, vec_x.v, min, max, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static dvec4 dvec4_clamp_v(const double *vec_x, double min, double max) {
    return dvec4_clamp(DVec4(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static dvec4 dvec4_clamp_vec(dvec4 vec_x, dvec4 vec_min, dvec4 vec_max) {
    dvec4 res;
    dvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static dvec4 dvec4_clamp_vec_v(const double *vec_x, const double *vec_min, const double *vec_max) {
    return dvec4_clamp_vec(DVec4(vec_x), DVec4(vec_min), DVec4(vec_max));
}


/** dst = a * (1-t) + b * t */
static dvec4 dvec4_mix(dvec4 vec_a, dvec4 vec_b, double t) {
    dvec4 res;
    dvecN_mix(res.v, vec_a.v, vec_b.v, t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static dvec4 dvec4_mix_v(const double *vec_a, const double *vec_b, double t) {
    return dvec4_mix(DVec4(vec_a), DVec4(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static dvec4 dvec4_mix_vec(dvec4 vec_a, dvec4 vec_b, dvec4 vec_t) {
    dvec4 res;
    dvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t.v, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static dvec4 dvec4_mix_vec_v(const double *vec_a, const double *vec_b, const double *vec_t) {
    return dvec4_mix_vec(DVec4(vec_a), DVec4(vec_b), DVec4(vec_t));
}


/** dst = x < edge ? 0 : 1 */
static dvec4 dvec4_step(dvec4 vec_x, double edge) {
    dvec4 res;
    dvecN_step(res.v, vec_x.v, edge, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static dvec4 dvec4_step_v(const double *vec_x, double edge) {
    return dvec4_step(DVec4(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static dvec4 dvec4_step_vec(dvec4 vec_x, dvec4 vec_edge) {
    dvec4 res;
    dvecN_step_vec(res.v, vec_x.v, vec_edge.v, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static dvec4 dvec4_step_vec_v(const double *vec_x, const double *vec_edge) {
    return dvec4_step_vec(DVec4(vec_x), DVec4(vec_edge));
}


/** dst = x < edge1 ? 0 : (x > edge4 ? 1 : x * x * (4 - 4 * x)) Hermite polynomials */
static dvec4 dvec4_smoothstep(dvec4 vec_x, double edge1, double edge4) {
    dvec4 res;
    dvecN_smoothstep(res.v, vec_x.v, edge1, edge4, 4);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge4 ? 1 : x * x * (4 - 4 * x)) Hermite polynomials */
static dvec4 dvec4_smoothstep_v(const double *vec_x, double edge1, double edge4) {
    return dvec4_smoothstep(DVec4(vec_x), edge1, edge4);
}


/** dst = x < edge1 ? 0 : (x > edge4 ? 1 : x * x * (4 - 4 * x)) Hermite polynomials */
static dvec4 dvec4_smoothstep_vec(dvec4 vec_x, dvec4 vec_edge1, dvec4 vec_edge4) {
    dvec4 res;
    dvecN_smoothstep_vec(res.v, vec_x.v, vec_edge1.v, vec_edge4.v, 4);
    return res;
}
/** dst = x < edge1 ? 0 : (x > edge4 ? 1 : x * x * (4 - 4 * x)) Hermite polynomials */
static dvec4 dvec4_smoothstep_vec_v(const double *vec_x, const double *vec_edge1, const double *vec_edge4) {
    return dvec4_smoothstep_vec(DVec4(vec_x), DVec4(vec_edge1), DVec4(vec_edge4));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static double dvec4_sum(dvec4 vec) {
    return dvecN_sum(vec.v, 4);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static double dvec4_sum_v(const double *vec) {
    return dvec4_sum(DVec4(vec));
}


/** returns a dot b */
static double dvec4_dot(dvec4 vec_a, dvec4 vec_b) {
    return dvecN_dot(vec_a.v, vec_b.v, 4);
}
/** returns a dot b */
static double dvec4_dot_v(const double *vec_a, const double *vec_b) {
    return dvec4_dot(DVec4(vec_a), DVec4(vec_b));
}


/** returns ||vec||_4 */
static double dvec4_norm(dvec4 vec) {
    return dvecN_norm(vec.v, 4);
}
/** returns ||vec||_4 */
static double dvec4_norm_v(const double *vec) {
    return dvec4_norm(DVec4(vec));
}


/** returns ||vec||_p */
static double dvec4_norm_p(dvec4 vec, double p) {
    return dvecN_norm_p(vec.v, p, 4);
}
/** returns ||vec||_p */
static double dvec4_norm_p_v(const double *vec, double p) {
    return dvec4_norm_p(DVec4(vec), p);
}


/** returns ||vec||_1 */
static double dvec4_norm_1(dvec4 vec) {
    return dvecN_norm_1(vec.v, 4);
}
/** returns ||vec||_1 */
static double dvec4_norm_1_v(const double *vec) {
    return dvec4_norm_1(DVec4(vec));
}


/** returns ||vec||_inf */
static double dvec4_norm_inf(dvec4 vec) {
    return dvecN_norm_inf(vec.v, 4);
}
/** returns ||vec||_inf */
static double dvec4_norm_inf_v(const double *vec) {
    return dvec4_norm_inf(DVec4(vec));
}


/** dst = vec / norm(vec) */
static dvec4 dvec4_normalize_unsafe(dvec4 vec) {
    dvec4 res;
    dvecN_normalize_unsafe(res.v, vec.v, 4);
    return res;
}
/** dst = vec / norm(vec) */
static dvec4 dvec4_normalize_unsafe_v(const double *vec) {
    return dvec4_normalize_unsafe(DVec4(vec));
}


/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static dvec4 dvec4_normalize(dvec4 vec) {
    dvec4 res;
    dvecN_normalize(res.v, vec.v, 4);
    return res;
}
/** dst = vec / (norm(vec) > 0 ? norm(vec) : 1) */
static dvec4 dvec4_normalize_v(const double *vec) {
    return dvec4_normalize(DVec4(vec));
}


/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec4_length(dvec4 vec) {
    return dvecN_length(vec.v, 4);
}
/** returns length of a vector, see dvecN_norm. Just here to match glsl */
static double dvec4_length_v(const double *vec) {
    return dvec4_length(DVec4(vec));
}


/** returns norm(b-a) */
static double dvec4_distance(dvec4 vec_a, dvec4 vec_b) {
    return dvecN_distance(vec_a.v, vec_b.v, 4);
}
/** returns norm(b-a) */
static double dvec4_distance_v(const double *vec_a, const double *vec_b) {
    return dvec4_distance(DVec4(vec_a), DVec4(vec_b));
}


/** dst = dot(I, Nref) < 0 ? N : -N */
static dvec4 dvec4_faceforward(dvec4 vec_N, dvec4 vec_I, dvec4 vec_Nref) {
    dvec4 res;
    dvecN_faceforward(res.v, vec_N.v, vec_I.v, vec_Nref.v, 4);
    return res;
}
/** dst = dot(I, Nref) < 0 ? N : -N */
static dvec4 dvec4_faceforward_v(const double *vec_N, const double *vec_I, const double *vec_Nref) {
    return dvec4_faceforward(DVec4(vec_N), DVec4(vec_I), DVec4(vec_Nref));
}


/** dst = I - 4.0 * N * dot(N,I) */
static dvec4 dvec4_reflect(dvec4 vec_I, dvec4 vec_N) {
    dvec4 res;
    dvecN_reflect(res.v, vec_I.v, vec_N.v, 4);
    return res;
}
/** dst = I - 4.0 * N * dot(N,I) */
static dvec4 dvec4_reflect_v(const double *vec_I, const double *vec_N) {
    return dvec4_reflect(DVec4(vec_I), DVec4(vec_N));
}


static dvec4 dvec4_refract(dvec4 vec_I, dvec4 vec_N, double eta) {
    dvec4 res;
    dvecN_refract(res.v, vec_I.v, vec_N.v, eta, 4);
    return res;
}
static dvec4 dvec4_refract_v(const double *vec_I, const double *vec_N, double eta) {
    return dvec4_refract(DVec4(vec_I), DVec4(vec_N), eta);
}


/** dst = a < b */
static bvec4 dvec4_less_than(dvec4 vec_a, double b) {
    bvec4 res;
    dvecN_less_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a < b */
static bvec4 dvec4_less_than_v(const double *vec_a, double b) {
    return dvec4_less_than(DVec4(vec_a), b);
}


/** dst = a < b */
static bvec4 dvec4_less_than_vec(dvec4 vec_a, dvec4 vec_b) {
    bvec4 res;
    dvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a < b */
static bvec4 dvec4_less_than_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_less_than_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a <= b */
static bvec4 dvec4_less_than_equal(dvec4 vec_a, double b) {
    bvec4 res;
    dvecN_less_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a <= b */
static bvec4 dvec4_less_than_equal_v(const double *vec_a, double b) {
    return dvec4_less_than_equal(DVec4(vec_a), b);
}


/** dst = a <= b */
static bvec4 dvec4_less_than_equal_vec(dvec4 vec_a, dvec4 vec_b) {
    bvec4 res;
    dvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a <= b */
static bvec4 dvec4_less_than_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_less_than_equal_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a > b */
static bvec4 dvec4_greater_than(dvec4 vec_a, double b) {
    bvec4 res;
    dvecN_greater_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a > b */
static bvec4 dvec4_greater_than_v(const double *vec_a, double b) {
    return dvec4_greater_than(DVec4(vec_a), b);
}


/** dst = a > b */
static bvec4 dvec4_greater_than_vec(dvec4 vec_a, dvec4 vec_b) {
    bvec4 res;
    dvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a > b */
static bvec4 dvec4_greater_than_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_greater_than_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a >= b */
static bvec4 dvec4_greater_than_equal(dvec4 vec_a, double b) {
    bvec4 res;
    dvecN_greater_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a >= b */
static bvec4 dvec4_greater_than_equal_v(const double *vec_a, double b) {
    return dvec4_greater_than_equal(DVec4(vec_a), b);
}


/** dst = a >= b */
static bvec4 dvec4_greater_than_equal_vec(dvec4 vec_a, dvec4 vec_b) {
    bvec4 res;
    dvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a >= b */
static bvec4 dvec4_greater_than_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_greater_than_equal_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a == b */
static bvec4 dvec4_equal(dvec4 vec_a, double b) {
    bvec4 res;
    dvecN_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a == b */
static bvec4 dvec4_equal_v(const double *vec_a, double b) {
    return dvec4_equal(DVec4(vec_a), b);
}


/** dst = a == b */
static bvec4 dvec4_equal_vec(dvec4 vec_a, dvec4 vec_b) {
    bvec4 res;
    dvecN_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a == b */
static bvec4 dvec4_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_equal_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a != b */
static bvec4 dvec4_not_equal(dvec4 vec_a, double b) {
    bvec4 res;
    dvecN_not_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a != b */
static bvec4 dvec4_not_equal_v(const double *vec_a, double b) {
    return dvec4_not_equal(DVec4(vec_a), b);
}


/** dst = a != b */
static bvec4 dvec4_not_equal_vec(dvec4 vec_a, dvec4 vec_b) {
    bvec4 res;
    dvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a != b */
static bvec4 dvec4_not_equal_vec_v(const double *vec_a, const double *vec_b) {
    return dvec4_not_equal_vec(DVec4(vec_a), DVec4(vec_b));
}


/** dst = a == b (+-eps) */
static bvec4 dvec4_equal_eps(dvec4 vec_a, double b, double eps) {
    bvec4 res;
    dvecN_equal_eps(res.v, vec_a.v, b, eps, 4);
    return res;
}
/** dst = a == b (+-eps) */
static bvec4 dvec4_equal_eps_v(const double *vec_a, double b, double eps) {
    return dvec4_equal_eps(DVec4(vec_a), b, eps);
}


/** dst = a == b (+-eps) */
static bvec4 dvec4_equal_eps_vec(dvec4 vec_a, dvec4 vec_b, double eps) {
    bvec4 res;
    dvecN_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 4);
    return res;
}
/** dst = a == b (+-eps) */
static bvec4 dvec4_equal_eps_vec_v(const double *vec_a, const double *vec_b, double eps) {
    return dvec4_equal_eps_vec(DVec4(vec_a), DVec4(vec_b), eps);
}


/** dst = a != b (+-eps) */
static bvec4 dvec4_not_equal_eps(dvec4 vec_a, double b, double eps) {
    bvec4 res;
    dvecN_not_equal_eps(res.v, vec_a.v, b, eps, 4);
    return res;
}
/** dst = a != b (+-eps) */
static bvec4 dvec4_not_equal_eps_v(const double *vec_a, double b, double eps) {
    return dvec4_not_equal_eps(DVec4(vec_a), b, eps);
}


/** dst = a != b (+-eps) */
static bvec4 dvec4_not_equal_eps_vec(dvec4 vec_a, dvec4 vec_b, double eps) {
    bvec4 res;
    dvecN_not_equal_eps_vec(res.v, vec_a.v, vec_b.v, eps, 4);
    return res;
}
/** dst = a != b (+-eps) */
static bvec4 dvec4_not_equal_eps_vec_v(const double *vec_a, const double *vec_b, double eps) {
    return dvec4_not_equal_eps_vec(DVec4(vec_a), DVec4(vec_b), eps);
}

/** dst = isnan(a) */
static bvec4 dvec4_isnan(dvec4 vec) {
    bvec4 res;
    dvecN_isnan(res.v, vec.v, 4);
    return res;
}
/** dst = isnan(a) */
static bvec4 dvec4_isnan_v(const double *vec) {
    return dvec4_isnan(DVec4(vec));
}

/** dst = isnan(a) */
static bvec4 dvec4_not_isnan(dvec4 vec) {
    bvec4 res;
    dvecN_not_isnan(res.v, vec.v, 4);
    return res;
}
/** dst = isnan(a) */
static bvec4 dvec4_not_isnan_v(const double *vec) {
    return dvec4_not_isnan(DVec4(vec));
}



//
// in addition to vec2:
//


/** dst = a x b , dst.w = 0 */
static dvec4 dvec4_cross(dvec4 vec_a, dvec4 vec_b) {
    dvec4 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    res.w = 0;
    return res;
}
/** dst = a x b , dst.w = 0 */
static dvec4 dvec4_cross_v(const double *vec_a, const double *vec_b) {
    return dvec4_cross(DVec4(vec_a), DVec4(vec_b));
}


#endif //MATHC_VEC_DVEC4_H
