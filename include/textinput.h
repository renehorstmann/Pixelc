#ifndef PIXELC_TEXTINPUT_H
#define PIXELC_TEXTINPUT_H

#include "r/ro_types.h"
#include "camera.h"
#include "e/input.h"

#define TEXTINPUT_MAX_CHARS 32

typedef struct {
    eInput *input_ref;
    
    char text[TEXTINPUT_MAX_CHARS];
    bool finished;

    struct {
        // RoSingle field_bg;
        RoText textfield;
        RoBatch keys;
        RoBatch chars;
    } L;
} TextInput;

TextInput *textinput_new(eInput *input);

void textinput_kill(TextInput **self_ptr);

void textinput_update(TextInput *self, const Camera_s *cam, float dtime);

void textinput_render(const TextInput *self, const mat4 *camera_mat);

#endif //PIXELC_TEXTINPUT_H
