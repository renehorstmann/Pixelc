#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "color.h"

enum brushmodes {BRUSH_MODE_DOT, BRUSH_MODE_FREE};


void brush_init();

void brush_pointer_event(ePointer_s pointer);

void brush_set_color(Color_s col);

enum brushmodes brush_get_mode();

void brush_set_mode(enum brushmodes mode);

#endif //PIXELC_BRUSH_H
