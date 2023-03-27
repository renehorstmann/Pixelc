#ifndef M_SCA_INT_H
#define M_SCA_INT_H

#include <stdlib.h>  // abs
#include <limits.h>  // INT_MAX
#include <math.h>
#include "../common.h"

/** maximum possible value */
#define ISCA_MAX INT_MAX

/** minimum possible value */
#define ISCA_MIN INT_MIN

/** for printing in IO */
#define ISCA_PRINT_FORMAT_SPECIFIER "i"

/** dst = pow(x, y) */
static int isca_pow(int x, int y) {
    return (int) pow(x, y);
}

/** dst = exp(x) */
static int isca_exp(int x) {
    return (int) exp(x);
}

/** dst = log(x) */
static int isca_log(int x) {
    return (int) log(x);
}

/** dst = exp2(x) */
static int isca_exp2(int x) {
    return (int) exp2(x);
}

/** dst = log2(x) */
static int isca_log2(int x) {
    return (int) log2(x);
}

/** dst = sqrt(x) */
static int isca_sqrt(int x) {
    return (int) sqrt(x);
}

/** dst = abs(x) */
static int isca_abs(int x) {
    return abs(x);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static int isca_sign(int x) {
    return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

/** dst = (x % y + y) % y (always positive, if y>0) **/
static int isca_mod(int x, int y) {
    return (x % y + y) % y;
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
static int isca_mix(int a, int b, float t) {
    return (int) (a * (1.0f - t) + b * t);
}

/** dst = x < edge ? 0 : 1 */
static int isca_step(int x, int edge) {
    return x < edge ? 0 : 1;
}

#endif //M_SCA_INT_H
