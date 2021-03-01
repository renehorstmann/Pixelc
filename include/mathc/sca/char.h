#ifndef MATHC_SCA_CHAR_H
#define MATHC_SCA_CHAR_H

#include <stdlib.h>  // abs
#include <math.h>

/** dst = pow(x, y) */
static char csca_pow(char x, char y) {
    return pow(x, y);
}

/** dst = exp(x) */
static char csca_exp(char x) {
    return exp(x);
}

/** dst = log(x) */
static char csca_log(char x) {
    return log(x);
}

/** dst = exp2(x) */
static char csca_exp2(char x) {
    return exp2(x);
}

/** dst = log2(x) */
static char csca_log2(char x) {
    return log2(x);
}

/** dst = sqrt(x) */
static char csca_sqrt(char x) {
    return sqrt(x);
}

/** dst = abs(x) */
static char csca_abs(char x) {
    return abs(x);
}

/** dst = a < b ? a : b */
static char csca_min(char a, char b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static char csca_max(char a, char b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static char csca_clamp(char x, char min, char max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static char csca_mix(char a, char b, float t) {
    return a * (1.0-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static char csca_step(char x, char edge) {
    return x < edge ? 0: 1;
}

#endif //MATHC_SCA_CHAR_H
