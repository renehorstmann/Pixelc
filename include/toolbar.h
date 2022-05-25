#ifndef PIXELC_TOOLBAR_H
#define PIXELC_TOOLBAR_H

#include "r/ro_types.h"
#include "u/color.h"
#include "u/container.h"
#include "tool.h"

#define TOOLBAR_TOOLS_LEN 28
#define TOOLBAR_LAYER_TOOLS_LEN 5
#define TOOLBAR_SELECTION_SET_TOOLS_LEN 3
#define TOOLBAR_SELECTION_PASTE_TOOLS_LEN 7


typedef struct {
    Tool **tools;
    int tools_len;

    uContainer container;
    enum u_container_align align;

    RoSingle bg;
} ToolbarContainer;

static bool toolbar_container_valid(const ToolbarContainer *self) {
    return self->tools_len>0;
}

typedef struct Toolbar {
    ToolRefs refs;

    ToolbarContainer active;
    ToolbarContainer layer; 
    ToolbarContainer selection;

    union {
        Tool *all_tools[TOOLBAR_TOOLS_LEN];
        struct {
            Tool *tooltip;
            Tool *save;
            Tool *save_hd;
            Tool *import;
            Tool *clear;
            Tool *undo;
            Tool *redo;
            Tool *selection;
            Tool *layer;
            Tool *kernel;
            Tool *secondary_color;
            Tool *shading;
            Tool *camera;
            Tool *grid;
            Tool *preview;
            Tool *size;
            Tool *display;

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
            Tool *mode_pipette;
        } tools;
    };
    
    union {
        Tool *all_layer_tools[TOOLBAR_LAYER_TOOLS_LEN];
        struct {
            Tool *move_prev;
            Tool *select;
            Tool *move_next;
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

    struct {
        enum selectionctrl_mode last_selectionctrl_mode;

        uColor_s active_bg_a, active_bg_b;
        uColor_s layer_bg_a, layer_bg_b;
        uColor_s selection_bg_a, selection_bg_b;
    } L;
} Toolbar;


Toolbar *toolbar_new(struct eWindow *window,
                     eInput *input,
                     Camera_s *cam,
                     CameraCtrl *camctrl,
                     Canvas *canvas,
                     Brush *brush, Palette *palette,
                     SelectionCtrl *selectionctrl,
                     Dialog *dialog,
                     Animation *animation,
                     uColor_s active_bg_a, uColor_s active_bg_b,
                     uColor_s secondary_bg_a, uColor_s secondary_bg_b,
                     uColor_s selection_bg_a, uColor_s selection_bg_b);

void toolbar_update(Toolbar *self, float dtime);

void toolbar_render(const Toolbar *self, const mat4 *cam_mat);

// returns toolbar_contains(pointer.pos.xy)
bool toolbar_pointer_event(Toolbar *self, ePointer_s pointer);

float toolbar_size(const Toolbar *self);

// returns true if pos is within the toolbar
bool toolbar_contains(const Toolbar *self, vec2 pos);

// returns NULL if not found
Tool *toolbar_get_tool_by_pos(const Toolbar *self, vec2 pos);

void toolbar_show_layer(Toolbar *self);

void toolbar_hide_layer(Toolbar *self);

#endif //PIXELC_TOOLBAR_H
