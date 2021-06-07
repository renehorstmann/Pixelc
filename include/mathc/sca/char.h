#ifndef MATHC_SCA_CHAR_H
#define MATHC_SCA_CHAR_H

#include <stdlib.h>  // abs
#include <stdint.h>
#include <math.h>

/** dst = pow(x, y) */
static int8_t csca_pow(int8_t x, int8_t y) {
    return pow(x, y);
}

/** dst = exp(x) */
static int8_t csca_exp(int8_t x) {
    return exp(x);
}

/** dst = log(x) */
static int8_t csca_log(int8_t x) {
    return log(x);
}

/** dst = exp2(x) */
static int8_t csca_exp2(int8_t x) {
    return exp2(x);
}

/** dst = log2(x) */
static int8_t csca_log2(int8_t x) {
    return log2(x);
}

/** dst = sqrt(x) */
static int8_t csca_sqrt(int8_t x) {
    return sqrt(x);
}

/** dst = abs(x) */
static int8_t csca_abs(int8_t x) {
    return abs(x);
}

/** dst = a < b ? a : b */
static int8_t csca_min(int8_t a, int8_t b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static int8_t csca_max(int8_t a, int8_t b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static int8_t csca_clamp(int8_t x, int8_t min, int8_t max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static int8_t csca_mix(int8_t a, int8_t b, float t) {
    return a * (1.0-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static int8_t csca_step(int8_t x, int8_t edge) {
    return x < edge ? 0: 1;
}

#endif //MATHC_SCA_CHAR_H
