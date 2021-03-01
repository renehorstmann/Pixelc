#ifndef MATHC_VEC_BVEC4_H
#define MATHC_VEC_BVEC4_H

#include "bvecn.h"
#include "../types/bool.h"


/** dst = unit_x */
static bvec4 bvec4_unit_x() {
    return (bvec4) {{true, false, false, false}};
}

/** dst = unit_y */
static bvec4 bvec4_unit_y() {
    return (bvec4) {{false, true, false, false}};
}

/** dst = unit_z */
static bvec4 bvec4_unit_z() {
    return (bvec4) {{false, false, true, false}};
}

/** dst = unit_w */
static bvec4 bvec4_unit_w() {
    return (bvec4) {{false, false, false, true}};
}


/** bvec_a == bvec_b */
static bool bvec4_cmp(bvec4 a, bvec4 b) {
    return bvecN_cmp(a.v, b.v, 4);
}

/** dst = scalar */
static bvec4 bvec4_set(bool set) {
    bvec4 res;
    bvecN_set(res.v, set, 4);
    return res;
}


/** dst = !vec */
static bvec4 bvec4_not(bvec4 vec) {
    bvec4 res;
    bvecN_not(res.v, vec.v, 4);
    return res;
}
/** dst = !vec */
static bvec4 bvec4_not_v(const bool *vec) {
    return bvec4_not(BVec4(vec));
}


/** dst = a || b */
static bvec4 bvec4_or(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_or(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a || b */
static bvec4 bvec4_or_v(const bool *vec_a, const bool *vec_b) {
    return bvec4_or(BVec4(vec_a), BVec4(vec_b));
}


/** dst = !(a || b) */
static bvec4 bvec4_nor(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_nor(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = !(a || b) */
static bvec4 bvec4_nor_v(const bool *vec_a, const bool *vec_b) {
    return bvec4_nor(BVec4(vec_a), BVec4(vec_b));
}


/** dst = a ^ b */
static bvec4 bvec4_xor(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_xor(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a ^ b */
static bvec4 bvec4_xor_v(const bool *vec_a, const bool *vec_b) {
    return bvec4_xor(BVec4(vec_a), BVec4(vec_b));
}


/** dst = !(a ^ b) */
static bvec4 bvec4_nxor(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_nxor(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = !(a ^ b) */
static bvec4 bvec4_nxor_v(const bool *vec_a, const bool *vec_b) {
    return bvec4_nxor(BVec4(vec_a), BVec4(vec_b));
}


/** dst = a && b */
static bvec4 bvec4_and(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_and(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = a && b */
static bvec4 bvec4_and_v(const bool *vec_a, const bool *vec_b) {
    return bvec4_and(BVec4(vec_a), BVec4(vec_b));
}


/** dst = !(a && b) */
static bvec4 bvec4_nand(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_nand(res.v, vec_a.v, vec_b.v, 4);
    return res;
}
/** dst = !(a && b) */
static bvec4 bvec4_nand_v(const bool *vec_a, const bool *vec_b) {
    return bvec4_nand(BVec4(vec_a), BVec4(vec_b));
}


/** returns the sum of true values */
static int bvec4_sum(bvec4 vec) {
    return bvecN_sum(vec.v, 4);
}
/** returns the sum of true values */
static int bvec4_sum_v(const bool *vec) {
    return bvec4_sum(BVec4(vec));
}


/** returns sum(vec) > 0 */
static bool bvec4_any(bvec4 vec) {
    return bvecN_any(vec.v, 4);
}
/** returns sum(vec) > 0 */
static bool bvec4_any_v(const bool *vec) {
    return bvec4_any(BVec4(vec));
}


/** returns sum(vec) == n */
static bool bvec4_all(bvec4 vec) {
    return bvecN_all(vec.v, 4);
}
/** returns sum(vec) == n */
static bool bvec4_all_v(const bool *vec) {
    return bvec4_all(BVec4(vec));
}

#endif //MATHC_VEC_BVEC4_H
