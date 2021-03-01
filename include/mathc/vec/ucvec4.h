#ifndef MATHC_VEC_UCVEC4_H
#define MATHC_VEC_UCVEC4_H

#include "ucvecn.h"
#include "../types/uchar.h"
#include "../types/bool.h"


/** dst = unit_x */
static ucvec4 ucvec4_unit_x() {
    return (ucvec4) {{1, 0, 0, 0}};
}

/** dst = unit_y */
static ucvec4 ucvec4_unit_y() {
    return (ucvec4) {{0, 1, 0, 0}};
}

/** dst = unit_z */
static ucvec4 ucvec4_unit_z() {
    return (ucvec4) {{0, 0, 1, 0}};
}

/** dst = unit_w */
static ucvec4 ucvec4_unit_w() {
    return (ucvec4) {{0, 0, 0, 1}};
}

/** ucvec_a == ucvec_b */
static bool ucvec4_cmp(ucvec4 a, ucvec4 b) {
    return ucvecN_cmp(a.v, b.v, 4);
}


/** dst = scalar */
static ucvec4 ucvec4_set(uchar scalar) {
    ucvec4 res;
    ucvecN_set(res.v, scalar, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_float(const float *v) {
    ucvec4 res;
    ucvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_double(const double *v) {
    ucvec4 res;
    ucvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_int(const int *v) {
    ucvec4 res;
    ucvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_unsigned(const unsigned *v) {
    ucvec4 res;
    ucvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_char(const char *v) {
    ucvec4 res;
    ucvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (ucvec4) v */
static ucvec4 ucvec4_cast_from_bool(const bool *v) {
    ucvec4 res;
    ucvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = vec * 255 */
static ucvec4 ucvec4_cast_from_float_1(const float *v) {
    ucvec4 res;
    ucvecN_cast_from_float_1(res.v, v, 4);
    return res;
}

/** dst = vec * 255 */
static ucvec4 ucvec4_cast_from_double_1(const double *v) {
    ucvec4 res;
    ucvecN_cast_from_double_1(res.v, v, 4);
    return res;
}


/** dst = a + b */
static ucvec4 ucvec4_add_vec(ucvec4 vec_a, ucvec4 vec_b) {
    ucvec4 res;
    ucvecN_add_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a + b */
static ucvec4 ucvec4_add_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_add_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a + b */
static ucvec4 ucvec4_add(ucvec4 vec_a, uchar scalar_b) {
    ucvec4 res;
    ucvecN_add(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a + b */
static ucvec4 ucvec4_add_v(const uchar *vec_a, uchar scalar_b) {
    return ucvec4_add(UCVec4(vec_a), scalar_b);
}


/** dst = a - b */
static ucvec4 ucvec4_sub_vec(ucvec4 vec_a, ucvec4 vec_b) {
    ucvec4 res;
    ucvecN_sub_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a - b */
static ucvec4 ucvec4_sub_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_sub_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a - b */
static ucvec4 ucvec4_sub(ucvec4 vec_a, uchar scalar_b) {
    ucvec4 res;
    ucvecN_sub(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a - b */
static ucvec4 ucvec4_sub_v(const uchar *vec_a, uchar scalar_b) {
    return ucvec4_sub(UCVec4(vec_a), scalar_b);
}


/** dst = a * b */
static ucvec4 ucvec4_scale_vec(ucvec4 vec_a, ucvec4 vec_b) {
    ucvec4 res;
    ucvecN_scale_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a * b */
static ucvec4 ucvec4_scale_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_scale_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a * b */
static ucvec4 ucvec4_scale(ucvec4 vec_a, uchar scalar_b) {
    ucvec4 res;
    ucvecN_scale(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a * b */
static ucvec4 ucvec4_scale_v(const uchar *vec_a, uchar scalar_b) {
    return ucvec4_scale(UCVec4(vec_a), scalar_b);
}


/** dst = a / b */
static ucvec4 ucvec4_div_vec(ucvec4 vec_a, ucvec4 vec_b) {
    ucvec4 res;
    ucvecN_div_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a / b */
static ucvec4 ucvec4_div_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_div_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a / b */
static ucvec4 ucvec4_div(ucvec4 vec_a, uchar scalar_b) {
    ucvec4 res;
    ucvecN_div(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a / b */
static ucvec4 ucvec4_div_v(const uchar *vec_a, uchar scalar_b) {
    return ucvec4_div(UCVec4(vec_a), scalar_b);
}



/** dst = x % y */
static ucvec4 ucvec4_mod(ucvec4 vec_x, uchar y) {
    ucvec4 res;
    ucvecN_mod(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = x % y */
static ucvec4 ucvec4_mod_v(const uchar *vec_x, uchar y) {
    return ucvec4_mod(UCVec4(vec_x), y);
}


/** dst = x % y */
static ucvec4 ucvec4_mod_vec(ucvec4 vec_x, ucvec4 vec_y) {
    ucvec4 res;
    ucvecN_mod_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = x % y */
static ucvec4 ucvec4_mod_vec_v(const uchar *vec_x, const uchar *vec_y) {
    return ucvec4_mod_vec(UCVec4(vec_x), UCVec4(vec_y));
}


/** dst = a < b ? a : b */
static ucvec4 ucvec4_min(ucvec4 vec_x, uchar y) {
    ucvec4 res;
    ucvecN_min(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a < b ? a : b */
static ucvec4 ucvec4_min_v(const uchar *vec_x, uchar y) {
    return ucvec4_min(UCVec4(vec_x), y);
}


/** dst = a < b ? a : b */
static ucvec4 ucvec4_min_vec(ucvec4 vec_x, ucvec4 vec_y) {
    ucvec4 res;
    ucvecN_min_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a < b ? a : b */
static ucvec4 ucvec4_min_vec_v(const uchar *vec_x, const uchar *vec_y) {
    return ucvec4_min_vec(UCVec4(vec_x), UCVec4(vec_y));
}


/** dst = a > b ? a : b */
static ucvec4 ucvec4_max(ucvec4 vec_x, uchar y) {
    ucvec4 res;
    ucvecN_max(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a > b ? a : b */
static ucvec4 ucvec4_max_v(const uchar *vec_x, uchar y) {
    return ucvec4_max(UCVec4(vec_x), y);
}


/** dst = a > b ? a : b */
static ucvec4 ucvec4_max_vec(ucvec4 vec_x, ucvec4 vec_y) {
    ucvec4 res;
    ucvecN_max_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a > b ? a : b */
static ucvec4 ucvec4_max_vec_v(const uchar *vec_x, const uchar *vec_y) {
    return ucvec4_max_vec(UCVec4(vec_x), UCVec4(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec4 ucvec4_clamp(ucvec4 vec_x, uchar min, uchar max) {
    ucvec4 res;
    ucvecN_clamp(res.v, vec_x.v, min, max, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ucvec4 ucvec4_clamp_v(const uchar *vec_x, uchar min, uchar max) {
    return ucvec4_clamp(UCVec4(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static ucvec4 ucvec4_clamp_vec(ucvec4 vec_x, ucvec4 vec_min, ucvec4 vec_max) {
    ucvec4 res;
    ucvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static ucvec4 ucvec4_clamp_vec_v(const uchar *vec_x, const uchar *vec_min, const uchar *vec_max) {
    return ucvec4_clamp_vec(UCVec4(vec_x), UCVec4(vec_min), UCVec4(vec_max));
}


/** dst = a * (1-t) + b * t */
static ucvec4 ucvec4_mix(ucvec4 vec_a, ucvec4 vec_b, float t) {
    ucvec4 res;
    ucvecN_mix(res.v, vec_a.v, vec_b.v, t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static ucvec4 ucvec4_mix_v(const uchar *vec_a, const uchar *vec_b, float t) {
    return ucvec4_mix(UCVec4(vec_a), UCVec4(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static ucvec4 ucvec4_mix_vec(ucvec4 vec_a, ucvec4 vec_b, const float *vec_t) {
    ucvec4 res;
    ucvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static ucvec4 ucvec4_mix_vec_v(const uchar *vec_a, const uchar *vec_b, const float *vec_t) {
    return ucvec4_mix_vec(UCVec4(vec_a), UCVec4(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static ucvec4 ucvec4_step(ucvec4 vec_x, uchar edge) {
    ucvec4 res;
    ucvecN_step(res.v, vec_x.v, edge, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ucvec4 ucvec4_step_v(const uchar *vec_x, uchar edge) {
    return ucvec4_step(UCVec4(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static ucvec4 ucvec4_step_vec(ucvec4 vec_x, ucvec4 vec_edge) {
    ucvec4 res;
    ucvecN_step_vec(res.v, vec_x.v, vec_edge.v, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static ucvec4 ucvec4_step_vec_v(const uchar *vec_x, const uchar *vec_edge) {
    return ucvec4_step_vec(UCVec4(vec_x), UCVec4(vec_edge));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static uchar ucvec4_sum(ucvec4 vec) {
    return ucvecN_sum(vec.v, 4);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static uchar ucvec4_sum_v(const uchar *vec) {
    return ucvec4_sum(UCVec4(vec));
}


/** returns a dot b */
static uchar ucvec4_dot(ucvec4 vec_a, ucvec4 vec_b) {
    return ucvecN_dot(vec_a.v, vec_b.v, 4);
}
/** returns a dot b */
static uchar ucvec4_dot_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_dot(UCVec4(vec_a), UCVec4(vec_b));
}


/** returns ||vec||_4 */
static float ucvec4_norm(ucvec4 vec) {
    return ucvecN_norm(vec.v, 4);
}
/** returns ||vec||_4 */
static float ucvec4_norm_v(const uchar *vec) {
    return ucvec4_norm(UCVec4(vec));
}



/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static float ucvec4_length(ucvec4 vec) {
    return ucvecN_length(vec.v, 4);
}
/** returns length of a vector, see ucvecN_norm. Just here to match glsl */
static float ucvec4_length_v(const uchar *vec) {
    return ucvec4_length(UCVec4(vec));
}


/** returns norm(b-a) */
static float ucvec4_distance(ucvec4 vec_a, ucvec4 vec_b) {
    return ucvecN_distance(vec_a.v, vec_b.v, 4);
}
/** returns norm(b-a) */
static float ucvec4_distance_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_distance(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a < b */
static bvec4 ucvec4_less_than(ucvec4 vec_a, uchar b) {
    bvec4 res;
    ucvecN_less_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a < b */
static bvec4 ucvec4_less_than_v(const uchar *vec_a, uchar b) {
    return ucvec4_less_than(UCVec4(vec_a), b);
}


/** dst = a < b */
static bvec4 ucvec4_less_than_vec(ucvec4 vec_a, ucvec4 vec_b) {
    bvec4 res;
    ucvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a < b */
static bvec4 ucvec4_less_than_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_less_than_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a <= b */
static bvec4 ucvec4_less_than_equal(ucvec4 vec_a, uchar b) {
    bvec4 res;
    ucvecN_less_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a <= b */
static bvec4 ucvec4_less_than_equal_v(const uchar *vec_a, uchar b) {
    return ucvec4_less_than_equal(UCVec4(vec_a), b);
}


/** dst = a <= b */
static bvec4 ucvec4_less_than_equal_vec(ucvec4 vec_a, ucvec4 vec_b) {
    bvec4 res;
    ucvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a <= b */
static bvec4 ucvec4_less_than_equal_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_less_than_equal_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a > b */
static bvec4 ucvec4_greater_than(ucvec4 vec_a, uchar b) {
    bvec4 res;
    ucvecN_greater_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a > b */
static bvec4 ucvec4_greater_than_v(const uchar *vec_a, uchar b) {
    return ucvec4_greater_than(UCVec4(vec_a), b);
}


/** dst = a > b */
static bvec4 ucvec4_greater_than_vec(ucvec4 vec_a, ucvec4 vec_b) {
    bvec4 res;
    ucvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a > b */
static bvec4 ucvec4_greater_than_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_greater_than_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a >= b */
static bvec4 ucvec4_greater_than_equal(ucvec4 vec_a, uchar b) {
    bvec4 res;
    ucvecN_greater_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a >= b */
static bvec4 ucvec4_greater_than_equal_v(const uchar *vec_a, uchar b) {
    return ucvec4_greater_than_equal(UCVec4(vec_a), b);
}


/** dst = a >= b */
static bvec4 ucvec4_greater_than_equal_vec(ucvec4 vec_a, ucvec4 vec_b) {
    bvec4 res;
    ucvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a >= b */
static bvec4 ucvec4_greater_than_equal_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_greater_than_equal_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a == b */
static bvec4 ucvec4_equal(ucvec4 vec_a, uchar b) {
    bvec4 res;
    ucvecN_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a == b */
static bvec4 ucvec4_equal_v(const uchar *vec_a, uchar b) {
    return ucvec4_equal(UCVec4(vec_a), b);
}


/** dst = a == b */
static bvec4 ucvec4_equal_vec(ucvec4 vec_a, ucvec4 vec_b) {
    bvec4 res;
    ucvecN_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a == b */
static bvec4 ucvec4_equal_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_equal_vec(UCVec4(vec_a), UCVec4(vec_b));
}


/** dst = a != b */
static bvec4 ucvec4_not_equal(ucvec4 vec_a, uchar b) {
    bvec4 res;
    ucvecN_not_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a != b */
static bvec4 ucvec4_not_equal_v(const uchar *vec_a, uchar b) {
    return ucvec4_not_equal(UCVec4(vec_a), b);
}


/** dst = a != b */
static bvec4 ucvec4_not_equal_vec(ucvec4 vec_a, ucvec4 vec_b) {
    bvec4 res;
    ucvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a != b */
static bvec4 ucvec4_not_equal_vec_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_not_equal_vec(UCVec4(vec_a), UCVec4(vec_b));
}



//
// in addition to vec2:
//


/** dst = a x b , dst.w = 0 */
static ucvec4 ucvec4_cross(ucvec4 vec_a, ucvec4 vec_b) {
    ucvec4 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    res.w = 0;
    return res;
}
/** dst = a x b , dst.w = 0 */
static ucvec4 ucvec4_cross_v(const uchar *vec_a, const uchar *vec_b) {
    return ucvec4_cross(UCVec4(vec_a), UCVec4(vec_b));
}


#endif //MATHC_VEC_UCVEC4_H
