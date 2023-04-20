#ifndef PIXELC_TOOLTIP_H
#define PIXELC_TOOLTIP_H

//
// Shows tooltip above the palette
//

#include "s/s.h"
#include "m/types/float.h"


#define TOOLTIP_TITLE_MAX 16
#define TOOLTIP_TIP_MAX 256

struct Tooltip_Globals {
    bool show;
};
extern struct Tooltip_Globals tooltip;


void tooltip_init();

void tooltip_update(float dtime);

void tooltip_render(const mat4 *camera_mat);

// pass NULL, NULL to clear
void tooltip_set(const char *title, const char *tip);

// saves the config to the savestate config.json 
// uses object "tooltip"
void tooltip_save_config();

// loads the config from the savestate config.json
// uses object "tooltip"
void tooltip_load_config();


#endif //PIXELC_TOOLTIP_H
