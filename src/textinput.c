#include "rhc/alloc.h"
#include "mathc/sca/float.h"
#include "r/texture.h"
#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/ro_text.h"
#include "u/pose.h"
#include "textinput.h"

#define KEY_COLS 10
#define KEY_ROWS 4
#define MAX_WIDTH 250

//
// private
//


// shift alternates between lower, upper, alt
// S = shift
// BB = backspace
// CC = cancel
// SSSSSS = space
// OO = ok

static const char layout[4][10] = {
   "qwertzhiop",
   "asdfghjkl_",
   "SyxcvbnmBB",
   "CCSSSSSSOO"
};
static const char layout_alt[4][10] = {
   "1234567890",
   "+-*/=<>()%",
   "S!?#.,;:BB",
   "CCSSSSSSOO"   
};

void set_key_pos(mat4 *pose, const Camera_s *cam, int col, int row, int cols, float y_offset) {
    float width = camera_width(cam)-16;
    width = sca_min(width, MAX_WIDTH);
    
    
    float x = 8-width/2 + width * col / KEY_COLS + (cols-1) * 8;
    float y = cam->RO.bottom + 12 + 16*(KEY_ROWS-row-1) + y_offset;
    u_pose_set_xy(pose, (int) x, (int) y);
}



//
// public
//

TextInput *textinput_new(eInput *input) {
    TextInput *self = rhc_calloc(sizeof *self);
    
    self->input_ref = input;
    
    self->L.textfield = ro_text_new_font85(TEXTINPUT_MAX_CHARS);
    
    self->L.keys = ro_batch_new(27, 
            r_texture_new_file(2, 1, "res/textinput_key.png"));
    
    self->L.chars = ro_batch_new(27, self->L.textfield.ro.L.tex);
    self->L.chars.owns_tex = false;
    
    self->L.shift = ro_single_new(
            r_texture_new_file(2, 3, "res/textinput_key_shift.png"));
    self->L.space = ro_single_new(
            r_texture_new_file(2, 1, "res/textinput_key_space.png"));
    self->L.special = ro_batch_new(3,
            r_texture_new_file(2, 3, "res/textinput_key_special.png"));
            
    for(int i=0; i<27; i++) {
        self->L.keys.rects[i].pose = u_pose_new(0, 0, 16, 16);
        self->L.chars.rects[i].pose = u_pose_new(0, 0, 5, 8);
        self->L.chars.rects[i].color = R_COLOR_BLACK;
    }
    
    self->L.shift.rect.pose = u_pose_new(0, 0, 16, 16);
    self->L.space.rect.pose = u_pose_new(0, 0, 16*6, 16);
    for(int i=0; i<3; i++) {
        self->L.special.rects[i].pose = u_pose_new(0, 0, 16*2, 16);
        self->L.special.rects[i].sprite.y = i;
    }
    
    return self;
}

void textinput_kill(TextInput **self_ptr) {
    TextInput *self = *self_ptr;
    if(!self)
        return;
    
    ro_text_kill(&self->L.textfield);
    ro_batch_kill(&self->L.keys);
    ro_batch_kill(&self->L.chars);
    
    rhc_free(self);
    *self_ptr = NULL;
}

void textinput_update(TextInput *self, const Camera_s *cam, float dtime) {
    ro_text_set_text(&self->L.textfield, self->text);
    
    int idx = 0;
    for(int r=0; r<3; r++) {
        for(int c=0; c<10; c++) {
            char key = self->L.shiftstate==TEXTINPUT_SHIFT_ALT?  layout_alt[r][c] : layout[r][c];
            if(isupper(key))
                continue;
            if(self->L.shiftstate==TEXTINPUT_SHIFT_UPPER)
                key = toupper(key);
                
            set_key_pos(&self->L.keys.rects[idx].pose, cam, c, r, 1, 0);
            set_key_pos(&self->L.chars.rects[idx].pose, cam, c, r, 1, 1);
            
            self->L.textfield.sprite_fn(&self->L.chars.rects[idx].sprite, key);
            
            idx++;
        } 
    }
    
    set_key_pos(&self->L.shift.rect.pose, cam, 0, 2, 1, 0);
    set_key_pos(&self->L.space.rect.pose, cam, 2, 3, 6, 0);
    
    // ok, cancel, backspace
    set_key_pos(&self->L.special.rects[0].pose, cam, 8, 3, 2, 0);
    set_key_pos(&self->L.special.rects[1].pose, cam, 0, 3, 2, 0);
    set_key_pos(&self->L.special.rects[2].pose, cam, 8, 2, 2, 0);
    
    ro_batch_update(&self->L.keys);
    ro_batch_update(&self->L.chars);
    ro_batch_update(&self->L.special);
}

void textinput_render(const TextInput *self, const mat4 *cam_mat) {
    ro_text_render(&self->L.textfield, cam_mat);
    ro_batch_render(&self->L.keys, cam_mat);
    ro_batch_render(&self->L.chars, cam_mat);
    ro_single_render(&self->L.shift, cam_mat);
    ro_single_render(&self->L.space, cam_mat);
    ro_batch_render(&self->L.special, cam_mat);
}

