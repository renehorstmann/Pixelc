#ifndef MATHC_UTILS_COLOR_H
#define MATHC_UTILS_COLOR_H

#include "../vec/vec3.h"

// rgb[0:1] hsv[0:360, 0:1, 0:1]
static vec3 vec3_rgb2hsv(vec3 rgb) {
    vec3 hsv;
    float min, max, delta;

    min = rgb.r < rgb.g ? rgb.r : rgb.g;
    min = min  < rgb.b ? min  : rgb.b;

    max = rgb.r > rgb.g ? rgb.r : rgb.g;
    max = max  > rgb.b ? max  : rgb.b;

    hsv.v2 = max;
    delta = max - min;
    if (delta < 0.00001f) {
        hsv.v0 = 0; // undefined
        hsv.v1 = 0;
        return hsv;
    }
    if( max > 0.0 ) {
        // NOTE: if Max is == 0, this divide would cause a crash
        hsv.v1 = (delta / max);
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        hsv.v0 = 0;
        hsv.v1 = 0;
        return hsv;
    }
    if(rgb.r >= max )
        // > is bogus, just keeps compilor happy
        hsv.v0 = (rgb.g - rgb.b) / delta;
        // between yellow & magenta
    else if(rgb.g >= max )
        hsv.v0 = 2.0 + (rgb.b - rgb.r) / delta;
        // between cyan & yellow
    else
        hsv.v0 = 4.0 + (rgb.r - rgb.g) / delta;
    // between magenta & cyan

    hsv.v0 *= 60.0; // degrees

    if(hsv.v0 < 0)
        hsv.v0 += 360.0;
    return hsv;
}

// rgb[0:1] hsv[0:360, 0:1, 0:1]
static vec3 vec3_hsv2rgb(vec3 hsv) {
    vec3 rgb;
    float hh, p, q, t, ff;
    long i;

    if(hsv.v1 <= 0.0) {
        // < is bogus, just shuts up warnings
        rgb.r = hsv.v2;
        rgb.g = hsv.v2;
        rgb.b = hsv.v2;
        return rgb;
    }
    hh = hsv.v0;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = hsv.v2 * (1.0 - hsv.v1);
    q = hsv.v2 * (1.0 - (hsv.v1 * ff));
    t = hsv.v2 * (1.0 - (hsv.v1 * (1.0 - ff)));

    switch(i) {
        case 0:
            rgb.r = hsv.v2;
            rgb.g = t;
            rgb.b = p;
            break;
        case 1:
            rgb.r = q;
            rgb.g = hsv.v2;
            rgb.b = p;
            break;
        case 2:
            rgb.r = p;
            rgb.g = hsv.v2;
            rgb.b = t;
            break;

        case 3:
            rgb.r = p;
            rgb.g = q;
            rgb.b = hsv.v2;
            break;
        case 4:
            rgb.r = t;
            rgb.g = p;
            rgb.b = hsv.v2;
            break;
        case 5:
        default:
            rgb.r = hsv.v2;
            rgb.g = p;
            rgb.b = q;
            break;
    }
    return rgb;
}

#endif //MATHC_UTILS_COLOR_H
