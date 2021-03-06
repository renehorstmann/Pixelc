#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "u/color.h"

enum brushmodes {
    BRUSH_MODE_FREE,
    BRUSH_MODE_DOT,
    BRUSH_MODE_DITHER,
    BRUSH_MODE_DITHER2,
    BRUSH_MODE_FILL,
    BRUSH_MODE_FILL8,
    BRUSH_MODE_REPLACE,
    BRUSH_NUM_MODES
};

enum selectionmode {
    BRUSH_SELECTION_NONE,
    BRUSH_SELECTION_COPY,
    BRUSH_SELECTION_CUT,
    BRUSH_SELECTION_PASTE,
    BRUSH_NUM_SELECTION_MODES
};

struct BrushGlobals_s {
    uColor_s current_color;
    uColor_s secondary_color;
    enum brushmodes mode;
    int shape;
    bool shading_active;
    enum selectionmode selection_mode;
};
extern struct BrushGlobals_s brush;


void brush_init();

void brush_pointer_event(ePointer_s pointer);

bool brush_draw_pixel(int c, int r);

bool brush_draw(int c, int r);

void brush_abort_current_draw();

void brush_set_selection_active(bool active, bool reset);


#endif //PIXELC_BRUSH_H
