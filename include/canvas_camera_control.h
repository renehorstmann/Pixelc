#ifndef PIXELC_CANVAS_CAMERA_CONTROL_H
#define PIXELC_CANVAS_CAMERA_CONTROL_H

#include <stdbool.h>
#include "e/input.h"

#define CANVAS_CAMERA_CONTROL_WHEEL_ZOOM_FACTOR 1.1
#define CANVAS_CAMERA_CONTROL_SMOOTH_ALPHA 0.5

void canvas_camera_control_init();

void canvas_camera_control_set_home();

bool canvas_camera_control_pointer_event(ePointer_s pointer);

#endif //PIXELC_CANVAS_CAMERA_CONTROL_H
