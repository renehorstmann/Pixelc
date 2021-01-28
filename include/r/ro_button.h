#ifndef R_BUTTON_H
#define R_BUTTON_H

#include <stdbool.h>
#include "ro_single.h"


void r_ro_button_init(rRoSingle *self, const float *vp, GLuint tex_sink);

bool r_ro_button_is_pressed(rRoSingle *self);

void r_ro_button_set_pressed(rRoSingle *self, bool pressed);

bool r_ro_button_clicked(rRoSingle *self, bool pointer_in_rect, bool up);

bool r_ro_button_pressed(rRoSingle *self, bool pointer_in_rect, bool up);

#endif //R_BUTTON_H
