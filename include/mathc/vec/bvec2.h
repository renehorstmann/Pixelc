#ifndef MATHC_VEC_BVEC2_H
#define MATHC_VEC_BVEC2_H

#include "bvecn.h"
#include "../types/bool.h"


/** dst = unit_x */
static bvec2 bvec2_unit_x() {
    return (bvec2) {{true, false}};
}

/** dst = unit_y */
static bvec2 bvec2_unit_y() {
    return (bvec2) {{false, true}};
}

/** bvec_a == bvec_b */
static bool bvec2_cmp(bvec2 a, bvec2 b) {
    return bvecN_cmp(a.v, b.v, 2);
}

/** dst = scalar */
static bvec2 bvec2_set(bool set) {
    bvec2 res;
    bvecN_set(res.v, set, 2);
    return res;
}


/** dst = !vec */
static bvec2 bvec2_not(bvec2 vec) {
    bvec2 res;
    bvecN_not(res.v, vec.v, 2);
    return res;
}
/** dst = !vec */
static bvec2 bvec2_not_v(const bool *vec) {
    return bvec2_not(BVec2(vec));
}


/** dst = a || b */
static bvec2 bvec2_or(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_or(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a || b */
static bvec2 bvec2_or_v(const bool *vec_a, const bool *vec_b) {
    return bvec2_or(BVec2(vec_a), BVec2(vec_b));
}


/** dst = !(a || b) */
static bvec2 bvec2_nor(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_nor(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = !(a || b) */
static bvec2 bvec2_nor_v(const bool *vec_a, const bool *vec_b) {
    return bvec2_nor(BVec2(vec_a), BVec2(vec_b));
}


/** dst = a ^ b */
static bvec2 bvec2_xor(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_xor(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a ^ b */
static bvec2 bvec2_xor_v(const bool *vec_a, const bool *vec_b) {
    return bvec2_xor(BVec2(vec_a), BVec2(vec_b));
}


/** dst = !(a ^ b) */
static bvec2 bvec2_nxor(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_nxor(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = !(a ^ b) */
static bvec2 bvec2_nxor_v(const bool *vec_a, const bool *vec_b) {
    return bvec2_nxor(BVec2(vec_a), BVec2(vec_b));
}


/** dst = a && b */
static bvec2 bvec2_and(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_and(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = a && b */
static bvec2 bvec2_and_v(const bool *vec_a, const bool *vec_b) {
    return bvec2_and(BVec2(vec_a), BVec2(vec_b));
}


/** dst = !(a && b) */
static bvec2 bvec2_nand(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_nand(res.v, vec_a.v, vec_b.v, 2);
    return res;
}
/** dst = !(a && b) */
static bvec2 bvec2_nand_v(const bool *vec_a, const bool *vec_b) {
    return bvec2_nand(BVec2(vec_a), BVec2(vec_b));
}


/** returns the sum of true values */
static int bvec2_sum(bvec2 vec) {
    return bvecN_sum(vec.v, 2);
}
/** returns the sum of true values */
static int bvec2_sum_v(const bool *vec) {
    return bvec2_sum(BVec2(vec));
}


/** returns sum(vec) > 0 */
static bool bvec2_any(bvec2 vec) {
    return bvecN_any(vec.v, 2);
}
/** returns sum(vec) > 0 */
static bool bvec2_any_v(const bool *vec) {
    return bvec2_any(BVec2(vec));
}


/** returns sum(vec) == n */
static bool bvec2_all(bvec2 vec) {
    return bvecN_all(vec.v, 2);
}
/** returns sum(vec) == n */
static bool bvec2_all_v(const bool *vec) {
    return bvec2_all(BVec2(vec));
}

#endif //MATHC_VEC_BVEC2_H
