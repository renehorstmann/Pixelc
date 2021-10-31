#ifndef PIXELC_TEXTINPUT_H
#define PIXELC_TEXTINPUT_H

#include "r/ro_types.h"
#include "camera.h"
#include "e/input.h"

#define TEXTINPUT_MAX_CHARS 32

enum TextInput_shiftstate {
    TEXTINPUT_SHIFT_LOWER,
    TEXTINPUT_SHIFT_UPPER,
    TEXTINPUT_SHIFT_ALT,
    TEXTINPUT_SHIFT_NUM_STATES
};

typedef struct {
    eInput *input_ref;
    const Camera_s *camera_ref;
    
    char text[TEXTINPUT_MAX_CHARS];
    bool finished;

    struct {
        // RoSingle field_bg;
        RoText textfield;
        RoBatch keys;
        RoBatch chars;
        RoSingle shift, space;
        RoBatch special;
        RoSingle bg;
        
        enum TextInput_shiftstate shiftstate;
        
        float blink_time;
    } L;
} TextInput;

TextInput *textinput_new(eInput *input, const Camera_s *cam);

void textinput_kill(TextInput **self_ptr);

void textinput_update(TextInput *self, float dtime);

void textinput_render(const TextInput *self, const mat4 *cam_mat);

#endif //PIXELC_TEXTINPUT_H
