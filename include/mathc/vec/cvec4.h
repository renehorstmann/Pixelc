#ifndef MATHC_VEC_CVEC4_H
#define MATHC_VEC_CVEC4_H

#include "cvecn.h"
#include "../types/char.h"
#include "../types/bool.h"


/** dst = unit_x */
static cvec4 cvec4_unit_x() {
    return (cvec4) {{1, 0, 0, 0}};
}

/** dst = unit_y */
static cvec4 cvec4_unit_y() {
    return (cvec4) {{0, 1, 0, 0}};
}

/** dst = unit_z */
static cvec4 cvec4_unit_z() {
    return (cvec4) {{0, 0, 1, 0}};
}

/** dst = unit_w */
static cvec4 cvec4_unit_w() {
    return (cvec4) {{0, 0, 0, 1}};
}

/** cvec_a == cvec_b */
static bool cvec4_cmp(cvec4 a, cvec4 b) {
    return cvecN_cmp(a.v, b.v, 4);
}


/** dst = scalar */
static cvec4 cvec4_set(char scalar) {
    cvec4 res;
    cvecN_set(res.v, scalar, 4);
    return res;
}

/** dst = (cvec4) v */
static cvec4 cvec4_cast_from_float(const float *v) {
    cvec4 res;
    cvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (cvec4) v */
static cvec4 cvec4_cast_from_double(const double *v) {
    cvec4 res;
    cvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (cvec4) v */
static cvec4 cvec4_cast_from_int(const int *v) {
    cvec4 res;
    cvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (cvec4) v */
static cvec4 cvec4_cast_from_unsigned(const unsigned *v) {
    cvec4 res;
    cvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (cvec4) v */
static cvec4 cvec4_cast_from_uchar(const unsigned char *v) {
    cvec4 res;
    cvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (cvec4) v */
static cvec4 cvec4_cast_from_bool(const bool *v) {
    cvec4 res;
    cvecN_cast_into(res.v, v, 4);
    return res;
}



/** dst = -vec */
static cvec4 cvec4_neg(cvec4 vec) {
    cvec4 res;
    cvecN_neg(res.v, vec.v, 4);
    return res;
}
/** dst = -vec */
static cvec4 cvec4_neg_v(const char *vec) {
    return cvec4_neg(CVec4(vec));
}


/** dst = a + b */
static cvec4 cvec4_add_vec(cvec4 vec_a, cvec4 vec_b) {
    cvec4 res;
    cvecN_add_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a + b */
static cvec4 cvec4_add_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_add_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a + b */
static cvec4 cvec4_add(cvec4 vec_a, char scalar_b) {
    cvec4 res;
    cvecN_add(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a + b */
static cvec4 cvec4_add_v(const char *vec_a, char scalar_b) {
    return cvec4_add(CVec4(vec_a), scalar_b);
}


/** dst = a - b */
static cvec4 cvec4_sub_vec(cvec4 vec_a, cvec4 vec_b) {
    cvec4 res;
    cvecN_sub_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a - b */
static cvec4 cvec4_sub_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_sub_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a - b */
static cvec4 cvec4_sub(cvec4 vec_a, char scalar_b) {
    cvec4 res;
    cvecN_sub(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a - b */
static cvec4 cvec4_sub_v(const char *vec_a, char scalar_b) {
    return cvec4_sub(CVec4(vec_a), scalar_b);
}


/** dst = a * b */
static cvec4 cvec4_scale_vec(cvec4 vec_a, cvec4 vec_b) {
    cvec4 res;
    cvecN_scale_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a * b */
static cvec4 cvec4_scale_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_scale_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a * b */
static cvec4 cvec4_scale(cvec4 vec_a, char scalar_b) {
    cvec4 res;
    cvecN_scale(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a * b */
static cvec4 cvec4_scale_v(const char *vec_a, char scalar_b) {
    return cvec4_scale(CVec4(vec_a), scalar_b);
}


/** dst = a / b */
static cvec4 cvec4_div_vec(cvec4 vec_a, cvec4 vec_b) {
    cvec4 res;
    cvecN_div_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a / b */
static cvec4 cvec4_div_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_div_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a / b */
static cvec4 cvec4_div(cvec4 vec_a, char scalar_b) {
    cvec4 res;
    cvecN_div(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a / b */
static cvec4 cvec4_div_v(const char *vec_a, char scalar_b) {
    return cvec4_div(CVec4(vec_a), scalar_b);
}


/** dst = abs(x) */
static cvec4 cvec4_abs(cvec4 vec_x) {
    cvec4 res;
    cvecN_abs(res.v, vec_x.v, 4);
    return res;
}
/** dst = abs(x) */
static cvec4 cvec4_abs_v(const char *vec_x) {
    return cvec4_abs(CVec4(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static cvec4 cvec4_sign(cvec4 vec_x) {
    cvec4 res;
    cvecN_sign(res.v, vec_x.v, 4);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static cvec4 cvec4_sign_v(const char *vec_x) {
    return cvec4_sign(CVec4(vec_x));
}


/** dst = x % y */
static cvec4 cvec4_mod(cvec4 vec_x, char y) {
    cvec4 res;
    cvecN_mod(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = x % y */
static cvec4 cvec4_mod_v(const char *vec_x, char y) {
    return cvec4_mod(CVec4(vec_x), y);
}


/** dst = x % y */
static cvec4 cvec4_mod_vec(cvec4 vec_x, cvec4 vec_y) {
    cvec4 res;
    cvecN_mod_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = x % y */
static cvec4 cvec4_mod_vec_v(const char *vec_x, const char *vec_y) {
    return cvec4_mod_vec(CVec4(vec_x), CVec4(vec_y));
}


/** dst = a < b ? a : b */
static cvec4 cvec4_min(cvec4 vec_x, char y) {
    cvec4 res;
    cvecN_min(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a < b ? a : b */
static cvec4 cvec4_min_v(const char *vec_x, char y) {
    return cvec4_min(CVec4(vec_x), y);
}


/** dst = a < b ? a : b */
static cvec4 cvec4_min_vec(cvec4 vec_x, cvec4 vec_y) {
    cvec4 res;
    cvecN_min_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a < b ? a : b */
static cvec4 cvec4_min_vec_v(const char *vec_x, const char *vec_y) {
    return cvec4_min_vec(CVec4(vec_x), CVec4(vec_y));
}


/** dst = a > b ? a : b */
static cvec4 cvec4_max(cvec4 vec_x, char y) {
    cvec4 res;
    cvecN_max(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a > b ? a : b */
static cvec4 cvec4_max_v(const char *vec_x, char y) {
    return cvec4_max(CVec4(vec_x), y);
}


/** dst = a > b ? a : b */
static cvec4 cvec4_max_vec(cvec4 vec_x, cvec4 vec_y) {
    cvec4 res;
    cvecN_max_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a > b ? a : b */
static cvec4 cvec4_max_vec_v(const char *vec_x, const char *vec_y) {
    return cvec4_max_vec(CVec4(vec_x), CVec4(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static cvec4 cvec4_clamp(cvec4 vec_x, char min, char max) {
    cvec4 res;
    cvecN_clamp(res.v, vec_x.v, min, max, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static cvec4 cvec4_clamp_v(const char *vec_x, char min, char max) {
    return cvec4_clamp(CVec4(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static cvec4 cvec4_clamp_vec(cvec4 vec_x, cvec4 vec_min, cvec4 vec_max) {
    cvec4 res;
    cvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static cvec4 cvec4_clamp_vec_v(const char *vec_x, const char *vec_min, const char *vec_max) {
    return cvec4_clamp_vec(CVec4(vec_x), CVec4(vec_min), CVec4(vec_max));
}

/** dst = a * (1-t) + b * t */
static cvec4 cvec4_mix(cvec4 vec_a, cvec4 vec_b, float t) {
    cvec4 res;
    cvecN_mix(res.v, vec_a.v, vec_b.v, t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static cvec4 cvec4_mix_v(const char *vec_a, const char *vec_b, float t) {
    return cvec4_mix(CVec4(vec_a), CVec4(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static cvec4 cvec4_mix_vec(cvec4 vec_a, cvec4 vec_b, const float *vec_t) {
    cvec4 res;
    cvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static cvec4 cvec4_mix_vec_v(const char *vec_a, const char *vec_b, const float *vec_t) {
    return cvec4_mix_vec(CVec4(vec_a), CVec4(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static cvec4 cvec4_step(cvec4 vec_x, char edge) {
    cvec4 res;
    cvecN_step(res.v, vec_x.v, edge, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static cvec4 cvec4_step_v(const char *vec_x, char edge) {
    return cvec4_step(CVec4(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static cvec4 cvec4_step_vec(cvec4 vec_x, cvec4 vec_edge) {
    cvec4 res;
    cvecN_step_vec(res.v, vec_x.v, vec_edge.v, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static cvec4 cvec4_step_vec_v(const char *vec_x, const char *vec_edge) {
    return cvec4_step_vec(CVec4(vec_x), CVec4(vec_edge));
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int cvec4_sum(cvec4 vec) {
    return cvecN_sum(vec.v, 4);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int cvec4_sum_v(const char *vec) {
    return cvec4_sum(CVec4(vec));
}


/** returns a dot b */
static int cvec4_dot(cvec4 vec_a, cvec4 vec_b) {
    return cvecN_dot(vec_a.v, vec_b.v, 4);
}
/** returns a dot b */
static int cvec4_dot_v(const char *vec_a, const char *vec_b) {
    return cvec4_dot(CVec4(vec_a), CVec4(vec_b));
}


/** returns ||vec||_4 */
static float cvec4_norm(cvec4 vec) {
    return cvecN_norm(vec.v, 4);
}
/** returns ||vec||_4 */
static float cvec4_norm_v(const char *vec) {
    return cvec4_norm(CVec4(vec));
}


/** returns ||vec||_p */
static float cvec4_norm_p(cvec4 vec, float p) {
    return cvecN_norm_p(vec.v, p, 4);
}
/** returns ||vec||_p */
static float cvec4_norm_p_v(const char *vec, float p) {
    return cvec4_norm_p(CVec4(vec), p);
}


/** returns ||vec||_1 */
static int cvec4_norm_1(cvec4 vec) {
    return cvecN_norm_1(vec.v, 4);
}
/** returns ||vec||_1 */
static int cvec4_norm_1_v(const char *vec) {
    return cvec4_norm_1(CVec4(vec));
}


/** returns ||vec||_inf */
static int cvec4_norm_inf(cvec4 vec) {
    return cvecN_norm_inf(vec.v, 4);
}
/** returns ||vec||_inf */
static int cvec4_norm_inf_v(const char *vec) {
    return cvec4_norm_inf(CVec4(vec));
}


/** returns length of a vector, see cvecN_norm. Just here to match glsl */
static float cvec4_length(cvec4 vec) {
    return cvecN_length(vec.v, 4);
}
/** returns length of a vector, see cvecN_norm. Just here to match glsl */
static float cvec4_length_v(const char *vec) {
    return cvec4_length(CVec4(vec));
}


/** returns norm(b-a) */
static float cvec4_distance(cvec4 vec_a, cvec4 vec_b) {
    return cvecN_distance(vec_a.v, vec_b.v, 4);
}
/** returns norm(b-a) */
static float cvec4_distance_v(const char *vec_a, const char *vec_b) {
    return cvec4_distance(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a < b */
static bvec4 cvec4_less_than(cvec4 vec_a, char b) {
    bvec4 res;
    cvecN_less_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a < b */
static bvec4 cvec4_less_than_v(const char *vec_a, char b) {
    return cvec4_less_than(CVec4(vec_a), b);
}


/** dst = a < b */
static bvec4 cvec4_less_than_vec(cvec4 vec_a, cvec4 vec_b) {
    bvec4 res;
    cvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a < b */
static bvec4 cvec4_less_than_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_less_than_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a <= b */
static bvec4 cvec4_less_than_equal(cvec4 vec_a, char b) {
    bvec4 res;
    cvecN_less_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a <= b */
static bvec4 cvec4_less_than_equal_v(const char *vec_a, char b) {
    return cvec4_less_than_equal(CVec4(vec_a), b);
}


/** dst = a <= b */
static bvec4 cvec4_less_than_equal_vec(cvec4 vec_a, cvec4 vec_b) {
    bvec4 res;
    cvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a <= b */
static bvec4 cvec4_less_than_equal_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_less_than_equal_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a > b */
static bvec4 cvec4_greater_than(cvec4 vec_a, char b) {
    bvec4 res;
    cvecN_greater_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a > b */
static bvec4 cvec4_greater_than_v(const char *vec_a, char b) {
    return cvec4_greater_than(CVec4(vec_a), b);
}


/** dst = a > b */
static bvec4 cvec4_greater_than_vec(cvec4 vec_a, cvec4 vec_b) {
    bvec4 res;
    cvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a > b */
static bvec4 cvec4_greater_than_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_greater_than_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a >= b */
static bvec4 cvec4_greater_than_equal(cvec4 vec_a, char b) {
    bvec4 res;
    cvecN_greater_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a >= b */
static bvec4 cvec4_greater_than_equal_v(const char *vec_a, char b) {
    return cvec4_greater_than_equal(CVec4(vec_a), b);
}


/** dst = a >= b */
static bvec4 cvec4_greater_than_equal_vec(cvec4 vec_a, cvec4 vec_b) {
    bvec4 res;
    cvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a >= b */
static bvec4 cvec4_greater_than_equal_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_greater_than_equal_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a == b */
static bvec4 cvec4_equal(cvec4 vec_a, char b) {
    bvec4 res;
    cvecN_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a == b */
static bvec4 cvec4_equal_v(const char *vec_a, char b) {
    return cvec4_equal(CVec4(vec_a), b);
}


/** dst = a == b */
static bvec4 cvec4_equal_vec(cvec4 vec_a, cvec4 vec_b) {
    bvec4 res;
    cvecN_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a == b */
static bvec4 cvec4_equal_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_equal_vec(CVec4(vec_a), CVec4(vec_b));
}


/** dst = a != b */
static bvec4 cvec4_not_equal(cvec4 vec_a, char b) {
    bvec4 res;
    cvecN_not_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a != b */
static bvec4 cvec4_not_equal_v(const char *vec_a, char b) {
    return cvec4_not_equal(CVec4(vec_a), b);
}


/** dst = a != b */
static bvec4 cvec4_not_equal_vec(cvec4 vec_a, cvec4 vec_b) {
    bvec4 res;
    cvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a != b */
static bvec4 cvec4_not_equal_vec_v(const char *vec_a, const char *vec_b) {
    return cvec4_not_equal_vec(CVec4(vec_a), CVec4(vec_b));
}



//
// in addition to vec2:
//


/** dst = a x b , dst.w = 0 */
static cvec4 cvec4_cross(cvec4 vec_a, cvec4 vec_b) {
    cvec4 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    res.w = 0;
    return res;
}
/** dst = a x b , dst.w = 0 */
static cvec4 cvec4_cross_v(const char *vec_a, const char *vec_b) {
    return cvec4_cross(CVec4(vec_a), CVec4(vec_b));
}


#endif //MATHC_VEC_CVEC4_H
