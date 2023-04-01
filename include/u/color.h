#ifndef U_COLOR_H
#define U_COLOR_H

//
// pixel color based on m ucvec4 (uchar)
//

#include "s/s.h"
#include "m/vec/ucvec3.h"
#include "m/vec/ucvec4.h"
#include "m/vec/vec4.h"

// a color is a unsigned char vector with rgba elements
// access like other m types
typedef ucvec4 uColor_s;

// returns a == b
static bool u_color_equals(uColor_s a, uColor_s b) {
    return ucvec4_cmp(a, b);
}

// blends color b onto color a
static uColor_s u_color_blend(uColor_s a, uColor_s b) {
    uColor_s res;
    res.rgb = ucvec3_mix(a.rgb, b.rgb, b.a / 255.0f);
    res.a = ucsca_max(a.a, b.a);
    return res;
}

// casts a color into a vec4 in the range [0:1]
static vec4 u_color_to_vec4(uColor_s color) {
    return vec4_cast_from_uchar_1(color.v);
}

// casts a vec4 to a color from the range [0:1]
static uColor_s u_color_from_vec4(vec4 color) {
    return ucvec4_cast_from_float_1(color.v);
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
    s_error_set("color from hex failed");
    s_log_error("u_color_from_hex failed: for %s", hex_string);
    return c;
}

static const uColor_s U_COLOR_TRANSPARENT = {0, 0, 0, 0};
static const uColor_s U_COLOR_BLACK = {0, 0, 0, 255};
static const uColor_s U_COLOR_WHITE = {255, 255, 255, 255};
static const uColor_s U_COLOR_RED = {255, 0, 0, 255};
static const uColor_s U_COLOR_GREEN = {0, 255, 0, 255};
static const uColor_s U_COLOR_BLUE = {0, 0, 255, 255};


#endif //U_COLOR_H
