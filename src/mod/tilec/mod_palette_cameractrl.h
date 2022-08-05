#ifndef PIXELC_MOD_PALETTE_CAMERACTRL_H
#define PIXELC_MOD_PALETTE_CAMERACTRL_H

//
// Controls the camera to zoom and move the canvas
//

#include "s/s.h"
#include "e/input.h"

struct ModPaletteCameraCtrl_Globals {
    // turn this mode true, to let every pointer just move the camera
    bool move_mode;
};
extern struct ModPaletteCameraCtrl_Globals mod_palette_cameractrl;


void mod_palette_cameractrl_init();

void mod_palette_cameractrl_update(float dtime);

void mod_palette_cameractrl_set_home(void);

bool mod_palette_cameractrl_pointer_event(ePointer_s pointer);

#endif //PIXELC_MOD_PALETTE_CAMERACTRL_H
