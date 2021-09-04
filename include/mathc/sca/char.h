#ifndef MATHC_SCA_CHAR_H
#define MATHC_SCA_CHAR_H

#include <stdlib.h>  // abs
#include <math.h>

/** dst = pow(x, y) */
static signed char csca_pow(signed char x, signed char y) {
    return pow(x, y);
}

/** dst = exp(x) */
static signed char csca_exp(signed char x) {
    return exp(x);
}

/** dst = log(x) */
static signed char csca_log(signed char x) {
    return log(x);
}

/** dst = exp2(x) */
static signed char csca_exp2(signed char x) {
    return exp2(x);
}

/** dst = log2(x) */
static signed char csca_log2(signed char x) {
    return log2(x);
}

/** dst = sqrt(x) */
static signed char csca_sqrt(signed char x) {
    return sqrt(x);
}

/** dst = abs(x) */
static signed char csca_abs(signed char x) {
    return abs(x);
}

/** dst = x % m (always positive) **/
static signed char csca_mod_positive(signed char x, unsigned y) {
    signed char dst = (int) x % (int) y;
    if (dst < 0) {
        dst += y;
    }
    return dst;
}

/** dst = a < b ? a : b */
static signed char csca_min(signed char a, signed char b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static signed char csca_max(signed char a, signed char b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static signed char csca_clamp(signed char x, signed char min, signed char max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static signed char csca_mix(signed char a, signed char b, float t) {
    return a * (1.0-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static signed char csca_step(signed char x, signed char edge) {
    return x < edge ? 0: 1;
}

#endif //MATHC_SCA_CHAR_H
