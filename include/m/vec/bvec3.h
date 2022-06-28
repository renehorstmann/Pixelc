#ifndef M_VEC_BVEC3_H
#define M_VEC_BVEC3_H


#include "bvecn.h"
#include "../types/bvec3.h"


/** bvec_a == bvec_b */
static bool bvec3_cmp(bvec3 a, bvec3 b) {
    return bvecN_cmp(a.v, b.v, 3);
}

/** dst = v0, v1, ... */
static bvec3 bvec3_new(bool v0, bool v1, bool v2
) {
    return (bvec3) {v0, v1, v2
    };
}

/** dst = scalar */
static bvec3 bvec3_set(bool set) {
    bvec3 res;
    bvecN_set(res.v, set, 3);
    return res;
}


/** dst = unit_x */
static bvec3 bvec3_unit_x() {
    bvec3 res;
    bvecN_unit_x(res.v, 3);
    return res;
}


/** dst = unit_y */
static bvec3 bvec3_unit_y() {
    bvec3 res;
    bvecN_unit_y(res.v, 3);
    return res;
}


/** dst = unit_z */
static bvec3 bvec3_unit_z() {
    bvec3 res;
    bvecN_unit_z(res.v, 3);
    return res;
}


/** dst = !vec */
static bvec3 bvec3_not(bvec3 vec) {
    bvec3 res;
    bvecN_not(res.v, vec.v, 3);
    return res;
}


/** dst = a || b */
static bvec3 bvec3_or(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_or(res.v, vec_a.v, vec_b.v, 3);
    return res;
}


/** dst = !(a || b) */
static bvec3 bvec3_nor(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_nor(res.v, vec_a.v, vec_b.v, 3);
    return res;
}


/** dst = a ^ b */
static bvec3 bvec3_xor(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_xor(res.v, vec_a.v, vec_b.v, 3);
    return res;
}


/** dst = !(a ^ b) */
static bvec3 bvec3_nxor(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_nxor(res.v, vec_a.v, vec_b.v, 3);
    return res;
}


/** dst = a && b */
static bvec3 bvec3_and(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_and(res.v, vec_a.v, vec_b.v, 3);
    return res;
}


/** dst = !(a && b) */
static bvec3 bvec3_nand(bvec3 vec_a, bvec3 vec_b) {
    bvec3 res;
    bvecN_nand(res.v, vec_a.v, vec_b.v, 3);
    return res;
}


/** returns the sum of true values */
static int bvec3_sum(bvec3 vec) {
    return bvecN_sum(vec.v, 3);
}


/** returns sum(vec) > 0 */
static bool bvec3_any(bvec3 vec) {
    return bvecN_any(vec.v, 3);
}


/** returns sum(vec) == n */
static bool bvec3_all(bvec3 vec) {
    return bvecN_all(vec.v, 3);
}

#endif //M_VEC_BVEC3_H
