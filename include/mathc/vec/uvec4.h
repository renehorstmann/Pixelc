#ifndef MATHC_VEC_UVEC4_H
#define MATHC_VEC_UVEC4_H

#include "uvecn.h"
#include "../types/uint.h"
#include "../types/bool.h"


/** dst = unit_x */
static uvec4 uvec4_unit_x() {
    return (uvec4) {{1, 0, 0, 0}};
}

/** dst = unit_y */
static uvec4 uvec4_unit_y() {
    return (uvec4) {{0, 1, 0, 0}};
}

/** dst = unit_z */
static uvec4 uvec4_unit_z() {
    return (uvec4) {{0, 0, 1, 0}};
}

/** dst = unit_w */
static uvec4 uvec4_unit_w() {
    return (uvec4) {{0, 0, 0, 1}};
}

/** uvec_a == uvec_b */
static bool uvec4_cmp(uvec4 a, uvec4 b) {
    return uvecN_cmp(a.v, b.v, 4);
}


/** dst = scalar */
static uvec4 uvec4_set(unsigned scalar) {
    uvec4 res;
    uvecN_set(res.v, scalar, 4);
    return res;
}

/** dst = (uvec4) v */
static uvec4 uvec4_cast_from_float(const float *v) {
    uvec4 res;
    uvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (uvec4) v */
static uvec4 uvec4_cast_from_double(const double *v) {
    uvec4 res;
    uvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (uvec4) v */
static uvec4 uvec4_cast_from_int(const int *v) {
    uvec4 res;
    uvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (uvec4) v */
static uvec4 uvec4_cast_from_char(const char *v) {
    uvec4 res;
    uvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (uvec4) v */
static uvec4 uvec4_cast_from_uchar(const unsigned char *v) {
    uvec4 res;
    uvecN_cast_into(res.v, v, 4);
    return res;
}

/** dst = (uvec4) v */
static uvec4 uvec4_cast_from_bool(const bool *v) {
    uvec4 res;
    uvecN_cast_into(res.v, v, 4);
    return res;
}


/** dst = a + b */
static uvec4 uvec4_add_vec(uvec4 vec_a, uvec4 vec_b) {
    uvec4 res;
    uvecN_add_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a + b */
static uvec4 uvec4_add_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_add_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a + b */
static uvec4 uvec4_add(uvec4 vec_a, unsigned scalar_b) {
    uvec4 res;
    uvecN_add(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a + b */
static uvec4 uvec4_add_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec4_add(UVec4(vec_a), scalar_b);
}


/** dst = a - b */
static uvec4 uvec4_sub_vec(uvec4 vec_a, uvec4 vec_b) {
    uvec4 res;
    uvecN_sub_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a - b */
static uvec4 uvec4_sub_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_sub_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a - b */
static uvec4 uvec4_sub(uvec4 vec_a, unsigned scalar_b) {
    uvec4 res;
    uvecN_sub(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a - b */
static uvec4 uvec4_sub_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec4_sub(UVec4(vec_a), scalar_b);
}


/** dst = a * b */
static uvec4 uvec4_scale_vec(uvec4 vec_a, uvec4 vec_b) {
    uvec4 res;
    uvecN_scale_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a * b */
static uvec4 uvec4_scale_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_scale_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a * b */
static uvec4 uvec4_scale(uvec4 vec_a, unsigned scalar_b) {
    uvec4 res;
    uvecN_scale(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a * b */
static uvec4 uvec4_scale_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec4_scale(UVec4(vec_a), scalar_b);
}


/** dst = a / b */
static uvec4 uvec4_div_vec(uvec4 vec_a, uvec4 vec_b) {
    uvec4 res;
    uvecN_div_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a / b */
static uvec4 uvec4_div_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_div_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a / b */
static uvec4 uvec4_div(uvec4 vec_a, unsigned scalar_b) {
    uvec4 res;
    uvecN_div(res.v, vec_a.v, scalar_b, 4);
    return res;
}
/** dst = a / b */
static uvec4 uvec4_div_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec4_div(UVec4(vec_a), scalar_b);
}



/** dst = x % y */
static uvec4 uvec4_mod(uvec4 vec_x, unsigned y) {
    uvec4 res;
    uvecN_mod(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = x % y */
static uvec4 uvec4_mod_v(const unsigned *vec_x, unsigned y) {
    return uvec4_mod(UVec4(vec_x), y);
}


/** dst = x % y */
static uvec4 uvec4_mod_vec(uvec4 vec_x, uvec4 vec_y) {
    uvec4 res;
    uvecN_mod_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = x % y */
static uvec4 uvec4_mod_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec4_mod_vec(UVec4(vec_x), UVec4(vec_y));
}


/** dst = a < b ? a : b */
static uvec4 uvec4_min(uvec4 vec_x, unsigned y) {
    uvec4 res;
    uvecN_min(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a < b ? a : b */
static uvec4 uvec4_min_v(const unsigned *vec_x, unsigned y) {
    return uvec4_min(UVec4(vec_x), y);
}


/** dst = a < b ? a : b */
static uvec4 uvec4_min_vec(uvec4 vec_x, uvec4 vec_y) {
    uvec4 res;
    uvecN_min_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a < b ? a : b */
static uvec4 uvec4_min_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec4_min_vec(UVec4(vec_x), UVec4(vec_y));
}


/** dst = a > b ? a : b */
static uvec4 uvec4_max(uvec4 vec_x, unsigned y) {
    uvec4 res;
    uvecN_max(res.v, vec_x.v, y, 4);
    return res;
}
/** dst = a > b ? a : b */
static uvec4 uvec4_max_v(const unsigned *vec_x, unsigned y) {
    return uvec4_max(UVec4(vec_x), y);
}


/** dst = a > b ? a : b */
static uvec4 uvec4_max_vec(uvec4 vec_x, uvec4 vec_y) {
    uvec4 res;
    uvecN_max_vec(res.v, vec_x.v, vec_y.v, 4);
    return res;
}
/** dst = a > b ? a : b */
static uvec4 uvec4_max_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec4_max_vec(UVec4(vec_x), UVec4(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static uvec4 uvec4_clamp(uvec4 vec_x, unsigned min, unsigned max) {
    uvec4 res;
    uvecN_clamp(res.v, vec_x.v, min, max, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static uvec4 uvec4_clamp_v(const unsigned *vec_x, unsigned min, unsigned max) {
    return uvec4_clamp(UVec4(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static uvec4 uvec4_clamp_vec(uvec4 vec_x, uvec4 vec_min, uvec4 vec_max) {
    uvec4 res;
    uvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 4);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static uvec4 uvec4_clamp_vec_v(const unsigned *vec_x, const unsigned *vec_min, const unsigned *vec_max) {
    return uvec4_clamp_vec(UVec4(vec_x), UVec4(vec_min), UVec4(vec_max));
}


/** dst = a * (1-t) + b * t */
static uvec4 uvec4_mix(uvec4 vec_a, uvec4 vec_b, float t) {
    uvec4 res;
    uvecN_mix(res.v, vec_a.v, vec_b.v, t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static uvec4 uvec4_mix_v(const unsigned *vec_a, const unsigned *vec_b, float t) {
    return uvec4_mix(UVec4(vec_a), UVec4(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static uvec4 uvec4_mix_vec(uvec4 vec_a, uvec4 vec_b, const float *vec_t) {
    uvec4 res;
    uvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 4);
    return res;
}
/** dst = a * (1-t) + b * t */
static uvec4 uvec4_mix_vec_v(const unsigned *vec_a, const unsigned *vec_b, const float *vec_t) {
    return uvec4_mix_vec(UVec4(vec_a), UVec4(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static uvec4 uvec4_step(uvec4 vec_x, unsigned edge) {
    uvec4 res;
    uvecN_step(res.v, vec_x.v, edge, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static uvec4 uvec4_step_v(const unsigned *vec_x, unsigned edge) {
    return uvec4_step(UVec4(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static uvec4 uvec4_step_vec(uvec4 vec_x, uvec4 vec_edge) {
    uvec4 res;
    uvecN_step_vec(res.v, vec_x.v, vec_edge.v, 4);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static uvec4 uvec4_step_vec_v(const unsigned *vec_x, const unsigned *vec_edge) {
    return uvec4_step_vec(UVec4(vec_x), UVec4(vec_edge));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned uvec4_sum(uvec4 vec) {
    return uvecN_sum(vec.v, 4);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned uvec4_sum_v(const unsigned *vec) {
    return uvec4_sum(UVec4(vec));
}


/** returns a dot b */
static unsigned uvec4_dot(uvec4 vec_a, uvec4 vec_b) {
    return uvecN_dot(vec_a.v, vec_b.v, 4);
}
/** returns a dot b */
static unsigned uvec4_dot_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_dot(UVec4(vec_a), UVec4(vec_b));
}


/** returns ||vec||_4 */
static float uvec4_norm(uvec4 vec) {
    return uvecN_norm(vec.v, 4);
}
/** returns ||vec||_4 */
static float uvec4_norm_v(const unsigned *vec) {
    return uvec4_norm(UVec4(vec));
}



/** returns length of a vector, see uvecN_norm. Just here to match glsl */
static float uvec4_length(uvec4 vec) {
    return uvecN_length(vec.v, 4);
}
/** returns length of a vector, see uvecN_norm. Just here to match glsl */
static float uvec4_length_v(const unsigned *vec) {
    return uvec4_length(UVec4(vec));
}


/** returns norm(b-a) */
static float uvec4_distance(uvec4 vec_a, uvec4 vec_b) {
    return uvecN_distance(vec_a.v, vec_b.v, 4);
}
/** returns norm(b-a) */
static float uvec4_distance_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_distance(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a < b */
static bvec4 uvec4_less_than(uvec4 vec_a, unsigned b) {
    bvec4 res;
    uvecN_less_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a < b */
static bvec4 uvec4_less_than_v(const unsigned *vec_a, unsigned b) {
    return uvec4_less_than(UVec4(vec_a), b);
}


/** dst = a < b */
static bvec4 uvec4_less_than_vec(uvec4 vec_a, uvec4 vec_b) {
    bvec4 res;
    uvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a < b */
static bvec4 uvec4_less_than_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_less_than_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a <= b */
static bvec4 uvec4_less_than_equal(uvec4 vec_a, unsigned b) {
    bvec4 res;
    uvecN_less_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a <= b */
static bvec4 uvec4_less_than_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec4_less_than_equal(UVec4(vec_a), b);
}


/** dst = a <= b */
static bvec4 uvec4_less_than_equal_vec(uvec4 vec_a, uvec4 vec_b) {
    bvec4 res;
    uvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a <= b */
static bvec4 uvec4_less_than_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_less_than_equal_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a > b */
static bvec4 uvec4_greater_than(uvec4 vec_a, unsigned b) {
    bvec4 res;
    uvecN_greater_than(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a > b */
static bvec4 uvec4_greater_than_v(const unsigned *vec_a, unsigned b) {
    return uvec4_greater_than(UVec4(vec_a), b);
}


/** dst = a > b */
static bvec4 uvec4_greater_than_vec(uvec4 vec_a, uvec4 vec_b) {
    bvec4 res;
    uvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a > b */
static bvec4 uvec4_greater_than_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_greater_than_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a >= b */
static bvec4 uvec4_greater_than_equal(uvec4 vec_a, unsigned b) {
    bvec4 res;
    uvecN_greater_than_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a >= b */
static bvec4 uvec4_greater_than_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec4_greater_than_equal(UVec4(vec_a), b);
}


/** dst = a >= b */
static bvec4 uvec4_greater_than_equal_vec(uvec4 vec_a, uvec4 vec_b) {
    bvec4 res;
    uvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a >= b */
static bvec4 uvec4_greater_than_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_greater_than_equal_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a == b */
static bvec4 uvec4_equal(uvec4 vec_a, unsigned b) {
    bvec4 res;
    uvecN_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a == b */
static bvec4 uvec4_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec4_equal(UVec4(vec_a), b);
}


/** dst = a == b */
static bvec4 uvec4_equal_vec(uvec4 vec_a, uvec4 vec_b) {
    bvec4 res;
    uvecN_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a == b */
static bvec4 uvec4_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_equal_vec(UVec4(vec_a), UVec4(vec_b));
}


/** dst = a != b */
static bvec4 uvec4_not_equal(uvec4 vec_a, unsigned b) {
    bvec4 res;
    uvecN_not_equal(res.v, vec_a.v, b, 4);
    return res;
}
/** dst = a != b */
static bvec4 uvec4_not_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec4_not_equal(UVec4(vec_a), b);
}


/** dst = a != b */
static bvec4 uvec4_not_equal_vec(uvec4 vec_a, uvec4 vec_b) {
    bvec4 res;
    uvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a != b */
static bvec4 uvec4_not_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_not_equal_vec(UVec4(vec_a), UVec4(vec_b));
}



//
// in addition to vec2:
//


/** dst = a x b , dst.w = 0 */
static uvec4 uvec4_cross(uvec4 vec_a, uvec4 vec_b) {
    uvec4 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    res.w = 0;
    return res;
}
/** dst = a x b , dst.w = 0 */
static uvec4 uvec4_cross_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec4_cross(UVec4(vec_a), UVec4(vec_b));
}


#endif //MATHC_VEC_UVEC4_H
