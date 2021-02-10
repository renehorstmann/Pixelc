#ifndef PIXELC_SELECTION_H
#define PIXELC_SELECTION_H

#include <stdbool.h>
#include "image.h"

void selection_init(int left, int top, int width, int height);

void selection_kill();

bool selection_contains(int x, int y);

void selection_copy(Image *from, int layer);

void selection_cut(Image *from, int layer, Color_s replace);

void selection_paste(Image *to, int layer);

#endif //PIXELC_SELECTION_H
