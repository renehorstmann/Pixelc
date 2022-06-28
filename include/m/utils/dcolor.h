#ifndef M_UTILS_DCOLOR_H
#define M_UTILS_DCOLOR_H


#include "../vec/dvec3.h"

// rgb[0:1] hsv[0:360, 0:1, 0:1]
static dvec3 dvec3_rgb2hsv(dvec3 rgb) {
    dvec3 hsv;
    double min, max, delta;

    min = rgb.r < rgb.g ? rgb.r : rgb.g;
    min = min < rgb.b ? min : rgb.b;

    max = rgb.r > rgb.g ? rgb.r : rgb.g;
    max = max > rgb.b ? max : rgb.b;

    hsv.v2 = max;
    delta = max - min;
    if (delta < (double) 0.00001) {
        hsv.v0 = 0; // undefined
        hsv.v1 = 0;
        return hsv;
    }
    if (max > 0) {
        // NOTE: if Max is == 0, this divide would cause a crash
        hsv.v1 = (delta / max);
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        hsv.v0 = 0;
        hsv.v1 = 0;
        return hsv;
    }
    if (rgb.r >= max)
        // > is bogus, just keeps compilor happy
        hsv.v0 = (rgb.g - rgb.b) / delta;
        // between yellow & magenta
    else if (rgb.g >= max)
        hsv.v0 = (double) 2 + (rgb.b - rgb.r) / delta;
        // between cyan & yellow
    else
        hsv.v0 = (double) 4 + (rgb.r - rgb.g) / delta;
    // between magenta & cyan

    hsv.v0 *= 60; // degrees

    if (hsv.v0 < 0)
        hsv.v0 += 360;
    return hsv;
}

// rgb[0:1] hsv[0:360, 0:1, 0:1]
static dvec3 dvec3_hsv2rgb(dvec3 hsv) {
    dvec3 rgb;
    double hh, p, q, t, ff;
    long i;

    if (hsv.v1 <= 0.0) {
        // < is bogus, just shuts up warnings
        rgb.r = hsv.v2;
        rgb.g = hsv.v2;
        rgb.b = hsv.v2;
        return rgb;
    }
    hh = hsv.v0;
    if (hh >= 360) hh = 0;
    hh /= 60;
    i = (long) hh;
    ff = hh - i;
    p = hsv.v2 * ((double) 1 - hsv.v1);
    q = hsv.v2 * ((double) 1 - (hsv.v1 * ff));
    t = hsv.v2 * ((double) 1 - (hsv.v1 * ((double) 1 - ff)));

    switch (i) {
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

#endif //M_UTILS_DCOLOR_H
