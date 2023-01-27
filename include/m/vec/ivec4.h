#ifndef M_VEC_IVEC4_H
#define M_VEC_IVEC4_H


#include "ivecn.h"
#include "../types/ivec4.h"
#include "../types/bvec4.h"


/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_float(const float *cast) {
    ivec4 res;
    ivecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_double(const double *cast) {
    ivec4 res;
    ivecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_int(const int *cast) {
    ivec4 res;
    ivecN_cast_into(res.v, cast, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_uchar(const unsigned char *cast) {
    ivec4 res;
    ivecN_cast_into(res.v, cast, 4);
    return res;
}


/** dst = vec * 255 */
static ivec4 ivec4_cast_from_float_1(const float *cast) {
    ivec4 res;
    ivecN_cast_from_float_1(res.v, cast, 4);
    return res;
}

/** dst = vec * 255 */
static ivec4 ivec4_cast_from_double_1(const double *cast) {
    ivec4 res;
    ivecN_cast_from_double_1(res.v, cast, 4);
    return res;
}

/** dst = vec * 255 */
static ivec4 ivec4_cast_from_longdouble_1(const long double *cast) {
    ivec4 res;
    ivecN_cast_from_longdouble_1(res.v, cast, 4);
    return res;
}

/** a == b */
static bool ivec4_cmp(ivec4 a, ivec4 b) {
    return ivecN_cmp(a.v, b.v, 4);
}


/** dst = s */
static ivec4 ivec4_set(int s) {
    ivec4 res;
    ivecN_set(res.v, s, 4);
    return res;
}

/** dst = v0, v1, ... */
static ivec4 ivec4_new(int v0, int v1
         , int v2
         , int v3
) {
    ivec4 self;
    self.v0 = v0;
    self.v1 = v1;
    self.v2 = v2;
    self.v3 = v3;
    return self;
}

/** dst = unit_x */
static ivec4 ivec4_unit_x() {
    ivec4 res;
    ivecN_unit_x(res.v, 4);
    return res;
}


/** dst = unit_y */
static ivec4 ivec4_unit_y() {
    ivec4 res;
    ivecN_unit_y(res.v, 4);
    return res;
}


/** dst = unit_z */
static ivec4 ivec4_unit_z() {
    ivec4 res;
    ivecN_unit_z(res.v, 4);
    return res;
}


/** dst = unit_w */
static ivec4 ivec4_unit_w() {
    ivec4 res;
    ivecN_unit_w(res.v, 4);
    return res;
}


/** dst = -v */
static ivec4 ivec4_neg(ivec4 v) {
    ivec4 res;
    ivecN_neg(res.v, v.v, 4);
    return res;
}


/** dst = a + b */
static ivec4 ivec4_add_vec(ivec4 a, ivec4 b) {
    ivec4 res;
    ivecN_add_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a + b */
static ivec4 ivec4_add(ivec4 a, int b) {
    ivec4 res;
    ivecN_add(res.v, a.v, b, 4);
    return res;
}


/** dst = a - b */
static ivec4 ivec4_sub_vec(ivec4 a, ivec4 b) {
    ivec4 res;
    ivecN_sub_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a - b */
static ivec4 ivec4_sub(ivec4 a, int b) {
    ivec4 res;
    ivecN_sub(res.v, a.v, b, 4);
    return res;
}


/** dst = a * b */
static ivec4 ivec4_scale_vec(ivec4 a, ivec4 b) {
    ivec4 res;
    ivecN_scale_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a * b */
static ivec4 ivec4_scale(ivec4 a, int b) {
    ivec4 res;
    ivecN_scale(res.v, a.v, b, 4);
    return res;
}


/** dst = a / b */
static ivec4 ivec4_div_vec(ivec4 a, ivec4 b) {
    ivec4 res;
    ivecN_div_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a / b */
static ivec4 ivec4_div(ivec4 a, int b) {
    ivec4 res;
    ivecN_div(res.v, a.v, b, 4);
    return res;
}




















/** dst = pow(x, y) */
static ivec4 ivec4_pow(ivec4 x, int y) {
    ivec4 res;
    ivecN_pow(res.v, x.v, y, 4);
    return res;
}


/** dst = pow(x, y) */
static ivec4 ivec4_pow_vec(ivec4 x, ivec4 y) {
    ivec4 res;
    ivecN_pow_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = exp(x) */
static ivec4 ivec4_exp(ivec4 x) {
    ivec4 res;
    ivecN_exp(res.v, x.v, 4);
    return res;
}


/** dst = log(x) */
static ivec4 ivec4_log(ivec4 x) {
    ivec4 res;
    ivecN_log(res.v, x.v, 4);
    return res;
}


/** dst = exp2(x) */
static ivec4 ivec4_exp2(ivec4 x) {
    ivec4 res;
    ivecN_exp2(res.v, x.v, 4);
    return res;
}


/** dst = log2(x) */
static ivec4 ivec4_log2(ivec4 x) {
    ivec4 res;
    ivecN_log2(res.v, x.v, 4);
    return res;
}


/** dst = sqrt(x) */
static ivec4 ivec4_sqrt(ivec4 x) {
    ivec4 res;
    ivecN_sqrt(res.v, x.v, 4);
    return res;
}




/** dst = abs(x) */
static ivec4 ivec4_abs(ivec4 x) {
    ivec4 res;
    ivecN_abs(res.v, x.v, 4);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec4 ivec4_sign(ivec4 x) {
    ivec4 res;
    ivecN_sign(res.v, x.v, 4);
    return res;
}








/** dst = (x % y + y) % y (always positive, if y>0) **/
static ivec4 ivec4_mod(ivec4 x, int y) {
    ivec4 res;
    ivecN_mod(res.v, x.v, y, 4);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ivec4 ivec4_mod_vec(ivec4 x, ivec4 y) {
    ivec4 res;
    ivecN_mod_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = a < b ? a : b */
static ivec4 ivec4_min(ivec4 x, int y) {
    ivec4 res;
    ivecN_min(res.v, x.v, y, 4);
    return res;
}


/** dst = a < b ? a : b */
static ivec4 ivec4_min_vec(ivec4 x, ivec4 y) {
    ivec4 res;
    ivecN_min_vec(res.v, x.v, y.v, 4);
    return res;
}


/** dst = a > b ? a : b */
static ivec4 ivec4_max(ivec4 x, int y) {
    ivec4 res;
    ivecN_max(res.v, x.v, y, 4);
    return res;
}


/** dst = a > b ? a : b */
static ivec4 ivec4_max_vec(ivec4 x, ivec4 y) {
    ivec4 res;
    ivecN_max_vec(res.v, x.v, y.v, 4);
    return res;
}


/** returns the index of the min v value */
static int ivec4_min_index(ivec4 vec) {
    return ivecN_min_index(vec.v, 4);
}


/** returns the index of the max v value */
static int ivec4_max_index(ivec4 vec) {
    return ivecN_max_index(vec.v, 4);
}

/** dst = x < min ? min : (x > max ? max : x) */
static ivec4 ivec4_clamp(ivec4 x, int min, int max) {
    ivec4 res;
    ivecN_clamp(res.v, x.v, min, max, 4);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec4 ivec4_clamp_vec(ivec4 x, ivec4 min, ivec4 max) {
    ivec4 res;
    ivecN_clamp_vec(res.v, x.v, min.v, max.v, 4);
    return res;
}


/** dst = a * (1-t) + b * t */
static ivec4 ivec4_mix(ivec4 a, ivec4 b, int t) {
    ivec4 res;
    ivecN_mix(res.v, a.v, b.v, t, 4);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ivec4 ivec4_step(ivec4 x, int edge) {
    ivec4 res;
    ivecN_step(res.v, x.v, edge, 4);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ivec4 ivec4_step_vec(ivec4 x, ivec4 edge) {
    ivec4 res;
    ivecN_step_vec(res.v, x.v, edge.v, 4);
    return res;
}






/** returns v[0] + v[1] + ... + v[n-1] */
static int ivec4_sum(ivec4 v) {
    return ivecN_sum(v.v, 4);
}


/** returns a dot b */
static int ivec4_dot(ivec4 a, ivec4 b) {
    return ivecN_dot(a.v, b.v, 4);
}


/** dst = a x b , dst.w... = 0 */
static ivec4 ivec4_cross(ivec4 a, ivec4 b) {
    ivec4 res;
    ivecN_cross(res.v, a.v, b.v, 4);
    return res;
}


/** returns ||v||_4 */
static int ivec4_norm(ivec4 v) {
    return ivecN_norm(v.v, 4);
}


/** returns ||v||_p */
static int ivec4_norm_p(ivec4 v, int p) {
    return ivecN_norm_p(v.v, p, 4);
}


/** returns ||v||_1 */
static int ivec4_norm_1(ivec4 v) {
    return ivecN_norm_1(v.v, 4);
}


/** returns ||v||_inf */
static int ivec4_norm_inf(ivec4 v) {
    return ivecN_norm_inf(v.v, 4);
}






/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static int ivec4_length(ivec4 v) {
    return ivecN_length(v.v, 4);
}


/** returns norm(b-a) */
static int ivec4_distance(ivec4 a, ivec4 b) {
    return ivecN_distance(a.v, b.v, 4);
}


/** returns dot(b-a) */
static int ivec4_sqr_distance(ivec4 a, ivec4 b) {
    return ivecN_sqr_distance(a.v, b.v, 4);
}








/** dst = a < b */
static bvec4 ivec4_less_than(ivec4 a, int b) {
    bvec4 res;
    ivecN_less_than(res.v, a.v, b, 4);
    return res;
}


/** dst = a < b */
static bvec4 ivec4_less_than_vec(ivec4 a, ivec4 b) {
    bvec4 res;
    ivecN_less_than_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a <= b */
static bvec4 ivec4_less_than_equal(ivec4 a, int b) {
    bvec4 res;
    ivecN_less_than_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a <= b */
static bvec4 ivec4_less_than_equal_vec(ivec4 a, ivec4 b) {
    bvec4 res;
    ivecN_less_than_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a > b */
static bvec4 ivec4_greater_than(ivec4 a, int b) {
    bvec4 res;
    ivecN_greater_than(res.v, a.v, b, 4);
    return res;
}


/** dst = a > b */
static bvec4 ivec4_greater_than_vec(ivec4 a, ivec4 b) {
    bvec4 res;
    ivecN_greater_than_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a >= b */
static bvec4 ivec4_greater_than_equal(ivec4 a, int b) {
    bvec4 res;
    ivecN_greater_than_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a >= b */
static bvec4 ivec4_greater_than_equal_vec(ivec4 a, ivec4 b) {
    bvec4 res;
    ivecN_greater_than_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a == b */
static bvec4 ivec4_equal(ivec4 a, int b) {
    bvec4 res;
    ivecN_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a == b */
static bvec4 ivec4_equal_vec(ivec4 a, ivec4 b) {
    bvec4 res;
    ivecN_equal_vec(res.v, a.v, b.v, 4);
    return res;
}


/** dst = a != b */
static bvec4 ivec4_not_equal(ivec4 a, int b) {
    bvec4 res;
    ivecN_not_equal(res.v, a.v, b, 4);
    return res;
}


/** dst = a != b */
static bvec4 ivec4_not_equal_vec(ivec4 a, ivec4 b) {
    bvec4 res;
    ivecN_not_equal_vec(res.v, a.v, b.v, 4);
    return res;
}

















#endif //M_VEC_IVEC4_H
