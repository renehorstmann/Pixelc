#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "u/color.h"
#include "canvas.h"
#include "selection.h"
#include "brushmode.h"

struct Toolbar;

enum brush_modes {
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
    
    uColor_s current_color;
    uColor_s secondary_color;
    enum brush_modes mode;
    int shape;
    bool shading_active;
    
    uImage kernel;
    
    struct {
        const Selection *selection_ref;
    } in;
    
    struct {
        bool change;
    } L;
} Brush;

Brush *brush_new(Canvas *canvas);

void brush_pointer_event(Brush *self, ePointer_s pointer);

bool brush_draw_pixel(Brush *self, int c, int r);

bool brush_draw(Brush *self, int c, int r);

void brush_abort_current_draw(Brush *self);

void brush_clear(Brush *self);


// creates the default kernel files
// sets self->kernel to the first new kernel file
// resets the config->kernels_size and saves the config
void brush_reset_kernel_files(Brush *self /*, Config *config */);

#endif //PIXELC_BRUSH_H
