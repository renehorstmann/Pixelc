#ifndef MATHC_VEC_IVEC3_H
#define MATHC_VEC_IVEC3_H

#include "ivecn.h"
#include "../types/int.h"
#include "../types/bool.h"


/** dst = unit_x */
static ivec3 ivec3_unit_x() {
    return (ivec3) {{1, 0, 0}};
}

/** dst = unit_y */
static ivec3 ivec3_unit_y() {
    return (ivec3) {{0, 1, 0}};
}

/** dst = unit_z */
static ivec3 ivec3_unit_z() {
    return (ivec3) {{0, 0, 1}};
}

/** ivec_a == ivec_b */
static bool ivec3_cmp(ivec3 a, ivec3 b) {
    return ivecN_cmp(a.v, b.v, 3);
}


/** dst = scalar */
static ivec3 ivec3_set(int scalar) {
    ivec3 res;
    ivecN_set(res.v, scalar, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_float(const float *v) {
    ivec3 res;
    ivecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_double(const double *v) {
    ivec3 res;
    ivecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_unsigned(const unsigned *v) {
    ivec3 res;
    ivecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_char(const signed char *v) {
    ivec3 res;
    ivecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_uchar(const unsigned char *v) {
    ivec3 res;
    ivecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ivec3) v */
static ivec3 ivec3_cast_from_bool(const bool *v) {
    ivec3 res;
    ivecN_cast_into(res.v, v, 3);
    return res;
}


/** dst = -vec */
static ivec3 ivec3_neg(ivec3 vec) {
    ivec3 res;
    ivecN_neg(res.v, vec.v, 3);
    return res;
}
/** dst = -vec */
static ivec3 ivec3_neg_v(const int *vec) {
    return ivec3_neg(IVec3(vec));
}


/** dst = a + b */
static ivec3 ivec3_add_vec(ivec3 vec_a, ivec3 vec_b) {
    ivec3 res;
    ivecN_add_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a + b */
static ivec3 ivec3_add_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_add_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a + b */
static ivec3 ivec3_add(ivec3 vec_a, int scalar_b) {
    ivec3 res;
    ivecN_add(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a + b */
static ivec3 ivec3_add_v(const int *vec_a, int scalar_b) {
    return ivec3_add(IVec3(vec_a), scalar_b);
}


/** dst = a - b */
static ivec3 ivec3_sub_vec(ivec3 vec_a, ivec3 vec_b) {
    ivec3 res;
    ivecN_sub_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a - b */
static ivec3 ivec3_sub_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_sub_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a - b */
static ivec3 ivec3_sub(ivec3 vec_a, int scalar_b) {
    ivec3 res;
    ivecN_sub(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a - b */
static ivec3 ivec3_sub_v(const int *vec_a, int scalar_b) {
    return ivec3_sub(IVec3(vec_a), scalar_b);
}


/** dst = a * b */
static ivec3 ivec3_scale_vec(ivec3 vec_a, ivec3 vec_b) {
    ivec3 res;
    ivecN_scale_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a * b */
static ivec3 ivec3_scale_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_scale_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a * b */
static ivec3 ivec3_scale(ivec3 vec_a, int scalar_b) {
    ivec3 res;
    ivecN_scale(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a * b */
static ivec3 ivec3_scale_v(const int *vec_a, int scalar_b) {
    return ivec3_scale(IVec3(vec_a), scalar_b);
}


/** dst = a / b */
static ivec3 ivec3_div_vec(ivec3 vec_a, ivec3 vec_b) {
    ivec3 res;
    ivecN_div_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a / b */
static ivec3 ivec3_div_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_div_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a / b */
static ivec3 ivec3_div(ivec3 vec_a, int scalar_b) {
    ivec3 res;
    ivecN_div(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a / b */
static ivec3 ivec3_div_v(const int *vec_a, int scalar_b) {
    return ivec3_div(IVec3(vec_a), scalar_b);
}


/** dst = abs(x) */
static ivec3 ivec3_abs(ivec3 vec_x) {
    ivec3 res;
    ivecN_abs(res.v, vec_x.v, 3);
    return res;
}
/** dst = abs(x) */
static ivec3 ivec3_abs_v(const int *vec_x) {
    return ivec3_abs(IVec3(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec3 ivec3_sign(ivec3 vec_x) {
    ivec3 res;
    ivecN_sign(res.v, vec_x.v, 3);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static ivec3 ivec3_sign_v(const int *vec_x) {
    return ivec3_sign(IVec3(vec_x));
}


/** dst = x % y */
static ivec3 ivec3_mod(ivec3 vec_x, int y) {
    ivec3 res;
    ivecN_mod(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = x % y */
static ivec3 ivec3_mod_v(const int *vec_x, int y) {
    return ivec3_mod(IVec3(vec_x), y);
}


/** dst = x % y */
static ivec3 ivec3_mod_vec(ivec3 vec_x, ivec3 vec_y) {
    ivec3 res;
    ivecN_mod_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = x % y */
static ivec3 ivec3_mod_vec_v(const int *vec_x, const int *vec_y) {
    return ivec3_mod_vec(IVec3(vec_x), IVec3(vec_y));
}


/** dst = a < b ? a : b */
static ivec3 ivec3_min(ivec3 vec_x, int y) {
    ivec3 res;
    ivecN_min(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a < b ? a : b */
static ivec3 ivec3_min_v(const int *vec_x, int y) {
    return ivec3_min(IVec3(vec_x), y);
}


/** dst = a < b ? a : b */
static ivec3 ivec3_min_vec(ivec3 vec_x, ivec3 vec_y) {
    ivec3 res;
    ivecN_min_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a < b ? a : b */
static ivec3 ivec3_min_vec_v(const int *vec_x, const int *vec_y) {
    return ivec3_min_vec(IVec3(vec_x), IVec3(vec_y));
}


/** dst = a > b ? a : b */
static ivec3 ivec3_max(ivec3 vec_x, int y) {
    ivec3 res;
    ivecN_max(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a > b ? a : b */
static ivec3 ivec3_max_v(const int *vec_x, int y) {
    return ivec3_max(IVec3(vec_x), y);
}


/** dst = a > b ? a : b */
static ivec3 ivec3_max_vec(ivec3 vec_x, ivec3 vec_y) {
    ivec3 res;
    ivecN_max_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a > b ? a : b */
static ivec3 ivec3_max_vec_v(const int *vec_x, const int *vec_y) {
    return ivec3_max_vec(IVec3(vec_x), IVec3(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec3 ivec3_clamp(ivec3 vec_x, int min, int max) {
    ivec3 res;
    ivecN_clamp(res.v, vec_x.v, min, max, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ivec3 ivec3_clamp_v(const int *vec_x, int min, int max) {
    return ivec3_clamp(IVec3(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static ivec3 ivec3_clamp_vec(ivec3 vec_x, ivec3 vec_min, ivec3 vec_max) {
    ivec3 res;
    ivecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ivec3 ivec3_clamp_vec_v(const int *vec_x, const int *vec_min, const int *vec_max) {
    return ivec3_clamp_vec(IVec3(vec_x), IVec3(vec_min), IVec3(vec_max));
}

/** dst = a * (1-t) + b * t */
static ivec3 ivec3_mix(ivec3 vec_a, ivec3 vec_b, float t) {
    ivec3 res;
    ivecN_mix(res.v, vec_a.v, vec_b.v, t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static ivec3 ivec3_mix_v(const int *vec_a, const int *vec_b, float t) {
    return ivec3_mix(IVec3(vec_a), IVec3(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static ivec3 ivec3_mix_vec(ivec3 vec_a, ivec3 vec_b, const float *vec_t) {
    ivec3 res;
    ivecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static ivec3 ivec3_mix_vec_v(const int *vec_a, const int *vec_b, const float *vec_t) {
    return ivec3_mix_vec(IVec3(vec_a), IVec3(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static ivec3 ivec3_step(ivec3 vec_x, int edge) {
    ivec3 res;
    ivecN_step(res.v, vec_x.v, edge, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ivec3 ivec3_step_v(const int *vec_x, int edge) {
    return ivec3_step(IVec3(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static ivec3 ivec3_step_vec(ivec3 vec_x, ivec3 vec_edge) {
    ivec3 res;
    ivecN_step_vec(res.v, vec_x.v, vec_edge.v, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ivec3 ivec3_step_vec_v(const int *vec_x, const int *vec_edge) {
    return ivec3_step_vec(IVec3(vec_x), IVec3(vec_edge));
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int ivec3_sum(ivec3 vec) {
    return ivecN_sum(vec.v, 3);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int ivec3_sum_v(const int *vec) {
    return ivec3_sum(IVec3(vec));
}


/** returns a dot b */
static int ivec3_dot(ivec3 vec_a, ivec3 vec_b) {
    return ivecN_dot(vec_a.v, vec_b.v, 3);
}
/** returns a dot b */
static int ivec3_dot_v(const int *vec_a, const int *vec_b) {
    return ivec3_dot(IVec3(vec_a), IVec3(vec_b));
}


/** returns ||vec||_3 */
static float ivec3_norm(ivec3 vec) {
    return ivecN_norm(vec.v, 3);
}
/** returns ||vec||_3 */
static float ivec3_norm_v(const int *vec) {
    return ivec3_norm(IVec3(vec));
}


/** returns ||vec||_p */
static float ivec3_norm_p(ivec3 vec, float p) {
    return ivecN_norm_p(vec.v, p, 3);
}
/** returns ||vec||_p */
static float ivec3_norm_p_v(const int *vec, float p) {
    return ivec3_norm_p(IVec3(vec), p);
}


/** returns ||vec||_1 */
static int ivec3_norm_1(ivec3 vec) {
    return ivecN_norm_1(vec.v, 3);
}
/** returns ||vec||_1 */
static int ivec3_norm_1_v(const int *vec) {
    return ivec3_norm_1(IVec3(vec));
}


/** returns ||vec||_inf */
static int ivec3_norm_inf(ivec3 vec) {
    return ivecN_norm_inf(vec.v, 3);
}
/** returns ||vec||_inf */
static int ivec3_norm_inf_v(const int *vec) {
    return ivec3_norm_inf(IVec3(vec));
}


/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static float ivec3_length(ivec3 vec) {
    return ivecN_length(vec.v, 3);
}
/** returns length of a vector, see ivecN_norm. Just here to match glsl */
static float ivec3_length_v(const int *vec) {
    return ivec3_length(IVec3(vec));
}


/** returns norm(b-a) */
static float ivec3_distance(ivec3 vec_a, ivec3 vec_b) {
    return ivecN_distance(vec_a.v, vec_b.v, 3);
}
/** returns norm(b-a) */
static float ivec3_distance_v(const int *vec_a, const int *vec_b) {
    return ivec3_distance(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a < b */
static bvec3 ivec3_less_than(ivec3 vec_a, int b) {
    bvec3 res;
    ivecN_less_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a < b */
static bvec3 ivec3_less_than_v(const int *vec_a, int b) {
    return ivec3_less_than(IVec3(vec_a), b);
}


/** dst = a < b */
static bvec3 ivec3_less_than_vec(ivec3 vec_a, ivec3 vec_b) {
    bvec3 res;
    ivecN_less_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a < b */
static bvec3 ivec3_less_than_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_less_than_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a <= b */
static bvec3 ivec3_less_than_equal(ivec3 vec_a, int b) {
    bvec3 res;
    ivecN_less_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a <= b */
static bvec3 ivec3_less_than_equal_v(const int *vec_a, int b) {
    return ivec3_less_than_equal(IVec3(vec_a), b);
}


/** dst = a <= b */
static bvec3 ivec3_less_than_equal_vec(ivec3 vec_a, ivec3 vec_b) {
    bvec3 res;
    ivecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a <= b */
static bvec3 ivec3_less_than_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_less_than_equal_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a > b */
static bvec3 ivec3_greater_than(ivec3 vec_a, int b) {
    bvec3 res;
    ivecN_greater_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a > b */
static bvec3 ivec3_greater_than_v(const int *vec_a, int b) {
    return ivec3_greater_than(IVec3(vec_a), b);
}


/** dst = a > b */
static bvec3 ivec3_greater_than_vec(ivec3 vec_a, ivec3 vec_b) {
    bvec3 res;
    ivecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a > b */
static bvec3 ivec3_greater_than_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_greater_than_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a >= b */
static bvec3 ivec3_greater_than_equal(ivec3 vec_a, int b) {
    bvec3 res;
    ivecN_greater_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a >= b */
static bvec3 ivec3_greater_than_equal_v(const int *vec_a, int b) {
    return ivec3_greater_than_equal(IVec3(vec_a), b);
}


/** dst = a >= b */
static bvec3 ivec3_greater_than_equal_vec(ivec3 vec_a, ivec3 vec_b) {
    bvec3 res;
    ivecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a >= b */
static bvec3 ivec3_greater_than_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_greater_than_equal_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a == b */
static bvec3 ivec3_equal(ivec3 vec_a, int b) {
    bvec3 res;
    ivecN_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a == b */
static bvec3 ivec3_equal_v(const int *vec_a, int b) {
    return ivec3_equal(IVec3(vec_a), b);
}


/** dst = a == b */
static bvec3 ivec3_equal_vec(ivec3 vec_a, ivec3 vec_b) {
    bvec3 res;
    ivecN_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a == b */
static bvec3 ivec3_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_equal_vec(IVec3(vec_a), IVec3(vec_b));
}


/** dst = a != b */
static bvec3 ivec3_not_equal(ivec3 vec_a, int b) {
    bvec3 res;
    ivecN_not_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a != b */
static bvec3 ivec3_not_equal_v(const int *vec_a, int b) {
    return ivec3_not_equal(IVec3(vec_a), b);
}


/** dst = a != b */
static bvec3 ivec3_not_equal_vec(ivec3 vec_a, ivec3 vec_b) {
    bvec3 res;
    ivecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a != b */
static bvec3 ivec3_not_equal_vec_v(const int *vec_a, const int *vec_b) {
    return ivec3_not_equal_vec(IVec3(vec_a), IVec3(vec_b));
}



//
// in addition to vec2:
//

/** dst = a x b */
static ivec3 ivec3_cross(ivec3 vec_a, ivec3 vec_b) {
    ivec3 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    return res;
}
/** dst = a x b */
static ivec3 ivec3_cross_v(const int *vec_a, const int *vec_b) {
    return ivec3_cross(IVec3(vec_a), IVec3(vec_b));
}


#endif //MATHC_VEC_IVEC3_H
