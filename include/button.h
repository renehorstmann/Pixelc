#ifndef PIXELC_BUTTON_H
#define PIXELC_BUTTON_H

#include <stdbool.h>
#include "e/input.h"
#include "r/ro_single.h"

void button_init(rRoSingle *self, GLuint tex_sink);

bool button_is_pressed(rRoSingle *self);

void button_set_pressed(rRoSingle *self, bool pressed);

bool button_clicked(rRoSingle *self, ePointer_s pointer);

bool button_pressed(rRoSingle *self, ePointer_s pointer);

bool button_toggled(rRoSingle *self, ePointer_s pointer);

#endif //PIXELC_BUTTON_H
