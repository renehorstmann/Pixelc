#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "u/color.h"
#include "canvas.h"
#include "selection.h"
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

enum selectionmode {
    BRUSH_SELECTION_NONE,
    BRUSH_SELECTION_COPY,
    BRUSH_SELECTION_CUT,
    BRUSH_SELECTION_PASTE,
    BRUSH_NUM_SELECTION_MODES
};

typedef struct Brush {
    Selection *selection;
    BrushMode *brushmode;

    Canvas *canvas_ref;
    struct Toolbar *toolbar_ref;    // warning, set by toolbar.c

    uColor_s current_color;
    uColor_s secondary_color;
    enum brushmodes mode;
    int shape;
    bool shading_active;
    enum selectionmode selection_mode;

    struct {
        bool change;
        bool selection_active;
        bool selection_set;
        bool selection_moving;
        ivec2 selection_pos;
    } L;
} Brush;

Brush *brush_new(Canvas *canvas);

void brush_pointer_event(Brush *self, ePointer_s pointer);

bool brush_draw_pixel(Brush *self, int c, int r);

bool brush_draw(Brush *self, int c, int r);

void brush_abort_current_draw(Brush *self);

void brush_set_selection_active(Brush *self, bool active, bool reset);


#endif //PIXELC_BRUSH_H
