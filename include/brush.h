#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "color.h"

enum brushmodes {
    BRUSH_MODE_FREE, 
    BRUSH_MODE_DOT, 
    BRUSH_MODE_FILL, 
    BRUSH_MODE_FILL8,
    BRUSH_NUM_MODES};
    
enum brushshapes {
	BRUSH_SHAPE_DOT,
	BRUSH_SHAPE_DITHER,
	BRUSH_SHAPE_DITHER2,
	BRUSH_NUM_SHAPES};
	
enum brushsizes {
	BRUSH_SIZE_1 = 0,
	BRUSH_SIZE_3 = 1,
	BRUSH_SIZE_5 = 2,
	BRUSH_NUM_SIZES = 3};

extern Color_s brush_current_color;
extern Color_s brush_secondary_color;
extern enum brushmodes brush_mode;
extern enum brushshapes brush_shape;
extern enum brushsizes brush_size;
extern bool brush_shading_active;

void brush_init();

void brush_pointer_event(ePointer_s pointer);

bool brush_draw_pixel(float x, float y);

bool brush_draw(float x, float y);

void brush_abort_current_draw();

#endif //PIXELC_BRUSH_H
