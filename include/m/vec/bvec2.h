#ifndef M_VEC_BVEC2_H
#define M_VEC_BVEC2_H


#include "bvecn.h"
#include "../types/bvec2.h"


/** bvec_a == bvec_b */
static bool bvec2_cmp(bvec2 a, bvec2 b) {
    return bvecN_cmp(a.v, b.v, 2);
}

/** dst = v0, v1, ... */
static bvec2 bvec2_new(bool v0, bool v1
) {
    bvec2 self;
    self.v0 = v0;
    self.v1 = v1;
    return self;
}

/** dst = scalar */
static bvec2 bvec2_set(bool set) {
    bvec2 res;
    bvecN_set(res.v, set, 2);
    return res;
}


/** dst = unit_x */
static bvec2 bvec2_unit_x() {
    bvec2 res;
    bvecN_unit_x(res.v, 2);
    return res;
}


/** dst = unit_y */
static bvec2 bvec2_unit_y() {
    bvec2 res;
    bvecN_unit_y(res.v, 2);
    return res;
}






/** dst = !vec */
static bvec2 bvec2_not(bvec2 vec) {
    bvec2 res;
    bvecN_not(res.v, vec.v, 2);
    return res;
}


/** dst = a || b */
static bvec2 bvec2_or(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_or(res.v, vec_a.v, vec_b.v, 2);
    return res;
}


/** dst = !(a || b) */
static bvec2 bvec2_nor(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_nor(res.v, vec_a.v, vec_b.v, 2);
    return res;
}


/** dst = a ^ b */
static bvec2 bvec2_xor(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_xor(res.v, vec_a.v, vec_b.v, 2);
    return res;
}


/** dst = !(a ^ b) */
static bvec2 bvec2_nxor(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_nxor(res.v, vec_a.v, vec_b.v, 2);
    return res;
}


/** dst = a && b */
static bvec2 bvec2_and(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_and(res.v, vec_a.v, vec_b.v, 2);
    return res;
}


/** dst = !(a && b) */
static bvec2 bvec2_nand(bvec2 vec_a, bvec2 vec_b) {
    bvec2 res;
    bvecN_nand(res.v, vec_a.v, vec_b.v, 2);
    return res;
}


/** returns the sum of true values */
static int bvec2_sum(bvec2 vec) {
    return bvecN_sum(vec.v, 2);
}


/** returns sum(vec) > 0 */
static bool bvec2_any(bvec2 vec) {
    return bvecN_any(vec.v, 2);
}


/** returns sum(vec) == n */
static bool bvec2_all(bvec2 vec) {
    return bvecN_all(vec.v, 2);
}

#endif //M_VEC_BVEC2_H
