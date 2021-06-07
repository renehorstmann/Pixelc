#ifndef MATHC_VEC_CVEC2_H
#define MATHC_VEC_CVEC2_H

#include "cvecn.h"
#include "../types/char.h"
#include "../types/bool.h"


/** dst = unit_x */
static cvec2 cvec2_unit_x() {
    return (cvec2) {{1, 0}};
}

/** dst = unit_y */
static cvec2 cvec2_unit_y() {
    return (cvec2) {{0, 1}};
}

/** cvec_a == cvec_b */
static bool cvec2_cmp(cvec2 a, cvec2 b) {
    return cvecN_cmp(a.v, b.v, 2);
}


/** dst = scalar */
static cvec2 cvec2_set(int8_t scalar) {
    cvec2 res;
    cvecN_set(res.v, scalar, 2);
    return res;
}

/** dst = (cvec2) v */
static cvec2 cvec2_cast_from_float(const float *v) {
    cvec2 res;
    cvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (cvec2) v */
static cvec2 cvec2_cast_from_double(const double *v) {
    cvec2 res;
    cvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (cvec2) v */
static cvec2 cvec2_cast_from_int(const int *v) {
    cvec2 res;
    cvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (cvec2) v */
static cvec2 cvec2_cast_from_unsigned(const unsigned *v) {
    cvec2 res;
    cvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (cvec2) v */
static cvec2 cvec2_cast_from_uchar(const uint8_t *v) {
    cvec2 res;
    cvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (cvec2) v */
static cvec2 cvec2_cast_from_bool(const bool *v) {
    cvec2 res;
    cvecN_cast_into(res.v, v, 2);
    return res;
}


/** dst = -vec */
static cvec2 cvec2_neg(cvec2 vec) {
    cvec2 res;
    cvecN_neg(res.v, vec.v, 2);
    return res;
}
/** dst = -vec */
static cvec2 cvec2_neg_v(const int8_t *vec) {
    return cvec2_neg(CVec2(vec));
}


/** dst = a + b */
static cvec2 cvec2_add_vec(cvec2 vec_a, cvec2 vec_b) {
    cvec2 res;
    cvecN_add_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a + b */
static cvec2 cvec2_add_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_add_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a + b */
static cvec2 cvec2_add(cvec2 vec_a, int8_t scalar_b) {
    cvec2 res;
    cvecN_add(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a + b */
static cvec2 cvec2_add_v(const int8_t *vec_a, int8_t scalar_b) {
    return cvec2_add(CVec2(vec_a), scalar_b);
}


/** dst = a - b */
static cvec2 cvec2_sub_vec(cvec2 vec_a, cvec2 vec_b) {
    cvec2 res;
    cvecN_sub_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a - b */
static cvec2 cvec2_sub_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_sub_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a - b */
static cvec2 cvec2_sub(cvec2 vec_a, int8_t scalar_b) {
    cvec2 res;
    cvecN_sub(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a - b */
static cvec2 cvec2_sub_v(const int8_t *vec_a, int8_t scalar_b) {
    return cvec2_sub(CVec2(vec_a), scalar_b);
}


/** dst = a * b */
static cvec2 cvec2_scale_vec(cvec2 vec_a, cvec2 vec_b) {
    cvec2 res;
    cvecN_scale_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a * b */
static cvec2 cvec2_scale_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_scale_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a * b */
static cvec2 cvec2_scale(cvec2 vec_a, int8_t scalar_b) {
    cvec2 res;
    cvecN_scale(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a * b */
static cvec2 cvec2_scale_v(const int8_t *vec_a, int8_t scalar_b) {
    return cvec2_scale(CVec2(vec_a), scalar_b);
}


/** dst = a / b */
static cvec2 cvec2_div_vec(cvec2 vec_a, cvec2 vec_b) {
    cvec2 res;
    cvecN_div_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a / b */
static cvec2 cvec2_div_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_div_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a / b */
static cvec2 cvec2_div(cvec2 vec_a, int8_t scalar_b) {
    cvec2 res;
    cvecN_div(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a / b */
static cvec2 cvec2_div_v(const int8_t *vec_a, int8_t scalar_b) {
    return cvec2_div(CVec2(vec_a), scalar_b);
}

/** dst = abs(x) */
static cvec2 cvec2_abs(cvec2 vec_x) {
    cvec2 res;
    cvecN_abs(res.v, vec_x.v, 2);
    return res;
}
/** dst = abs(x) */
static cvec2 cvec2_abs_v(const int8_t *vec_x) {
    return cvec2_abs(CVec2(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static cvec2 cvec2_sign(cvec2 vec_x) {
    cvec2 res;
    cvecN_sign(res.v, vec_x.v, 2);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static cvec2 cvec2_sign_v(const int8_t *vec_x) {
    return cvec2_sign(CVec2(vec_x));
}


/** dst = x % y */
static cvec2 cvec2_mod(cvec2 vec_x, int8_t y) {
    cvec2 res;
    cvecN_mod(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = x % y */
static cvec2 cvec2_mod_v(const int8_t *vec_x, int8_t y) {
    return cvec2_mod(CVec2(vec_x), y);
}


/** dst = x % y */
static cvec2 cvec2_mod_vec(cvec2 vec_x, cvec2 vec_y) {
    cvec2 res;
    cvecN_mod_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = x % y */
static cvec2 cvec2_mod_vec_v(const int8_t *vec_x, const int8_t *vec_y) {
    return cvec2_mod_vec(CVec2(vec_x), CVec2(vec_y));
}


/** dst = a < b ? a : b */
static cvec2 cvec2_min(cvec2 vec_x, int8_t y) {
    cvec2 res;
    cvecN_min(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a < b ? a : b */
static cvec2 cvec2_min_v(const int8_t *vec_x, int8_t y) {
    return cvec2_min(CVec2(vec_x), y);
}


/** dst = a < b ? a : b */
static cvec2 cvec2_min_vec(cvec2 vec_x, cvec2 vec_y) {
    cvec2 res;
    cvecN_min_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a < b ? a : b */
static cvec2 cvec2_min_vec_v(const int8_t *vec_x, const int8_t *vec_y) {
    return cvec2_min_vec(CVec2(vec_x), CVec2(vec_y));
}


/** dst = a > b ? a : b */
static cvec2 cvec2_max(cvec2 vec_x, int8_t y) {
    cvec2 res;
    cvecN_max(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a > b ? a : b */
static cvec2 cvec2_max_v(const int8_t *vec_x, int8_t y) {
    return cvec2_max(CVec2(vec_x), y);
}


/** dst = a > b ? a : b */
static cvec2 cvec2_max_vec(cvec2 vec_x, cvec2 vec_y) {
    cvec2 res;
    cvecN_max_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a > b ? a : b */
static cvec2 cvec2_max_vec_v(const int8_t *vec_x, const int8_t *vec_y) {
    return cvec2_max_vec(CVec2(vec_x), CVec2(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static cvec2 cvec2_clamp(cvec2 vec_x, int8_t min, int8_t max) {
    cvec2 res;
    cvecN_clamp(res.v, vec_x.v, min, max, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static cvec2 cvec2_clamp_v(const int8_t *vec_x, int8_t min, int8_t max) {
    return cvec2_clamp(CVec2(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static cvec2 cvec2_clamp_vec(cvec2 vec_x, cvec2 vec_min, cvec2 vec_max) {
    cvec2 res;
    cvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static cvec2 cvec2_clamp_vec_v(const int8_t *vec_x, const int8_t *vec_min, const int8_t *vec_max) {
    return cvec2_clamp_vec(CVec2(vec_x), CVec2(vec_min), CVec2(vec_max));
}

/** dst = a * (1-t) + b * t */
static cvec2 cvec2_mix(cvec2 vec_a, cvec2 vec_b, float t) {
    cvec2 res;
    cvecN_mix(res.v, vec_a.v, vec_b.v, t, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static cvec2 cvec2_mix_v(const int8_t *vec_a, const int8_t *vec_b, float t) {
    return cvec2_mix(CVec2(vec_a), CVec2(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static cvec2 cvec2_mix_vec(cvec2 vec_a, cvec2 vec_b, const float *vec_t) {
    cvec2 res;
    cvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static cvec2 cvec2_mix_vec_v(const int8_t *vec_a, const int8_t *vec_b, const float *vec_t) {
    return cvec2_mix_vec(CVec2(vec_a), CVec2(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static cvec2 cvec2_step(cvec2 vec_x, int8_t edge) {
    cvec2 res;
    cvecN_step(res.v, vec_x.v, edge, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static cvec2 cvec2_step_v(const int8_t *vec_x, int8_t edge) {
    return cvec2_step(CVec2(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static cvec2 cvec2_step_vec(cvec2 vec_x, cvec2 vec_edge) {
    cvec2 res;
    cvecN_step_vec(res.v, vec_x.v, vec_edge.v, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static cvec2 cvec2_step_vec_v(const int8_t *vec_x, const int8_t *vec_edge) {
    return cvec2_step_vec(CVec2(vec_x), CVec2(vec_edge));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int cvec2_sum(cvec2 vec) {
    return cvecN_sum(vec.v, 2);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int cvec2_sum_v(const int8_t *vec) {
    return cvec2_sum(CVec2(vec));
}


/** returns a dot b */
static int cvec2_dot(cvec2 vec_a, cvec2 vec_b) {
    return cvecN_dot(vec_a.v, vec_b.v, 2);
}
/** returns a dot b */
static int cvec2_dot_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_dot(CVec2(vec_a), CVec2(vec_b));
}


/** returns ||vec||_2 */
static float cvec2_norm(cvec2 vec) {
    return cvecN_norm(vec.v, 2);
}
/** returns ||vec||_2 */
static float cvec2_norm_v(const int8_t *vec) {
    return cvec2_norm(CVec2(vec));
}


/** returns ||vec||_p */
static float cvec2_norm_p(cvec2 vec, float p) {
    return cvecN_norm_p(vec.v, p, 2);
}
/** returns ||vec||_p */
static float cvec2_norm_p_v(const int8_t *vec, float p) {
    return cvec2_norm_p(CVec2(vec), p);
}


/** returns ||vec||_1 */
static int cvec2_norm_1(cvec2 vec) {
    return cvecN_norm_1(vec.v, 2);
}
/** returns ||vec||_1 */
static int cvec2_norm_1_v(const int8_t *vec) {
    return cvec2_norm_1(CVec2(vec));
}


/** returns ||vec||_inf */
static int cvec2_norm_inf(cvec2 vec) {
    return cvecN_norm_inf(vec.v, 2);
}
/** returns ||vec||_inf */
static int cvec2_norm_inf_v(const int8_t *vec) {
    return cvec2_norm_inf(CVec2(vec));
}


/** returns length of a vector, see cvecN_norm. Just here to match glsl */
static float cvec2_length(cvec2 vec) {
    return cvecN_length(vec.v, 2);
}
/** returns length of a vector, see cvecN_norm. Just here to match glsl */
static float cvec2_length_v(const int8_t *vec) {
    return cvec2_length(CVec2(vec));
}


/** returns norm(b-a) */
static float cvec2_distance(cvec2 vec_a, cvec2 vec_b) {
    return cvecN_distance(vec_a.v, vec_b.v, 2);
}
/** returns norm(b-a) */
static float cvec2_distance_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_distance(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a < b */
static bvec2 cvec2_less_than(cvec2 vec_a, int8_t b) {
    bvec2 res;
    cvecN_less_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a < b */
static bvec2 cvec2_less_than_v(const int8_t *vec_a, int8_t b) {
    return cvec2_less_than(CVec2(vec_a), b);
}


/** dst = a < b */
static bvec2 cvec2_less_than_vec(cvec2 vec_a, cvec2 vec_b) {
    bvec2 res;
    cvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a < b */
static bvec2 cvec2_less_than_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_less_than_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a <= b */
static bvec2 cvec2_less_than_equal(cvec2 vec_a, int8_t b) {
    bvec2 res;
    cvecN_less_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a <= b */
static bvec2 cvec2_less_than_equal_v(const int8_t *vec_a, int8_t b) {
    return cvec2_less_than_equal(CVec2(vec_a), b);
}


/** dst = a <= b */
static bvec2 cvec2_less_than_equal_vec(cvec2 vec_a, cvec2 vec_b) {
    bvec2 res;
    cvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a <= b */
static bvec2 cvec2_less_than_equal_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_less_than_equal_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a > b */
static bvec2 cvec2_greater_than(cvec2 vec_a, int8_t b) {
    bvec2 res;
    cvecN_greater_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a > b */
static bvec2 cvec2_greater_than_v(const int8_t *vec_a, int8_t b) {
    return cvec2_greater_than(CVec2(vec_a), b);
}


/** dst = a > b */
static bvec2 cvec2_greater_than_vec(cvec2 vec_a, cvec2 vec_b) {
    bvec2 res;
    cvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a > b */
static bvec2 cvec2_greater_than_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_greater_than_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a >= b */
static bvec2 cvec2_greater_than_equal(cvec2 vec_a, int8_t b) {
    bvec2 res;
    cvecN_greater_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a >= b */
static bvec2 cvec2_greater_than_equal_v(const int8_t *vec_a, int8_t b) {
    return cvec2_greater_than_equal(CVec2(vec_a), b);
}


/** dst = a >= b */
static bvec2 cvec2_greater_than_equal_vec(cvec2 vec_a, cvec2 vec_b) {
    bvec2 res;
    cvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a >= b */
static bvec2 cvec2_greater_than_equal_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_greater_than_equal_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a == b */
static bvec2 cvec2_equal(cvec2 vec_a, int8_t b) {
    bvec2 res;
    cvecN_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a == b */
static bvec2 cvec2_equal_v(const int8_t *vec_a, int8_t b) {
    return cvec2_equal(CVec2(vec_a), b);
}


/** dst = a == b */
static bvec2 cvec2_equal_vec(cvec2 vec_a, cvec2 vec_b) {
    bvec2 res;
    cvecN_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a == b */
static bvec2 cvec2_equal_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_equal_vec(CVec2(vec_a), CVec2(vec_b));
}


/** dst = a != b */
static bvec2 cvec2_not_equal(cvec2 vec_a, int8_t b) {
    bvec2 res;
    cvecN_not_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a != b */
static bvec2 cvec2_not_equal_v(const int8_t *vec_a, int8_t b) {
    return cvec2_not_equal(CVec2(vec_a), b);
}


/** dst = a != b */
static bvec2 cvec2_not_equal_vec(cvec2 vec_a, cvec2 vec_b) {
    bvec2 res;
    cvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a != b */
static bvec2 cvec2_not_equal_vec_v(const int8_t *vec_a, const int8_t *vec_b) {
    return cvec2_not_equal_vec(CVec2(vec_a), CVec2(vec_b));
}

#endif //MATHC_VEC_CVEC2_H
