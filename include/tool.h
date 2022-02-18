#ifndef PIXELC_TOOL_H
#define PIXELC_TOOL_H

#include "e/input.h"
#include "r/ro_types.h"
#include "camera.h"
#include "cameractrl.h"
#include "canvas.h"
#include "brush.h"
#include "palette.h"
#include "selectionctrl.h"
#include "dialog.h"
#include "animation.h"

#define TOOL_NAME_LEN 16
#define TOOL_TIP_LEN 128

#define TOOL_BUTTON_ADDITIONAL_DATA_SIZE 64
#define TOOL_LONG_PRESS_TIME 0.75

struct Toolbar;

typedef struct {
    struct eWindow *window;
    eInput *input;

    Camera_s *cam;
    CameraCtrl *camctrl;
    Canvas *canvas;
    Brush *brush;
    Palette *palette;
    SelectionCtrl *selectionctrl;
    Dialog *dialog;
    Animation *animation;
    struct Toolbar *toolbar;
} ToolRefs;


struct Tool;

typedef void (*tool_kill_fun)(struct Tool **self_ptr);

typedef void (*tool_update_fun)(struct Tool *self, float dtime, ToolRefs refs);

typedef void (*tool_render_fun)(const struct Tool *self, const mat4 *cam_mat);

typedef void (*tool_pointer_event_fun)(struct Tool *self, ePointer_s pointer, ToolRefs refs);


typedef struct Tool {
    char name[TOOL_NAME_LEN];
    char tip[TOOL_TIP_LEN];
    
    vec2 size;
    
    struct {
        // as left, top
        vec2 pos;
    } in;
    
    // vtable
    tool_kill_fun kill;
    tool_update_fun update;
    tool_render_fun render;
    tool_pointer_event_fun pointer_event;
} Tool;


typedef bool (*tool_button_active)(Tool *self, float dtime, ToolRefs refs);

typedef struct {
    Tool super;
    RoSingle ro;
    vec4 padding_lrbt; // left, right, bottom, top
    uint8_t additional_data[TOOL_BUTTON_ADDITIONAL_DATA_SIZE];
    bool active;
    // vtable
    tool_button_active opt_is_active;
} ToolButton;

// Returns a ToolButton
Tool *tool_button_new(const char *name, 
        const char *tip, 
        const char *tex_file, 
        tool_pointer_event_fun pointer_event,
        tool_button_active opt_is_active);
        
//
// tool list
//

Tool *tool_new_tooltip();
Tool *tool_new_save();
Tool *tool_new_save_hd();
Tool *tool_new_import();
Tool *tool_new_clear();
Tool *tool_new_undo();
Tool *tool_new_redo();
Tool *tool_new_selection();
Tool *tool_new_kernel();
Tool *tool_new_secondary_color();
Tool *tool_new_shading();
Tool *tool_new_camera();
Tool *tool_new_grid();
Tool *tool_new_preview();
Tool *tool_new_layer();
Tool *tool_new_size();

Tool *tool_new_mode_none();
Tool *tool_new_mode_free();
Tool *tool_new_mode_dot();
Tool *tool_new_mode_line();
Tool *tool_new_mode_rect();
Tool *tool_new_mode_circle();
Tool *tool_new_mode_dither();
Tool *tool_new_mode_dither_inv();
Tool *tool_new_mode_fill();
Tool *tool_new_mode_fill8();
Tool *tool_new_mode_replace();
Tool *tool_new_mode_pipette();

Tool *tool_new_selection_set_move();
Tool *tool_new_selection_set_copy();
Tool *tool_new_selection_set_cut();

Tool *tool_new_selection_paste_rotate_l();
Tool *tool_new_selection_paste_rotate_r();
Tool *tool_new_selection_paste_mirror_v();
Tool *tool_new_selection_paste_mirror_h();
Tool *tool_new_selection_paste_blend();
Tool *tool_new_selection_paste_copy();
Tool *tool_new_selection_paste_ok();


#endif //PIXELC_TOOL_H
