#ifndef M_VEC_BVEC4_H
#define M_VEC_BVEC4_H


#include "bvecn.h"
#include "../types/bvec4.h"


/** bvec_a == bvec_b */
static bool bvec4_cmp(bvec4 a, bvec4 b) {
    return bvecN_cmp(a.v, b.v, 4);
}

/** dst = v0, v1, ... */
static bvec4 bvec4_new(bool v0, bool v1, bool v2, bool v3
) {
    bvec4 self;
    self.v0 = v0;
    self.v1 = v1;
    self.v2 = v2;
    self.v3 = v3;
    return self;
}

/** dst = scalar */
static bvec4 bvec4_set(bool set) {
    bvec4 res;
    bvecN_set(res.v, set, 4);
    return res;
}


/** dst = unit_x */
static bvec4 bvec4_unit_x() {
    bvec4 res;
    bvecN_unit_x(res.v, 4);
    return res;
}


/** dst = unit_y */
static bvec4 bvec4_unit_y() {
    bvec4 res;
    bvecN_unit_y(res.v, 4);
    return res;
}


/** dst = unit_z */
static bvec4 bvec4_unit_z() {
    bvec4 res;
    bvecN_unit_z(res.v, 4);
    return res;
}


/** dst = unit_w */
static bvec4 bvec4_unit_w() {
    bvec4 res;
    bvecN_unit_w(res.v, 4);
    return res;
}


/** dst = !vec */
static bvec4 bvec4_not(bvec4 vec) {
    bvec4 res;
    bvecN_not(res.v, vec.v, 4);
    return res;
}


/** dst = a || b */
static bvec4 bvec4_or(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_or(res.v, vec_a.v, vec_b.v, 4);
    return res;
}


/** dst = !(a || b) */
static bvec4 bvec4_nor(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_nor(res.v, vec_a.v, vec_b.v, 4);
    return res;
}


/** dst = a ^ b */
static bvec4 bvec4_xor(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_xor(res.v, vec_a.v, vec_b.v, 4);
    return res;
}


/** dst = !(a ^ b) */
static bvec4 bvec4_nxor(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_nxor(res.v, vec_a.v, vec_b.v, 4);
    return res;
}


/** dst = a && b */
static bvec4 bvec4_and(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_and(res.v, vec_a.v, vec_b.v, 4);
    return res;
}


/** dst = !(a && b) */
static bvec4 bvec4_nand(bvec4 vec_a, bvec4 vec_b) {
    bvec4 res;
    bvecN_nand(res.v, vec_a.v, vec_b.v, 4);
    return res;
}


/** returns the sum of true values */
static int bvec4_sum(bvec4 vec) {
    return bvecN_sum(vec.v, 4);
}


/** returns sum(vec) > 0 */
static bool bvec4_any(bvec4 vec) {
    return bvecN_any(vec.v, 4);
}


/** returns sum(vec) == n */
static bool bvec4_all(bvec4 vec) {
    return bvecN_all(vec.v, 4);
}

#endif //M_VEC_BVEC4_H
