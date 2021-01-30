#ifndef PIXELC_TOOLBAR_H
#define PIXELC_TOOLBAR_H

#include <stdbool.h>
#include "e/input.h"


void toolbar_init();

void toolbar_update(float dtime);

void toolbar_render();

// return true if the pointer was used (indicate event done)
bool toolbar_pointer_event(ePointer_s pointer);

#endif //PIXELC_TOOLBAR_H
