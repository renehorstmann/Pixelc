#ifndef PIXELC_TILE_PALETTE_CAMERACTRL_H
#define PIXELC_TILE_PALETTE_CAMERACTRL_H

//
// Controls the camera to zoom and move the canvas
//

#include "s/s.h"
#include "e/input.h"

struct TilePaletteCameraCtrl_Globals {
    // turn this tile true, to let every pointer just move the camera
    bool move_mode;
};
extern struct TilePaletteCameraCtrl_Globals tile_palette_cameractrl;


void tile_palette_cameractrl_init();

void tile_palette_cameractrl_update(float dtime);

void tile_palette_cameractrl_set_home(void);

bool tile_palette_cameractrl_pointer_event(ePointer_s pointer);

#endif //PIXELC_TILE_PALETTE_CAMERACTRL_H
