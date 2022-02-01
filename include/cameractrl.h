#ifndef PIXELC_CAMERACTRL_H
#define PIXELC_CAMERACTRL_H

#include <stdbool.h>
#include "e/input.h"
#include "camera.h"
#include "brush.h"


typedef struct {
    eInput *input_ref;
    Camera_s *camera_ref;
    Brush *brush_ref;

    // turn this mode true, to let every pointer just move the camera
    bool move_mode;

    struct {
        vec2 pos;
        float size;

        vec2 pos0;
        vec2 move0;

        float size0;
        vec2 touch[2];
        bvec2 touching;
        float distance0;
        float distance;
        bool touched;

        struct {
            vec2 pointer_pos;
            bool moving;
        } cursor;

    } L;
} CameraCtrl;

CameraCtrl *cameractrl_new(eInput *input, Camera_s *camera, Brush *brush_ref);

void cameractrl_set_home(CameraCtrl *self, int canvas_cols, int canvas_rows);

bool cameractrl_pointer_event(CameraCtrl *self, ePointer_s pointer);

#endif //PIXELC_CAMERACTRL_H
