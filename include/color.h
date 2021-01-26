#ifndef PIXELC_COLOR_H
#define PIXELC_COLOR_H

#include <stdint.h>
#include "e/core.h"
#include "mathc/types/float.h"

typedef union {
    uint8_t data[4];
    struct {
        uint8_t r, g, b, a;
    };
} color;
_Static_assert(sizeof(color) == 4, "color not packed?");

static vec4 color_to_vec4(color c) {
	return (vec4) {{
		c.r / 255.0f,
		c.g / 255.0f,
		c.b / 255.0f,
		c.a / 255.0f
	}};
}

static color color_from_vec4(vec4 v) {
    return (color) {
        v.x * 255,
        v.y * 255,
        v.z * 255,
        v.w * 255
    };
}

static color color_from_hex(const char *hex_string) {
    color c = {0};
    char buf[8];
    if(*hex_string == '#')
        hex_string++;

    // rgb
    if(strlen(hex_string) == 6) {
        for(int i=0; i<3; i++) {
            strncpy(buf, hex_string, 2);
            hex_string+=2;
            c.data[i] = strtol(buf, NULL, 16);
        }
        c.a = 255;
        return c;
    }

    // rgba
    if(strlen(hex_string) == 8) {
        for(int i=0; i<4; i++) {
            strncpy(buf, hex_string, 2);
            hex_string+=2;
            c.data[i] = strtol(buf, NULL, 16);
        }
        return c;
    }

    // error
    SDL_Log("color_from_hex failed for: %s", hex_string);
    return c;
}

static void color_print(color c) {
    SDL_Log("(color) {%d, %d, %d, %d}", c.r, c.g, c.b, c.a);
}

static const color COLOR_TRANSPARENT = {0, 0, 0, 0};
static const color COLOR_BLACK = {0, 0, 0, 255};
static const color COLOR_WHITE = {255, 255, 255, 255};
static const color COLOR_RED = {255, 0, 0, 255};
static const color COLOR_GREEN = {255, 0, 0, 255};
static const color COLOR_BLUE = {255, 0, 0, 255};


#endif //PIXELC_COLOR_H
