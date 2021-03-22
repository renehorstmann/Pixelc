#include "u/pose.h"
#include "camera.h"
#include "button.h"


void button_init(rRoSingle *self, GLuint tex_sink) {
    r_ro_single_init(self, camera.gl, tex_sink);

    u_pose_set_size(&self->rect.uv, 0.5, 1);
}

bool button_is_pressed(rRoSingle *self) {
    return u_pose_get_x(self->rect.uv) > 0.25;
}

void button_set_pressed(rRoSingle *self, bool pressed) {
    u_pose_set_x(&self->rect.uv, pressed ? 0.5 : 0);
}


bool button_clicked(rRoSingle *self, ePointer_s pointer) {
    bool in_r = u_pose_aa_contains(self->rect.pose, pointer.pos.xy);
    bool press = pointer.action == E_POINTER_DOWN && in_r;
    bool clicked = pointer.action == E_POINTER_UP && button_is_pressed(self);   // was pressed before

    if (press) {
        button_set_pressed(self, true);
    }
    if (!in_r || clicked) {
        button_set_pressed(self, false);
    }
    return clicked;
}

bool button_pressed(rRoSingle *self, ePointer_s pointer) {
    bool press = pointer.action == E_POINTER_DOWN && u_pose_aa_contains(self->rect.pose, pointer.pos.xy);

    if (press) {
        button_set_pressed(self, true);
    }
    return press;
}

bool button_toggled(rRoSingle *self, ePointer_s pointer) {
    bool toggle = pointer.action == E_POINTER_UP && u_pose_aa_contains(self->rect.pose, pointer.pos.xy);

    if (toggle) {
        button_set_pressed(self, !button_is_pressed(self));
    }
    return toggle;
}
