#ifndef M_VEC_UCVEC2_H
#define M_VEC_UCVEC2_H


#include "ucvecn.h"
#include "../types/ucvec2.h"
#include "../types/bvec2.h"


/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_float(const float *cast) {
    ucvec2 res;
    ucvecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_double(const double *cast) {
    ucvec2 res;
    ucvecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_int(const int *cast) {
    ucvec2 res;
    ucvecN_cast_into(res.v, cast, 2);
    return res;
}

/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_uchar(const unsigned char *cast) {
    ucvec2 res;
    ucvecN_cast_into(res.v, cast, 2);
    return res;
}


/** dst = vec * 255 */
static ucvec2 ucvec2_cast_from_float_1(const float *cast) {
    ucvec2 res;
    ucvecN_cast_from_float_1(res.v, cast, 2);
    return res;
}

/** dst = vec * 255 */
static ucvec2 ucvec2_cast_from_double_1(const double *cast) {
    ucvec2 res;
    ucvecN_cast_from_double_1(res.v, cast, 2);
    return res;
}

/** dst = vec * 255 */
static ucvec2 ucvec2_cast_from_longdouble_1(const long double *cast) {
    ucvec2 res;
    ucvecN_cast_from_longdouble_1(res.v, cast, 2);
    return res;
}

/** a == b */
static bool ucvec2_cmp(ucvec2 a, ucvec2 b) {
    return ucvecN_cmp(a.v, b.v, 2);
}


/** dst = s */
static ucvec2 ucvec2_set(unsigned char s) {
    ucvec2 res;
    ucvecN_set(res.v, s, 2);
    return res;
}

/** dst = v0, v1, ... */
static ucvec2 ucvec2_new(unsigned char v0, unsigned char v1
) {
    ucvec2 self;
    self.v0 = v0;
    self.v1 = v1;
    return self;
}

/** dst = unit_x */
static ucvec2 ucvec2_unit_x() {
    ucvec2 res;
    ucvecN_unit_x(res.v, 2);
    return res;
}


/** dst = unit_y */
static ucvec2 ucvec2_unit_y() {
    ucvec2 res;
    ucvecN_unit_y(res.v, 2);
    return res;
}


/** dst = a + b */
static ucvec2 ucvec2_add_vec(ucvec2 a, ucvec2 b) {
    ucvec2 res;
    ucvecN_add_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a + b */
static ucvec2 ucvec2_add(ucvec2 a, unsigned char b) {
    ucvec2 res;
    ucvecN_add(res.v, a.v, b, 2);
    return res;
}


/** dst = a - b */
static ucvec2 ucvec2_sub_vec(ucvec2 a, ucvec2 b) {
    ucvec2 res;
    ucvecN_sub_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a - b */
static ucvec2 ucvec2_sub(ucvec2 a, unsigned char b) {
    ucvec2 res;
    ucvecN_sub(res.v, a.v, b, 2);
    return res;
}


/** dst = a * b */
static ucvec2 ucvec2_scale_vec(ucvec2 a, ucvec2 b) {
    ucvec2 res;
    ucvecN_scale_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a * b */
static ucvec2 ucvec2_scale(ucvec2 a, unsigned char b) {
    ucvec2 res;
    ucvecN_scale(res.v, a.v, b, 2);
    return res;
}


/** dst = a / b */
static ucvec2 ucvec2_div_vec(ucvec2 a, ucvec2 b) {
    ucvec2 res;
    ucvecN_div_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a / b */
static ucvec2 ucvec2_div(ucvec2 a, unsigned char b) {
    ucvec2 res;
    ucvecN_div(res.v, a.v, b, 2);
    return res;
}

/** dst = a + b * c */
static ucvec2 ucvec2_add_scaled_vec(ucvec2 a, ucvec2 b, ucvec2 c) {
    ucvec2 res;
    ucvecN_add_scaled_vec(res.v, a.v, b.v, c.v, 2);
    return res;
}

/** dst = a + b * c */
static ucvec2 ucvec2_add_scaled(ucvec2 a, ucvec2 b, unsigned char c) {
    ucvec2 res;
    ucvecN_add_scaled(res.v, a.v, b.v, c, 2);
    return res;
}


/** dst = pow(x, y) */
static ucvec2 ucvec2_pow(ucvec2 x, unsigned char y) {
    ucvec2 res;
    ucvecN_pow(res.v, x.v, y, 2);
    return res;
}


/** dst = pow(x, y) */
static ucvec2 ucvec2_pow_vec(ucvec2 x, ucvec2 y) {
    ucvec2 res;
    ucvecN_pow_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = exp(x) */
static ucvec2 ucvec2_exp(ucvec2 x) {
    ucvec2 res;
    ucvecN_exp(res.v, x.v, 2);
    return res;
}


/** dst = log(x) */
static ucvec2 ucvec2_log(ucvec2 x) {
    ucvec2 res;
    ucvecN_log(res.v, x.v, 2);
    return res;
}


/** dst = exp2(x) */
static ucvec2 ucvec2_exp2(ucvec2 x) {
    ucvec2 res;
    ucvecN_exp2(res.v, x.v, 2);
    return res;
}


/** dst = log2(x) */
static ucvec2 ucvec2_log2(ucvec2 x) {
    ucvec2 res;
    ucvecN_log2(res.v, x.v, 2);
    return res;
}


/** dst = sqrt(x) */
static ucvec2 ucvec2_sqrt(ucvec2 x) {
    ucvec2 res;
    ucvecN_sqrt(res.v, x.v, 2);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ucvec2 ucvec2_mod(ucvec2 x, unsigned char y) {
    ucvec2 res;
    ucvecN_mod(res.v, x.v, y, 2);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ucvec2 ucvec2_mod_vec(ucvec2 x, ucvec2 y) {
    ucvec2 res;
    ucvecN_mod_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = a < b ? a : b */
static ucvec2 ucvec2_min(ucvec2 x, unsigned char y) {
    ucvec2 res;
    ucvecN_min(res.v, x.v, y, 2);
    return res;
}


/** dst = a < b ? a : b */
static ucvec2 ucvec2_min_vec(ucvec2 x, ucvec2 y) {
    ucvec2 res;
    ucvecN_min_vec(res.v, x.v, y.v, 2);
    return res;
}


/** dst = a > b ? a : b */
static ucvec2 ucvec2_max(ucvec2 x, unsigned char y) {
    ucvec2 res;
    ucvecN_max(res.v, x.v, y, 2);
    return res;
}


/** dst = a > b ? a : b */
static ucvec2 ucvec2_max_vec(ucvec2 x, ucvec2 y) {
    ucvec2 res;
    ucvecN_max_vec(res.v, x.v, y.v, 2);
    return res;
}


/** returns the index of the min v value */
static int ucvec2_min_index(ucvec2 vec) {
    return ucvecN_min_index(vec.v, 2);
}


/** returns the index of the max v value */
static int ucvec2_max_index(ucvec2 vec) {
    return ucvecN_max_index(vec.v, 2);
}

/** dst = x < min ? min : (x > max ? max : x) */
static ucvec2 ucvec2_clamp(ucvec2 x, unsigned char min, unsigned char max) {
    ucvec2 res;
    ucvecN_clamp(res.v, x.v, min, max, 2);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec2 ucvec2_clamp_vec(ucvec2 x, ucvec2 min, ucvec2 max) {
    ucvec2 res;
    ucvecN_clamp_vec(res.v, x.v, min.v, max.v, 2);
    return res;
}


/** dst = a * (1-t) + b * t */
static ucvec2 ucvec2_mix(ucvec2 a, ucvec2 b, unsigned char t) {
    ucvec2 res;
    ucvecN_mix(res.v, a.v, b.v, t, 2);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ucvec2 ucvec2_step(ucvec2 x, unsigned char edge) {
    ucvec2 res;
    ucvecN_step(res.v, x.v, edge, 2);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ucvec2 ucvec2_step_vec(ucvec2 x, ucvec2 edge) {
    ucvec2 res;
    ucvecN_step_vec(res.v, x.v, edge.v, 2);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static unsigned char ucvec2_sum(ucvec2 v) {
    return ucvecN_sum(v.v, 2);
}


/** returns a dot b */
static unsigned char ucvec2_dot(ucvec2 a, ucvec2 b) {
    return ucvecN_dot(a.v, b.v, 2);
}


/** dst = a x b , dst.w... = 0 */
static ucvec2 ucvec2_cross(ucvec2 a, ucvec2 b) {
    ucvec2 res;
    ucvecN_cross(res.v, a.v, b.v, 2);
    return res;
}


/** returns ||v||_2 */
static unsigned char ucvec2_norm(ucvec2 v) {
    return ucvecN_norm(v.v, 2);
}


/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static unsigned char ucvec2_length(ucvec2 v) {
    return ucvecN_length(v.v, 2);
}


/** returns norm(b-a) */
static unsigned char ucvec2_distance(ucvec2 a, ucvec2 b) {
    return ucvecN_distance(a.v, b.v, 2);
}


/** returns dot(b-a) */
static unsigned char ucvec2_sqr_distance(ucvec2 a, ucvec2 b) {
    return ucvecN_sqr_distance(a.v, b.v, 2);
}


/** dst = a < b */
static bvec2 ucvec2_less_than(ucvec2 a, unsigned char b) {
    bvec2 res;
    ucvecN_less_than(res.v, a.v, b, 2);
    return res;
}


/** dst = a < b */
static bvec2 ucvec2_less_than_vec(ucvec2 a, ucvec2 b) {
    bvec2 res;
    ucvecN_less_than_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a <= b */
static bvec2 ucvec2_less_than_equal(ucvec2 a, unsigned char b) {
    bvec2 res;
    ucvecN_less_than_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a <= b */
static bvec2 ucvec2_less_than_equal_vec(ucvec2 a, ucvec2 b) {
    bvec2 res;
    ucvecN_less_than_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a > b */
static bvec2 ucvec2_greater_than(ucvec2 a, unsigned char b) {
    bvec2 res;
    ucvecN_greater_than(res.v, a.v, b, 2);
    return res;
}


/** dst = a > b */
static bvec2 ucvec2_greater_than_vec(ucvec2 a, ucvec2 b) {
    bvec2 res;
    ucvecN_greater_than_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a >= b */
static bvec2 ucvec2_greater_than_equal(ucvec2 a, unsigned char b) {
    bvec2 res;
    ucvecN_greater_than_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a >= b */
static bvec2 ucvec2_greater_than_equal_vec(ucvec2 a, ucvec2 b) {
    bvec2 res;
    ucvecN_greater_than_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a == b */
static bvec2 ucvec2_equal(ucvec2 a, unsigned char b) {
    bvec2 res;
    ucvecN_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a == b */
static bvec2 ucvec2_equal_vec(ucvec2 a, ucvec2 b) {
    bvec2 res;
    ucvecN_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


/** dst = a != b */
static bvec2 ucvec2_not_equal(ucvec2 a, unsigned char b) {
    bvec2 res;
    ucvecN_not_equal(res.v, a.v, b, 2);
    return res;
}


/** dst = a != b */
static bvec2 ucvec2_not_equal_vec(ucvec2 a, ucvec2 b) {
    bvec2 res;
    ucvecN_not_equal_vec(res.v, a.v, b.v, 2);
    return res;
}


#endif //M_VEC_UCVEC2_H
