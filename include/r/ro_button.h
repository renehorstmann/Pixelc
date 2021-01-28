#ifndef R_BUTTON_H
#define R_BUTTON_H

#include <stdbool.h>
#include "ro_single.h"


void r_ro_button_init(rRoSingle *self, const float *vp, GLuint tex_sink);

bool r_ro_button_clicked(rRoSingle *self, bool pointer_in_rect, bool up);


#endif //R_BUTTON_H
