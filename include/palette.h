#ifndef PIXELC_PALETTE_H
#define PIXELC_PALETTE_H

#include <stdbool.h>
#include "e/input.h"
#include "color.h"

#define PALETTE_MAX 60
#define PALETTE_COLS 10

void palette_init();

// return true if the pointer was used (indicate event done)
bool palette_pointer_event(ePointer_s pointer);

void palette_set_colors(const Color_s *palette, int size);

void palette_select_color(int index);

void palette_update(float dtime);

void palette_render();

#endif //PIXELC_PALETTE_H
