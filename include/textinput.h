#ifndef SOME_TEXTINPUT_H
#define SOME_TEXTINPUT_H

//
// Textinput for a line with rhe (virtual) keyboard
// creates and isus its owh camera (size=180)
//

#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "mathc/types/int.h"

#define TEXTINPUT_MAX_CHARS 27
#define TEXTINPUT_TITLE_MAX_LENGTH 18

enum TextInput_shiftstate {
    TEXTINPUT_SHIFT_LOWER,
    TEXTINPUT_SHIFT_UPPER,
    TEXTINPUT_SHIFT_ALT,
    TEXTINPUT_SHIFT_NUM_STATES
};

enum TextInput_state {
    TEXTINPUT_IN_PROGRESS,
    TEXTINPUT_CANCELED,
    TEXTINPUT_DONE,
    TEXTINPUT_NUM_STATES,
};

typedef struct {
    // default = true
    // reset for example by ok_active = strlen(out.text) > 4
    bool ok_active;

    char text[TEXTINPUT_MAX_CHARS + 1];   // + '\0'
    enum TextInput_state state;
    enum TextInput_shiftstate shiftstate;

    struct {
        RoText title;
        RoText textfield;
        RoBatch keys;
        RoBatch chars;
        RoSingle shift, space;
        RoBatch special;
        RoSingle text_bg, bg;

        int max_chars;
        float blink_time;

        struct {
            mat4 p, p_inv;
            float left, right, top, bottom;
            float width, height;
        } cam;
    } L;
} TextInput;

// if opt_max_chars <= 0, TEXTINPUT_MAX_CHARS is used instead
TextInput *textinput_new(const char *title, int opt_max_chars);

void textinput_kill(TextInput **self_ptr);

void textinput_update(TextInput *self, float dtime);

void textinput_render(const TextInput *self);

#endif //SOME_TEXTINPUT_H
