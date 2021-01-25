#ifndef PIXELC_COLOR_H
#define PIXELC_COLOR_H

#include "e/core.h"
#include <stdint.h>

typedef struct {
    uint8_t r, g, b, a;
} color;
_Static_assert(sizeof(color) == 4, "color not packed?");

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
