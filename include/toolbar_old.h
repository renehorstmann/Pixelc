#ifndef PIXELC_TOOLBAR_OLD_H
#define PIXELC_TOOLBAR_OLD_H

#include <stdbool.h>
#include "e/input.h"
#include "r/ro_types.h"
#include "canvas.h"
#include "brush.h"
#include "selectionctrl.h"
#include "cameractrl.h"
#include "animation.h"

#define TOOLBAR_OLD_MODES 7
#define TOOLBAR_OLD_TOOL_MAX 32

struct ToolbarOld_Tool {
    RoSingle btn;
    float x, y;
};

typedef struct ToolbarOld {
    const Camera_s *camera_ref;
    Canvas *canvas_ref;
    Brush *brush_ref;
    SelectionCtrl *selectionctrl_ref;
    CameraCtrl *canvascamctrl_ref;
    Animation *animation_ref;

    bool show_selection_copy_cut;
    bool show_selection_ok;

    // private
    struct {
        struct ToolbarOld_Tool tools[TOOLBAR_OLD_TOOL_MAX];
        int tools_size;

        RoSingle *undo;
        RoSingle *clear;
        RoSingle *import;
        RoSingle *selection;
        RoSingle *grid;
        bool grid_status;

        RoSingle *camera;
        RoSingle *animation;
        RoSingle *shade;

        RoSingle *modes[TOOLBAR_OLD_MODES];

        RoSingle *shape_minus;
        RoSingle *shape_plus;

        //non tools:
        RoSingle shape;
        float shape_minus_time, shape_plus_time;

        RoSingle color_bg, color_drop;

        RoSingle selection_copy;
        RoSingle selection_cut;
        RoSingle selection_rotate_left;
        RoSingle selection_rotate_right;
        RoSingle selection_mirror_horizontal;
        RoSingle selection_mirror_vertical;
        RoSingle selection_blend;
        RoSingle selection_ok;
        RoSingle selection_move[8];

        RoSingle layer_prev;
        RoSingle layer_next;
        RoText layer_num;

        bool prev_show_selection_ok;
    } L;
} ToolbarOld;

ToolbarOld *toolbar_old_new(const Camera_s *camera,
                     Canvas *canvas,
                     Brush *brush,
                     SelectionCtrl *selectionctrl,
                     CameraCtrl *canvascamctrl,
                     Animation *animation);

void toolbar_old_update(ToolbarOld *self, float dtime);

void toolbar_old_render(ToolbarOld *self, const mat4 *camera_mat);

// return true if the pointer was used (indicate event done)
bool toolbar_old_pointer_event(ToolbarOld *self, ePointer_s pointer);

#endif //PIXELC_TOOLBAR_OLD_H