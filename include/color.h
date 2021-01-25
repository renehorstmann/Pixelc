#ifndef PIXELC_COLOR_H
#define PIXELC_COLOR_H

#include <stdint.h>
#include "e/core.h"
#include "mathc/types/float.h"

typedef struct {
    uint8_t r, g, b, a;
} color;
_Static_assert(sizeof(color) == 4, "color not packed?");

static vec4 color_to_float(color c) {
	return (vec4) {{
		c.r / 255.0f,
		c.g / 255.0f,
		c.b / 255.0f,
		c.a / 255.0f
	}};
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
