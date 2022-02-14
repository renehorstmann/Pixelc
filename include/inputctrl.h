#ifndef PIXELC_INPUT_H
#define PIXELC_INPUT_H

#include "camera.h"
#include "camera.h"
#include "palette.h"
#include "brush.h"
#include "selectionctrl.h"
#include "cameractrl.h"
#include "toolbar.h"
#include "tooltip.h"
#include "multitouchcursor.h"

typedef struct {
    const Camera_s *camera_ref;
    Palette *palette_ref;
    Brush *brush_ref;
    SelectionCtrl *selectionctrl_ref;
    Toolbar *toolbar_ref;
    Tooltip *tooltip_ref;
    CameraCtrl *canvascamctrl_ref;
    MultiTouchCursor *mtc_ref;
} InputCtrl;

InputCtrl *inputctrl_new(eInput *input, 
        const Camera_s *camera, 
        Palette *palette, 
        Brush *brush, 
        SelectionCtrl *selectionctrl, 
        Toolbar *toolbar,
        Tooltip *tooltip,
        CameraCtrl *canvascamctrl, 
        MultiTouchCursor *mtc);

#endif //PIXELC_INPUT_H
