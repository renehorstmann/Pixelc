#ifndef MATHC_VEC_UCVEC3_H
#define MATHC_VEC_UCVEC3_H

#include "ucvecn.h"
#include "../types/uchar.h"
#include "../types/bool.h"


/** dst = unit_x */
static ucvec3 ucvec3_unit_x() {
    return (ucvec3) {{1, 0, 0}};
}

/** dst = unit_y */
static ucvec3 ucvec3_unit_y() {
    return (ucvec3) {{0, 1, 0}};
}

/** dst = unit_z */
static ucvec3 ucvec3_unit_z() {
    return (ucvec3) {{0, 0, 1}};
}

/** ucvec_a == ucvec_b */
static bool ucvec3_cmp(ucvec3 a, ucvec3 b) {
    return ucvecN_cmp(a.v, b.v, 3);
}


/** dst = scalar */
static ucvec3 ucvec3_set(unsigned char scalar) {
    ucvec3 res;
    ucvecN_set(res.v, scalar, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_float(const float *v) {
    ucvec3 res;
    ucvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_double(const double *v) {
    ucvec3 res;
    ucvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_int(const int *v) {
    ucvec3 res;
    ucvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_unsigned(const unsigned *v) {
    ucvec3 res;
    ucvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_char(const signed char *v) {
    ucvec3 res;
    ucvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (ucvec3) v */
static ucvec3 ucvec3_cast_from_bool(const bool *v) {
    ucvec3 res;
    ucvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = vec * 255 */
static ucvec3 ucvec3_cast_from_float_1(const float *v) {
    ucvec3 res;
    ucvecN_cast_from_float_1(res.v, v, 3);
    return res;
}

/** dst = vec * 255 */
static ucvec3 ucvec3_cast_from_double_1(const double *v) {
    ucvec3 res;
    ucvecN_cast_from_double_1(res.v, v, 3);
    return res;
}


/** dst = a + b */
static ucvec3 ucvec3_add_vec(ucvec3 vec_a, ucvec3 vec_b) {
    ucvec3 res;
    ucvecN_add_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a + b */
static ucvec3 ucvec3_add_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_add_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a + b */
static ucvec3 ucvec3_add(ucvec3 vec_a, unsigned char scalar_b) {
    ucvec3 res;
    ucvecN_add(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a + b */
static ucvec3 ucvec3_add_v(const unsigned char *vec_a, unsigned char scalar_b) {
    return ucvec3_add(UCVec3(vec_a), scalar_b);
}


/** dst = a - b */
static ucvec3 ucvec3_sub_vec(ucvec3 vec_a, ucvec3 vec_b) {
    ucvec3 res;
    ucvecN_sub_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a - b */
static ucvec3 ucvec3_sub_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_sub_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a - b */
static ucvec3 ucvec3_sub(ucvec3 vec_a, unsigned char scalar_b) {
    ucvec3 res;
    ucvecN_sub(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a - b */
static ucvec3 ucvec3_sub_v(const unsigned char *vec_a, unsigned char scalar_b) {
    return ucvec3_sub(UCVec3(vec_a), scalar_b);
}


/** dst = a * b */
static ucvec3 ucvec3_scale_vec(ucvec3 vec_a, ucvec3 vec_b) {
    ucvec3 res;
    ucvecN_scale_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a * b */
static ucvec3 ucvec3_scale_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_scale_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a * b */
static ucvec3 ucvec3_scale(ucvec3 vec_a, unsigned char scalar_b) {
    ucvec3 res;
    ucvecN_scale(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a * b */
static ucvec3 ucvec3_scale_v(const unsigned char *vec_a, unsigned char scalar_b) {
    return ucvec3_scale(UCVec3(vec_a), scalar_b);
}


/** dst = a / b */
static ucvec3 ucvec3_div_vec(ucvec3 vec_a, ucvec3 vec_b) {
    ucvec3 res;
    ucvecN_div_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a / b */
static ucvec3 ucvec3_div_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_div_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a / b */
static ucvec3 ucvec3_div(ucvec3 vec_a, unsigned char scalar_b) {
    ucvec3 res;
    ucvecN_div(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a / b */
static ucvec3 ucvec3_div_v(const unsigned char *vec_a, unsigned char scalar_b) {
    return ucvec3_div(UCVec3(vec_a), scalar_b);
}


/** dst = x % y */
static ucvec3 ucvec3_mod(ucvec3 vec_x, unsigned char y) {
    ucvec3 res;
    ucvecN_mod(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = x % y */
static ucvec3 ucvec3_mod_v(const unsigned char *vec_x, unsigned char y) {
    return ucvec3_mod(UCVec3(vec_x), y);
}


/** dst = x % y */
static ucvec3 ucvec3_mod_vec(ucvec3 vec_x, ucvec3 vec_y) {
    ucvec3 res;
    ucvecN_mod_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = x % y */
static ucvec3 ucvec3_mod_vec_v(const unsigned char *vec_x, const unsigned char *vec_y) {
    return ucvec3_mod_vec(UCVec3(vec_x), UCVec3(vec_y));
}


/** dst = a < b ? a : b */
static ucvec3 ucvec3_min(ucvec3 vec_x, unsigned char y) {
    ucvec3 res;
    ucvecN_min(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a < b ? a : b */
static ucvec3 ucvec3_min_v(const unsigned char *vec_x, unsigned char y) {
    return ucvec3_min(UCVec3(vec_x), y);
}


/** dst = a < b ? a : b */
static ucvec3 ucvec3_min_vec(ucvec3 vec_x, ucvec3 vec_y) {
    ucvec3 res;
    ucvecN_min_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a < b ? a : b */
static ucvec3 ucvec3_min_vec_v(const unsigned char *vec_x, const unsigned char *vec_y) {
    return ucvec3_min_vec(UCVec3(vec_x), UCVec3(vec_y));
}


/** dst = a > b ? a : b */
static ucvec3 ucvec3_max(ucvec3 vec_x, unsigned char y) {
    ucvec3 res;
    ucvecN_max(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a > b ? a : b */
static ucvec3 ucvec3_max_v(const unsigned char *vec_x, unsigned char y) {
    return ucvec3_max(UCVec3(vec_x), y);
}


/** dst = a > b ? a : b */
static ucvec3 ucvec3_max_vec(ucvec3 vec_x, ucvec3 vec_y) {
    ucvec3 res;
    ucvecN_max_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a > b ? a : b */
static ucvec3 ucvec3_max_vec_v(const unsigned char *vec_x, const unsigned char *vec_y) {
    return ucvec3_max_vec(UCVec3(vec_x), UCVec3(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec3 ucvec3_clamp(ucvec3 vec_x, unsigned char min, unsigned char max) {
    ucvec3 res;
    ucvecN_clamp(res.v, vec_x.v, min, max, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ucvec3 ucvec3_clamp_v(const unsigned char *vec_x, unsigned char min, unsigned char max) {
    return ucvec3_clamp(UCVec3(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec3 ucvec3_clamp_vec(ucvec3 vec_x, ucvec3 vec_min, ucvec3 vec_max) {
    ucvec3 res;
    ucvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ucvec3 ucvec3_clamp_vec_v(const unsigned char *vec_x, const unsigned char *vec_min, const unsigned char *vec_max) {
    return ucvec3_clamp_vec(UCVec3(vec_x), UCVec3(vec_min), UCVec3(vec_max));
}


/** dst = a * (1-t) + b * t */
static ucvec3 ucvec3_mix(ucvec3 vec_a, ucvec3 vec_b, float t) {
    ucvec3 res;
    ucvecN_mix(res.v, vec_a.v, vec_b.v, t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static ucvec3 ucvec3_mix_v(const unsigned char *vec_a, const unsigned char *vec_b, float t) {
    return ucvec3_mix(UCVec3(vec_a), UCVec3(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static ucvec3 ucvec3_mix_vec(ucvec3 vec_a, ucvec3 vec_b, const float *vec_t) {
    ucvec3 res;
    ucvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static ucvec3 ucvec3_mix_vec_v(const unsigned char *vec_a, const unsigned char *vec_b, const float *vec_t) {
    return ucvec3_mix_vec(UCVec3(vec_a), UCVec3(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static ucvec3 ucvec3_step(ucvec3 vec_x, unsigned char edge) {
    ucvec3 res;
    ucvecN_step(res.v, vec_x.v, edge, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ucvec3 ucvec3_step_v(const unsigned char *vec_x, unsigned char edge) {
    return ucvec3_step(UCVec3(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static ucvec3 ucvec3_step_vec(ucvec3 vec_x, ucvec3 vec_edge) {
    ucvec3 res;
    ucvecN_step_vec(res.v, vec_x.v, vec_edge.v, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ucvec3 ucvec3_step_vec_v(const unsigned char *vec_x, const unsigned char *vec_edge) {
    return ucvec3_step_vec(UCVec3(vec_x), UCVec3(vec_edge));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned char ucvec3_sum(ucvec3 vec) {
    return ucvecN_sum(vec.v, 3);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned char ucvec3_sum_v(const unsigned char *vec) {
    return ucvec3_sum(UCVec3(vec));
}


/** returns a dot b */
static unsigned char ucvec3_dot(ucvec3 vec_a, ucvec3 vec_b) {
    return ucvecN_dot(vec_a.v, vec_b.v, 3);
}
/** returns a dot b */
static unsigned char ucvec3_dot_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_dot(UCVec3(vec_a), UCVec3(vec_b));
}


/** returns ||vec||_3 */
static float ucvec3_norm(ucvec3 vec) {
    return ucvecN_norm(vec.v, 3);
}
/** returns ||vec||_3 */
static float ucvec3_norm_v(const unsigned char *vec) {
    return ucvec3_norm(UCVec3(vec));
}



/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static float ucvec3_length(ucvec3 vec) {
    return ucvecN_length(vec.v, 3);
}
/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static float ucvec3_length_v(const unsigned char *vec) {
    return ucvec3_length(UCVec3(vec));
}


/** returns norm(b-a) */
static float ucvec3_distance(ucvec3 vec_a, ucvec3 vec_b) {
    return ucvecN_distance(vec_a.v, vec_b.v, 3);
}
/** returns norm(b-a) */
static float ucvec3_distance_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_distance(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a < b */
static bvec3 ucvec3_less_than(ucvec3 vec_a, unsigned char b) {
    bvec3 res;
    ucvecN_less_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a < b */
static bvec3 ucvec3_less_than_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec3_less_than(UCVec3(vec_a), b);
}


/** dst = a < b */
static bvec3 ucvec3_less_than_vec(ucvec3 vec_a, ucvec3 vec_b) {
    bvec3 res;
    ucvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a < b */
static bvec3 ucvec3_less_than_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_less_than_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a <= b */
static bvec3 ucvec3_less_than_equal(ucvec3 vec_a, unsigned char b) {
    bvec3 res;
    ucvecN_less_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a <= b */
static bvec3 ucvec3_less_than_equal_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec3_less_than_equal(UCVec3(vec_a), b);
}


/** dst = a <= b */
static bvec3 ucvec3_less_than_equal_vec(ucvec3 vec_a, ucvec3 vec_b) {
    bvec3 res;
    ucvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a <= b */
static bvec3 ucvec3_less_than_equal_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_less_than_equal_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a > b */
static bvec3 ucvec3_greater_than(ucvec3 vec_a, unsigned char b) {
    bvec3 res;
    ucvecN_greater_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a > b */
static bvec3 ucvec3_greater_than_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec3_greater_than(UCVec3(vec_a), b);
}


/** dst = a > b */
static bvec3 ucvec3_greater_than_vec(ucvec3 vec_a, ucvec3 vec_b) {
    bvec3 res;
    ucvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a > b */
static bvec3 ucvec3_greater_than_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_greater_than_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a >= b */
static bvec3 ucvec3_greater_than_equal(ucvec3 vec_a, unsigned char b) {
    bvec3 res;
    ucvecN_greater_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a >= b */
static bvec3 ucvec3_greater_than_equal_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec3_greater_than_equal(UCVec3(vec_a), b);
}


/** dst = a >= b */
static bvec3 ucvec3_greater_than_equal_vec(ucvec3 vec_a, ucvec3 vec_b) {
    bvec3 res;
    ucvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a >= b */
static bvec3 ucvec3_greater_than_equal_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_greater_than_equal_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a == b */
static bvec3 ucvec3_equal(ucvec3 vec_a, unsigned char b) {
    bvec3 res;
    ucvecN_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a == b */
static bvec3 ucvec3_equal_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec3_equal(UCVec3(vec_a), b);
}


/** dst = a == b */
static bvec3 ucvec3_equal_vec(ucvec3 vec_a, ucvec3 vec_b) {
    bvec3 res;
    ucvecN_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a == b */
static bvec3 ucvec3_equal_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_equal_vec(UCVec3(vec_a), UCVec3(vec_b));
}


/** dst = a != b */
static bvec3 ucvec3_not_equal(ucvec3 vec_a, unsigned char b) {
    bvec3 res;
    ucvecN_not_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a != b */
static bvec3 ucvec3_not_equal_v(const unsigned char *vec_a, unsigned char b) {
    return ucvec3_not_equal(UCVec3(vec_a), b);
}


/** dst = a != b */
static bvec3 ucvec3_not_equal_vec(ucvec3 vec_a, ucvec3 vec_b) {
    bvec3 res;
    ucvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a != b */
static bvec3 ucvec3_not_equal_vec_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_not_equal_vec(UCVec3(vec_a), UCVec3(vec_b));
}



//
// in addition to vec2:
//

/** dst = a x b */
static ucvec3 ucvec3_cross(ucvec3 vec_a, ucvec3 vec_b) {
    ucvec3 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    return res;
}
/** dst = a x b */
static ucvec3 ucvec3_cross_v(const unsigned char *vec_a, const unsigned char *vec_b) {
    return ucvec3_cross(UCVec3(vec_a), UCVec3(vec_b));
}


#endif //MATHC_VEC_UCVEC3_H
