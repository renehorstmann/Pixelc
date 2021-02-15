#ifndef MATHC_SCA_DOUBLE_H
#define MATHC_SCA_DOUBLE_H

#include <math.h>

/** dst = a * M_PI / 180 */
static double dsca_radians(double deg) {
    return deg * M_PI / 180.0;
}

/** dst = a * 180 / M_PI */
static double dsca_degrees(double rad) {
    return rad * 180.0 / M_PI;
}

/** dst = sin(angle_rad) */
static double dsca_sin(double angle_rad) {
    return sin(angle_rad);
}

/** dst = cos(angle_rad) */
static double dsca_cos(double angle_rad) {
    return cos(angle_rad);
}

/** dst = tan(angle_rad) */
static double dsca_tan(double angle_rad) {
    return tan(angle_rad);
}

/** dst = asin(x) */
static double dsca_asin(double x) {
    return asin(x);
}

/** dst = acos(x) */
static double dsca_acos(double x) {
    return acos(x);
}

/** dst = atan(x) */
static double dsca_atan(double x) {
    return atan(x);
}

/** dst = atan2(y, x) */
static double dsca_atan2(double y, double x) {
    return atan2(y, x);
}

/** dst = pow(x, y) */
static double dsca_pow(double x, double y) {
    return pow(x, y);
}

/** dst = exp(x) */
static double dsca_exp(double x) {
    return exp(x);
}

/** dst = log(x) */
static double dsca_log(double x) {
    return log(x);
}

/** dst = exp2(x) */
static double dsca_exp2(double x) {
    return exp2(x);
}

/** dst = log2(x) */
static double dsca_log2(double x) {
    return log2(x);
}

/** dst = sqrt(x) */
static double dsca_sqrt(double x) {
    return sqrt(x);
}

/** dst = 1 / sqrt(x) */
static double dsca_inversesqrt(double x) {
    return 1.0 / sqrt(x);
}

/** dst = abs(x) */
static double dsca_abs(double x) {
    return fabs(x);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static double dsca_sign(double x) {
    return x > 0.0 ? 1.0 : (x < 0.0 ? -1.0 : 0.0);
}

/** dst = floor(x) */
static double dsca_floor(double x) {
    return floor(x);
}

/** dst = ceil(x) */
static double dsca_ceil(double x) {
    return ceil(x);
}

/** dst = 1 - floor(x) */
static double dsca_fract(double x) {
    return 1.0 - floor(x);
}

/** dst = x - y * floor(x/y) */
static double dsca_mod(double x, double y) {
    return x - y * floor(x / y);
}

/** dst = a < b ? a : b */
static double dsca_min(double a, double b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static double dsca_max(double a, double b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static double dsca_clamp(double x, double min, double max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static double dsca_mix(double a, double b, double t) {
    return a * (1.0-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static double dsca_step(double x, double edge) {
    return x < edge ? 0.0 : 1.0;
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static double dsca_smoothstep(double x, double edge1, double edge2) {
    return x < edge1 ? 0.0 : (x > edge2 ? 1.0 : x * x * (3.0 - 2.0 * x));
}

/** dst = isnan(x) */
static double dsca_isnan(double x) {
    return isnan(x);
}

#endif //MATHC_SCA_DOUBLE_H
