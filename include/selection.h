#ifndef PIXELC_SELECTION_H
#define PIXELC_SELECTION_H

#include <stdbool.h>
#include "mathc/types/int.h"
#include "image.h"


void selection_init(int left, int top, int cols, int rows);

void selection_kill();

bool selection_active();

ivec2 selection_pos();
ivec2 selection_size();

void selection_move(int left, int top);

bool selection_contains(int c, int r);

void selection_copy(const Image *from, int layer);

void selection_cut(Image *from, int layer, Color_s replace);

void selection_paste(Image *to, int layer);

#endif //PIXELC_SELECTION_H
