
#include "mathc/float.h"
#include "u/pose.h"
#include "r/ro_button.h"


void r_ro_button_init(rRoSingle *self, const float *vp, GLuint tex_sink) {
	r_ro_single_init(self, vp, tex_sink);
	
	u_pose_set_size(&self->rect.uv, 0.5, 1);
}

bool r_ro_button_is_pressed(rRoSingle *self) {
	return u_pose_get_x(self->rect.uv) > 0.25;
}

void r_ro_button_set_pressed(rRoSingle *self, bool pressed) {
	u_pose_set_x(&self->rect.uv, pressed ? 0.5 : 0);
}

bool r_ro_button_clicked(rRoSingle *self, bool pointer_in_rect, bool up) {
	bool press = pointer_in_rect && !up;
	r_ro_button_set_pressed(self, press);
	return pointer_in_rect && up;
}

bool r_ro_button_pressed(rRoSingle *self, bool pointer_in_rect, bool up) {
	bool press = pointer_in_rect && !up && !r_ro_button_is_pressed(self);
	if(press)
	    r_ro_button_set_pressed(self, true);
	return press;
}

