#ifndef PIXELC_TOOLTIP_H
#define PIXELC_TOOLTIP_H

#include "toolbar.h"

typedef struct Tooltip {
    Toolbar *toolbar_ref;
    
    bool active;
    
    struct {
        RoSingle bg;
        RoSingle bg_shadow;
        RoText title;
        RoText title_shadow;
        RoText name;
        RoText tip;
    } L;
} Tooltip;

Tooltip *tooltip_new();

void tooltip_update(Tooltip *self, float dtime);

void tooltip_render(const Tooltip *self, const mat4 *cam_mat);

bool tooltip_pointer_event(Tooltip *self, ePointer_s pointer);

void tooltip_set(Tooltip *self, const char *name, const char *tip);

#endif //PIXELC_TOOLTIP_H
