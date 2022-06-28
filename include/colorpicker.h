#ifndef SOME_COLORPICKER_H
#define SOME_COLORPICKER_H

//
// Color picker to select an uColor by hsv and values
// creates and usus its own camera (size=180)
//

#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/ro_text.h"
#include "u/image.h"
#include "m/types/int.h"

#define COLORPICKER_TITLE_MAX_LENGTH 28

enum colorpicker_state {
    COLORPICKER_IN_PROGRESS,
    COLORPICKER_CANCELED,
    COLORPICKER_DONE,
    COLORPICKER_NUM_STATES,
};

typedef struct {
    // default = true
    // reset for example by ok_active = strlen(out.text) > 4
    bool ok_active;
    vec4 bg_color;

    uColor_s color;
    enum colorpicker_state state;
    
    struct {
        RoText title;
        RoText title_shadow;
        RoSingle h, s, v;
        RoSingle r, g, b;
        RoSingle a, a_bg;
        RoBatch slider;
        RoText h_num, s_num, v_num;
        RoText r_num, g_num, b_num;
        RoText a_num;
        RoSingle color_prev, color_new;
        RoSingle color_bg;
        RoBatch btns;
        RoSingle bg;

        uColor_s init_color;
        bool enable_touch;

        struct {
            mat4 p, p_inv;
            float left, right, top, bottom;
            float width, height;
        } cam;
    } L;
} ColorPicker;


ColorPicker *colorpicker_new(const char *title, uColor_s init_color);

void colorpicker_kill(ColorPicker **self_ptr);

void colorpicker_update(ColorPicker *self, float dtime);

void colorpicker_render(const ColorPicker *self);

#endif //SOME_COLORPICKER_H
