#ifndef PIXELC_CAMERACTRL_H
#define PIXELC_CAMERACTRL_H

#include <stdbool.h>
#include "e/input.h"
#include "camera.h"
#include "brush.h"

#define CAMERA_CONTROL_WHEEL_ZOOM_FACTOR 1.1
#define CAMERA_CONTROL_SMOOTH_ALPHA 0.5

typedef struct {
    Camera_s *camera_ref;
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
} CameraCtrl;

CameraCtrl *cameractrl_new(eInput *input, Camera_s *camera, Brush *brush_ref);

void cameractrl_set_home(CameraCtrl *self);

bool cameractrl_pointer_event(CameraCtrl *self, ePointer_s pointer);

#endif //PIXELC_CAMERACTRL_H
