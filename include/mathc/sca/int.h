#ifndef MATHC_SCA_INT_H
#define MATHC_SCA_INT_H

#include <stdlib.h>  // abs
#include <math.h>

/** dst = pow(x, y) */
static int isca_pow(int x, int y) {
    return pow(x, y);
}

/** dst = exp(x) */
static int isca_exp(int x) {
    return exp(x);
}

/** dst = log(x) */
static int isca_log(int x) {
    return log(x);
}

/** dst = exp2(x) */
static int isca_exp2(int x) {
    return exp2(x);
}

/** dst = log2(x) */
static int isca_log2(int x) {
    return log2(x);
}

/** dst = sqrt(x) */
static int isca_sqrt(int x) {
    return sqrt(x);
}

/** dst = 1 / sqrt(x) */
static int isca_inversesqrt(int x) {
    return 1.0 / sqrt(x);
}

/** dst = abs(x) */
static int isca_abs(int x) {
    return abs(x);
}

/** dst = a < b ? a : b */
static int isca_min(int a, int b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static int isca_max(int a, int b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static int isca_clamp(int x, int min, int max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static int isca_mix(int a, int b, int t) {
    return a * (1.0-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static int isca_step(int x, int edge) {
    return x < edge ? 0.0 : 1.0;
}

#endif //MATHC_SCA_INT_H
