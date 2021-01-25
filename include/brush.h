#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "color.h"

void brush_init();

void brush_pointer_event(ePointer_s pointer);

void brush_set_color(color col);

#endif //PIXELC_BRUSH_H
