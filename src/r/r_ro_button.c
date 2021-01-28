
#include "mathc/float.h"
#include "u/pose.h"
#include "r/ro_button.h"


void r_ro_button_init(rRoSingle *self, const float *vp, GLuint tex_sink) {
	r_ro_single_init(self, vp, tex_sink);
	
	u_pose_set_size(&self->rect.uv, 0.5, 1);
}

bool r_ro_button_clicked(rRoSingle *self, bool pointer_in_rect, bool up) {
	if(pointer_in_rect && !up) {
		u_pose_set_x(&self->rect.uv, 0.5);
	} else {
		u_pose_set_x(&self->rect.uv, 0);
	}
	return pointer_in_rect && up;
}

