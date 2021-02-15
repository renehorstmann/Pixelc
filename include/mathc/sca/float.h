#ifndef MATHC_SCA_FLOAT_H
#define MATHC_SCA_FLOAT_H

#include <math.h>

/** dst = a * M_PI / 180 */
static float sca_radians(float deg) {
    return deg * M_PI / 180.0f;
}

/** dst = a * 180 / M_PI */
static float sca_degrees(float rad) {
    return rad * 180.0f / M_PI;
}

/** dst = sin(angle_rad) */
static float sca_sin(float angle_rad) {
    return sinf(angle_rad);
}

/** dst = cos(angle_rad) */
static float sca_cos(float angle_rad) {
    return cosf(angle_rad);
}

/** dst = tan(angle_rad) */
static float sca_tan(float angle_rad) {
    return tanf(angle_rad);
}

/** dst = asin(x) */
static float sca_asin(float x) {
    return asinf(x);
}

/** dst = acos(x) */
static float sca_acos(float x) {
    return acosf(x);
}

/** dst = atan(x) */
static float sca_atan(float x) {
    return atanf(x);
}

/** dst = atan2(y, x) */
static float sca_atan2(float y, float x) {
    return atan2f(y, x);
}

/** dst = pow(x, y) */
static float sca_pow(float x, float y) {
    return powf(x, y);
}

/** dst = exp(x) */
static float sca_exp(float x) {
    return expf(x);
}

/** dst = log(x) */
static float sca_log(float x) {
    return logf(x);
}

/** dst = exp2(x) */
static float sca_exp2(float x) {
    return exp2f(x);
}

/** dst = log2(x) */
static float sca_log2(float x) {
    return log2f(x);
}

/** dst = sqrt(x) */
static float sca_sqrt(float x) {
    return sqrtf(x);
}

/** dst = 1 / sqrt(x) */
static float sca_inversesqrt(float x) {
    return 1.0f / sqrtf(x);
}

/** dst = abs(x) */
static float sca_abs(float x) {
    return fabsf(x);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static float sca_sign(float x) {
    return x > 0.0f ? 1.0f : (x < 0.0f ? -1.0f : 0.0f);
}

/** dst = floor(x) */
static float sca_floor(float x) {
    return floorf(x);
}

/** dst = ceil(x) */
static float sca_ceil(float x) {
    return ceilf(x);
}

/** dst = 1 - floor(x) */
static float sca_fract(float x) {
    return 1.0f - floorf(x);
}

/** dst = x - y * floor(x/y) */
static float sca_mod(float x, float y) {
    return x - y * floorf(x / y);
}

/** dst = a < b ? a : b */
static float sca_min(float a, float b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static float sca_max(float a, float b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static float sca_clamp(float x, float min, float max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static float sca_mix(float a, float b, float t) {
    return a * (1.0f-t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static float sca_step(float x, float edge) {
    return x < edge ? 0.0f : 1.0f;
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static float sca_smoothstep(float x, float edge1, float edge2) {
    return x < edge1 ? 0.0f : (x > edge2 ? 1.0f : x * x * (3.0f - 2.0f * x));
}

/** dst = isnan(x) */
static float sca_isnan(float x) {
    return isnan(x);
}

#endif //MATHC_SCA_FLOAT_H
