#include "modal.h"

struct Modal_Globals modal;

void modal_update(float dtime) {
    if(modal.textinput)
        textinput_update(modal.textinput, dtime);
    if(modal.colorpicker)
        colorpicker_update(modal.colorpicker, dtime);
}

void modal_render() {
    if(modal.textinput)
        textinput_render(modal.textinput);
    if(modal.colorpicker)
        colorpicker_render(modal.colorpicker);
}
