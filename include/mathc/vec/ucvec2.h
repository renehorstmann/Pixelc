#ifndef MATHC_VEC_UCVEC2_H
#define MATHC_VEC_UCVEC2_H

#include "ucvecn.h"
#include "../types/uchar.h"
#include "../types/bool.h"


/** dst = unit_x */
static ucvec2 ucvec2_unit_x() {
    return (ucvec2) {{1, 0}};
}

/** dst = unit_y */
static ucvec2 ucvec2_unit_y() {
    return (ucvec2) {{0, 1}};
}

/** ucvec_a == ucvec_b */
static bool ucvec2_cmp(ucvec2 a, ucvec2 b) {
    return ucvecN_cmp(a.v, b.v, 2);
}

/** dst = scalar */
static ucvec2 ucvec2_set(unsigned char scalar) {
    ucvec2 res;
    ucvecN_set(res.v, scalar, 2);
    return res;
}


/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_float(const float *v) {
    ucvec2 res;
    ucvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_double(const double *v) {
    ucvec2 res;
    ucvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_int(const int *v) {
    ucvec2 res;
    ucvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_unsigned(const unsigned *v) {
    ucvec2 res;
    ucvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_char(const signed char *v) {
    ucvec2 res;
    ucvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (ucvec2) v */
static ucvec2 ucvec2_cast_from_bool(const bool *v) {
    ucvec2 res;
    ucvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = vec * 255 */
static ucvec2 ucvec2_cast_from_float_1(const float *v) {
    ucvec2 res;
    ucvecN_cast_from_float_1(res.v, v, 2);
    return res;
}

/** dst = vec * 255 */
static ucvec2 ucvec2_cast_from_double_1(const double *v) {
    ucvec2 res;
    ucvecN_cast_from_double_1(res.v, v, 2);
    return res;
}


/** dst = a + b */
static ucvec2 ucvec2_add_vec(ucvec2 vec_a, ucvec2 vec_b) {
    ucvec2 res;
    ucvecN_add_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a + b */
static ucvec2 ucvec2_add_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_add_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a + b */
static ucvec2 ucvec2_add(ucvec2 vec_a, unsigned char scalar_b) {
    ucvec2 res;
    ucvecN_add(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a + b */
static ucvec2 ucvec2_add_v(const unsigned char *vec_a, unsigned char scalar_b) {
    return ucvec2_add(UCVec2(vec_a), scalar_b);
}


/** dst = a - b */
static ucvec2 ucvec2_sub_vec(ucvec2 vec_a, ucvec2 vec_b) {
    ucvec2 res;
    ucvecN_sub_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a - b */
static ucvec2 ucvec2_sub_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_sub_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a - b */
static ucvec2 ucvec2_sub(ucvec2 vec_a, unsigned char scalar_b) {
    ucvec2 res;
    ucvecN_sub(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a - b */
static ucvec2 ucvec2_sub_v(const unsigned char *vec_a, unsigned char scalar_b) {
    return ucvec2_sub(UCVec2(vec_a), scalar_b);
}


/** dst = a * b */
static ucvec2 ucvec2_scale_vec(ucvec2 vec_a, ucvec2 vec_b) {
    ucvec2 res;
    ucvecN_scale_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a * b */
static ucvec2 ucvec2_scale_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_scale_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a * b */
static ucvec2 ucvec2_scale(ucvec2 vec_a, unsigned char scalar_b) {
    ucvec2 res;
    ucvecN_scale(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a * b */
static ucvec2 ucvec2_scale_v(const unsigned char *vec_a, unsigned char scalar_b) {
    return ucvec2_scale(UCVec2(vec_a), scalar_b);
}


/** dst = a / b */
static ucvec2 ucvec2_div_vec(ucvec2 vec_a, ucvec2 vec_b) {
    ucvec2 res;
    ucvecN_div_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a / b */
static ucvec2 ucvec2_div_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_div_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a / b */
static ucvec2 ucvec2_div(ucvec2 vec_a, unsigned char scalar_b) {
    ucvec2 res;
    ucvecN_div(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a / b */
static ucvec2 ucvec2_div_v(const unsigned char *vec_a, unsigned char scalar_b) {
    return ucvec2_div(UCVec2(vec_a), scalar_b);
}


/** dst = x % y */
static ucvec2 ucvec2_mod(ucvec2 vec_x, unsigned char y) {
    ucvec2 res;
    ucvecN_mod(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = x % y */
static ucvec2 ucvec2_mod_v(const unsigned char *vec_x, unsigned char y) {
    return ucvec2_mod(UCVec2(vec_x), y);
}


/** dst = x % y */
static ucvec2 ucvec2_mod_vec(ucvec2 vec_x, ucvec2 vec_y) {
    ucvec2 res;
    ucvecN_mod_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = x % y */
static ucvec2 ucvec2_mod_vec_v(const unsigned char *vec_x, const unsigned char *vec_y) {
    return ucvec2_mod_vec(UCVec2(vec_x), UCVec2(vec_y));
}


/** dst = a < b ? a : b */
static ucvec2 ucvec2_min(ucvec2 vec_x, unsigned char y) {
    ucvec2 res;
    ucvecN_min(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a < b ? a : b */
static ucvec2 ucvec2_min_v(const unsigned char *vec_x, unsigned char y) {
    return ucvec2_min(UCVec2(vec_x), y);
}


/** dst = a < b ? a : b */
static ucvec2 ucvec2_min_vec(ucvec2 vec_x, ucvec2 vec_y) {
    ucvec2 res;
    ucvecN_min_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a < b ? a : b */
static ucvec2 ucvec2_min_vec_v(const unsigned char *vec_x, const unsigned char *vec_y) {
    return ucvec2_min_vec(UCVec2(vec_x), UCVec2(vec_y));
}


/** dst = a > b ? a : b */
static ucvec2 ucvec2_max(ucvec2 vec_x, unsigned char y) {
    ucvec2 res;
    ucvecN_max(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a > b ? a : b */
static ucvec2 ucvec2_max_v(const unsigned char *vec_x, unsigned char y) {
    return ucvec2_max(UCVec2(vec_x), y);
}


/** dst = a > b ? a : b */
static ucvec2 ucvec2_max_vec(ucvec2 vec_x, ucvec2 vec_y) {
    ucvec2 res;
    ucvecN_max_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a > b ? a : b */
static ucvec2 ucvec2_max_vec_v(const unsigned char *vec_x, const unsigned char *vec_y) {
    return ucvec2_max_vec(UCVec2(vec_x), UCVec2(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec2 ucvec2_clamp(ucvec2 vec_x, unsigned char min, unsigned char max) {
    ucvec2 res;
    ucvecN_clamp(res.v, vec_x.v, min, max, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ucvec2 ucvec2_clamp_v(const unsigned char *vec_x, unsigned char min, unsigned char max) {
    return ucvec2_clamp(UCVec2(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec2 ucvec2_clamp_vec(ucvec2 vec_x, ucvec2 vec_min, ucvec2 vec_max) {
    ucvec2 res;
    ucvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ucvec2 ucvec2_clamp_vec_v(const unsigned char *vec_x, const unsigned char *vec_min, const unsigned char *vec_max) {
    return ucvec2_clamp_vec(UCVec2(vec_x), UCVec2(vec_min), UCVec2(vec_max));
}


/** dst = a * (1-t) + b * t */
static ucvec2 ucvec2_mix(ucvec2 vec_a, ucvec2 vec_b, float t) {
    ucvec2 res;
    ucvecN_mix(res.v, vec_a.v, vec_b.v, t, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static ucvec2 ucvec2_mix_v(const unsigned char *vec_a, const unsigned char *vec_b, float t) {
    return ucvec2_mix(UCVec2(vec_a), UCVec2(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static ucvec2 ucvec2_mix_vec(ucvec2 vec_a, ucvec2 vec_b, const float *vec_t) {
    ucvec2 res;
    ucvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 2);
    return res;
}
/** dst = a * (1-t) + b * t */
static ucvec2 ucvec2_mix_vec_v(const unsigned char *vec_a, const unsigned char *vec_b, const float *vec_t) {
    return ucvec2_mix_vec(UCVec2(vec_a), UCVec2(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static ucvec2 ucvec2_step(ucvec2 vec_x, unsigned char edge) {
    ucvec2 res;
    ucvecN_step(res.v, vec_x.v, edge, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ucvec2 ucvec2_step_v(const unsigned char *vec_x, unsigned char edge) {
    return ucvec2_step(UCVec2(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static ucvec2 ucvec2_step_vec(ucvec2 vec_x, ucvec2 vec_edge) {
    ucvec2 res;
    ucvecN_step_vec(res.v, vec_x.v, vec_edge.v, 2);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ucvec2 ucvec2_step_vec_v(const unsigned char *vec_x, const unsigned char *vec_edge) {
    return ucvec2_step_vec(UCVec2(vec_x), UCVec2(vec_edge));
}

/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned char ucvec2_sum(ucvec2 vec) {
    return ucvecN_sum(vec.v, 2);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned char ucvec2_sum_v(const unsigned char *vec) {
    return ucvec2_sum(UCVec2(vec));
}


/** returns a dot b */
static unsigned char ucvec2_dot(ucvec2 vec_a, ucvec2 vec_b) {
    return ucvecN_dot(vec_a.v, vec_b.v, 2);
}
/** returns a dot b */
static unsigned char ucvec2_dot_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_dot(UCVec2(vec_a), UCVec2(vec_b));
}


/** returns ||vec||_2 */
static float ucvec2_norm(ucvec2 vec) {
    return ucvecN_norm(vec.v, 2);
}
/** returns ||vec||_2 */
static float ucvec2_norm_v(const unsigned char *vec) {
    return ucvec2_norm(UCVec2(vec));
}


/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static float ucvec2_length(ucvec2 vec) {
    return ucvecN_length(vec.v, 2);
}
/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static float ucvec2_length_v(const unsigned char *vec) {
    return ucvec2_length(UCVec2(vec));
}


/** returns norm(b-a) */
static float ucvec2_distance(ucvec2 vec_a, ucvec2 vec_b) {
    return ucvecN_distance(vec_a.v, vec_b.v, 2);
}
/** returns norm(b-a) */
static float ucvec2_distance_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_distance(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a < b */
static bvec2 ucvec2_less_than(ucvec2 vec_a, unsigned char b) {
    bvec2 res;
    ucvecN_less_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a < b */
static bvec2 ucvec2_less_than_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec2_less_than(UCVec2(vec_a), b);
}


/** dst = a < b */
static bvec2 ucvec2_less_than_vec(ucvec2 vec_a, ucvec2 vec_b) {
    bvec2 res;
    ucvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a < b */
static bvec2 ucvec2_less_than_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_less_than_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a <= b */
static bvec2 ucvec2_less_than_equal(ucvec2 vec_a, unsigned char b) {
    bvec2 res;
    ucvecN_less_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a <= b */
static bvec2 ucvec2_less_than_equal_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec2_less_than_equal(UCVec2(vec_a), b);
}


/** dst = a <= b */
static bvec2 ucvec2_less_than_equal_vec(ucvec2 vec_a, ucvec2 vec_b) {
    bvec2 res;
    ucvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a <= b */
static bvec2 ucvec2_less_than_equal_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_less_than_equal_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a > b */
static bvec2 ucvec2_greater_than(ucvec2 vec_a, unsigned char b) {
    bvec2 res;
    ucvecN_greater_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a > b */
static bvec2 ucvec2_greater_than_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec2_greater_than(UCVec2(vec_a), b);
}


/** dst = a > b */
static bvec2 ucvec2_greater_than_vec(ucvec2 vec_a, ucvec2 vec_b) {
    bvec2 res;
    ucvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a > b */
static bvec2 ucvec2_greater_than_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_greater_than_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a >= b */
static bvec2 ucvec2_greater_than_equal(ucvec2 vec_a, unsigned char b) {
    bvec2 res;
    ucvecN_greater_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a >= b */
static bvec2 ucvec2_greater_than_equal_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec2_greater_than_equal(UCVec2(vec_a), b);
}


/** dst = a >= b */
static bvec2 ucvec2_greater_than_equal_vec(ucvec2 vec_a, ucvec2 vec_b) {
    bvec2 res;
    ucvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a >= b */
static bvec2 ucvec2_greater_than_equal_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_greater_than_equal_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a == b */
static bvec2 ucvec2_equal(ucvec2 vec_a, unsigned char b) {
    bvec2 res;
    ucvecN_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a == b */
static bvec2 ucvec2_equal_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec2_equal(UCVec2(vec_a), b);
}


/** dst = a == b */
static bvec2 ucvec2_equal_vec(ucvec2 vec_a, ucvec2 vec_b) {
    bvec2 res;
    ucvecN_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a == b */
static bvec2 ucvec2_equal_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_equal_vec(UCVec2(vec_a), UCVec2(vec_b));
}


/** dst = a != b */
static bvec2 ucvec2_not_equal(ucvec2 vec_a, unsigned char b) {
    bvec2 res;
    ucvecN_not_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a != b */
static bvec2 ucvec2_not_equal_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec2_not_equal(UCVec2(vec_a), b);
}


/** dst = a != b */
static bvec2 ucvec2_not_equal_vec(ucvec2 vec_a, ucvec2 vec_b) {
    bvec2 res;
    ucvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a != b */
static bvec2 ucvec2_not_equal_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec2_not_equal_vec(UCVec2(vec_a), UCVec2(vec_b));
}

#endif //MATHC_VEC_UCVEC2_H
