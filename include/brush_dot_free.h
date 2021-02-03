#ifndef PIXELC_BRUSH_DOT_FREE_H
#define PIXELC_BRUSH_DOT_FREE_H

#include <stdbool.h>
#include "e/input.h"

bool brush_dot(ePointer_s pointer);

bool brush_free(ePointer_s pointer, bool *is_drawing);

#endif //PIXELC_BRUSH_DOT_FREE_H
