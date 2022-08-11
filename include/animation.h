#ifndef PIXELC_ANIMATION_H
#define PIXELC_ANIMATION_H

//
// Shows the image frames animated behind the canvas
//

#include "s/s.h"
#include "m/types/float.h"


enum animation_mode {
    ANIMATION_MODE_SINGLE,
    ANIMATION_MODE_REPEAT_H,
    ANIMATION_MODE_REPEAT_V,
    ANIMATION_MODE_REPEAT_HV,
    ANIMATION_NUM_MODES,
};

struct Animation_Globals {
    // shows the preview
    bool show;

    // preview size (default: 1.0)
    float size;

    // default: ANIMATION_MODE_SINGLE
    enum animation_mode mode;

    // if true, shows if frames are active (default: true)
    bool auto_show;
};
extern struct Animation_Globals animation;

void animation_init();

void animation_update(float dtime);

void animation_render(const mat4 *camera_mat);

#endif //PIXELC_ANIMATION_H
