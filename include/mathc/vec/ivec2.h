#ifndef MATHC_VEC_IVEC2_H
#define MATHC_VEC_IVEC2_H

#include "ivecn.h"
#include "../types/int.h"
#include "../types/bool.h"


/** dst = unit_x */
static ivec2 ivec2_unit_x() {
    return (ivec2) {{1, 0}};
}

/** dst = unit_y */
static ivec2 ivec2_unit_y() {
    return (ivec2) {{0, 1}};
}

/** ivec_a == ivec_b */
static bool ivec2_cmp(ivec2 a, ivec2 b) {
    return ivecN_cmp(a.v, b.v, 2);
}


/** dst = scalar */
static ivec2 ivec2_set(int scalar) {
    ivec2 res;
    ivecN_set(res.v, scalar, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_float(const float *v) {
    ivec2 res;
    ivecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_double(const double *v) {
    ivec2 res;
    ivecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_unsigned(const unsigned *v) {
    ivec2 res;
    ivecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_char(const signed char *v) {
    ivec2 res;
    ivecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_uchar(const unsigned char *v) {
    ivec2 res;
    ivecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ivec2) v */
static ivec2 ivec2_cast_from_bool(const bool *v) {
    ivec2 res;
    ivecN_cast_into(res.v, v, 2);
    return res;
}


/** dst = -vec */
static ivec2 ivec2_neg(ivec2 vec) {
    ivec2 res;
    ivecN_neg(res.v, vec.v, 2);
    return res;
}
/** dst = -vec */
static ivec2 ivec2_neg_v(const int *vec) {
    return ivec2_neg(IVec2(vec));
}


/** dst = a + b */
static ivec2 ivec2_add_vec(ivec2 vec_a, ivec2 vec_b) {
    ivec2 res;
    ivecN_add_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a + b */
static ivec2 ivec2_add_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_add_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a + b */
static ivec2 ivec2_add(ivec2 vec_a, int scalar_b) {
    ivec2 res;
    ivecN_add(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a + b */
static ivec2 ivec2_add_v(const int *vec_a, int scalar_b) {
    return ivec2_add(IVec2(vec_a), scalar_b);
}


/** dst = a - b */
static ivec2 ivec2_sub_vec(ivec2 vec_a, ivec2 vec_b) {
    ivec2 res;
    ivecN_sub_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a - b */
static ivec2 ivec2_sub_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_sub_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a - b */
static ivec2 ivec2_sub(ivec2 vec_a, int scalar_b) {
    ivec2 res;
    ivecN_sub(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a - b */
static ivec2 ivec2_sub_v(const int *vec_a, int scalar_b) {
    return ivec2_sub(IVec2(vec_a), scalar_b);
}


/** dst = a * b */
static ivec2 ivec2_scale_vec(ivec2 vec_a, ivec2 vec_b) {
    ivec2 res;
    ivecN_scale_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a * b */
static ivec2 ivec2_scale_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_scale_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a * b */
static ivec2 ivec2_scale(ivec2 vec_a, int scalar_b) {
    ivec2 res;
    ivecN_scale(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a * b */
static ivec2 ivec2_scale_v(const int *vec_a, int scalar_b) {
    return ivec2_scale(IVec2(vec_a), scalar_b);
}


/** dst = a / b */
static ivec2 ivec2_div_vec(ivec2 vec_a, ivec2 vec_b) {
    ivec2 res;
    ivecN_div_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a / b */
static ivec2 ivec2_div_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_div_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a / b */
static ivec2 ivec2_div(ivec2 vec_a, int scalar_b) {
    ivec2 res;
    ivecN_div(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a / b */
static ivec2 ivec2_div_v(const int *vec_a, int scalar_b) {
    return ivec2_div(IVec2(vec_a), scalar_b);
}

/** dst = abs(x) */
static ivec2 ivec2_abs(ivec2 vec_x) {
    ivec2 res;
    ivecN_abs(res.v, vec_x.v, 2);
    return res;
}
/** dst = abs(x) */
static ivec2 ivec2_abs_v(const int *vec_x) {
    return ivec2_abs(IVec2(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec2 ivec2_sign(ivec2 vec_x) {
    ivec2 res;
    ivecN_sign(res.v, vec_x.v, 2);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec2 ivec2_sign_v(const int *vec_x) {
    return ivec2_sign(IVec2(vec_x));
}


/** dst = x % y */
static ivec2 ivec2_mod(ivec2 vec_x, int y) {
    ivec2 res;
    ivecN_mod(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = x % y */
static ivec2 ivec2_mod_v(const int *vec_x, int y) {
    return ivec2_mod(IVec2(vec_x), y);
}


/** dst = x % y */
static ivec2 ivec2_mod_vec(ivec2 vec_x, ivec2 vec_y) {
    ivec2 res;
    ivecN_mod_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = x % y */
static ivec2 ivec2_mod_vec_v(const int *vec_x, const int *vec_y) {
    return ivec2_mod_vec(IVec2(vec_x), IVec2(vec_y));
}


/** dst = a < b ? a : b */
static ivec2 ivec2_min(ivec2 vec_x, int y) {
    ivec2 res;
    ivecN_min(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a < b ? a : b */
static ivec2 ivec2_min_v(const int *vec_x, int y) {
    return ivec2_min(IVec2(vec_x), y);
}


/** dst = a < b ? a : b */
static ivec2 ivec2_min_vec(ivec2 vec_x, ivec2 vec_y) {
    ivec2 res;
    ivecN_min_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a < b ? a : b */
static ivec2 ivec2_min_vec_v(const int *vec_x, const int *vec_y) {
    return ivec2_min_vec(IVec2(vec_x), IVec2(vec_y));
}


/** dst = a > b ? a : b */
static ivec2 ivec2_max(ivec2 vec_x, int y) {
    ivec2 res;
    ivecN_max(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a > b ? a : b */
static ivec2 ivec2_max_v(const int *vec_x, int y) {
    return ivec2_max(IVec2(vec_x), y);
}


/** dst = a > b ? a : b */
static ivec2 ivec2_max_vec(ivec2 vec_x, ivec2 vec_y) {
    ivec2 res;
    ivecN_max_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a > b ? a : b */
static ivec2 ivec2_max_vec_v(const int *vec_x, const int *vec_y) {
    return ivec2_max_vec(IVec2(vec_x), IVec2(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec2 ivec2_clamp(ivec2 vec_x, int min, int max) {
    ivec2 res;
    ivecN_clamp(res.v, vec_x.v, min, max, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ivec2 ivec2_clamp_v(const int *vec_x, int min, int max) {
    return ivec2_clamp(IVec2(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec2 ivec2_clamp_vec(ivec2 vec_x, ivec2 vec_min, ivec2 vec_max) {
    ivec2 res;
    ivecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ivec2 ivec2_clamp_vec_v(const int *vec_x, const int *vec_min, const int *vec_max) {
    return ivec2_clamp_vec(IVec2(vec_x), IVec2(vec_min), IVec2(vec_max));
}

/** dst = a * (1-t) + b * t */
static ivec2 ivec2_mix(ivec2 vec_a, ivec2 vec_b, float t) {
    ivec2 res;
    ivecN_mix(res.v, vec_a.v, vec_b.v, t, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static ivec2 ivec2_mix_v(const int *vec_a, const int *vec_b, float t) {
    return ivec2_mix(IVec2(vec_a), IVec2(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static ivec2 ivec2_mix_vec(ivec2 vec_a, ivec2 vec_b, const float *vec_t) {
    ivec2 res;
    ivecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static ivec2 ivec2_mix_vec_v(const int *vec_a, const int *vec_b, const float *vec_t) {
    return ivec2_mix_vec(IVec2(vec_a), IVec2(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static ivec2 ivec2_step(ivec2 vec_x, int edge) {
    ivec2 res;
    ivecN_step(res.v, vec_x.v, edge, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ivec2 ivec2_step_v(const int *vec_x, int edge) {
    return ivec2_step(IVec2(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static ivec2 ivec2_step_vec(ivec2 vec_x, ivec2 vec_edge) {
    ivec2 res;
    ivecN_step_vec(res.v, vec_x.v, vec_edge.v, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ivec2 ivec2_step_vec_v(const int *vec_x, const int *vec_edge) {
    return ivec2_step_vec(IVec2(vec_x), IVec2(vec_edge));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int ivec2_sum(ivec2 vec) {
    return ivecN_sum(vec.v, 2);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int ivec2_sum_v(const int *vec) {
    return ivec2_sum(IVec2(vec));
}


/** returns a dot b */
static int ivec2_dot(ivec2 vec_a, ivec2 vec_b) {
    return ivecN_dot(vec_a.v, vec_b.v, 2);
}
/** returns a dot b */
static int ivec2_dot_v(const int *vec_a, const int *vec_b) {
    return ivec2_dot(IVec2(vec_a), IVec2(vec_b));
}


/** returns ||vec||_2 */
static float ivec2_norm(ivec2 vec) {
    return ivecN_norm(vec.v, 2);
}
/** returns ||vec||_2 */
static float ivec2_norm_v(const int *vec) {
    return ivec2_norm(IVec2(vec));
}


/** returns ||vec||_p */
static float ivec2_norm_p(ivec2 vec, float p) {
    return ivecN_norm_p(vec.v, p, 2);
}
/** returns ||vec||_p */
static float ivec2_norm_p_v(const int *vec, float p) {
    return ivec2_norm_p(IVec2(vec), p);
}


/** returns ||vec||_1 */
static int ivec2_norm_1(ivec2 vec) {
    return ivecN_norm_1(vec.v, 2);
}
/** returns ||vec||_1 */
static int ivec2_norm_1_v(const int *vec) {
    return ivec2_norm_1(IVec2(vec));
}


/** returns ||vec||_inf */
static int ivec2_norm_inf(ivec2 vec) {
    return ivecN_norm_inf(vec.v, 2);
}
/** returns ||vec||_inf */
static int ivec2_norm_inf_v(const int *vec) {
    return ivec2_norm_inf(IVec2(vec));
}


/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static float ivec2_length(ivec2 vec) {
    return ivecN_length(vec.v, 2);
}
/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static float ivec2_length_v(const int *vec) {
    return ivec2_length(IVec2(vec));
}


/** returns norm(b-a) */
static float ivec2_distance(ivec2 vec_a, ivec2 vec_b) {
    return ivecN_distance(vec_a.v, vec_b.v, 2);
}
/** returns norm(b-a) */
static float ivec2_distance_v(const int *vec_a, const int *vec_b) {
    return ivec2_distance(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a < b */
static bvec2 ivec2_less_than(ivec2 vec_a, int b) {
    bvec2 res;
    ivecN_less_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a < b */
static bvec2 ivec2_less_than_v(const int *vec_a, int b) {
    return ivec2_less_than(IVec2(vec_a), b);
}


/** dst = a < b */
static bvec2 ivec2_less_than_vec(ivec2 vec_a, ivec2 vec_b) {
    bvec2 res;
    ivecN_less_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a < b */
static bvec2 ivec2_less_than_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_less_than_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a <= b */
static bvec2 ivec2_less_than_equal(ivec2 vec_a, int b) {
    bvec2 res;
    ivecN_less_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a <= b */
static bvec2 ivec2_less_than_equal_v(const int *vec_a, int b) {
    return ivec2_less_than_equal(IVec2(vec_a), b);
}


/** dst = a <= b */
static bvec2 ivec2_less_than_equal_vec(ivec2 vec_a, ivec2 vec_b) {
    bvec2 res;
    ivecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a <= b */
static bvec2 ivec2_less_than_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_less_than_equal_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a > b */
static bvec2 ivec2_greater_than(ivec2 vec_a, int b) {
    bvec2 res;
    ivecN_greater_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a > b */
static bvec2 ivec2_greater_than_v(const int *vec_a, int b) {
    return ivec2_greater_than(IVec2(vec_a), b);
}


/** dst = a > b */
static bvec2 ivec2_greater_than_vec(ivec2 vec_a, ivec2 vec_b) {
    bvec2 res;
    ivecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a > b */
static bvec2 ivec2_greater_than_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_greater_than_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a >= b */
static bvec2 ivec2_greater_than_equal(ivec2 vec_a, int b) {
    bvec2 res;
    ivecN_greater_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a >= b */
static bvec2 ivec2_greater_than_equal_v(const int *vec_a, int b) {
    return ivec2_greater_than_equal(IVec2(vec_a), b);
}


/** dst = a >= b */
static bvec2 ivec2_greater_than_equal_vec(ivec2 vec_a, ivec2 vec_b) {
    bvec2 res;
    ivecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a >= b */
static bvec2 ivec2_greater_than_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_greater_than_equal_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a == b */
static bvec2 ivec2_equal(ivec2 vec_a, int b) {
    bvec2 res;
    ivecN_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a == b */
static bvec2 ivec2_equal_v(const int *vec_a, int b) {
    return ivec2_equal(IVec2(vec_a), b);
}


/** dst = a == b */
static bvec2 ivec2_equal_vec(ivec2 vec_a, ivec2 vec_b) {
    bvec2 res;
    ivecN_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a == b */
static bvec2 ivec2_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_equal_vec(IVec2(vec_a), IVec2(vec_b));
}


/** dst = a != b */
static bvec2 ivec2_not_equal(ivec2 vec_a, int b) {
    bvec2 res;
    ivecN_not_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a != b */
static bvec2 ivec2_not_equal_v(const int *vec_a, int b) {
    return ivec2_not_equal(IVec2(vec_a), b);
}


/** dst = a != b */
static bvec2 ivec2_not_equal_vec(ivec2 vec_a, ivec2 vec_b) {
    bvec2 res;
    ivecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a != b */
static bvec2 ivec2_not_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec2_not_equal_vec(IVec2(vec_a), IVec2(vec_b));
}

#endif //MATHC_VEC_IVEC2_H
