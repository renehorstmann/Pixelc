#ifndef PIXELC_MODAL_H
#define PIXELC_MODAL_H

#include "textinput.h"
#include "colorpicker.h"

struct Modal_Globals {

    // set these to NULL to deactivate
    TextInput *textinput;
    ColorPicker *colorpicker;
};
extern struct Modal_Globals modal;

static bool modal_active() {
    return modal.textinput || modal.colorpicker;
}

void modal_update(float dtime);

// modal apps have their own camera
void modal_render();

#endif //PIXELC_MODAL_H
