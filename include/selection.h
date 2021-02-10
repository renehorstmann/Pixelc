#ifndef PIXELC_SELECTION_H
#define PIXELC_SELECTION_H

#include <stdbool.h>
#include "image.h"

void selection_init(int x, int y, int rows, int cols);

void selection_kill();

void selection_move(int x, int y);

bool selection_active();

bool selection_contains(int x, int y);

void selection_copy(const Image *from, int layer);

void selection_cut(Image *from, int layer, Color_s replace);

void selection_paste(Image *to, int layer);

#endif //PIXELC_SELECTION_H
