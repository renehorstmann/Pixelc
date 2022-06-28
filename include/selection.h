#ifndef PIXELC_SELECTION_H
#define PIXELC_SELECTION_H

#include "u/image.h"
#include "m/types/int.h"

typedef struct {
    int left, top;
    int cols, rows;
    bool blend;
    uImage opt_img;
} Selection;

Selection *selection_new(int left, int top, int cols, int rows);

void selection_kill(Selection **self_ptr);

bool selection_contains(const Selection *self, int c, int r);

void selection_copy(Selection *self, uImage from, int layer);

void selection_cut(Selection *self, uImage from, int layer, uColor_s replace);

void selection_paste(Selection *self, uImage to, int layer);

void selection_rotate(Selection *self, bool right);

void selection_mirror(Selection *self, bool vertical);

#endif //PIXELC_SELECTION_H
