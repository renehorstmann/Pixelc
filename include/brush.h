#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "color.h"

enum brushmodes {
    BRUSH_MODE_FREE, 
    BRUSH_MODE_DOT,
    BRUSH_MODE_DITHER,
    BRUSH_MODE_DITHER2,
    BRUSH_MODE_FILL, 
    BRUSH_MODE_FILL8,
    BRUSH_NUM_MODES};

extern Color_s brush_current_color;
extern Color_s brush_secondary_color;
extern enum brushmodes brush_mode;
extern int brush_shape;
extern bool brush_shading_active;

void brush_init();

void brush_pointer_event(ePointer_s pointer);

bool brush_draw_pixel(float x, float y);

bool brush_draw(float x, float y);

void brush_abort_current_draw();

#endif //PIXELC_BRUSH_H
