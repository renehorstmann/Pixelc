#ifndef PIXELC_INPUT_H
#define PIXELC_INPUT_H

#include "camera.h"
#include "canvascam.h"
#include "palette.h"
#include "brush.h"
#include "canvascamctrl.h"
#include "toolbar.h"

typedef struct {
    const Camera_s *camera_ref;
    const CanvasCam_s *canvascam_ref;
    Palette *palette_ref;
    Brush *brush_ref;
    Toolbar *toolbar_ref;
    CanvasCamCtrl *canvascamctrl_ref;
} InputCtrl;

InputCtrl *inputctrl_new(eInput *input, const Camera_s *camera, const CanvasCam_s *canvascam,
                         Palette *palette, Brush *brush, Toolbar *toolbar, CanvasCamCtrl *canvascamctrl);

#endif //PIXELC_INPUT_H
