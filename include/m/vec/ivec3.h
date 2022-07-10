#ifndef M_VEC_IVEC3_H
#define M_VEC_IVEC3_H


#include "ivecn.h"
#include "../types/ivec3.h"
#include "../types/bvec3.h"


/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_float(const float *cast) {
    ivec3 res;
    ivecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_double(const double *cast) {
    ivec3 res;
    ivecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_int(const int *cast) {
    ivec3 res;
    ivecN_cast_into(res.v, cast, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_uchar(const unsigned char *cast) {
    ivec3 res;
    ivecN_cast_into(res.v, cast, 3);
    return res;
}


/** dst = vec * 255 */
static ivec3 ivec3_cast_from_float_1(const float *cast) {
    ivec3 res;
    ivecN_cast_from_float_1(res.v, cast, 3);
    return res;
}

/** dst = vec * 255 */
static ivec3 ivec3_cast_from_double_1(const double *cast) {
    ivec3 res;
    ivecN_cast_from_double_1(res.v, cast, 3);
    return res;
}

/** dst = vec * 255 */
static ivec3 ivec3_cast_from_longdouble_1(const long double *cast) {
    ivec3 res;
    ivecN_cast_from_longdouble_1(res.v, cast, 3);
    return res;
}

/** a == b */
static bool ivec3_cmp(ivec3 a, ivec3 b) {
    return ivecN_cmp(a.v, b.v, 3);
}


/** dst = s */
static ivec3 ivec3_set(int s) {
    ivec3 res;
    ivecN_set(res.v, s, 3);
    return res;
}


/** dst = v0, v1, ... */
static ivec3 ivec3_new(int v0, int v1, int v2
) {
    return (ivec3) {v0, v1, v2
    };
}

/** dst = unit_x */
static ivec3 ivec3_unit_x() {
    ivec3 res;
    ivecN_unit_x(res.v, 3);
    return res;
}


/** dst = unit_y */
static ivec3 ivec3_unit_y() {
    ivec3 res;
    ivecN_unit_y(res.v, 3);
    return res;
}


/** dst = unit_z */
static ivec3 ivec3_unit_z() {
    ivec3 res;
    ivecN_unit_z(res.v, 3);
    return res;
}


/** dst = -v */
static ivec3 ivec3_neg(ivec3 v) {
    ivec3 res;
    ivecN_neg(res.v, v.v, 3);
    return res;
}


/** dst = a + b */
static ivec3 ivec3_add_vec(ivec3 a, ivec3 b) {
    ivec3 res;
    ivecN_add_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a + b */
static ivec3 ivec3_add(ivec3 a, int b) {
    ivec3 res;
    ivecN_add(res.v, a.v, b, 3);
    return res;
}


/** dst = a - b */
static ivec3 ivec3_sub_vec(ivec3 a, ivec3 b) {
    ivec3 res;
    ivecN_sub_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a - b */
static ivec3 ivec3_sub(ivec3 a, int b) {
    ivec3 res;
    ivecN_sub(res.v, a.v, b, 3);
    return res;
}


/** dst = a * b */
static ivec3 ivec3_scale_vec(ivec3 a, ivec3 b) {
    ivec3 res;
    ivecN_scale_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a * b */
static ivec3 ivec3_scale(ivec3 a, int b) {
    ivec3 res;
    ivecN_scale(res.v, a.v, b, 3);
    return res;
}


/** dst = a / b */
static ivec3 ivec3_div_vec(ivec3 a, ivec3 b) {
    ivec3 res;
    ivecN_div_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a / b */
static ivec3 ivec3_div(ivec3 a, int b) {
    ivec3 res;
    ivecN_div(res.v, a.v, b, 3);
    return res;
}


/** dst = pow(x, y) */
static ivec3 ivec3_pow(ivec3 x, int y) {
    ivec3 res;
    ivecN_pow(res.v, x.v, y, 3);
    return res;
}


/** dst = pow(x, y) */
static ivec3 ivec3_pow_vec(ivec3 x, ivec3 y) {
    ivec3 res;
    ivecN_pow_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = exp(x) */
static ivec3 ivec3_exp(ivec3 x) {
    ivec3 res;
    ivecN_exp(res.v, x.v, 3);
    return res;
}


/** dst = log(x) */
static ivec3 ivec3_log(ivec3 x) {
    ivec3 res;
    ivecN_log(res.v, x.v, 3);
    return res;
}


/** dst = exp2(x) */
static ivec3 ivec3_exp2(ivec3 x) {
    ivec3 res;
    ivecN_exp2(res.v, x.v, 3);
    return res;
}


/** dst = log2(x) */
static ivec3 ivec3_log2(ivec3 x) {
    ivec3 res;
    ivecN_log2(res.v, x.v, 3);
    return res;
}


/** dst = sqrt(x) */
static ivec3 ivec3_sqrt(ivec3 x) {
    ivec3 res;
    ivecN_sqrt(res.v, x.v, 3);
    return res;
}


/** dst = abs(x) */
static ivec3 ivec3_abs(ivec3 x) {
    ivec3 res;
    ivecN_abs(res.v, x.v, 3);
    return res;
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec3 ivec3_sign(ivec3 x) {
    ivec3 res;
    ivecN_sign(res.v, x.v, 3);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ivec3 ivec3_mod(ivec3 x, int y) {
    ivec3 res;
    ivecN_mod(res.v, x.v, y, 3);
    return res;
}


/** dst = (x % y + y) % y (always positive, if y>0) **/
static ivec3 ivec3_mod_vec(ivec3 x, ivec3 y) {
    ivec3 res;
    ivecN_mod_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = a < b ? a : b */
static ivec3 ivec3_min(ivec3 x, int y) {
    ivec3 res;
    ivecN_min(res.v, x.v, y, 3);
    return res;
}


/** dst = a < b ? a : b */
static ivec3 ivec3_min_vec(ivec3 x, ivec3 y) {
    ivec3 res;
    ivecN_min_vec(res.v, x.v, y.v, 3);
    return res;
}


/** dst = a > b ? a : b */
static ivec3 ivec3_max(ivec3 x, int y) {
    ivec3 res;
    ivecN_max(res.v, x.v, y, 3);
    return res;
}


/** dst = a > b ? a : b */
static ivec3 ivec3_max_vec(ivec3 x, ivec3 y) {
    ivec3 res;
    ivecN_max_vec(res.v, x.v, y.v, 3);
    return res;
}


/** returns the index of the min v value */
static int ivec3_min_index(ivec3 vec) {
    return ivecN_min_index(vec.v, 3);
}


/** returns the index of the max v value */
static int ivec3_max_index(ivec3 vec) {
    return ivecN_max_index(vec.v, 3);
}

/** dst = x < min ? min : (x > max ? max : x) */
static ivec3 ivec3_clamp(ivec3 x, int min, int max) {
    ivec3 res;
    ivecN_clamp(res.v, x.v, min, max, 3);
    return res;
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec3 ivec3_clamp_vec(ivec3 x, ivec3 min, ivec3 max) {
    ivec3 res;
    ivecN_clamp_vec(res.v, x.v, min.v, max.v, 3);
    return res;
}


/** dst = a * (1-t) + b * t */
static ivec3 ivec3_mix(ivec3 a, ivec3 b, float t) {
    ivec3 res;
    ivecN_mix(res.v, a.v, b.v, t, 3);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ivec3 ivec3_step(ivec3 x, int edge) {
    ivec3 res;
    ivecN_step(res.v, x.v, edge, 3);
    return res;
}


/** dst = x < edge ? 0 : 1 */
static ivec3 ivec3_step_vec(ivec3 x, ivec3 edge) {
    ivec3 res;
    ivecN_step_vec(res.v, x.v, edge.v, 3);
    return res;
}


/** returns v[0] + v[1] + ... + v[n-1] */
static int ivec3_sum(ivec3 v) {
    return ivecN_sum(v.v, 3);
}


/** returns a dot b */
static int ivec3_dot(ivec3 a, ivec3 b) {
    return ivecN_dot(a.v, b.v, 3);
}


/** dst = a x b , dst.w... = 0 */
static ivec3 ivec3_cross(ivec3 a, ivec3 b) {
    ivec3 res;
    ivecN_cross(res.v, a.v, b.v, 3);
    return res;
}


/** returns ||v||_3 */
static int ivec3_norm(ivec3 v) {
    return ivecN_norm(v.v, 3);
}


/** returns ||v||_p */
static int ivec3_norm_p(ivec3 v, int p) {
    return ivecN_norm_p(v.v, p, 3);
}


/** returns ||v||_1 */
static int ivec3_norm_1(ivec3 v) {
    return ivecN_norm_1(v.v, 3);
}


/** returns ||v||_inf */
static int ivec3_norm_inf(ivec3 v) {
    return ivecN_norm_inf(v.v, 3);
}


/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static int ivec3_length(ivec3 v) {
    return ivecN_length(v.v, 3);
}


/** returns norm(b-a) */
static int ivec3_distance(ivec3 a, ivec3 b) {
    return ivecN_distance(a.v, b.v, 3);
}


/** returns dot(b-a) */
static int ivec3_sqr_distance(ivec3 a, ivec3 b) {
    return ivecN_sqr_distance(a.v, b.v, 3);
}


/** dst = a < b */
static bvec3 ivec3_less_than(ivec3 a, int b) {
    bvec3 res;
    ivecN_less_than(res.v, a.v, b, 3);
    return res;
}


/** dst = a < b */
static bvec3 ivec3_less_than_vec(ivec3 a, ivec3 b) {
    bvec3 res;
    ivecN_less_than_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a <= b */
static bvec3 ivec3_less_than_equal(ivec3 a, int b) {
    bvec3 res;
    ivecN_less_than_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a <= b */
static bvec3 ivec3_less_than_equal_vec(ivec3 a, ivec3 b) {
    bvec3 res;
    ivecN_less_than_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a > b */
static bvec3 ivec3_greater_than(ivec3 a, int b) {
    bvec3 res;
    ivecN_greater_than(res.v, a.v, b, 3);
    return res;
}


/** dst = a > b */
static bvec3 ivec3_greater_than_vec(ivec3 a, ivec3 b) {
    bvec3 res;
    ivecN_greater_than_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a >= b */
static bvec3 ivec3_greater_than_equal(ivec3 a, int b) {
    bvec3 res;
    ivecN_greater_than_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a >= b */
static bvec3 ivec3_greater_than_equal_vec(ivec3 a, ivec3 b) {
    bvec3 res;
    ivecN_greater_than_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a == b */
static bvec3 ivec3_equal(ivec3 a, int b) {
    bvec3 res;
    ivecN_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a == b */
static bvec3 ivec3_equal_vec(ivec3 a, ivec3 b) {
    bvec3 res;
    ivecN_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


/** dst = a != b */
static bvec3 ivec3_not_equal(ivec3 a, int b) {
    bvec3 res;
    ivecN_not_equal(res.v, a.v, b, 3);
    return res;
}


/** dst = a != b */
static bvec3 ivec3_not_equal_vec(ivec3 a, ivec3 b) {
    bvec3 res;
    ivecN_not_equal_vec(res.v, a.v, b.v, 3);
    return res;
}


#endif //M_VEC_IVEC3_H
