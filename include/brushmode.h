#ifndef PIXELC_BRUSHMODE_H
#define PIXELC_BRUSHMODE_H

#include <stdbool.h>
#include "e/input.h"
#include "canvas.h"

struct Brush;

typedef struct {
    struct Brush *brush_ref;
    const Canvas *canvas_ref;

    struct {
        bool is_drawing;
        ivec2 last;
    } L;
} BrushMode;

BrushMode *brushmode_new(struct Brush *brush, const Canvas *canvas);

void brushmode_reset(BrushMode *self);

bool brushmode_dot(BrushMode *self, ePointer_s pointer);

bool brushmode_free(BrushMode *self, ePointer_s pointer);

bool brushmode_free_line(BrushMode *self, ePointer_s pointer);

bool brushmode_fill(BrushMode *self, ePointer_s pointer, bool mode8);

bool brushmode_replace(BrushMode *self, ePointer_s pointer);

#endif //PIXELC_BRUSHMODE_H
