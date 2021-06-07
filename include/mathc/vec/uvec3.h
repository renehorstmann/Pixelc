#ifndef MATHC_VEC_UVEC3_H
#define MATHC_VEC_UVEC3_H

#include "uvecn.h"
#include "../types/uint.h"
#include "../types/bool.h"


/** dst = unit_x */
static uvec3 uvec3_unit_x() {
    return (uvec3) {{1, 0, 0}};
}

/** dst = unit_y */
static uvec3 uvec3_unit_y() {
    return (uvec3) {{0, 1, 0}};
}

/** dst = unit_z */
static uvec3 uvec3_unit_z() {
    return (uvec3) {{0, 0, 1}};
}

/** uvec_a == uvec_b */
static bool uvec3_cmp(uvec3 a, uvec3 b) {
    return uvecN_cmp(a.v, b.v, 3);
}


/** dst = scalar */
static uvec3 uvec3_set(unsigned scalar) {
    uvec3 res;
    uvecN_set(res.v, scalar, 3);
    return res;
}

/** dst = (uvec3) v */
static uvec3 uvec3_cast_from_float(const float *v) {
    uvec3 res;
    uvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (uvec3) v */
static uvec3 uvec3_cast_from_double(const double *v) {
    uvec3 res;
    uvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (uvec3) v */
static uvec3 uvec3_cast_from_int(const int *v) {
    uvec3 res;
    uvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (uvec3) v */
static uvec3 uvec3_cast_from_char(const signed char *v) {
    uvec3 res;
    uvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (uvec3) v */
static uvec3 uvec3_cast_from_uchar(const unsigned char *v) {
    uvec3 res;
    uvecN_cast_into(res.v, v, 3);
    return res;
}

/** dst = (uvec3) v */
static uvec3 uvec3_cast_from_bool(const bool *v) {
    uvec3 res;
    uvecN_cast_into(res.v, v, 3);
    return res;
}


/** dst = a + b */
static uvec3 uvec3_add_vec(uvec3 vec_a, uvec3 vec_b) {
    uvec3 res;
    uvecN_add_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a + b */
static uvec3 uvec3_add_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_add_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a + b */
static uvec3 uvec3_add(uvec3 vec_a, unsigned scalar_b) {
    uvec3 res;
    uvecN_add(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a + b */
static uvec3 uvec3_add_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec3_add(UVec3(vec_a), scalar_b);
}


/** dst = a - b */
static uvec3 uvec3_sub_vec(uvec3 vec_a, uvec3 vec_b) {
    uvec3 res;
    uvecN_sub_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a - b */
static uvec3 uvec3_sub_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_sub_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a - b */
static uvec3 uvec3_sub(uvec3 vec_a, unsigned scalar_b) {
    uvec3 res;
    uvecN_sub(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a - b */
static uvec3 uvec3_sub_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec3_sub(UVec3(vec_a), scalar_b);
}


/** dst = a * b */
static uvec3 uvec3_scale_vec(uvec3 vec_a, uvec3 vec_b) {
    uvec3 res;
    uvecN_scale_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a * b */
static uvec3 uvec3_scale_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_scale_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a * b */
static uvec3 uvec3_scale(uvec3 vec_a, unsigned scalar_b) {
    uvec3 res;
    uvecN_scale(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a * b */
static uvec3 uvec3_scale_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec3_scale(UVec3(vec_a), scalar_b);
}


/** dst = a / b */
static uvec3 uvec3_div_vec(uvec3 vec_a, uvec3 vec_b) {
    uvec3 res;
    uvecN_div_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a / b */
static uvec3 uvec3_div_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_div_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a / b */
static uvec3 uvec3_div(uvec3 vec_a, unsigned scalar_b) {
    uvec3 res;
    uvecN_div(res.v, vec_a.v, scalar_b, 3);
    return res;
}
/** dst = a / b */
static uvec3 uvec3_div_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec3_div(UVec3(vec_a), scalar_b);
}


/** dst = x % y */
static uvec3 uvec3_mod(uvec3 vec_x, unsigned y) {
    uvec3 res;
    uvecN_mod(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = x % y */
static uvec3 uvec3_mod_v(const unsigned *vec_x, unsigned y) {
    return uvec3_mod(UVec3(vec_x), y);
}


/** dst = x % y */
static uvec3 uvec3_mod_vec(uvec3 vec_x, uvec3 vec_y) {
    uvec3 res;
    uvecN_mod_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = x % y */
static uvec3 uvec3_mod_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec3_mod_vec(UVec3(vec_x), UVec3(vec_y));
}


/** dst = a < b ? a : b */
static uvec3 uvec3_min(uvec3 vec_x, unsigned y) {
    uvec3 res;
    uvecN_min(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a < b ? a : b */
static uvec3 uvec3_min_v(const unsigned *vec_x, unsigned y) {
    return uvec3_min(UVec3(vec_x), y);
}


/** dst = a < b ? a : b */
static uvec3 uvec3_min_vec(uvec3 vec_x, uvec3 vec_y) {
    uvec3 res;
    uvecN_min_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a < b ? a : b */
static uvec3 uvec3_min_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec3_min_vec(UVec3(vec_x), UVec3(vec_y));
}


/** dst = a > b ? a : b */
static uvec3 uvec3_max(uvec3 vec_x, unsigned y) {
    uvec3 res;
    uvecN_max(res.v, vec_x.v, y, 3);
    return res;
}
/** dst = a > b ? a : b */
static uvec3 uvec3_max_v(const unsigned *vec_x, unsigned y) {
    return uvec3_max(UVec3(vec_x), y);
}


/** dst = a > b ? a : b */
static uvec3 uvec3_max_vec(uvec3 vec_x, uvec3 vec_y) {
    uvec3 res;
    uvecN_max_vec(res.v, vec_x.v, vec_y.v, 3);
    return res;
}
/** dst = a > b ? a : b */
static uvec3 uvec3_max_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec3_max_vec(UVec3(vec_x), UVec3(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static uvec3 uvec3_clamp(uvec3 vec_x, unsigned min, unsigned max) {
    uvec3 res;
    uvecN_clamp(res.v, vec_x.v, min, max, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static uvec3 uvec3_clamp_v(const unsigned *vec_x, unsigned min, unsigned max) {
    return uvec3_clamp(UVec3(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static uvec3 uvec3_clamp_vec(uvec3 vec_x, uvec3 vec_min, uvec3 vec_max) {
    uvec3 res;
    uvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 3);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static uvec3 uvec3_clamp_vec_v(const unsigned *vec_x, const unsigned *vec_min, const unsigned *vec_max) {
    return uvec3_clamp_vec(UVec3(vec_x), UVec3(vec_min), UVec3(vec_max));
}


/** dst = a * (1-t) + b * t */
static uvec3 uvec3_mix(uvec3 vec_a, uvec3 vec_b, float t) {
    uvec3 res;
    uvecN_mix(res.v, vec_a.v, vec_b.v, t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static uvec3 uvec3_mix_v(const unsigned *vec_a, const unsigned *vec_b, float t) {
    return uvec3_mix(UVec3(vec_a), UVec3(vec_b), t);
}


/** dst = a * (1-t) + b * t */
static uvec3 uvec3_mix_vec(uvec3 vec_a, uvec3 vec_b, const float *vec_t) {
    uvec3 res;
    uvecN_mix_vec(res.v, vec_a.v, vec_b.v, vec_t, 3);
    return res;
}
/** dst = a * (1-t) + b * t */
static uvec3 uvec3_mix_vec_v(const unsigned *vec_a, const unsigned *vec_b, const float *vec_t) {
    return uvec3_mix_vec(UVec3(vec_a), UVec3(vec_b), vec_t);
}


/** dst = x < edge ? 0 : 1 */
static uvec3 uvec3_step(uvec3 vec_x, unsigned edge) {
    uvec3 res;
    uvecN_step(res.v, vec_x.v, edge, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static uvec3 uvec3_step_v(const unsigned *vec_x, unsigned edge) {
    return uvec3_step(UVec3(vec_x), edge);
}


/** dst = x < edge ? 0 : 1 */
static uvec3 uvec3_step_vec(uvec3 vec_x, uvec3 vec_edge) {
    uvec3 res;
    uvecN_step_vec(res.v, vec_x.v, vec_edge.v, 3);
    return res;
}
/** dst = x < edge ? 0 : 1 */
static uvec3 uvec3_step_vec_v(const unsigned *vec_x, const unsigned *vec_edge) {
    return uvec3_step_vec(UVec3(vec_x), UVec3(vec_edge));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned uvec3_sum(uvec3 vec) {
    return uvecN_sum(vec.v, 3);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned uvec3_sum_v(const unsigned *vec) {
    return uvec3_sum(UVec3(vec));
}


/** returns a dot b */
static unsigned uvec3_dot(uvec3 vec_a, uvec3 vec_b) {
    return uvecN_dot(vec_a.v, vec_b.v, 3);
}
/** returns a dot b */
static unsigned uvec3_dot_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_dot(UVec3(vec_a), UVec3(vec_b));
}


/** returns ||vec||_3 */
static float uvec3_norm(uvec3 vec) {
    return uvecN_norm(vec.v, 3);
}
/** returns ||vec||_3 */
static float uvec3_norm_v(const unsigned *vec) {
    return uvec3_norm(UVec3(vec));
}



/** returns length of a vector, see uvecN_norm. Just here to match glsl */
static float uvec3_length(uvec3 vec) {
    return uvecN_length(vec.v, 3);
}
/** returns length of a vector, see uvecN_norm. Just here to match glsl */
static float uvec3_length_v(const unsigned *vec) {
    return uvec3_length(UVec3(vec));
}


/** returns norm(b-a) */
static float uvec3_distance(uvec3 vec_a, uvec3 vec_b) {
    return uvecN_distance(vec_a.v, vec_b.v, 3);
}
/** returns norm(b-a) */
static float uvec3_distance_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_distance(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a < b */
static bvec3 uvec3_less_than(uvec3 vec_a, unsigned b) {
    bvec3 res;
    uvecN_less_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a < b */
static bvec3 uvec3_less_than_v(const unsigned *vec_a, unsigned b) {
    return uvec3_less_than(UVec3(vec_a), b);
}


/** dst = a < b */
static bvec3 uvec3_less_than_vec(uvec3 vec_a, uvec3 vec_b) {
    bvec3 res;
    uvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a < b */
static bvec3 uvec3_less_than_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_less_than_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a <= b */
static bvec3 uvec3_less_than_equal(uvec3 vec_a, unsigned b) {
    bvec3 res;
    uvecN_less_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a <= b */
static bvec3 uvec3_less_than_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec3_less_than_equal(UVec3(vec_a), b);
}


/** dst = a <= b */
static bvec3 uvec3_less_than_equal_vec(uvec3 vec_a, uvec3 vec_b) {
    bvec3 res;
    uvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a <= b */
static bvec3 uvec3_less_than_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_less_than_equal_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a > b */
static bvec3 uvec3_greater_than(uvec3 vec_a, unsigned b) {
    bvec3 res;
    uvecN_greater_than(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a > b */
static bvec3 uvec3_greater_than_v(const unsigned *vec_a, unsigned b) {
    return uvec3_greater_than(UVec3(vec_a), b);
}


/** dst = a > b */
static bvec3 uvec3_greater_than_vec(uvec3 vec_a, uvec3 vec_b) {
    bvec3 res;
    uvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a > b */
static bvec3 uvec3_greater_than_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_greater_than_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a >= b */
static bvec3 uvec3_greater_than_equal(uvec3 vec_a, unsigned b) {
    bvec3 res;
    uvecN_greater_than_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a >= b */
static bvec3 uvec3_greater_than_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec3_greater_than_equal(UVec3(vec_a), b);
}


/** dst = a >= b */
static bvec3 uvec3_greater_than_equal_vec(uvec3 vec_a, uvec3 vec_b) {
    bvec3 res;
    uvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a >= b */
static bvec3 uvec3_greater_than_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_greater_than_equal_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a == b */
static bvec3 uvec3_equal(uvec3 vec_a, unsigned b) {
    bvec3 res;
    uvecN_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a == b */
static bvec3 uvec3_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec3_equal(UVec3(vec_a), b);
}


/** dst = a == b */
static bvec3 uvec3_equal_vec(uvec3 vec_a, uvec3 vec_b) {
    bvec3 res;
    uvecN_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a == b */
static bvec3 uvec3_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_equal_vec(UVec3(vec_a), UVec3(vec_b));
}


/** dst = a != b */
static bvec3 uvec3_not_equal(uvec3 vec_a, unsigned b) {
    bvec3 res;
    uvecN_not_equal(res.v, vec_a.v, b, 3);
    return res;
}
/** dst = a != b */
static bvec3 uvec3_not_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec3_not_equal(UVec3(vec_a), b);
}


/** dst = a != b */
static bvec3 uvec3_not_equal_vec(uvec3 vec_a, uvec3 vec_b) {
    bvec3 res;
    uvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a != b */
static bvec3 uvec3_not_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_not_equal_vec(UVec3(vec_a), UVec3(vec_b));
}



//
// in addition to vec2:
//

/** dst = a x b */
static uvec3 uvec3_cross(uvec3 vec_a, uvec3 vec_b) {
    uvec3 res;
    res.x = vec_a.y * vec_b.z - vec_a.z * vec_b.y;
    res.y = vec_a.z * vec_b.x - vec_a.x * vec_b.z;
    res.z = vec_a.x * vec_b.y - vec_a.y * vec_b.x;
    return res;
}
/** dst = a x b */
static uvec3 uvec3_cross_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec3_cross(UVec3(vec_a), UVec3(vec_b));
}


#endif //MATHC_VEC_UVEC3_H
