#ifndef PIXELC_PALETTE_H
#define PIXELC_PALETTE_H

#include "color.h"

#define PALETTE_MAX 64

void palette_init();

// return true if the pointer was used (indicate event done)
bool palette_pointer_event(ePointer_s pointer);

void palette_set_colors(const color *palette, int size);

void palette_select_color(int index);

void palette_update(float dtime);

void palette_render();

#endif //PIXELC_PALETTE_H
