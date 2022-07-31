#ifndef PIXELC_TOOLBAR_H
#define PIXELC_TOOLBAR_H

//
// toolbar containing a class for a container and handling the tools
//

#include "r/ro_single.h"
#include "u/color.h"
#include "u/container.h"
#include "selectionctrl.h"
#include "tool.h"


#define TOOLBAR_MAX_TOOLS 64


typedef struct {
    Tool **tools;
    float tool_hover_times[TOOLBAR_MAX_TOOLS];
    int tools_len;

    uContainer container;
    enum u_container_align align;

    RoSingle bg;
    bool bg_packed;
} ToolbarContainer;

static bool toolbar_container_valid(const ToolbarContainer *self) {
    return self->tools_len > 0;
}

struct Toolbar_Globals {
    ToolbarContainer active;
    ToolbarContainer frames;
    ToolbarContainer layer;
    ToolbarContainer selection;

    Tool *tools[TOOLBAR_MAX_TOOLS];
    int tools_size;

    Tool *frames_tools[TOOLBAR_MAX_TOOLS];
    int frames_tools_size;

    Tool *layer_tools[TOOLBAR_MAX_TOOLS];
    int layer_tools_size;

    Tool *selection_set_tools[TOOLBAR_MAX_TOOLS];
    int selection_set_tools_size;

    Tool *selection_paste_tools[TOOLBAR_MAX_TOOLS];
    int selection_paste_tools_size;
};
extern struct Toolbar_Globals toolbar;


void toolbar_init();

void toolbar_update(float dtime);

void toolbar_render(const mat4 *cam_mat);

// returns toolbar_contains(pointer.pos.xy)
bool toolbar_pointer_event(ePointer_s pointer);

float toolbar_size();

// returns true if pos is within the toolbar
bool toolbar_contains(vec2 pos);

// returns NULL if not found
Tool *toolbar_get_tool_by_pos(vec2 pos);

void toolbar_show_frames();

void toolbar_hide_frames();

void toolbar_show_layer();

void toolbar_hide_layer();


#endif //PIXELC_TOOLBAR_H
