#ifndef PIXELC_BRUSHMODE_H
#define PIXELC_BRUSHMODE_H

#include <stdbool.h>
#include "e/input.h"

void brushmode_reset();

bool brushmode_dot(ePointer_s pointer);

bool brushmode_free(ePointer_s pointer);

bool brushmode_free_line(ePointer_s pointer);

bool brushmode_fill(ePointer_s pointer, bool mode8);

bool brushmode_replace(ePointer_s pointer);

#endif //PIXELC_BRUSHMODE_H
