#ifndef MATHC_VEC_IVEC4_H
#define MATHC_VEC_IVEC4_H

#include "ivecn.h"
#include "../types/int.h"
#include "../types/bool.h"


/** dst = unit_x */
static ivec4 ivec4_unit_x() {
    return (ivec4) {{1, 0, 0, 0}};
}

/** dst = unit_y */
static ivec4 ivec4_unit_y() {
    return (ivec4) {{0, 1, 0, 0}};
}

/** dst = unit_z */
static ivec4 ivec4_unit_z() {
    return (ivec4) {{0, 0, 1, 0}};
}

/** dst = unit_w */
static ivec4 ivec4_unit_w() {
    return (ivec4) {{0, 0, 0, 1}};
}

/** ivec_a == ivec_b */
static bool ivec4_cmp(ivec4 a, ivec4 b) {
    return ivecN_cmp(a.v, b.v, 4);
}


/** dst = scalar */
static ivec4 ivec4_set(int scalar) {
    ivec4 res;
    ivecN_set(res.v, scalar, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_float(const float *v) {
    ivec4 res;
    ivecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_double(const double *v) {
    ivec4 res;
    ivecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_unsigned(const unsigned *v) {
    ivec4 res;
    ivecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_char(const char *v) {
    ivec4 res;
    ivecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_uchar(const unsigned char *v) {
    ivec4 res;
    ivecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ivec4) v */
static ivec4 ivec4_cast_from_bool(const bool *v) {
    ivec4 res;
    ivecN_cast_into(res.v, v, 4);
    return res;
}



/** dst = -vec */
static ivec4 ivec4_neg(ivec4 vec) {
    ivec4 res;
    ivecN_neg(res.v, vec.v, 4);
    return res;
}
/** dst = -vec */
static ivec4 ivec4_neg_v(const int *vec) {
    return ivec4_neg(IVec4(vec));
}


/** dst = a + b */
static ivec4 ivec4_add_vec(ivec4 vec_a, ivec4 vec_b) {
    ivec4 res;
    ivecN_add_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a + b */
static ivec4 ivec4_add_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_add_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a + b */
static ivec4 ivec4_add(ivec4 vec_a, int scalar_b) {
    ivec4 res;
    ivecN_add(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a + b */
static ivec4 ivec4_add_v(const int *vec_a, int scalar_b) {
    return ivec4_add(IVec4(vec_a), scalar_b);
}


/** dst = a - b */
static ivec4 ivec4_sub_vec(ivec4 vec_a, ivec4 vec_b) {
    ivec4 res;
    ivecN_sub_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a - b */
static ivec4 ivec4_sub_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_sub_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a - b */
static ivec4 ivec4_sub(ivec4 vec_a, int scalar_b) {
    ivec4 res;
    ivecN_sub(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a - b */
static ivec4 ivec4_sub_v(const int *vec_a, int scalar_b) {
    return ivec4_sub(IVec4(vec_a), scalar_b);
}


/** dst = a * b */
static ivec4 ivec4_scale_vec(ivec4 vec_a, ivec4 vec_b) {
    ivec4 res;
    ivecN_scale_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a * b */
static ivec4 ivec4_scale_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_scale_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a * b */
static ivec4 ivec4_scale(ivec4 vec_a, int scalar_b) {
    ivec4 res;
    ivecN_scale(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a * b */
static ivec4 ivec4_scale_v(const int *vec_a, int scalar_b) {
    return ivec4_scale(IVec4(vec_a), scalar_b);
}


/** dst = a / b */
static ivec4 ivec4_div_vec(ivec4 vec_a, ivec4 vec_b) {
    ivec4 res;
    ivecN_div_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a / b */
static ivec4 ivec4_div_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_div_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a / b */
static ivec4 ivec4_div(ivec4 vec_a, int scalar_b) {
    ivec4 res;
    ivecN_div(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a / b */
static ivec4 ivec4_div_v(const int *vec_a, int scalar_b) {
    return ivec4_div(IVec4(vec_a), scalar_b);
}


/** dst = abs(x) */
static ivec4 ivec4_abs(ivec4 vec_x) {
    ivec4 res;
    ivecN_abs(res.v, vec_x.v, 4);
    return res;
}
/** dst = abs(x) */
static ivec4 ivec4_abs_v(const int *vec_x) {
    return ivec4_abs(IVec4(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec4 ivec4_sign(ivec4 vec_x) {
    ivec4 res;
    ivecN_sign(res.v, vec_x.v, 4);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec4 ivec4_sign_v(const int *vec_x) {
    return ivec4_sign(IVec4(vec_x));
}


/** dst = x % y */
static ivec4 ivec4_mod(ivec4 vec_x, int y) {
    ivec4 res;
    ivecN_mod(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = x % y */
static ivec4 ivec4_mod_v(const int *vec_x, int y) {
    return ivec4_mod(IVec4(vec_x), y);
}


/** dst = x % y */
static ivec4 ivec4_mod_vec(ivec4 vec_x, ivec4 vec_y) {
    ivec4 res;
    ivecN_mod_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = x % y */
static ivec4 ivec4_mod_vec_v(const int *vec_x, const int *vec_y) {
    return ivec4_mod_vec(IVec4(vec_x), IVec4(vec_y));
}


/** dst = a < b ? a : b */
static ivec4 ivec4_min(ivec4 vec_x, int y) {
    ivec4 res;
    ivecN_min(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a < b ? a : b */
static ivec4 ivec4_min_v(const int *vec_x, int y) {
    return ivec4_min(IVec4(vec_x), y);
}


/** dst = a < b ? a : b */
static ivec4 ivec4_min_vec(ivec4 vec_x, ivec4 vec_y) {
    ivec4 res;
    ivecN_min_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a < b ? a : b */
static ivec4 ivec4_min_vec_v(const int *vec_x, const int *vec_y) {
    return ivec4_min_vec(IVec4(vec_x), IVec4(vec_y));
}


/** dst = a > b ? a : b */
static ivec4 ivec4_max(ivec4 vec_x, int y) {
    ivec4 res;
    ivecN_max(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a > b ? a : b */
static ivec4 ivec4_max_v(const int *vec_x, int y) {
    return ivec4_max(IVec4(vec_x), y);
}


/** dst = a > b ? a : b */
static ivec4 ivec4_max_vec(ivec4 vec_x, ivec4 vec_y) {
    ivec4 res;
    ivecN_max_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a > b ? a : b */
static ivec4 ivec4_max_vec_v(const int *vec_x, const int *vec_y) {
    return ivec4_max_vec(IVec4(vec_x), IVec4(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec4 ivec4_clamp(ivec4 vec_x, int min, int max) {
    ivec4 res;
    ivecN_clamp(res.v, vec_x.v, min, max, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ivec4 ivec4_clamp_v(const int *vec_x, int min, int max) {
    return ivec4_clamp(IVec4(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec4 ivec4_clamp_vec(ivec4 vec_x, ivec4 vec_min, ivec4 vec_max) {
    ivec4 res;
    ivecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ivec4 ivec4_clamp_vec_v(const int *vec_x, const int *vec_min, const int *vec_max) {
    return ivec4_clamp_vec(IVec4(vec_x), IVec4(vec_min), IVec4(vec_max));
}

/** dst = a * (1-t) + b * t */
static ivec4 ivec4_mix(ivec4 vec_a, ivec4 vec_b, float t) {
    ivec4 res;
    ivecN_mix(res.v, vec_a.v, vec_b.v, t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static ivec4 ivec4_mix_v(const int *vec_a, const int *vec_b, float t) {
    return ivec4_mix(IVec4(vec_a), IVec4(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static ivec4 ivec4_mix_vec(ivec4 vec_a, ivec4 vec_b, const float *vec_t) {
    ivec4 res;
    ivecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static ivec4 ivec4_mix_vec_v(const int *vec_a, const int *vec_b, const float *vec_t) {
    return ivec4_mix_vec(IVec4(vec_a), IVec4(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static ivec4 ivec4_step(ivec4 vec_x, int edge) {
    ivec4 res;
    ivecN_step(res.v, vec_x.v, edge, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ivec4 ivec4_step_v(const int *vec_x, int edge) {
    return ivec4_step(IVec4(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static ivec4 ivec4_step_vec(ivec4 vec_x, ivec4 vec_edge) {
    ivec4 res;
    ivecN_step_vec(res.v, vec_x.v, vec_edge.v, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ivec4 ivec4_step_vec_v(const int *vec_x, const int *vec_edge) {
    return ivec4_step_vec(IVec4(vec_x), IVec4(vec_edge));
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int ivec4_sum(ivec4 vec) {
    return ivecN_sum(vec.v, 4);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int ivec4_sum_v(const int *vec) {
    return ivec4_sum(IVec4(vec));
}


/** returns a dot b */
static int ivec4_dot(ivec4 vec_a, ivec4 vec_b) {
    return ivecN_dot(vec_a.v, vec_b.v, 4);
}
/** returns a dot b */
static int ivec4_dot_v(const int *vec_a, const int *vec_b) {
    return ivec4_dot(IVec4(vec_a), IVec4(vec_b));
}


/** returns ||vec||_4 */
static float ivec4_norm(ivec4 vec) {
    return ivecN_norm(vec.v, 4);
}
/** returns ||vec||_4 */
static float ivec4_norm_v(const int *vec) {
    return ivec4_norm(IVec4(vec));
}


/** returns ||vec||_p */
static float ivec4_norm_p(ivec4 vec, float p) {
    return ivecN_norm_p(vec.v, p, 4);
}
/** returns ||vec||_p */
static float ivec4_norm_p_v(const int *vec, float p) {
    return ivec4_norm_p(IVec4(vec), p);
}


/** returns ||vec||_1 */
static int ivec4_norm_1(ivec4 vec) {
    return ivecN_norm_1(vec.v, 4);
}
/** returns ||vec||_1 */
static int ivec4_norm_1_v(const int *vec) {
    return ivec4_norm_1(IVec4(vec));
}


/** returns ||vec||_inf */
static int ivec4_norm_inf(ivec4 vec) {
    return ivecN_norm_inf(vec.v, 4);
}
/** returns ||vec||_inf */
static int ivec4_norm_inf_v(const int *vec) {
    return ivec4_norm_inf(IVec4(vec));
}


/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static float ivec4_length(ivec4 vec) {
    return ivecN_length(vec.v, 4);
}
/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static float ivec4_length_v(const int *vec) {
    return ivec4_length(IVec4(vec));
}


/** returns norm(b-a) */
static float ivec4_distance(ivec4 vec_a, ivec4 vec_b) {
    return ivecN_distance(vec_a.v, vec_b.v, 4);
}
/** returns norm(b-a) */
static float ivec4_distance_v(const int *vec_a, const int *vec_b) {
    return ivec4_distance(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a < b */
static bvec4 ivec4_less_than(ivec4 vec_a, int b) {
    bvec4 res;
    ivecN_less_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a < b */
static bvec4 ivec4_less_than_v(const int *vec_a, int b) {
    return ivec4_less_than(IVec4(vec_a), b);
}


/** dst = a < b */
static bvec4 ivec4_less_than_vec(ivec4 vec_a, ivec4 vec_b) {
    bvec4 res;
    ivecN_less_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a < b */
static bvec4 ivec4_less_than_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_less_than_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a <= b */
static bvec4 ivec4_less_than_equal(ivec4 vec_a, int b) {
    bvec4 res;
    ivecN_less_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a <= b */
static bvec4 ivec4_less_than_equal_v(const int *vec_a, int b) {
    return ivec4_less_than_equal(IVec4(vec_a), b);
}


/** dst = a <= b */
static bvec4 ivec4_less_than_equal_vec(ivec4 vec_a, ivec4 vec_b) {
    bvec4 res;
    ivecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a <= b */
static bvec4 ivec4_less_than_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_less_than_equal_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a > b */
static bvec4 ivec4_greater_than(ivec4 vec_a, int b) {
    bvec4 res;
    ivecN_greater_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a > b */
static bvec4 ivec4_greater_than_v(const int *vec_a, int b) {
    return ivec4_greater_than(IVec4(vec_a), b);
}


/** dst = a > b */
static bvec4 ivec4_greater_than_vec(ivec4 vec_a, ivec4 vec_b) {
    bvec4 res;
    ivecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a > b */
static bvec4 ivec4_greater_than_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_greater_than_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a >= b */
static bvec4 ivec4_greater_than_equal(ivec4 vec_a, int b) {
    bvec4 res;
    ivecN_greater_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a >= b */
static bvec4 ivec4_greater_than_equal_v(const int *vec_a, int b) {
    return ivec4_greater_than_equal(IVec4(vec_a), b);
}


/** dst = a >= b */
static bvec4 ivec4_greater_than_equal_vec(ivec4 vec_a, ivec4 vec_b) {
    bvec4 res;
    ivecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a >= b */
static bvec4 ivec4_greater_than_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_greater_than_equal_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a == b */
static bvec4 ivec4_equal(ivec4 vec_a, int b) {
    bvec4 res;
    ivecN_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a == b */
static bvec4 ivec4_equal_v(const int *vec_a, int b) {
    return ivec4_equal(IVec4(vec_a), b);
}


/** dst = a == b */
static bvec4 ivec4_equal_vec(ivec4 vec_a, ivec4 vec_b) {
    bvec4 res;
    ivecN_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a == b */
static bvec4 ivec4_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_equal_vec(IVec4(vec_a), IVec4(vec_b));
}


/** dst = a != b */
static bvec4 ivec4_not_equal(ivec4 vec_a, int b) {
    bvec4 res;
    ivecN_not_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a != b */
static bvec4 ivec4_not_equal_v(const int *vec_a, int b) {
    return ivec4_not_equal(IVec4(vec_a), b);
}


/** dst = a != b */
static bvec4 ivec4_not_equal_vec(ivec4 vec_a, ivec4 vec_b) {
    bvec4 res;
    ivecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a != b */
static bvec4 ivec4_not_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec4_not_equal_vec(IVec4(vec_a), IVec4(vec_b));
}



//
// in addition to vec2:
//


/** dst = a x b , dst.w = 0 */
static ivec4 ivec4_cross(ivec4 vec_a, ivec4 vec_b) {
    ivec4 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    res.w = 0;
    return res;
}
/** dst = a x b , dst.w = 0 */
static ivec4 ivec4_cross_v(const int *vec_a, const int *vec_b) {
    return ivec4_cross(IVec4(vec_a), IVec4(vec_b));
}


#endif //MATHC_VEC_IVEC4_H
