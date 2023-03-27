#ifndef M_VEC_UCVEC4_H
#define M_VEC_UCVEC4_H


#include "ucvecn.h"
#include "../types/ucvec4.h"
#include "../types/bvec4.h"


/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_float(const float *cast) {
    ucvec4 res;
    ucvecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_double(const double *cast) {
    ucvec4 res;
    ucvecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_int(const int *cast) {
    ucvec4 res;
    ucvecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_uchar(const unsigned char *cast) {
    ucvec4 res;
    ucvecN_cast_into(res.v, cast, 4);
    return res;
}


/** dst = vec * 255 */
static ucvec4 ucvec4_cast_from_float_1(const float *cast) {
    ucvec4 res;
    ucvecN_cast_from_float_1(res.v, cast, 4);
    return res;
}

/** dst = vec * 255 */
static ucvec4 ucvec4_cast_from_double_1(const double *cast) {
    ucvec4 res;
    ucvecN_cast_from_double_1(res.v, cast, 4);
    return res;
}

/** dst = vec * 255 */
static ucvec4 ucvec4_cast_from_longdouble_1(const long double *cast) {
    ucvec4 res;
    ucvecN_cast_from_longdouble_1(res.v, cast, 4);
    return res;
}

/** a == b */
static bool ucvec4_cmp(ucvec4 a, ucvec4 b) {
    return ucvecN_cmp(a.v, b.v, 4);
}


/** dst = s */
static ucvec4 ucvec4_set(unsigned char s) {
    ucvec4 res;
    ucvecN_set(res.v, s, 4);
    return res;
}

/** dst = v0, v1, ... */
static ucvec4 ucvec4_new(unsigned char v0, unsigned char v1, unsigned char v2, unsigned char v3
) {
    ucvec4 self;
    self.v0 = v0;
    self.v1 = v1;
    self.v2 = v2;
    self.v3 = v3;
    return self;
}

/** dst = unit_x */
static ucvec4 ucvec4_unit_x() {
    ucvec4 res;
    ucvecN_unit_x(res.v, 4);
    return res;
}


/** dst = unit_y */
static ucvec4 ucvec4_unit_y() {
    ucvec4 res;
    ucvecN_unit_y(res.v, 4);
    return res;
}


/** dst = unit_z */
static ucvec4 ucvec4_unit_z() {
    ucvec4 res;
    ucvecN_unit_z(res.v, 4);
    return res;
}


/** dst = unit_w */
static ucvec4 ucvec4_unit_w() {
    ucvec4 res;
    ucvecN_unit_w(res.v, 4);
    return res;
}


/** dst = a + b */
static ucvec4 ucvec4_add_vec(ucvec4 a, ucvec4 b) {
    ucvec4 res;
    ucvecN_add_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a + b */
static ucvec4 ucvec4_add(ucvec4 a, unsigned char b) {
    ucvec4 res;
    ucvecN_add(res.v, a.v, b, 4);
    return res;
}


/** dst = a - b */
static ucvec4 ucvec4_sub_vec(ucvec4 a, ucvec4 b) {
    ucvec4 res;
    ucvecN_sub_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a - b */
static ucvec4 ucvec4_sub(ucvec4 a, unsigned char b) {
    ucvec4 res;
    ucvecN_sub(res.v, a.v, b, 4);
    return res;
}


/** dst = a * b */
static ucvec4 ucvec4_scale_vec(ucvec4 a, ucvec4 b) {
    ucvec4 res;
    ucvecN_scale_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a * b */
static ucvec4 ucvec4_scale(ucvec4 a, unsigned char b) {
    ucvec4 res;
    ucvecN_scale(res.v, a.v, b, 4);
    return res;
}


/** dst = a / b */
static ucvec4 ucvec4_div_vec(ucvec4 a, ucvec4 b) {
    ucvec4 res;
    ucvecN_div_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a / b */
static ucvec4 ucvec4_div(ucvec4 a, unsigned char b) {
    ucvec4 res;
    ucvecN_div(res.v, a.v, b, 4);
    return res;
}

/** dst = a + b * c */
static ucvec4 ucvec4_add_scaled_vec(ucvec4 a, ucvec4 b, ucvec4 c) {
    ucvec4 res;
    ucvecN_add_scaled_vec(res.v, a.v, b.v, c.v, 4);
    return res;
}

/** dst = a + b * c */
static ucvec4 ucvec4_add_scaled(ucvec4 a, ucvec4 b, unsigned char c) {
    ucvec4 res;
    ucvecN_add_scaled(res.v, a.v, b.v, c, 4);
    return res;
}


/** dst = pow(x, y) */
static ucvec4 ucvec4_pow(ucvec4 x, unsigned char y) {
    ucvec4 res;
    ucvecN_pow(res.v, x.v, y, 4);
    return res;
}


/** dst = pow(x, y) */
static ucvec4 ucvec4_pow_vec(ucvec4 x, ucvec4 y) {
    ucvec4 res;
    ucvecN_pow_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = exp(x) */
static ucvec4 ucvec4_exp(ucvec4 x) {
    ucvec4 res;
    ucvecN_exp(res.v, x.v, 4);
    return res;
}


/** dst = log(x) */
static ucvec4 ucvec4_log(ucvec4 x) {
    ucvec4 res;
    ucvecN_log(res.v, x.v, 4);
    return res;
}


/** dst = exp2(x) */
static ucvec4 ucvec4_exp2(ucvec4 x) {
    ucvec4 res;
    ucvecN_exp2(res.v, x.v, 4);
    return res;
}


/** dst = log2(x) */
static ucvec4 ucvec4_log2(ucvec4 x) {
    ucvec4 res;
    ucvecN_log2(res.v, x.v, 4);
    return res;
}


/** dst = sqrt(x) */
static ucvec4 ucvec4_sqrt(ucvec4 x) {
    ucvec4 res;
    ucvecN_sqrt(res.v, x.v, 4);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ucvec4 ucvec4_mod(ucvec4 x, unsigned char y) {
    ucvec4 res;
    ucvecN_mod(res.v, x.v, y, 4);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ucvec4 ucvec4_mod_vec(ucvec4 x, ucvec4 y) {
    ucvec4 res;
    ucvecN_mod_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = a < b ? a : b */
static ucvec4 ucvec4_min(ucvec4 x, unsigned char y) {
    ucvec4 res;
    ucvecN_min(res.v, x.v, y, 4);
    return res;
}


/** dst = a < b ? a : b */
static ucvec4 ucvec4_min_vec(ucvec4 x, ucvec4 y) {
    ucvec4 res;
    ucvecN_min_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = a > b ? a : b */
static ucvec4 ucvec4_max(ucvec4 x, unsigned char y) {
    ucvec4 res;
    ucvecN_max(res.v, x.v, y, 4);
    return res;
}


/** dst = a > b ? a : b */
static ucvec4 ucvec4_max_vec(ucvec4 x, ucvec4 y) {
    ucvec4 res;
    ucvecN_max_vec(res.v, x.v, y.v, 4);
    return res;
}


/** returns the index of the min v value */
static int ucvec4_min_index(ucvec4 vec) {
    return ucvecN_min_index(vec.v, 4);
}


/** returns the index of the max v value */
static int ucvec4_max_index(ucvec4 vec) {
    return ucvecN_max_index(vec.v, 4);
}

/** dst = x < min ? min : (x > max ? max : x) */
static ucvec4 ucvec4_clamp(ucvec4 x, unsigned char min, unsigned char max) {
    ucvec4 res;
    ucvecN_clamp(res.v, x.v, min, max, 4);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec4 ucvec4_clamp_vec(ucvec4 x, ucvec4 min, ucvec4 max) {
    ucvec4 res;
    ucvecN_clamp_vec(res.v, x.v, min.v, max.v, 4);
    return res;
}


/** dst = a * (1-t) + b * t */
static ucvec4 ucvec4_mix(ucvec4 a, ucvec4 b, unsigned char t) {
    ucvec4 res;
    ucvecN_mix(res.v, a.v, b.v, t, 4);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ucvec4 ucvec4_step(ucvec4 x, unsigned char edge) {
    ucvec4 res;
    ucvecN_step(res.v, x.v, edge, 4);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ucvec4 ucvec4_step_vec(ucvec4 x, ucvec4 edge) {
    ucvec4 res;
    ucvecN_step_vec(res.v, x.v, edge.v, 4);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static unsigned char ucvec4_sum(ucvec4 v) {
    return ucvecN_sum(v.v, 4);
}


/** returns a dot b */
static unsigned char ucvec4_dot(ucvec4 a, ucvec4 b) {
    return ucvecN_dot(a.v, b.v, 4);
}


/** dst = a x b , dst.w... = 0 */
static ucvec4 ucvec4_cross(ucvec4 a, ucvec4 b) {
    ucvec4 res;
    ucvecN_cross(res.v, a.v, b.v, 4);
    return res;
}


/** returns ||v||_4 */
static unsigned char ucvec4_norm(ucvec4 v) {
    return ucvecN_norm(v.v, 4);
}


/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static unsigned char ucvec4_length(ucvec4 v) {
    return ucvecN_length(v.v, 4);
}


/** returns norm(b-a) */
static unsigned char ucvec4_distance(ucvec4 a, ucvec4 b) {
    return ucvecN_distance(a.v, b.v, 4);
}


/** returns dot(b-a) */
static unsigned char ucvec4_sqr_distance(ucvec4 a, ucvec4 b) {
    return ucvecN_sqr_distance(a.v, b.v, 4);
}


/** dst = a < b */
static bvec4 ucvec4_less_than(ucvec4 a, unsigned char b) {
    bvec4 res;
    ucvecN_less_than(res.v, a.v, b, 4);
    return res;
}


/** dst = a < b */
static bvec4 ucvec4_less_than_vec(ucvec4 a, ucvec4 b) {
    bvec4 res;
    ucvecN_less_than_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a <= b */
static bvec4 ucvec4_less_than_equal(ucvec4 a, unsigned char b) {
    bvec4 res;
    ucvecN_less_than_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a <= b */
static bvec4 ucvec4_less_than_equal_vec(ucvec4 a, ucvec4 b) {
    bvec4 res;
    ucvecN_less_than_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a > b */
static bvec4 ucvec4_greater_than(ucvec4 a, unsigned char b) {
    bvec4 res;
    ucvecN_greater_than(res.v, a.v, b, 4);
    return res;
}


/** dst = a > b */
static bvec4 ucvec4_greater_than_vec(ucvec4 a, ucvec4 b) {
    bvec4 res;
    ucvecN_greater_than_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a >= b */
static bvec4 ucvec4_greater_than_equal(ucvec4 a, unsigned char b) {
    bvec4 res;
    ucvecN_greater_than_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a >= b */
static bvec4 ucvec4_greater_than_equal_vec(ucvec4 a, ucvec4 b) {
    bvec4 res;
    ucvecN_greater_than_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a == b */
static bvec4 ucvec4_equal(ucvec4 a, unsigned char b) {
    bvec4 res;
    ucvecN_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a == b */
static bvec4 ucvec4_equal_vec(ucvec4 a, ucvec4 b) {
    bvec4 res;
    ucvecN_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a != b */
static bvec4 ucvec4_not_equal(ucvec4 a, unsigned char b) {
    bvec4 res;
    ucvecN_not_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a != b */
static bvec4 ucvec4_not_equal_vec(ucvec4 a, ucvec4 b) {
    bvec4 res;
    ucvecN_not_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


#endif //M_VEC_UCVEC4_H
