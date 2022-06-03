#ifndef PIXELC_CAMERACTRL_H
#define PIXELC_CAMERACTRL_H

#include "rhc/rhc.h"
#include "e/input.h"

struct CameraCtrl_Globals {
    // turn this mode true, to let every pointer just move the camera
    bool move_mode;
};
extern struct CameraCtrl_Globals cameractrl;


void cameractrl_init();

void cameractrl_set_home(int canvas_cols, int canvas_rows);

bool cameractrl_pointer_event(ePointer_s pointer);

#endif //PIXELC_CAMERACTRL_H
