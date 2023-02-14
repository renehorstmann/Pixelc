#ifndef M_SCA_FLOAT_H
#define M_SCA_FLOAT_H

#include <stdbool.h>
#include <float.h>  // for FLT_MAX, ...
#include <math.h>

/** maximum possible value */
#define SCA_MAX FLT_MAX

/** minimum possible value */
#define SCA_MIN (-FLT_MAX)

/** smallest positive value */
#define SCA_SMALL FLT_MIN

/** smallest positive value change */
#define SCA_EPS FLT_EPSILON

/* clone of some math.h constants */
#define SCA_E 2.718281828459045235360287471352662498f /* e */
#define SCA_LOG2E 1.442695040888963407359924681001892137f /* log_2 e */
#define SCA_LOG10E 0.434294481903251827651128918916605082f /* log_10 e */
#define SCA_LN2 0.693147180559945309417232121458176568f /* log_e 2 */
#define SCA_LN10 2.302585092994045684017991454684364208f /* log_e 10 */
#define SCA_PI 3.141592653589793238462643383279502884f /* pi */
#define SCA_PI_2 1.570796326794896619231321691639751442f /* pi/2 */
#define SCA_PI_4 0.785398163397448309615660845819875721f /* pi/4 */
#define SCA_1_PI 0.318309886183790671537767526745028724f /* 1/pi */
#define SCA_2_PI 0.636619772367581343075535053490057448f /* 2/pi */
#define SCA_2_SQRTPI 1.128379167095512573896158903121545172f /* 2/sqrt(pi) */
#define SCA_SQRT2 1.414213562373095048801688724209698079f /* sqrt(2) */
#define SCA_SQRT1_2 0.707106781186547524400844362104849039f /* 1/sqrt(2) */

/** for printing in IO */
#define SCA_PRINT_FORMAT_SPECIFIER "g"

/** dst = a * M_PI / 180 */
static float sca_radians(float deg) {
    return deg * SCA_PI / 180.0f;
}

/** dst = a * 180 / M_PI */
static float sca_degrees(float rad) {
    return rad * 180.0f / SCA_PI;
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
    return a * (1.0f - t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static float sca_step(float x, float edge) {
    return x < edge ? 0.0f : 1.0f;
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static float sca_smoothstep(float x, float edge1, float edge2) {
    x = sca_clamp((x-edge1) / (edge2-edge1), 0.0f, 1.0f);
    return x * x * (3.0f - 2.0f * x);
}

/** dst = isnan(x) */
static bool sca_isnan(float x) {
    return isnan(x);
}

/** dst = isinf(x) */
static bool sca_isinf(float x) {
    return isinf(x);
}

#endif //M_SCA_FLOAT_H
