#ifndef PIXELC_CANVASCAMCTRL_H
#define PIXELC_CANVASCAMCTRL_H

#include <stdbool.h>
#include "e/input.h"
#include "canvascam.h"
#include "brush.h"

#define CANVAS_CAMERA_CONTROL_WHEEL_ZOOM_FACTOR 1.1
#define CANVAS_CAMERA_CONTROL_SMOOTH_ALPHA 0.5

typedef struct {
    CanvasCam_s *camera_ref;
    Brush *brush_ref;

    struct {
        vec2 pos;
        float size;

        vec2 pos0;

        vec2 move0;

#ifdef OPTION_TOUCH
        float size0;
    vec2 touch[2];
    bvec2 touching;
    float distance0;
    bool touched;
#else
        vec2 pointer_pos;
        bool moving;
#endif

    } L;
} CanvasCamCtrl;

CanvasCamCtrl *canvascamctrl_new(eInput *input, CanvasCam_s *camera, Brush *brush_ref);

void canvascamctrl_set_home(CanvasCamCtrl *self);

bool canvascamctrl_pointer_event(CanvasCamCtrl *self, ePointer_s pointer);

#endif //PIXELC_CANVASCAMCTRL_H
