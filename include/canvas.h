#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include <stdint.h>

void canvas_init();

void canvas_update(float dtime);

void canvas_render();

void canvas_set_color(int x, int y, uint32_t color);

void canvas_set_color_rgba(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);

#endif //PIXELC_CANVAS_H
