#ifndef PIXELC_MODAL_H
#define PIXELC_MODAL_H

//
// modal views are displayed on top of everything else
// for the shared modules:
//      textinput
//      colorpicker
//

#include "textinput.h"
#include "colorpicker.h"


void modal_update(float dtime);

// modal apps have their own camera
void modal_render();

// returns true if an modal activity is running
bool modal_active();

// assumes that no other modal activity is running
// pass NULL to reset
void modal_set_textinput(TextInput *set);


// assumes that no other modal activity is running
// pass NULL to reset
void modal_set_colorpicker(ColorPicker *set);



#endif //PIXELC_MODAL_H
