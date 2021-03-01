#ifndef MATHC_SCA_UCHAR_H
#define MATHC_SCA_UCHAR_H

#include <math.h>

typedef unsigned char uchar;

/** dst = pow(x, y) */
static uchar ucsca_pow(uchar x, uchar y) {
    return pow(x, y);
}

/** dst = exp(x) */
static uchar ucsca_exp(uchar x) {
    return exp(x);
}

/** dst = log(x) */
static uchar ucsca_log(uchar x) {
    return log(x);
}

/** dst = exp2(x) */
static uchar ucsca_exp2(uchar x) {
    return exp2(x);
}

/** dst = log2(x) */
static uchar ucsca_log2(uchar x) {
    return log2(x);
}

/** dst = sqrt(x) */
static uchar ucsca_sqrt(uchar x) {
    return sqrt(x);
}

/** dst = a < b ? a : b */
static uchar ucsca_min(uchar a, uchar b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static uchar ucsca_max(uchar a, uchar b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static uchar ucsca_clamp(uchar x, uchar min, uchar max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static uchar ucsca_mix(uchar a, uchar b, float t) {
    return a * (1.0-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static uchar ucsca_step(uchar x, uchar edge) {
    return x < edge ? 0 : 1;
}

#endif //MATHC_SCA_UCHAR_H
