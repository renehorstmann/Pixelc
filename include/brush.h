#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "u/color.h"
#include "canvas.h"
#include "selectionctrl.h"
#include "brushmode.h"

struct Toolbar;

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


typedef struct Brush {
    BrushMode *brushmode;

    Canvas *canvas_ref;
    const SelectionCtrl *selectionctrl_ref;
    
    uColor_s current_color;
    uColor_s secondary_color;
    enum brushmodes mode;
    int shape;
    bool shading_active;
    
    struct {
        bool change;
    } L;
} Brush;

Brush *brush_new(Canvas *canvas, const SelectionCtrl *selectionctrl);

void brush_pointer_event(Brush *self, ePointer_s pointer);

bool brush_draw_pixel(Brush *self, int c, int r);

bool brush_draw(Brush *self, int c, int r);

void brush_abort_current_draw(Brush *self);

void brush_clear(Brush *self);

#endif //PIXELC_BRUSH_H
