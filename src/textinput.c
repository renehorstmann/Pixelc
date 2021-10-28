#include "rhc/alloc.h"
#include "r/texture.h"
#include "r/ro_batch.h"
#include "r/ro_text.h"
#include "textinput.h"

//
// private
//

//
// public
//

TextInput *textinput_new(eInput *input) {
    TextInput *self = rhc_calloc(sizeof *self);
    
    self->input_ref = input;
    
    self->L.textfield = ro_text_new_font85(TEXTINPUT_MAX_CHARS);
    
    self->L.keys = ro_batch_new(10, 
            r_texture_new_file(2, 1, "res/textinput_key.png"));
    
    self->L.chars = ro_batch_new(10, self->L.textfield.ro.L.tex);
    self->L.chars.owns_tex = false;
            
    for(int i=0; i<10; i++) {
        self->L.textfield.sprite_fn(&self->L.chars.rects[i].sprite, '0'+i);
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
}

void textinput_render(const TextInput *self, const mat4 *camera_mat) {
    ro_text_render(&self->L.textfield, camera_mat);
}

