#ifndef MATHC_UTILS_DCOLOR_H
#define MATHC_UTILS_DCOLOR_H

#include "../vec/dvec3.h"

// rgb[0:1] hsv[0:360, 0:1, 0:1]
static dvec3 dvec3_rgb2hsv(dvec3 rgb) {
    dvec3 hsv;
    double min, max, delta;

    min = rgb.v0 < rgb.v1 ? rgb.v0 : rgb.v1;
    min = min  < rgb.v2 ? min  : rgb.v2;

    max = rgb.v0 > rgb.v1 ? rgb.v0 : rgb.v1;
    max = max  > rgb.v2 ? max  : rgb.v2;

    hsv.v2 = max;
    delta = max - min;
    if (delta < 0.00001) {
        hsv.v0 = 0; // undifined
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
    if(rgb.v0 >= max )
        // > is bogus, just keeps compilor happy
        hsv.v0 = (rgb.v1 - rgb.v2) / delta;
        // between yellow & magenta
    else if(rgb.v1 >= max )
        hsv.v0 = 2.0 + (rgb.v2 - rgb.v0) / delta;
        // between cyan & yellow
    else
        hsv.v0 = 4.0 + (rgb.v0 - rgb.v1) / delta;
    // between magenta & cyan

    hsv.v0 *= 60.0; // degrees

    if(hsv.v0 < 0)
        hsv.v0 += 360.0;
    return hsv;
}

// rgb[0:1] hsv[0:360, 0:1, 0:1]
static dvec3 dvec3_hsv2rgb(dvec3 hsv) {
    dvec3 rgb;
    double hh, p, q, t, ff;
    long i;

    if(hsv.v1 <= 0.0) {
        // < is bogus, just shuts up warnings
        rgb.v0 = hsv.v2;
        rgb.v1 = hsv.v2;
        rgb.v2 = hsv.v2;
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
            rgb.v0 = hsv.v2;
            rgb.v1 = t;
            rgb.v2 = p;
            break;
        case 1:
            rgb.v0 = q;
            rgb.v1 = hsv.v2;
            rgb.v2 = p;
            break;
        case 2:
            rgb.v0 = p;
            rgb.v1 = hsv.v2;
            rgb.v2 = t;
            break;

        case 3:
            rgb.v0 = p;
            rgb.v1 = q;
            rgb.v2 = hsv.v2;
            break;
        case 4:
            rgb.v0 = t;
            rgb.v1 = p;
            rgb.v2 = hsv.v2;
            break;
        case 5:
        default:
            rgb.v0 = hsv.v2;
            rgb.v1 = p;
            rgb.v2 = q;
            break;
    }
    return rgb;
}

#endif //MATHC_UTILS_DCOLOR_H
