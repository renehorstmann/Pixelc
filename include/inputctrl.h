#ifndef PIXELC_INPUT_H
#define PIXELC_INPUT_H

#include "camera.h"
#include "camera.h"
#include "palette.h"
#include "brush.h"
#include "selectionctrl.h"
#include "cameractrl.h"
#include "toolbar.h"

typedef struct {
    const Camera_s *camera_ref;
    const Camera_s *canvascam_ref;
    Palette *palette_ref;
    Brush *brush_ref;
    SelectionCtrl *selectionctrl_ref;
    Toolbar *toolbar_ref;
    CameraCtrl *canvascamctrl_ref;
} InputCtrl;

InputCtrl *inputctrl_new(eInput *input, const Camera_s *camera, const Camera_s *canvascam,
                         Palette *palette, Brush *brush, 
                         SelectionCtrl *selectionctrl, Toolbar *toolbar, CameraCtrl *canvascamctrl);

#endif //PIXELC_INPUT_H
