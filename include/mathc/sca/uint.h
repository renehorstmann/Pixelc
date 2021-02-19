#ifndef MATHC_SCA_UINT_H
#define MATHC_SCA_UINT_H

#include <math.h>

/** dst = pow(x, y) */
static unsigned usca_pow(unsigned x, unsigned y) {
    return pow(x, y);
}

/** dst = exp(x) */
static unsigned usca_exp(unsigned x) {
    return exp(x);
}

/** dst = log(x) */
static unsigned usca_log(unsigned x) {
    return log(x);
}

/** dst = exp2(x) */
static unsigned usca_exp2(unsigned x) {
    return exp2(x);
}

/** dst = log2(x) */
static unsigned usca_log2(unsigned x) {
    return log2(x);
}

/** dst = sqrt(x) */
static unsigned usca_sqrt(unsigned x) {
    return sqrt(x);
}

/** dst = a < b ? a : b */
static unsigned usca_min(unsigned a, unsigned b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static unsigned usca_max(unsigned a, unsigned b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static unsigned usca_clamp(unsigned x, unsigned min, unsigned max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static unsigned usca_mix(unsigned a, unsigned b, unsigned t) {
    return a * (1.0-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static unsigned usca_step(unsigned x, unsigned edge) {
    return x < edge ? 0.0 : 1.0;
}

#endif //MATHC_SCA_UINT_H
