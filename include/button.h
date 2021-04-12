#ifndef PIXELC_BUTTON_H
#define PIXELC_BUTTON_H

#include <stdbool.h>
#include "e/input.h"
#include "r/ro_single.h"

void button_init(RoSingle *self, GLuint tex_sink);

bool button_is_pressed(RoSingle *self);

void button_set_pressed(RoSingle *self, bool pressed);

bool button_clicked(RoSingle *self, ePointer_s pointer);

bool button_pressed(RoSingle *self, ePointer_s pointer);

bool button_toggled(RoSingle *self, ePointer_s pointer);

#endif //PIXELC_BUTTON_H
