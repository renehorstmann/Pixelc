#ifndef PIXELC_BRUSH_MODE_H
#define PIXELC_BRUSH_MODE_H

#include <stdbool.h>
#include "e/input.h"

void brush_mode_reset();

bool brush_mode_dot(ePointer_s pointer);

bool brush_mode_free(ePointer_s pointer);

bool brush_mode_free_line(ePointer_s pointer);

bool brush_mode_fill(ePointer_s pointer, bool mode8);


#endif //PIXELC_BRUSH_MODE_H
