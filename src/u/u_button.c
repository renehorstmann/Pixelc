#include "u/pose.h"
#include "u/button.h"


bool u_button_is_pressed(rRect_s *self) {
    return self->sprite.x > 0.5;
}

void u_button_set_pressed(rRect_s *self, bool pressed) {
    self->sprite.x = pressed ? 1 : 0;
}


bool u_button_clicked(rRect_s *self, ePointer_s pointer) {
    bool in_r = u_pose_aa_contains(self->pose, pointer.pos.xy);
    bool press = pointer.action == E_POINTER_DOWN && in_r;
    bool clicked = pointer.action == E_POINTER_UP && u_button_is_pressed(self);   // was pressed before

    if (press) {
        u_button_set_pressed(self, true);
    }
    if (!in_r || clicked) {
        u_button_set_pressed(self, false);
    }
    return clicked;
}

bool u_button_pressed(rRect_s *self, ePointer_s pointer) {
    bool press = pointer.action == E_POINTER_DOWN && u_pose_aa_contains(self->pose, pointer.pos.xy);

    if (press) {
        u_button_set_pressed(self, true);
    }
    return press;
}

bool u_button_toggled(rRect_s *self, ePointer_s pointer) {
    bool toggle = pointer.action == E_POINTER_UP && u_pose_aa_contains(self->pose, pointer.pos.xy);

    if (toggle) {
        u_button_set_pressed(self, !u_button_is_pressed(self));
    }
    return toggle;
}




bool u_button_darken_is_pressed(rRect_s *self){
    return self->color.r < 0.99;
}

void u_button_darken_set_pressed(rRect_s *self, bool pressed, vec4 color_darken) {
    assert(color_darken.r <0.99 && "color_darken.r needs to be changed to get the button_darken working");
    self->color = pressed ? color_darken : R_COLOR_WHITE;
}

bool u_button_darken_clicked(rRect_s *self, ePointer_s pointer, vec4 color_darken) {
    bool in_r = u_pose_aa_contains(self->pose, pointer.pos.xy);
    bool press = pointer.action == E_POINTER_DOWN && in_r;
    bool clicked = pointer.action == E_POINTER_UP && u_button_darken_is_pressed(self);   // was pressed before

    if (press) {
        u_button_darken_set_pressed(self, true, color_darken);
    }
    if (!in_r || clicked) {
        u_button_darken_set_pressed(self, false, color_darken);
    }
    return clicked;
}

bool u_button_darken_pressed(rRect_s *self, ePointer_s pointer, vec4 color_darken) {
    bool press = pointer.action == E_POINTER_DOWN && u_pose_aa_contains(self->pose, pointer.pos.xy);

    if (press) {
        u_button_darken_set_pressed(self, true, color_darken);
    }
    return press;
}

bool u_button_darken_toggled(rRect_s *self, ePointer_s pointer, vec4 color_darken) {
    bool toggle = pointer.action == E_POINTER_UP && u_pose_aa_contains(self->pose, pointer.pos.xy);

    if (toggle) {
        u_button_darken_set_pressed(self, !u_button_is_pressed(self), color_darken);
    }
    return toggle;
}
