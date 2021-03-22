#ifndef PIXELC_PALETTE_H
#define PIXELC_PALETTE_H

#include <stdbool.h>
#include "e/input.h"
#include "color.h"

#define PALETTE_MAX 80

void palette_init();

void palette_update(float dtime);

void palette_render();

// return true if the pointer was used (indicate event done)
bool palette_pointer_event(ePointer_s pointer);

float palette_get_hud_size();

int palette_get_color();

void palette_set_color(int index);

void palette_set_colors(const Color_s *palette, int size);

#endif //PIXELC_PALETTE_H
