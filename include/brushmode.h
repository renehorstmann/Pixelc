#ifndef PIXELC_BRUSHMODE_H
#define PIXELC_BRUSHMODE_H

#include <stdbool.h>
#include "e/input.h"
#include "canvas.h"

enum brushmode_func {
    BRUSHMODE_FUNC_LINE,
    BRUSHMODE_FUNC_RECT,
    BRUSHMODE_FUNC_CIRCLE,
    BRUSHMODE_NUM_FUNCS
};

struct Brush;

typedef struct {
    struct Brush *brush_ref;
    Canvas *canvas_ref;

    struct {
        bool is_drawing;
        ivec2 start;
    } L;
} BrushMode;

BrushMode *brushmode_new(struct Brush *brush, Canvas *canvas);

void brushmode_reset(BrushMode *self);

bool brushmode_dot(BrushMode *self, ePointer_s pointer);

bool brushmode_free(BrushMode *self, ePointer_s pointer);

bool brushmode_func(BrushMode *self, ePointer_s pointer, enum brushmode_func func);

void brushmode_pipette(BrushMode *self, ePointer_s pointer);

bool brushmode_fill(BrushMode *self, ePointer_s pointer, bool mode8);

bool brushmode_replace(BrushMode *self, ePointer_s pointer);

#endif //PIXELC_BRUSHMODE_H
