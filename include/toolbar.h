#ifndef PIXELC_TOOLBAR_H
#define PIXELC_TOOLBAR_H

#include "r/ro_single.h"
#include "u/color.h"
#include "u/container.h"
#include "selectionctrl.h"
#include "tool.h"

#define TOOLBAR_TOOLS_LEN 30
#define TOOLBAR_LAYER_TOOLS_LEN (TOOL_LAYER_SELECT_NUM + 2)
#define TOOLBAR_FRAMES_TOOLS_LEN (TOOL_FRAMES_SELECT_NUM + 2)
#define TOOLBAR_SELECTION_SET_TOOLS_LEN 4
#define TOOLBAR_SELECTION_PASTE_TOOLS_LEN 7


typedef struct {
    Tool **tools;
    int tools_len;

    uContainer container;
    enum u_container_align align;

    RoSingle bg;
} ToolbarContainer;

static bool toolbar_container_valid(const ToolbarContainer *self) {
    return self->tools_len > 0;
}

struct Toolbar_Globals {
    ToolbarContainer active;
    ToolbarContainer frames;
    ToolbarContainer layer;
    ToolbarContainer selection;

    union {
        Tool *all_tools[TOOLBAR_TOOLS_LEN];
        struct {
            Tool *tooltip;
            Tool *save;
            Tool *import;
            Tool *display;
            Tool *size;
            Tool *tab;
            Tool *frames;
            Tool *layer;
            Tool *camera;
            Tool *grid;
            Tool *clear;
            Tool *undo;
            Tool *redo;
            Tool *selection;
            Tool *kernel;
            Tool *rgb;
            Tool *shading;
            Tool *secondary_color;
            
            Tool *mode_pipette;
            Tool *mode_none;
            Tool *mode_free;
            Tool *mode_dot;
            Tool *mode_line;
            Tool *mode_rect;
            Tool *mode_circle;
            Tool *mode_dither;
            Tool *mode_dither_inv;
            Tool *mode_fill;
            Tool *mode_fill8;
            Tool *mode_replace;
            
            
        } tools;
    };

    union {
        Tool *all_frames_tools[TOOLBAR_FRAMES_TOOLS_LEN];
        struct {
            Tool *select[TOOL_FRAMES_SELECT_NUM];
            Tool *blend;
            Tool *add;
        } frames_tools;
    };

    union {
        Tool *all_layer_tools[TOOLBAR_LAYER_TOOLS_LEN];
        struct {
            Tool *select[TOOL_LAYER_SELECT_NUM];
            Tool *blend;
            Tool *add;
        } layer_tools;
    };
    

    union {
        Tool *all_selection_set_tools[TOOLBAR_SELECTION_SET_TOOLS_LEN];
        struct {
            Tool *move;
            Tool *cut;
            Tool *copy;
            Tool *crop;
        } selection_set_tools;
    };

    union {
        Tool *all_selection_paste_tools[TOOLBAR_SELECTION_PASTE_TOOLS_LEN];
        struct {
            Tool *rotate_l;
            Tool *rotate_r;
            Tool *mirror_v;
            Tool *mirror_h;
            Tool *blend;
            Tool *copy;
            Tool *ok;
        } selection_paste_tools;
    };
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
