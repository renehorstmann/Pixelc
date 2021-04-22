#ifndef PIXELC_BACKGROUND_H
#define PIXELC_BACKGROUND_H

#include "u/color.h"

void background_init(uColor_s a, uColor_s b);

void background_update(float dtime);

void background_render();

#endif //PIXELC_BACKGROUND_H
