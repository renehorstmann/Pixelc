#ifndef PIXELC_CAMERACTRL_H
#define PIXELC_CAMERACTRL_H

#include "s/s.h"
#include "e/input.h"

struct CameraCtrl_Globals {
    // turn this mode true, to let every pointer just move the camera
    bool move_mode;
};
extern struct CameraCtrl_Globals cameractrl;


void cameractrl_init();

void cameractrl_update(float dtime);

void cameractrl_set_home(void);

bool cameractrl_pointer_event(ePointer_s pointer);

#endif //PIXELC_CAMERACTRL_H
