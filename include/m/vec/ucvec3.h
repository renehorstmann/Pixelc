#ifndef M_VEC_UCVEC3_H
#define M_VEC_UCVEC3_H


#include "ucvecn.h"
#include "../types/ucvec3.h"
#include "../types/bvec3.h"

// macro to create a ucvec3
#define ucvec3_(x, y \
, z\
) (ucvec3) {{(x), (y)\
, (z)\
}}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_float(const float *cast) {
    ucvec3 res;
    ucvecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_double(const double *cast) {
    ucvec3 res;
    ucvecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_int(const int *cast) {
    ucvec3 res;
    ucvecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_uchar(const unsigned char *cast) {
    ucvec3 res;
    ucvecN_cast_into(res.v, cast, 3);
    return res;
}


/** dst = vec * 255 */
static ucvec3 ucvec3_cast_from_float_1(const float *cast) {
    ucvec3 res;
    ucvecN_cast_from_float_1(res.v, cast, 3);
    return res;
}

/** dst = vec * 255 */
static ucvec3 ucvec3_cast_from_double_1(const double *cast) {
    ucvec3 res;
    ucvecN_cast_from_double_1(res.v, cast, 3);
    return res;
}

/** dst = vec * 255 */
static ucvec3 ucvec3_cast_from_longdouble_1(const long double *cast) {
    ucvec3 res;
    ucvecN_cast_from_longdouble_1(res.v, cast, 3);
    return res;
}

/** a == b */
static bool ucvec3_cmp(ucvec3 a, ucvec3 b) {
    return ucvecN_cmp(a.v, b.v, 3);
}


/** dst = s */
static ucvec3 ucvec3_set(unsigned char s) {
    ucvec3 res;
    ucvecN_set(res.v, s, 3);
    return res;
}

/** dst = v0, v1, ... */
static ucvec3 ucvec3_new(unsigned char v0, unsigned char v1, unsigned char v2
) {
    ucvec3 self;
    self.v0 = v0;
    self.v1 = v1;
    self.v2 = v2;
    return self;
}

/** dst = unit_x */
static ucvec3 ucvec3_unit_x() {
    ucvec3 res;
    ucvecN_unit_x(res.v, 3);
    return res;
}


/** dst = unit_y */
static ucvec3 ucvec3_unit_y() {
    ucvec3 res;
    ucvecN_unit_y(res.v, 3);
    return res;
}


/** dst = unit_z */
static ucvec3 ucvec3_unit_z() {
    ucvec3 res;
    ucvecN_unit_z(res.v, 3);
    return res;
}


/** dst = a + b */
static ucvec3 ucvec3_add_vec(ucvec3 a, ucvec3 b) {
    ucvec3 res;
    ucvecN_add_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a + b */
static ucvec3 ucvec3_add(ucvec3 a, unsigned char b) {
    ucvec3 res;
    ucvecN_add(res.v, a.v, b, 3);
    return res;
}


/** dst = a - b */
static ucvec3 ucvec3_sub_vec(ucvec3 a, ucvec3 b) {
    ucvec3 res;
    ucvecN_sub_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a - b */
static ucvec3 ucvec3_sub(ucvec3 a, unsigned char b) {
    ucvec3 res;
    ucvecN_sub(res.v, a.v, b, 3);
    return res;
}


/** dst = a * b */
static ucvec3 ucvec3_scale_vec(ucvec3 a, ucvec3 b) {
    ucvec3 res;
    ucvecN_scale_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a * b */
static ucvec3 ucvec3_scale(ucvec3 a, unsigned char b) {
    ucvec3 res;
    ucvecN_scale(res.v, a.v, b, 3);
    return res;
}


/** dst = a / b */
static ucvec3 ucvec3_div_vec(ucvec3 a, ucvec3 b) {
    ucvec3 res;
    ucvecN_div_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a / b */
static ucvec3 ucvec3_div(ucvec3 a, unsigned char b) {
    ucvec3 res;
    ucvecN_div(res.v, a.v, b, 3);
    return res;
}

/** dst = a + b * c */
static ucvec3 ucvec3_add_scaled_vec(ucvec3 a, ucvec3 b, ucvec3 c) {
    ucvec3 res;
    ucvecN_add_scaled_vec(res.v, a.v, b.v, c.v, 3);
    return res;
}

/** dst = a + b * c */
static ucvec3 ucvec3_add_scaled(ucvec3 a, ucvec3 b, unsigned char c) {
    ucvec3 res;
    ucvecN_add_scaled(res.v, a.v, b.v, c, 3);
    return res;
}


/** dst = pow(x, y) */
static ucvec3 ucvec3_pow(ucvec3 x, unsigned char y) {
    ucvec3 res;
    ucvecN_pow(res.v, x.v, y, 3);
    return res;
}


/** dst = pow(x, y) */
static ucvec3 ucvec3_pow_vec(ucvec3 x, ucvec3 y) {
    ucvec3 res;
    ucvecN_pow_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = exp(x) */
static ucvec3 ucvec3_exp(ucvec3 x) {
    ucvec3 res;
    ucvecN_exp(res.v, x.v, 3);
    return res;
}


/** dst = log(x) */
static ucvec3 ucvec3_log(ucvec3 x) {
    ucvec3 res;
    ucvecN_log(res.v, x.v, 3);
    return res;
}


/** dst = exp2(x) */
static ucvec3 ucvec3_exp2(ucvec3 x) {
    ucvec3 res;
    ucvecN_exp2(res.v, x.v, 3);
    return res;
}


/** dst = log2(x) */
static ucvec3 ucvec3_log2(ucvec3 x) {
    ucvec3 res;
    ucvecN_log2(res.v, x.v, 3);
    return res;
}


/** dst = sqrt(x) */
static ucvec3 ucvec3_sqrt(ucvec3 x) {
    ucvec3 res;
    ucvecN_sqrt(res.v, x.v, 3);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ucvec3 ucvec3_mod(ucvec3 x, unsigned char y) {
    ucvec3 res;
    ucvecN_mod(res.v, x.v, y, 3);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ucvec3 ucvec3_mod_vec(ucvec3 x, ucvec3 y) {
    ucvec3 res;
    ucvecN_mod_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = a < b ? a : b */
static ucvec3 ucvec3_min(ucvec3 x, unsigned char y) {
    ucvec3 res;
    ucvecN_min(res.v, x.v, y, 3);
    return res;
}


/** dst = a < b ? a : b */
static ucvec3 ucvec3_min_vec(ucvec3 x, ucvec3 y) {
    ucvec3 res;
    ucvecN_min_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = a > b ? a : b */
static ucvec3 ucvec3_max(ucvec3 x, unsigned char y) {
    ucvec3 res;
    ucvecN_max(res.v, x.v, y, 3);
    return res;
}


/** dst = a > b ? a : b */
static ucvec3 ucvec3_max_vec(ucvec3 x, ucvec3 y) {
    ucvec3 res;
    ucvecN_max_vec(res.v, x.v, y.v, 3);
    return res;
}


/** returns the index of the min v value */
static int ucvec3_min_index(ucvec3 vec) {
    return ucvecN_min_index(vec.v, 3);
}


/** returns the index of the max v value */
static int ucvec3_max_index(ucvec3 vec) {
    return ucvecN_max_index(vec.v, 3);
}

/** dst = x < min ? min : (x > max ? max : x) */
static ucvec3 ucvec3_clamp(ucvec3 x, unsigned char min, unsigned char max) {
    ucvec3 res;
    ucvecN_clamp(res.v, x.v, min, max, 3);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec3 ucvec3_clamp_vec(ucvec3 x, ucvec3 min, ucvec3 max) {
    ucvec3 res;
    ucvecN_clamp_vec(res.v, x.v, min.v, max.v, 3);
    return res;
}


/** dst = a * (1-t) + b * t */
static ucvec3 ucvec3_mix(ucvec3 a, ucvec3 b, float t) {
    ucvec3 res;
    ucvecN_mix(res.v, a.v, b.v, t, 3);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ucvec3 ucvec3_step(ucvec3 x, unsigned char edge) {
    ucvec3 res;
    ucvecN_step(res.v, x.v, edge, 3);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ucvec3 ucvec3_step_vec(ucvec3 x, ucvec3 edge) {
    ucvec3 res;
    ucvecN_step_vec(res.v, x.v, edge.v, 3);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static unsigned char ucvec3_sum(ucvec3 v) {
    return ucvecN_sum(v.v, 3);
}


/** returns a dot b */
static unsigned char ucvec3_dot(ucvec3 a, ucvec3 b) {
    return ucvecN_dot(a.v, b.v, 3);
}


/** dst = a x b , dst.w... = 0 */
static ucvec3 ucvec3_cross(ucvec3 a, ucvec3 b) {
    ucvec3 res;
    ucvecN_cross(res.v, a.v, b.v, 3);
    return res;
}


/** returns ||v||_3 */
static unsigned char ucvec3_norm(ucvec3 v) {
    return ucvecN_norm(v.v, 3);
}


/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static unsigned char ucvec3_length(ucvec3 v) {
    return ucvecN_length(v.v, 3);
}


/** returns norm(b-a) */
static unsigned char ucvec3_distance(ucvec3 a, ucvec3 b) {
    return ucvecN_distance(a.v, b.v, 3);
}


/** returns dot(b-a) */
static unsigned char ucvec3_sqr_distance(ucvec3 a, ucvec3 b) {
    return ucvecN_sqr_distance(a.v, b.v, 3);
}


/** dst = a < b */
static bvec3 ucvec3_less_than(ucvec3 a, unsigned char b) {
    bvec3 res;
    ucvecN_less_than(res.v, a.v, b, 3);
    return res;
}


/** dst = a < b */
static bvec3 ucvec3_less_than_vec(ucvec3 a, ucvec3 b) {
    bvec3 res;
    ucvecN_less_than_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a <= b */
static bvec3 ucvec3_less_than_equal(ucvec3 a, unsigned char b) {
    bvec3 res;
    ucvecN_less_than_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a <= b */
static bvec3 ucvec3_less_than_equal_vec(ucvec3 a, ucvec3 b) {
    bvec3 res;
    ucvecN_less_than_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a > b */
static bvec3 ucvec3_greater_than(ucvec3 a, unsigned char b) {
    bvec3 res;
    ucvecN_greater_than(res.v, a.v, b, 3);
    return res;
}


/** dst = a > b */
static bvec3 ucvec3_greater_than_vec(ucvec3 a, ucvec3 b) {
    bvec3 res;
    ucvecN_greater_than_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a >= b */
static bvec3 ucvec3_greater_than_equal(ucvec3 a, unsigned char b) {
    bvec3 res;
    ucvecN_greater_than_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a >= b */
static bvec3 ucvec3_greater_than_equal_vec(ucvec3 a, ucvec3 b) {
    bvec3 res;
    ucvecN_greater_than_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a == b */
static bvec3 ucvec3_equal(ucvec3 a, unsigned char b) {
    bvec3 res;
    ucvecN_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a == b */
static bvec3 ucvec3_equal_vec(ucvec3 a, ucvec3 b) {
    bvec3 res;
    ucvecN_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a != b */
static bvec3 ucvec3_not_equal(ucvec3 a, unsigned char b) {
    bvec3 res;
    ucvecN_not_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a != b */
static bvec3 ucvec3_not_equal_vec(ucvec3 a, ucvec3 b) {
    bvec3 res;
    ucvecN_not_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


#endif //M_VEC_UCVEC3_H
