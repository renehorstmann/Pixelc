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
