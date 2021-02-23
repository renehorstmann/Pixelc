#ifndef MATHC_VEC_UVEC2_H
#define MATHC_VEC_UVEC2_H

#include "uvecn.h"
#include "../types/uint.h"
#include "../types/bool.h"


/** dst = unit_x */
static uvec2 uvec2_unit_x() {
    return (uvec2) {{1, 0}};
}

/** dst = unit_y */
static uvec2 uvec2_unit_y() {
    return (uvec2) {{0, 1}};
}


/** dst = scalar */
static uvec2 uvec2_set(unsigned scalar) {
    uvec2 res;
    uvecN_set(res.v, scalar, 2);
    return res;
}


/** dst = (uvec2) v */
static uvec2 uvec2_cast_from_float(const float *v) {
    uvec2 res;
    uvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (uvec2) v */
static uvec2 uvec2_cast_from_double(const double *v) {
    uvec2 res;
    uvecN_cast_into(res.v, v, 2);
    return res;
}

/** dst = (uvec2) v */
static uvec2 uvec2_cast_from_int(const int *v) {
    uvec2 res;
    uvecN_cast_into(res.v, v, 2);
    return res;
}


/** dst = (uvec2) v */
static uvec2 uvec2_cast_from_bool(const bool *v) {
    uvec2 res;
    uvecN_cast_into(res.v, v, 2);
    return res;
}


/** dst = a + b */
static uvec2 uvec2_add_vec(uvec2 vec_a, uvec2 vec_b) {
    uvec2 res;
    uvecN_add_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a + b */
static uvec2 uvec2_add_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_add_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a + b */
static uvec2 uvec2_add(uvec2 vec_a, unsigned scalar_b) {
    uvec2 res;
    uvecN_add(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a + b */
static uvec2 uvec2_add_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec2_add(UVec2(vec_a), scalar_b);
}


/** dst = a - b */
static uvec2 uvec2_sub_vec(uvec2 vec_a, uvec2 vec_b) {
    uvec2 res;
    uvecN_sub_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a - b */
static uvec2 uvec2_sub_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_sub_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a - b */
static uvec2 uvec2_sub(uvec2 vec_a, unsigned scalar_b) {
    uvec2 res;
    uvecN_sub(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a - b */
static uvec2 uvec2_sub_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec2_sub(UVec2(vec_a), scalar_b);
}


/** dst = a * b */
static uvec2 uvec2_scale_vec(uvec2 vec_a, uvec2 vec_b) {
    uvec2 res;
    uvecN_scale_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a * b */
static uvec2 uvec2_scale_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_scale_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a * b */
static uvec2 uvec2_scale(uvec2 vec_a, unsigned scalar_b) {
    uvec2 res;
    uvecN_scale(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a * b */
static uvec2 uvec2_scale_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec2_scale(UVec2(vec_a), scalar_b);
}


/** dst = a / b */
static uvec2 uvec2_div_vec(uvec2 vec_a, uvec2 vec_b) {
    uvec2 res;
    uvecN_div_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a / b */
static uvec2 uvec2_div_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_div_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a / b */
static uvec2 uvec2_div(uvec2 vec_a, unsigned scalar_b) {
    uvec2 res;
    uvecN_div(res.v, vec_a.v, scalar_b, 2);
    return res;
}
/** dst = a / b */
static uvec2 uvec2_div_v(const unsigned *vec_a, unsigned scalar_b) {
    return uvec2_div(UVec2(vec_a), scalar_b);
}


/** dst = x % y */
static uvec2 uvec2_mod(uvec2 vec_x, unsigned y) {
    uvec2 res;
    uvecN_mod(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = x % y */
static uvec2 uvec2_mod_v(const unsigned *vec_x, unsigned y) {
    return uvec2_mod(UVec2(vec_x), y);
}


/** dst = x % y */
static uvec2 uvec2_mod_vec(uvec2 vec_x, uvec2 vec_y) {
    uvec2 res;
    uvecN_mod_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = x % y */
static uvec2 uvec2_mod_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec2_mod_vec(UVec2(vec_x), UVec2(vec_y));
}


/** dst = a < b ? a : b */
static uvec2 uvec2_min(uvec2 vec_x, unsigned y) {
    uvec2 res;
    uvecN_min(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a < b ? a : b */
static uvec2 uvec2_min_v(const unsigned *vec_x, unsigned y) {
    return uvec2_min(UVec2(vec_x), y);
}


/** dst = a < b ? a : b */
static uvec2 uvec2_min_vec(uvec2 vec_x, uvec2 vec_y) {
    uvec2 res;
    uvecN_min_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a < b ? a : b */
static uvec2 uvec2_min_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec2_min_vec(UVec2(vec_x), UVec2(vec_y));
}


/** dst = a > b ? a : b */
static uvec2 uvec2_max(uvec2 vec_x, unsigned y) {
    uvec2 res;
    uvecN_max(res.v, vec_x.v, y, 2);
    return res;
}
/** dst = a > b ? a : b */
static uvec2 uvec2_max_v(const unsigned *vec_x, unsigned y) {
    return uvec2_max(UVec2(vec_x), y);
}


/** dst = a > b ? a : b */
static uvec2 uvec2_max_vec(uvec2 vec_x, uvec2 vec_y) {
    uvec2 res;
    uvecN_max_vec(res.v, vec_x.v, vec_y.v, 2);
    return res;
}
/** dst = a > b ? a : b */
static uvec2 uvec2_max_vec_v(const unsigned *vec_x, const unsigned *vec_y) {
    return uvec2_max_vec(UVec2(vec_x), UVec2(vec_y));
}


/** dst = x < min ? min : (x > max ? max : x) */
static uvec2 uvec2_clamp(uvec2 vec_x, unsigned min, unsigned max) {
    uvec2 res;
    uvecN_clamp(res.v, vec_x.v, min, max, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static uvec2 uvec2_clamp_v(const unsigned *vec_x, unsigned min, unsigned max) {
    return uvec2_clamp(UVec2(vec_x), min, max);
}


/** dst = x < min ? min : (x > max ? max : x) */
static uvec2 uvec2_clamp_vec(uvec2 vec_x, uvec2 vec_min, uvec2 vec_max) {
    uvec2 res;
    uvecN_clamp_vec(res.v, vec_x.v, vec_min.v, vec_max.v, 2);
    return res;
}
/** dst = x < min ? min : (x > max ? max : x) */
static uvec2 uvec2_clamp_vec_v(const unsigned *vec_x, const unsigned *vec_min, const unsigned *vec_max) {
    return uvec2_clamp_vec(UVec2(vec_x), UVec2(vec_min), UVec2(vec_max));
}


/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned uvec2_sum(uvec2 vec) {
    return uvecN_sum(vec.v, 2);
}
/** returns vec[0] + vec[1] + ... + vec[n-1] */
static unsigned uvec2_sum_v(const unsigned *vec) {
    return uvec2_sum(UVec2(vec));
}


/** returns a dot b */
static unsigned uvec2_dot(uvec2 vec_a, uvec2 vec_b) {
    return uvecN_dot(vec_a.v, vec_b.v, 2);
}
/** returns a dot b */
static unsigned uvec2_dot_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_dot(UVec2(vec_a), UVec2(vec_b));
}


/** returns ||vec||_2 */
static float uvec2_norm(uvec2 vec) {
    return uvecN_norm(vec.v, 2);
}
/** returns ||vec||_2 */
static float uvec2_norm_v(const unsigned *vec) {
    return uvec2_norm(UVec2(vec));
}


/** returns length of a vector, see uvecN_norm. Just here to match glsl */
static float uvec2_length(uvec2 vec) {
    return uvecN_length(vec.v, 2);
}
/** returns length of a vector, see uvecN_norm. Just here to match glsl */
static float uvec2_length_v(const unsigned *vec) {
    return uvec2_length(UVec2(vec));
}


/** returns norm(b-a) */
static unsigned uvec2_distance(uvec2 vec_a, uvec2 vec_b) {
    return uvecN_distance(vec_a.v, vec_b.v, 2);
}
/** returns norm(b-a) */
static unsigned uvec2_distance_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_distance(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a < b */
static bvec2 uvec2_less_than(uvec2 vec_a, unsigned b) {
    bvec2 res;
    uvecN_less_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a < b */
static bvec2 uvec2_less_than_v(const unsigned *vec_a, unsigned b) {
    return uvec2_less_than(UVec2(vec_a), b);
}


/** dst = a < b */
static bvec2 uvec2_less_than_vec(uvec2 vec_a, uvec2 vec_b) {
    bvec2 res;
    uvecN_less_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a < b */
static bvec2 uvec2_less_than_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_less_than_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a <= b */
static bvec2 uvec2_less_than_equal(uvec2 vec_a, unsigned b) {
    bvec2 res;
    uvecN_less_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a <= b */
static bvec2 uvec2_less_than_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec2_less_than_equal(UVec2(vec_a), b);
}


/** dst = a <= b */
static bvec2 uvec2_less_than_equal_vec(uvec2 vec_a, uvec2 vec_b) {
    bvec2 res;
    uvecN_less_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a <= b */
static bvec2 uvec2_less_than_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_less_than_equal_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a > b */
static bvec2 uvec2_greater_than(uvec2 vec_a, unsigned b) {
    bvec2 res;
    uvecN_greater_than(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a > b */
static bvec2 uvec2_greater_than_v(const unsigned *vec_a, unsigned b) {
    return uvec2_greater_than(UVec2(vec_a), b);
}


/** dst = a > b */
static bvec2 uvec2_greater_than_vec(uvec2 vec_a, uvec2 vec_b) {
    bvec2 res;
    uvecN_greater_than_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a > b */
static bvec2 uvec2_greater_than_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_greater_than_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a >= b */
static bvec2 uvec2_greater_than_equal(uvec2 vec_a, unsigned b) {
    bvec2 res;
    uvecN_greater_than_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a >= b */
static bvec2 uvec2_greater_than_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec2_greater_than_equal(UVec2(vec_a), b);
}


/** dst = a >= b */
static bvec2 uvec2_greater_than_equal_vec(uvec2 vec_a, uvec2 vec_b) {
    bvec2 res;
    uvecN_greater_than_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a >= b */
static bvec2 uvec2_greater_than_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_greater_than_equal_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a == b */
static bvec2 uvec2_equal(uvec2 vec_a, unsigned b) {
    bvec2 res;
    uvecN_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a == b */
static bvec2 uvec2_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec2_equal(UVec2(vec_a), b);
}


/** dst = a == b */
static bvec2 uvec2_equal_vec(uvec2 vec_a, uvec2 vec_b) {
    bvec2 res;
    uvecN_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a == b */
static bvec2 uvec2_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_equal_vec(UVec2(vec_a), UVec2(vec_b));
}


/** dst = a != b */
static bvec2 uvec2_not_equal(uvec2 vec_a, unsigned b) {
    bvec2 res;
    uvecN_not_equal(res.v, vec_a.v, b, 2);
    return res;
}
/** dst = a != b */
static bvec2 uvec2_not_equal_v(const unsigned *vec_a, unsigned b) {
    return uvec2_not_equal(UVec2(vec_a), b);
}


/** dst = a != b */
static bvec2 uvec2_not_equal_vec(uvec2 vec_a, uvec2 vec_b) {
    bvec2 res;
    uvecN_not_equal_vec(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a != b */
static bvec2 uvec2_not_equal_vec_v(const unsigned *vec_a, const unsigned *vec_b) {
    return uvec2_not_equal_vec(UVec2(vec_a), UVec2(vec_b));
}

#endif //MATHC_VEC_UVEC2_H
