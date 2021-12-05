#ifndef U_COLOR_H
#define U_COLOR_H

//
// pixel color based on mathc ucvec4 (uchar)
//

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mathc/vec/ucvec4.h"
#include "mathc/vec/vec4.h"
#include "rhc/error.h"
#include "rhc/log.h"

// a color is a unsigned char vector with rgba elements
// access like other mathc types
typedef ucvec4 uColor_s;

// returns a == b
static bool u_color_equals(uColor_s a, uColor_s b) {
    return ucvec4_cmp(a, b);
}

// casts a color into a vec4 in the range [0:1]
static vec4 u_color_to_vec4(uColor_s color) {
    return vec4_cast_from_uchar_1(color.v);
}

// creates a color from a hex string
static uColor_s u_color_from_hex(const char *hex_string) {
    uColor_s c = {0};
    if (*hex_string == '#')
        hex_string++;

    // rgb
    if (strlen(hex_string) == 6) {
        for (int i = 0; i < 3; i++) {
            char buf[3] = {hex_string[0], hex_string[1], 0};
            hex_string += 2;
            c.v[i] = strtol(buf, NULL, 16);
        }
        c.a = 255;
        return c;
    }

    // rgba
    if (strlen(hex_string) == 8) {
        for (int i = 0; i < 4; i++) {
            char buf[3] = {hex_string[0], hex_string[1], 0};
            hex_string += 2;
            c.v[i] = strtol(buf, NULL, 16);
        }
        return c;
    }

    // error
    rhc_error = "color from hex failed";
    log_error("u_color_from_hex failed: for %s", hex_string);
    return c;
}

static const uColor_s U_COLOR_TRANSPARENT = {0, 0, 0, 0};
static const uColor_s U_COLOR_BLACK = {0, 0, 0, 255};
static const uColor_s U_COLOR_WHITE = {255, 255, 255, 255};
static const uColor_s U_COLOR_RED = {255, 0, 0, 255};
static const uColor_s U_COLOR_GREEN = {0, 255, 0, 255};
static const uColor_s U_COLOR_BLUE = {0, 0, 255, 255};


#endif //U_COLOR_H
