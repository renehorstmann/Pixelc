
#include "mathc/float.h"
#include "u/pose.h"
#include "hud_camera.h"
#include "button.h"



static bool in_rect(ePointer_s pointer, mat4 pose) {
    vec4 screen_pos = {{pointer.x, pointer.y, 0, 1}};

    mat4 pose_inv = mat4_inv(pose);
    mat4 screen_to_rect = mat4_mul_mat(pose_inv, hud_camera_p_inv);

    vec4 rect_pos = mat4_mul_vec(screen_to_rect, screen_pos);

    float x = rect_pos.x;
    float y = rect_pos.y;

    return x>=-0.5 && x<=0.5 && y>=-0.5 && y<=0.5;
}


void button_init(rRoSingle *self, GLuint tex_sink) {
	r_ro_single_init(self, &hud_camera_p.m00, tex_sink);
	
	u_pose_set_size(&self->rect.uv, 0.5, 1);
}

bool button_is_pressed(rRoSingle *self) {
	return u_pose_get_x(self->rect.uv) > 0.25;
}

void button_set_pressed(rRoSingle *self, bool pressed) {
	u_pose_set_x(&self->rect.uv, pressed ? 0.5 : 0);
}



bool button_clicked(rRoSingle *self, ePointer_s pointer) {
    bool in_r = in_rect(pointer, self->rect.pose);
    bool press = pointer.action == E_POINTER_DOWN && in_r;
    bool clicked = pointer.action == E_POINTER_UP && button_is_pressed(self);   // was pressed before

    if(press) {
        button_set_pressed(self, true);
    }
    if(!in_r || clicked) {
        button_set_pressed(self, false);
    }
    return clicked;
}

bool button_pressed(rRoSingle *self, ePointer_s pointer) {
    bool press = pointer.action == E_POINTER_DOWN && in_rect(pointer, self->rect.pose);

    if(press) {
        button_set_pressed(self, true);
    }
    return press;
}
