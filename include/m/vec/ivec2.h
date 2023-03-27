#ifndef M_VEC_IVEC2_H
#define M_VEC_IVEC2_H


#include "ivecn.h"
#include "../types/ivec2.h"
#include "../types/bvec2.h"


/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_float(const float *cast) {
    ivec2 res;
    ivecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_double(const double *cast) {
    ivec2 res;
    ivecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_int(const int *cast) {
    ivec2 res;
    ivecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_uchar(const unsigned char *cast) {
    ivec2 res;
    ivecN_cast_into(res.v, cast, 2);
    return res;
}


/** dst = vec * 255 */
static ivec2 ivec2_cast_from_float_1(const float *cast) {
    ivec2 res;
    ivecN_cast_from_float_1(res.v, cast, 2);
    return res;
}

/** dst = vec * 255 */
static ivec2 ivec2_cast_from_double_1(const double *cast) {
    ivec2 res;
    ivecN_cast_from_double_1(res.v, cast, 2);
    return res;
}

/** dst = vec * 255 */
static ivec2 ivec2_cast_from_longdouble_1(const long double *cast) {
    ivec2 res;
    ivecN_cast_from_longdouble_1(res.v, cast, 2);
    return res;
}

/** a == b */
static bool ivec2_cmp(ivec2 a, ivec2 b) {
    return ivecN_cmp(a.v, b.v, 2);
}


/** dst = s */
static ivec2 ivec2_set(int s) {
    ivec2 res;
    ivecN_set(res.v, s, 2);
    return res;
}

/** dst = v0, v1, ... */
static ivec2 ivec2_new(int v0, int v1
) {
    ivec2 self;
    self.v0 = v0;
    self.v1 = v1;
    return self;
}

/** dst = unit_x */
static ivec2 ivec2_unit_x() {
    ivec2 res;
    ivecN_unit_x(res.v, 2);
    return res;
}


/** dst = unit_y */
static ivec2 ivec2_unit_y() {
    ivec2 res;
    ivecN_unit_y(res.v, 2);
    return res;
}


/** dst = -v */
static ivec2 ivec2_neg(ivec2 v) {
    ivec2 res;
    ivecN_neg(res.v, v.v, 2);
    return res;
}


/** dst = a + b */
static ivec2 ivec2_add_vec(ivec2 a, ivec2 b) {
    ivec2 res;
    ivecN_add_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a + b */
static ivec2 ivec2_add(ivec2 a, int b) {
    ivec2 res;
    ivecN_add(res.v, a.v, b, 2);
    return res;
}


/** dst = a - b */
static ivec2 ivec2_sub_vec(ivec2 a, ivec2 b) {
    ivec2 res;
    ivecN_sub_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a - b */
static ivec2 ivec2_sub(ivec2 a, int b) {
    ivec2 res;
    ivecN_sub(res.v, a.v, b, 2);
    return res;
}


/** dst = a * b */
static ivec2 ivec2_scale_vec(ivec2 a, ivec2 b) {
    ivec2 res;
    ivecN_scale_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a * b */
static ivec2 ivec2_scale(ivec2 a, int b) {
    ivec2 res;
    ivecN_scale(res.v, a.v, b, 2);
    return res;
}


/** dst = a / b */
static ivec2 ivec2_div_vec(ivec2 a, ivec2 b) {
    ivec2 res;
    ivecN_div_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a / b */
static ivec2 ivec2_div(ivec2 a, int b) {
    ivec2 res;
    ivecN_div(res.v, a.v, b, 2);
    return res;
}

/** dst = a + b * c */
static ivec2 ivec2_add_scaled_vec(ivec2 a, ivec2 b, ivec2 c) {
    ivec2 res;
    ivecN_add_scaled_vec(res.v, a.v, b.v, c.v, 2);
    return res;
}

/** dst = a + b * c */
static ivec2 ivec2_add_scaled(ivec2 a, ivec2 b, int c) {
    ivec2 res;
    ivecN_add_scaled(res.v, a.v, b.v, c, 2);
    return res;
}


/** dst = pow(x, y) */
static ivec2 ivec2_pow(ivec2 x, int y) {
    ivec2 res;
    ivecN_pow(res.v, x.v, y, 2);
    return res;
}


/** dst = pow(x, y) */
static ivec2 ivec2_pow_vec(ivec2 x, ivec2 y) {
    ivec2 res;
    ivecN_pow_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = exp(x) */
static ivec2 ivec2_exp(ivec2 x) {
    ivec2 res;
    ivecN_exp(res.v, x.v, 2);
    return res;
}


/** dst = log(x) */
static ivec2 ivec2_log(ivec2 x) {
    ivec2 res;
    ivecN_log(res.v, x.v, 2);
    return res;
}


/** dst = exp2(x) */
static ivec2 ivec2_exp2(ivec2 x) {
    ivec2 res;
    ivecN_exp2(res.v, x.v, 2);
    return res;
}


/** dst = log2(x) */
static ivec2 ivec2_log2(ivec2 x) {
    ivec2 res;
    ivecN_log2(res.v, x.v, 2);
    return res;
}


/** dst = sqrt(x) */
static ivec2 ivec2_sqrt(ivec2 x) {
    ivec2 res;
    ivecN_sqrt(res.v, x.v, 2);
    return res;
}


/** dst = abs(x) */
static ivec2 ivec2_abs(ivec2 x) {
    ivec2 res;
    ivecN_abs(res.v, x.v, 2);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec2 ivec2_sign(ivec2 x) {
    ivec2 res;
    ivecN_sign(res.v, x.v, 2);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ivec2 ivec2_mod(ivec2 x, int y) {
    ivec2 res;
    ivecN_mod(res.v, x.v, y, 2);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ivec2 ivec2_mod_vec(ivec2 x, ivec2 y) {
    ivec2 res;
    ivecN_mod_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = a < b ? a : b */
static ivec2 ivec2_min(ivec2 x, int y) {
    ivec2 res;
    ivecN_min(res.v, x.v, y, 2);
    return res;
}


/** dst = a < b ? a : b */
static ivec2 ivec2_min_vec(ivec2 x, ivec2 y) {
    ivec2 res;
    ivecN_min_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = a > b ? a : b */
static ivec2 ivec2_max(ivec2 x, int y) {
    ivec2 res;
    ivecN_max(res.v, x.v, y, 2);
    return res;
}


/** dst = a > b ? a : b */
static ivec2 ivec2_max_vec(ivec2 x, ivec2 y) {
    ivec2 res;
    ivecN_max_vec(res.v, x.v, y.v, 2);
    return res;
}


/** returns the index of the min v value */
static int ivec2_min_index(ivec2 vec) {
    return ivecN_min_index(vec.v, 2);
}


/** returns the index of the max v value */
static int ivec2_max_index(ivec2 vec) {
    return ivecN_max_index(vec.v, 2);
}

/** dst = x < min ? min : (x > max ? max : x) */
static ivec2 ivec2_clamp(ivec2 x, int min, int max) {
    ivec2 res;
    ivecN_clamp(res.v, x.v, min, max, 2);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec2 ivec2_clamp_vec(ivec2 x, ivec2 min, ivec2 max) {
    ivec2 res;
    ivecN_clamp_vec(res.v, x.v, min.v, max.v, 2);
    return res;
}


/** dst = a * (1-t) + b * t */
static ivec2 ivec2_mix(ivec2 a, ivec2 b, int t) {
    ivec2 res;
    ivecN_mix(res.v, a.v, b.v, t, 2);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ivec2 ivec2_step(ivec2 x, int edge) {
    ivec2 res;
    ivecN_step(res.v, x.v, edge, 2);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ivec2 ivec2_step_vec(ivec2 x, ivec2 edge) {
    ivec2 res;
    ivecN_step_vec(res.v, x.v, edge.v, 2);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static int ivec2_sum(ivec2 v) {
    return ivecN_sum(v.v, 2);
}


/** returns a dot b */
static int ivec2_dot(ivec2 a, ivec2 b) {
    return ivecN_dot(a.v, b.v, 2);
}


/** dst = a x b , dst.w... = 0 */
static ivec2 ivec2_cross(ivec2 a, ivec2 b) {
    ivec2 res;
    ivecN_cross(res.v, a.v, b.v, 2);
    return res;
}


/** returns ||v||_2 */
static int ivec2_norm(ivec2 v) {
    return ivecN_norm(v.v, 2);
}


/** returns ||v||_p */
static int ivec2_norm_p(ivec2 v, int p) {
    return ivecN_norm_p(v.v, p, 2);
}


/** returns ||v||_1 */
static int ivec2_norm_1(ivec2 v) {
    return ivecN_norm_1(v.v, 2);
}


/** returns ||v||_inf */
static int ivec2_norm_inf(ivec2 v) {
    return ivecN_norm_inf(v.v, 2);
}


/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static int ivec2_length(ivec2 v) {
    return ivecN_length(v.v, 2);
}


/** returns norm(b-a) */
static int ivec2_distance(ivec2 a, ivec2 b) {
    return ivecN_distance(a.v, b.v, 2);
}


/** returns dot(b-a) */
static int ivec2_sqr_distance(ivec2 a, ivec2 b) {
    return ivecN_sqr_distance(a.v, b.v, 2);
}


/** dst = a < b */
static bvec2 ivec2_less_than(ivec2 a, int b) {
    bvec2 res;
    ivecN_less_than(res.v, a.v, b, 2);
    return res;
}


/** dst = a < b */
static bvec2 ivec2_less_than_vec(ivec2 a, ivec2 b) {
    bvec2 res;
    ivecN_less_than_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a <= b */
static bvec2 ivec2_less_than_equal(ivec2 a, int b) {
    bvec2 res;
    ivecN_less_than_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a <= b */
static bvec2 ivec2_less_than_equal_vec(ivec2 a, ivec2 b) {
    bvec2 res;
    ivecN_less_than_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a > b */
static bvec2 ivec2_greater_than(ivec2 a, int b) {
    bvec2 res;
    ivecN_greater_than(res.v, a.v, b, 2);
    return res;
}


/** dst = a > b */
static bvec2 ivec2_greater_than_vec(ivec2 a, ivec2 b) {
    bvec2 res;
    ivecN_greater_than_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a >= b */
static bvec2 ivec2_greater_than_equal(ivec2 a, int b) {
    bvec2 res;
    ivecN_greater_than_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a >= b */
static bvec2 ivec2_greater_than_equal_vec(ivec2 a, ivec2 b) {
    bvec2 res;
    ivecN_greater_than_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a == b */
static bvec2 ivec2_equal(ivec2 a, int b) {
    bvec2 res;
    ivecN_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a == b */
static bvec2 ivec2_equal_vec(ivec2 a, ivec2 b) {
    bvec2 res;
    ivecN_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a != b */
static bvec2 ivec2_not_equal(ivec2 a, int b) {
    bvec2 res;
    ivecN_not_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a != b */
static bvec2 ivec2_not_equal_vec(ivec2 a, ivec2 b) {
    bvec2 res;
    ivecN_not_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


#endif //M_VEC_IVEC2_H
