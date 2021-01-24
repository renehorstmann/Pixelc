#ifndef MATHC_VEC_BVEC3_H
#define MATHC_VEC_BVEC3_H

#include "bvecn.h"
#include "../types/bool.h"


/** dst = unit_x */
static bvec3 bvec3_unit_x() {
    return (bvec3) {{true, false, false}};
}

/** dst = unit_y */
static bvec3 bvec3_unit_y() {
    return (bvec3) {{false, true, false}};
}

/** dst = unit_z */
static bvec3 bvec3_unit_z() {
    return (bvec3) {{false, false, true}};
}


/** dst = scalar */
static bvec3 bvec3_set(bool set) {
    bvec3 res;
    bvecN_set(res.v, set, 3);
    return res;
}


/** dst = !vec */
static bvec3 bvec3_not(bvec3 vec) {
    bvec3 res;
    bvecN_not(res.v, vec.v, 3);
    return res;
}
/** dst = !vec */
static bvec3 bvec3_not_v(const bool *vec) {
    return bvec3_not(BVec3(vec));
}


/** dst = a || b */
static bvec3 bvec3_or(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_or(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a || b */
static bvec3 bvec3_or_v(const bool *vec_a, const bool *vec_b) {
    return bvec3_or(BVec3(vec_a), BVec3(vec_b));
}


/** dst = !(a || b) */
static bvec3 bvec3_nor(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_nor(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = !(a || b) */
static bvec3 bvec3_nor_v(const bool *vec_a, const bool *vec_b) {
    return bvec3_nor(BVec3(vec_a), BVec3(vec_b));
}


/** dst = a ^ b */
static bvec3 bvec3_xor(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_xor(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a ^ b */
static bvec3 bvec3_xor_v(const bool *vec_a, const bool *vec_b) {
    return bvec3_xor(BVec3(vec_a), BVec3(vec_b));
}


/** dst = !(a ^ b) */
static bvec3 bvec3_nxor(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_nxor(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = !(a ^ b) */
static bvec3 bvec3_nxor_v(const bool *vec_a, const bool *vec_b) {
    return bvec3_nxor(BVec3(vec_a), BVec3(vec_b));
}


/** dst = a && b */
static bvec3 bvec3_and(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_and(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = a && b */
static bvec3 bvec3_and_v(const bool *vec_a, const bool *vec_b) {
    return bvec3_and(BVec3(vec_a), BVec3(vec_b));
}


/** dst = !(a && b) */
static bvec3 bvec3_nand(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_nand(res.v, vec_a.v, vec_b.v, 3);
    return res;
}
/** dst = !(a && b) */
static bvec3 bvec3_nand_v(const bool *vec_a, const bool *vec_b) {
    return bvec3_nand(BVec3(vec_a), BVec3(vec_b));
}


/** returns the sum of true values */
static int bvec3_sum(bvec3 vec) {
    return bvecN_sum(vec.v, 3);
}
/** returns the sum of true values */
static int bvec3_sum_v(const bool *vec) {
    return bvec3_sum(BVec3(vec));
}


/** returns sum(vec) > 0 */
static bool bvec3_any(bvec3 vec) {
    return bvecN_any(vec.v, 3);
}
/** returns sum(vec) > 0 */
static bool bvec3_any_v(const bool *vec) {
    return bvec3_any(BVec3(vec));
}


/** returns sum(vec) == n */
static bool bvec3_all(bvec3 vec) {
    return bvecN_all(vec.v, 3);
}
/** returns sum(vec) == n */
static bool bvec3_all_v(const bool *vec) {
    return bvec3_all(BVec3(vec));
}

#endif //MATHC_VEC_BVEC3_H
