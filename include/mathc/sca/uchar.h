#ifndef MATHC_SCA_UCHAR_H
#define MATHC_SCA_UCHAR_H

#include <stdint.h>
#include <math.h>

/** dst = pow(x, y) */
static uint8_t ucsca_pow(uint8_t x, uint8_t y) {
    return pow(x, y);
}

/** dst = exp(x) */
static uint8_t ucsca_exp(uint8_t x) {
    return exp(x);
}

/** dst = log(x) */
static uint8_t ucsca_log(uint8_t x) {
    return log(x);
}

/** dst = exp2(x) */
static uint8_t ucsca_exp2(uint8_t x) {
    return exp2(x);
}

/** dst = log2(x) */
static uint8_t ucsca_log2(uint8_t x) {
    return log2(x);
}

/** dst = sqrt(x) */
static uint8_t ucsca_sqrt(uint8_t x) {
    return sqrt(x);
}

/** dst = a < b ? a : b */
static uint8_t ucsca_min(uint8_t a, uint8_t b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static uint8_t ucsca_max(uint8_t a, uint8_t b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static uint8_t ucsca_clamp(uint8_t x, uint8_t min, uint8_t max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static uint8_t ucsca_mix(uint8_t a, uint8_t b, float t) {
    return a * (1.0-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static uint8_t ucsca_step(uint8_t x, uint8_t edge) {
    return x < edge ? 0 : 1;
}

#endif //MATHC_SCA_UCHAR_H
