#ifndef PIXELC_CAMERA_CONTROL_H
#define PIXELC_CAMERA_CONTROL_H

#include <stdbool.h>
#include "e/input.h"

#define CAMERA_CONTROL_WHEEL_ZOOM_FACTOR 1.1
#define CAMERA_CONTROL_SMOOTH_ALPHA 0.5

void camera_control_init();

void camera_control_set_home();

bool camera_control_pointer_event(ePointer_s pointer);

#endif //PIXELC_CAMERA_CONTROL_H
