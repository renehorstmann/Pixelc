#ifndef PIXELC_COLOR_H
#define PIXELC_COLOR_H

#include <stdint.h>
#include <stdbool.h>
#include "e/core.h"
#include "mathc/vec/ucvec4.h"
#include "mathc/vec/vec4.h"

typedef ucvec4 Color_s;

static bool color_equals(Color_s a, Color_s b) {
	return ucvec4_cmp(a, b);
}

static vec4 color_to_vec4(Color_s color) {
    return vec4_cast_from_uchar_1(color.v);
}

static Color_s color_from_hex(const char *hex_string) {
    Color_s c = {0};
    if(*hex_string == '#')
        hex_string++;

    // rgb
    if(strlen(hex_string) == 6) {
        for(int i=0; i<3; i++) {
            char buf[3] = {hex_string[0], hex_string[1], 0};
            hex_string+=2;
            c.v[i] = strtol(buf, NULL, 16);
        }
        c.a = 255;
        return c;
    }

    // rgba
    if(strlen(hex_string) == 8) {
        for(int i=0; i<4; i++) {
            char buf[3] = {hex_string[0], hex_string[1], 0};
            hex_string+=2;
            c.v[i] = strtol(buf, NULL, 16);
        }
        return c;
    }

    // error
    SDL_Log("color_from_hex failed for: %s", hex_string);
    return c;
}

static const Color_s COLOR_TRANSPARENT = {0, 0, 0, 0};
static const Color_s COLOR_BLACK = {0, 0, 0, 255};
static const Color_s COLOR_WHITE = {255, 255, 255, 255};
static const Color_s COLOR_RED = {255, 0, 0, 255};
static const Color_s COLOR_GREEN = {0, 255, 0, 255};
static const Color_s COLOR_BLUE = {0, 0, 255, 255};


#endif //PIXELC_COLOR_H
