#ifndef PIXELC_ANIMATION_H
#define PIXELC_ANIMATION_H

#include <stdbool.h>

extern bool animation_show;


void animation_init(int frames, float fps);

void animation_update(float dtime);

void animation_render();

#endif //PIXELC_ANIMATION_H