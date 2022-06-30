#include "modal.h"

//
// private
//

static struct {
    TextInput *textinput;
    ColorPicker *colorpicker;
} L;

static void check_setable() {
    s_assume(!modal_active(), "already running an modal activity");
}

//
// public
//

void modal_update(float dtime) {
    if(L.textinput)
        textinput_update(L.textinput, dtime);
    if(L.colorpicker)
        colorpicker_update(L.colorpicker, dtime);
}

void modal_render() {
    if(L.textinput)
        textinput_render(L.textinput);
    if(L.colorpicker)
        colorpicker_render(L.colorpicker);
}

bool modal_active() {
    return L.textinput || L.colorpicker;
}

void modal_set_textinput(TextInput *set) {
    if(set)
        check_setable();
    L.textinput = set;
}


void modal_set_colorpicker(ColorPicker *set) {
    if(set)
        check_setable();
    L.colorpicker = set;
}
