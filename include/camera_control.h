#ifndef PIXELC_CAMERA_CONTROL_H
#define PIXELC_CAMERA_CONTROL_H

#include "e/input.h"

#define CAMERA_CONTROL_WHEEL_ZOOM_FACTOR 1.1

void camera_control_init();

void camera_control_pointer_event(ePointer_s pointer);

#endif //PIXELC_CAMERA_CONTROL_H
