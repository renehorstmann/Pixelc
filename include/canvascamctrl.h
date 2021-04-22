#ifndef PIXELC_CANVASCAMCTRL_H
#define PIXELC_CANVASCAMCTRL_H

#include <stdbool.h>
#include "e/input.h"

#define CANVAS_CAMERA_CONTROL_WHEEL_ZOOM_FACTOR 1.1
#define CANVAS_CAMERA_CONTROL_SMOOTH_ALPHA 0.5

void canvascamctrl_init();

void canvascamctrl_set_home();

bool canvascamctrl_pointer_event(ePointer_s pointer);

#endif //PIXELC_CANVASCAMCTRL_H
