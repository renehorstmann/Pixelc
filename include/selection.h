#ifndef PIXELC_SELECTION_H
#define PIXELC_SELECTION_H

#include "u/image.h"
#include "mathc/types/int.h"


void selection_init(int left, int top, int cols, int rows);

void selection_kill();

bool selection_active();

ivec2 selection_pos();

ivec2 selection_size();

void selection_move(int left, int top);

bool selection_contains(int c, int r);

void selection_copy(const uImage *from, int layer);

void selection_cut(uImage *from, int layer, uColor_s replace);

void selection_paste(uImage *to, int layer);

void selection_rotate(bool right);

void selection_mirror(bool vertical);

#endif //PIXELC_SELECTION_H
