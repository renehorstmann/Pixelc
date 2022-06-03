#ifndef PIXELC_ANIMATION_H
#define PIXELC_ANIMATION_H

#include "rhc/rhc.h"
#include "mathc/types/float.h"


struct Animation_Globals {
    bool show;
};
extern struct Animation_Globals animation;

void animation_init(int multi_cols, int multi_rows, float size, int frames, float fps);

void animation_update(float palette_hud_size, float dtime);

void animation_render(const mat4 *camera_mat);

void animation_longpress(vec2 pos, vec4 color);

#endif //PIXELC_ANIMATION_H
