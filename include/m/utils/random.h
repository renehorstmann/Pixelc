#ifndef M_UTILS_RANDOM
#define M_UTILS_RANDOM



#ifndef M_RANDOM_FUNCTION
#include <stdlib.h>
#define M_RANDOM_FUNCTION rand
#endif

#ifndef M_RANDOM_FUNCTION_MAX
#define M_RANDOM_FUNCTION_MAX RAND_MAX
#endif

#include "../types/vec2.h"
#include "../types/vec3.h"
#include "../types/vec4.h"
#include "../sca/float.h"

/** dst = rand() [0:1] */
static float sca_random() {
    return (float) 1 * M_RANDOM_FUNCTION() / (float) M_RANDOM_FUNCTION_MAX;
}

/** dst = rand() [a:b] */
static float sca_random_range(float a, float b) {
    return a + (b - a) * sca_random();
}

/** dst = mean +- amplitude * rand() */
static float sca_random_noise(float mean, float amplitude) {
    return mean - amplitude + 2 * amplitude * sca_random();
}

/** dst = mean +- sigma * normalized_rand() */
static float sca_random_normal(float mean, float sigma) {
    float u1, u2;
    do {
        u1 = sca_random();
    } while (u1 <= (float) 0.00000001);
    u2 = sca_random();

    float mag = sigma * sca_sqrt((float) -2 * log(u1));
    return mean + mag * sca_cos(2 * SCA_PI * u2);
}

//
// vecN
//

/** dst = rand() [0:1] */
static void vecN_random(float *dst, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_random();
    }
}

/** dst = rand() [a:b] */
static void vecN_random_range(float *dst, float a, float b, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_random_range(a, b);
    }
}

/** dst = rand() [a:b] */
static void vecN_random_range_vec(float *dst, const float *a, const float *b, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_random_range(a[i], b[i]);
    }
}

/** dst = mean +- amplitude * rand() */
static void vecN_random_noise(float *dst, float mean, float amplitude, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_random_noise(mean, amplitude);
    }
}

/** dst = mean +- amplitude * rand() */
static void vecN_random_noise_vec(float *dst, const float *mean, const float *amplitude, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_random_noise(mean[i], amplitude[i]);
    }
}

/** dst = mean +- sigma * normalized_rand() */
static void vecN_random_normal(float *dst, float mean, float sigma, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_random_normal(mean, sigma);
    }
}

/** dst = mean +- sigma * normalized_rand() */
static void vecN_random_normal_vec(float *dst, const float *mean, const float *sigma, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = sca_random_normal(mean[i], sigma[i]);
    }
}

//
// vec2
//

/** dst = rand() [0:1] */
static vec2 vec2_random() {
    vec2 res;
    vecN_random(res.v, 2);
    return res;
}

/** dst = rand() [a:b] */
static vec2 vec2_random_range(float a, float b) {
    vec2 res;
    vecN_random_range(res.v, a, b, 2);
    return res;
}

/** dst = rand() [a:b] */
static vec2 vec2_random_range_vec(vec2 a, vec2 b) {
    vec2 res;
    vecN_random_range_vec(res.v, a.v, b.v, 2);
    return res;
}

/** dst = mean +- amplitude * rand() */
static vec2 vec2_random_noise(float mean, float amplitude) {
    vec2 res;
    vecN_random_noise(res.v, mean, amplitude, 2);
    return res;
}

/** dst = mean +- amplitude * rand() */
static vec2 vec2_random_noise_vec(vec2 mean, vec2 amplitude) {
    vec2 res;
    vecN_random_noise_vec(res.v, mean.v, amplitude.v, 2);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static vec2 vec2_random_normal(float mean, float sigma) {
    vec2 res;
    vecN_random_normal(res.v, mean, sigma, 2);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static vec2 vec2_random_normal_vec(vec2 mean, vec2 sigma) {
    vec2 res;
    vecN_random_normal_vec(res.v, mean.v, sigma.v, 2);
    return res;
}

//
// vec3
//

/** dst = rand() [0:1] */
static vec3 vec3_random() {
    vec3 res;
    vecN_random(res.v, 3);
    return res;
}

/** dst = rand() [a:b] */
static vec3 vec3_random_range(float a, float b) {
    vec3 res;
    vecN_random_range(res.v, a, b, 3);
    return res;
}

/** dst = rand() [a:b] */
static vec3 vec3_random_range_vec(vec3 a, vec3 b) {
    vec3 res;
    vecN_random_range_vec(res.v, a.v, b.v, 3);
    return res;
}

/** dst = mean +- amplitude * rand() */
static vec3 vec3_random_noise(float mean, float amplitude) {
    vec3 res;
    vecN_random_noise(res.v, mean, amplitude, 3);
    return res;
}

/** dst = mean +- amplitude * rand() */
static vec3 vec3_random_noise_vec(vec3 mean, vec3 amplitude) {
    vec3 res;
    vecN_random_noise_vec(res.v, mean.v, amplitude.v, 3);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static vec3 vec3_random_normal(float mean, float sigma) {
    vec3 res;
    vecN_random_normal(res.v, mean, sigma, 3);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static vec3 vec3_random_normal_vec(vec3 mean, vec3 sigma) {
    vec3 res;
    vecN_random_normal_vec(res.v, mean.v, sigma.v, 3);
    return res;
}


//
// vec4
//

/** dst = rand() [0:1] */
static vec4 vec4_random() {
    vec4 res;
    vecN_random(res.v, 4);
    return res;
}

/** dst = rand() [a:b] */
static vec4 vec4_random_range(float a, float b) {
    vec4 res;
    vecN_random_range(res.v, a, b, 4);
    return res;
}

/** dst = rand() [a:b] */
static vec4 vec4_random_range_vec(vec4 a, vec4 b) {
    vec4 res;
    vecN_random_range_vec(res.v, a.v, b.v, 4);
    return res;
}

/** dst = mean +- amplitude * rand() */
static vec4 vec4_random_noise(float mean, float amplitude) {
    vec4 res;
    vecN_random_noise(res.v, mean, amplitude, 4);
    return res;
}

/** dst = mean +- amplitude * rand() */
static vec4 vec4_random_noise_vec(vec4 mean, vec4 amplitude) {
    vec4 res;
    vecN_random_noise_vec(res.v, mean.v, amplitude.v, 4);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static vec4 vec4_random_normal(float mean, float sigma) {
    vec4 res;
    vecN_random_normal(res.v, mean, sigma, 4);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static vec4 vec4_random_normal_vec(vec4 mean, vec4 sigma) {
    vec4 res;
    vecN_random_normal_vec(res.v, mean.v, sigma.v, 4);
    return res;
}

#endif // M_UTILS_RANDOM
