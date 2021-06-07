#ifndef MATHC_VEC_CVEC3_H
#define MATHC_VEC_CVEC3_H

#include "cvecn.h"
#include "../types/char.h"
#include "../types/bool.h"


/** dst = unit_x */
static cvec3 cvec3_unit_x() {
    return (cvec3) {{1, 0, 0}};
}

/** dst = unit_y */
static cvec3 cvec3_unit_y() {
    return (cvec3) {{0, 1, 0}};
}

/** dst = unit_z */
static cvec3 cvec3_unit_z() {
    return (cvec3) {{0, 0, 1}};
}

/** cvec_a == cvec_b */
static bool cvec3_cmp(cvec3 a, cvec3 b) {
    return cvecN_cmp(a.v, b.v, 3);
}


/** dst = scalar */
static cvec3 cvec3_set(signed char scalar) {
    cvec3 res;
    cvecN_set(res.v, scalar, 3);
    return res;
}

/** dst = (cvec3) v */
static cvec3 cvec3_cast_from_float(const float *v) {
    cvec3 res;
    cvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (cvec3) v */
static cvec3 cvec3_cast_from_double(const double *v) {
    cvec3 res;
    cvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (cvec3) v */
static cvec3 cvec3_cast_from_int(const int *v) {
    cvec3 res;
    cvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (cvec3) v */
static cvec3 cvec3_cast_from_unsigned(const unsigned *v) {
    cvec3 res;
    cvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (cvec3) v */
static cvec3 cvec3_cast_from_uchar(const unsigned char *v) {
    cvec3 res;
    cvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (cvec3) v */
static cvec3 cvec3_cast_from_bool(const bool *v) {
    cvec3 res;
    cvecN_cast_into(res.v, v, 3);
    return res;
}


/** dst = -vec */
static cvec3 cvec3_neg(cvec3 vec) {
    cvec3 res;
    cvecN_neg(res.v, vec.v, 3);
    return res;
}
/** dst = -vec */
static cvec3 cvec3_neg_v(const signed char *vec) {
    return cvec3_neg(CVec3(vec));
}


/** dst = a + b */
static cvec3 cvec3_add_vec(cvec3 vec_a, cvec3 vec_b) {
    cvec3 res;
    cvecN_add_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a + b */
static cvec3 cvec3_add_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_add_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a + b */
static cvec3 cvec3_add(cvec3 vec_a, signed char scalar_b) {
    cvec3 res;
    cvecN_add(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a + b */
static cvec3 cvec3_add_v(const signed char *vec_a, signed char scalar_b) {
    return cvec3_add(CVec3(vec_a), scalar_b);
}


/** dst = a - b */
static cvec3 cvec3_sub_vec(cvec3 vec_a, cvec3 vec_b) {
    cvec3 res;
    cvecN_sub_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a - b */
static cvec3 cvec3_sub_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_sub_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a - b */
static cvec3 cvec3_sub(cvec3 vec_a, signed char scalar_b) {
    cvec3 res;
    cvecN_sub(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a - b */
static cvec3 cvec3_sub_v(const signed char *vec_a, signed char scalar_b) {
    return cvec3_sub(CVec3(vec_a), scalar_b);
}


/** dst = a * b */
static cvec3 cvec3_scale_vec(cvec3 vec_a, cvec3 vec_b) {
    cvec3 res;
    cvecN_scale_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a * b */
static cvec3 cvec3_scale_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_scale_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a * b */
static cvec3 cvec3_scale(cvec3 vec_a, signed char scalar_b) {
    cvec3 res;
    cvecN_scale(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a * b */
static cvec3 cvec3_scale_v(const signed char *vec_a, signed char scalar_b) {
    return cvec3_scale(CVec3(vec_a), scalar_b);
}


/** dst = a / b */
static cvec3 cvec3_div_vec(cvec3 vec_a, cvec3 vec_b) {
    cvec3 res;
    cvecN_div_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a / b */
static cvec3 cvec3_div_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_div_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a / b */
static cvec3 cvec3_div(cvec3 vec_a, signed char scalar_b) {
    cvec3 res;
    cvecN_div(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a / b */
static cvec3 cvec3_div_v(const signed char *vec_a, signed char scalar_b) {
    return cvec3_div(CVec3(vec_a), scalar_b);
}


/** dst = abs(x) */
static cvec3 cvec3_abs(cvec3 vec_x) {
    cvec3 res;
    cvecN_abs(res.v, vec_x.v, 3);
    return res;
}
/** dst = abs(x) */
static cvec3 cvec3_abs_v(const signed char *vec_x) {
    return cvec3_abs(CVec3(vec_x));
}


/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static cvec3 cvec3_sign(cvec3 vec_x) {
    cvec3 res;
    cvecN_sign(res.v, vec_x.v, 3);
    return res;
}
/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static cvec3 cvec3_sign_v(const signed char *vec_x) {
    return cvec3_sign(CVec3(vec_x));
}


/** dst = x % y */
static cvec3 cvec3_mod(cvec3 vec_x, signed char y) {
    cvec3 res;
    cvecN_mod(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = x % y */
static cvec3 cvec3_mod_v(const signed char *vec_x, signed char y) {
    return cvec3_mod(CVec3(vec_x), y);
}


/** dst = x % y */
static cvec3 cvec3_mod_vec(cvec3 vec_x, cvec3 vec_y) {
    cvec3 res;
    cvecN_mod_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = x % y */
static cvec3 cvec3_mod_vec_v(const signed char *vec_x, const signed char *vec_y) {
    return cvec3_mod_vec(CVec3(vec_x), CVec3(vec_y));
}


/** dst = a < b ? a : b */
static cvec3 cvec3_min(cvec3 vec_x, signed char y) {
    cvec3 res;
    cvecN_min(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a < b ? a : b */
static cvec3 cvec3_min_v(const signed char *vec_x, signed char y) {
    return cvec3_min(CVec3(vec_x), y);
}


/** dst = a < b ? a : b */
static cvec3 cvec3_min_vec(cvec3 vec_x, cvec3 vec_y) {
    cvec3 res;
    cvecN_min_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a < b ? a : b */
static cvec3 cvec3_min_vec_v(const signed char *vec_x, const signed char *vec_y) {
    return cvec3_min_vec(CVec3(vec_x), CVec3(vec_y));
}


/** dst = a > b ? a : b */
static cvec3 cvec3_max(cvec3 vec_x, signed char y) {
    cvec3 res;
    cvecN_max(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a > b ? a : b */
static cvec3 cvec3_max_v(const signed char *vec_x, signed char y) {
    return cvec3_max(CVec3(vec_x), y);
}


/** dst = a > b ? a : b */
static cvec3 cvec3_max_vec(cvec3 vec_x, cvec3 vec_y) {
    cvec3 res;
    cvecN_max_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a > b ? a : b */
static cvec3 cvec3_max_vec_v(const signed char *vec_x, const signed char *vec_y) {
    return cvec3_max_vec(CVec3(vec_x), CVec3(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static cvec3 cvec3_clamp(cvec3 vec_x, signed char min, signed char max) {
    cvec3 res;
    cvecN_clamp(res.v, vec_x.v, min, max, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static cvec3 cvec3_clamp_v(const signed char *vec_x, signed char min, signed char max) {
    return cvec3_clamp(CVec3(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static cvec3 cvec3_clamp_vec(cvec3 vec_x, cvec3 vec_min, cvec3 vec_max) {
    cvec3 res;
    cvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static cvec3 cvec3_clamp_vec_v(const signed char *vec_x, const signed char *vec_min, const signed char *vec_max) {
    return cvec3_clamp_vec(CVec3(vec_x), CVec3(vec_min), CVec3(vec_max));
}

/** dst = a * (1-t) + b * t */
static cvec3 cvec3_mix(cvec3 vec_a, cvec3 vec_b, float t) {
    cvec3 res;
    cvecN_mix(res.v, vec_a.v, vec_b.v, t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static cvec3 cvec3_mix_v(const signed char *vec_a, const signed char *vec_b, float t) {
    return cvec3_mix(CVec3(vec_a), CVec3(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static cvec3 cvec3_mix_vec(cvec3 vec_a, cvec3 vec_b, const float *vec_t) {
    cvec3 res;
    cvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static cvec3 cvec3_mix_vec_v(const signed char *vec_a, const signed char *vec_b, const float *vec_t) {
    return cvec3_mix_vec(CVec3(vec_a), CVec3(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static cvec3 cvec3_step(cvec3 vec_x, signed char edge) {
    cvec3 res;
    cvecN_step(res.v, vec_x.v, edge, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static cvec3 cvec3_step_v(const signed char *vec_x, signed char edge) {
    return cvec3_step(CVec3(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static cvec3 cvec3_step_vec(cvec3 vec_x, cvec3 vec_edge) {
    cvec3 res;
    cvecN_step_vec(res.v, vec_x.v, vec_edge.v, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static cvec3 cvec3_step_vec_v(const signed char *vec_x, const signed char *vec_edge) {
    return cvec3_step_vec(CVec3(vec_x), CVec3(vec_edge));
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int cvec3_sum(cvec3 vec) {
    return cvecN_sum(vec.v, 3);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static int cvec3_sum_v(const signed char *vec) {
    return cvec3_sum(CVec3(vec));
}


/** returns a dot b */
static int cvec3_dot(cvec3 vec_a, cvec3 vec_b) {
    return cvecN_dot(vec_a.v, vec_b.v, 3);
}
/** returns a dot b */
static int cvec3_dot_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_dot(CVec3(vec_a), CVec3(vec_b));
}


/** returns ||vec||_3 */
static float cvec3_norm(cvec3 vec) {
    return cvecN_norm(vec.v, 3);
}
/** returns ||vec||_3 */
static float cvec3_norm_v(const signed char *vec) {
    return cvec3_norm(CVec3(vec));
}


/** returns ||vec||_p */
static float cvec3_norm_p(cvec3 vec, float p) {
    return cvecN_norm_p(vec.v, p, 3);
}
/** returns ||vec||_p */
static float cvec3_norm_p_v(const signed char *vec, float p) {
    return cvec3_norm_p(CVec3(vec), p);
}


/** returns ||vec||_1 */
static int cvec3_norm_1(cvec3 vec) {
    return cvecN_norm_1(vec.v, 3);
}
/** returns ||vec||_1 */
static int cvec3_norm_1_v(const signed char *vec) {
    return cvec3_norm_1(CVec3(vec));
}


/** returns ||vec||_inf */
static int cvec3_norm_inf(cvec3 vec) {
    return cvecN_norm_inf(vec.v, 3);
}
/** returns ||vec||_inf */
static int cvec3_norm_inf_v(const signed char *vec) {
    return cvec3_norm_inf(CVec3(vec));
}


/** returns length of a vector, see cvecN_norm. Just here to match glsl */
static float cvec3_length(cvec3 vec) {
    return cvecN_length(vec.v, 3);
}
/** returns length of a vector, see cvecN_norm. Just here to match glsl */
static float cvec3_length_v(const signed char *vec) {
    return cvec3_length(CVec3(vec));
}


/** returns norm(b-a) */
static float cvec3_distance(cvec3 vec_a, cvec3 vec_b) {
    return cvecN_distance(vec_a.v, vec_b.v, 3);
}
/** returns norm(b-a) */
static float cvec3_distance_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_distance(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a < b */
static bvec3 cvec3_less_than(cvec3 vec_a, signed char b) {
    bvec3 res;
    cvecN_less_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a < b */
static bvec3 cvec3_less_than_v(const signed char *vec_a, signed char b) {
    return cvec3_less_than(CVec3(vec_a), b);
}


/** dst = a < b */
static bvec3 cvec3_less_than_vec(cvec3 vec_a, cvec3 vec_b) {
    bvec3 res;
    cvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a < b */
static bvec3 cvec3_less_than_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_less_than_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a <= b */
static bvec3 cvec3_less_than_equal(cvec3 vec_a, signed char b) {
    bvec3 res;
    cvecN_less_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a <= b */
static bvec3 cvec3_less_than_equal_v(const signed char *vec_a, signed char b) {
    return cvec3_less_than_equal(CVec3(vec_a), b);
}


/** dst = a <= b */
static bvec3 cvec3_less_than_equal_vec(cvec3 vec_a, cvec3 vec_b) {
    bvec3 res;
    cvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a <= b */
static bvec3 cvec3_less_than_equal_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_less_than_equal_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a > b */
static bvec3 cvec3_greater_than(cvec3 vec_a, signed char b) {
    bvec3 res;
    cvecN_greater_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a > b */
static bvec3 cvec3_greater_than_v(const signed char *vec_a, signed char b) {
    return cvec3_greater_than(CVec3(vec_a), b);
}


/** dst = a > b */
static bvec3 cvec3_greater_than_vec(cvec3 vec_a, cvec3 vec_b) {
    bvec3 res;
    cvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a > b */
static bvec3 cvec3_greater_than_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_greater_than_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a >= b */
static bvec3 cvec3_greater_than_equal(cvec3 vec_a, signed char b) {
    bvec3 res;
    cvecN_greater_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a >= b */
static bvec3 cvec3_greater_than_equal_v(const signed char *vec_a, signed char b) {
    return cvec3_greater_than_equal(CVec3(vec_a), b);
}


/** dst = a >= b */
static bvec3 cvec3_greater_than_equal_vec(cvec3 vec_a, cvec3 vec_b) {
    bvec3 res;
    cvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a >= b */
static bvec3 cvec3_greater_than_equal_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_greater_than_equal_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a == b */
static bvec3 cvec3_equal(cvec3 vec_a, signed char b) {
    bvec3 res;
    cvecN_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a == b */
static bvec3 cvec3_equal_v(const signed char *vec_a, signed char b) {
    return cvec3_equal(CVec3(vec_a), b);
}


/** dst = a == b */
static bvec3 cvec3_equal_vec(cvec3 vec_a, cvec3 vec_b) {
    bvec3 res;
    cvecN_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a == b */
static bvec3 cvec3_equal_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_equal_vec(CVec3(vec_a), CVec3(vec_b));
}


/** dst = a != b */
static bvec3 cvec3_not_equal(cvec3 vec_a, signed char b) {
    bvec3 res;
    cvecN_not_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a != b */
static bvec3 cvec3_not_equal_v(const signed char *vec_a, signed char b) {
    return cvec3_not_equal(CVec3(vec_a), b);
}


/** dst = a != b */
static bvec3 cvec3_not_equal_vec(cvec3 vec_a, cvec3 vec_b) {
    bvec3 res;
    cvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a != b */
static bvec3 cvec3_not_equal_vec_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_not_equal_vec(CVec3(vec_a), CVec3(vec_b));
}



//
// in addition to vec2:
//

/** dst = a x b */
static cvec3 cvec3_cross(cvec3 vec_a, cvec3 vec_b) {
    cvec3 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    return res;
}
/** dst = a x b */
static cvec3 cvec3_cross_v(const signed char *vec_a, const signed char *vec_b) {
    return cvec3_cross(CVec3(vec_a), CVec3(vec_b));
}


#endif //MATHC_VEC_CVEC3_H
