#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "mathc/uchar.h"
#include "toolbar.h"

static bool toolbar_container_valid(const ToolbarContainer *self) {
    return self->tools_len>0;
}

static ToolbarContainer toolbar_container_new_invalid() {
    return (ToolbarContainer) {0};
}

static ToolbarContainer toolbar_container_new(Tool **tools, int tools_len, uColor_s bg_a, uColor_s bg_b) {
    ToolbarContainer self = {0};
    self.tools = rhc_calloc(sizeof *tools * tools_len);
    memcpy(self.tools, tools, sizeof *tools * tools_len);
    self.tools_len = tools_len;
    self.container = u_container_new(tools_len, 0, 0);
    self.align = U_CONTAINER_ALIGN_START;

    uColor_s buf[4];
    buf[0] = buf[3] = bg_a;
    buf[1] = buf[2] = bg_b;
    rTexture tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(tex);
    self.bg = ro_single_new(tex);
    
    return self;
}

static void toolbar_container_kill(ToolbarContainer *self) {
    if(!toolbar_container_valid(self))
        return;
    rhc_free(self->tools);
    u_container_kill(&self->container);
    ro_single_kill(&self->bg);
    *self = (ToolbarContainer) {0};
}

static void toolbar_container_update(ToolbarContainer *self, float start_pos, float dtime, ToolRefs refs) {
    if(!toolbar_container_valid(self))
        return;
    self->container.left = refs.cam->RO.left;
    self->container.top = refs.cam->RO.top;
    self->container.max_size = (vec2) {{camera_width(refs.cam), camera_height(refs.cam)}};

    if (camera_is_portrait_mode(refs.cam)) {
        self->container.top -= start_pos;
        self->container.mode = U_CONTAINER_MODE_FREE_H;
        self->container.align_width = self->align;
        self->container.align_height = U_CONTAINER_ALIGN_START;
    } else {
        self->container.left += start_pos;
        self->container.mode = U_CONTAINER_MODE_FREE_V;
        self->container.align_width = U_CONTAINER_ALIGN_START;
        self->container.align_height = self->align;
    }

    for (int i = 0; i < self->tools_len; i++) {
        self->container.items[i].size = self->tools[i]->size;
    }

    u_container_update(&self->container);

    for (int i = 0; i < self->tools_len; i++) {
        self->tools[i]->in.pos = (vec2) {{
                                                 self->container.items[i].out.left,
                                                 self->container.items[i].out.top
                                         }};
    }

    for (int i = 0; i < self->tools_len; i++) {
        self->tools[i]->update(self->tools[i], dtime, refs);
    }

    // bg
    float bg_w, bg_h;
    if (camera_is_portrait_mode(refs.cam)) {
        bg_w = camera_width(refs.cam);
        bg_h = self->container.out.size.y;
    } else {
        bg_w = self->container.out.size.x;
        bg_h = camera_height(refs.cam);
    }


    bg_w = self->container.out.size.x;
    bg_h = self->container.out.size.y;
    self->bg.rect.pose = u_pose_new_aa(self->container.out.left, self->container.out.top, bg_w, bg_h);
    self->bg.rect.uv = u_pose_new(0, 0, bg_w / 2, bg_h / 2);
}

static void toolbar_container_render(const ToolbarContainer *self, const mat4 *cam_mat) {
    if(!toolbar_container_valid(self))
        return;
    ro_single_render(&self->bg, cam_mat);
    for (int i = 0; i < self->tools_len; i++) {
        self->tools[i]->render(self->tools[i], cam_mat);
    }
}

// returns true if pos is within the toolbar
static bool toolbar_container_contains(const ToolbarContainer *self, vec2 pos) {
    if(!toolbar_container_valid(self))
        return false;
    return u_pose_aa_contains(u_pose_new_aa(
            self->container.out.left,
            self->container.out.top,
            self->container.out.size.x,
            self->container.out.size.y), pos);
}

// returns NULL if not found
static Tool *toolbar_container_get_tool_by_pos(const ToolbarContainer *self, vec2 pos) {
    if(!toolbar_container_contains(self, pos))
        return NULL;
    for(int i=0; i<self->tools_len; i++) {
        Tool *t = self->tools[i];
        if(pos.x>=t->in.pos.x 
                && pos.y<=t->in.pos.y
                && pos.x<=t->in.pos.x+t->size.x
                && pos.y>=t->in.pos.y-t->size.y)
            return t;
    }
    return NULL;
}

// returns toolbar_contains(pointer.pos.xy)
static bool toolbar_container_pointer_event(ToolbarContainer *self, ePointer_s pointer, ToolRefs refs) {
    if(!toolbar_container_valid(self))
        return false;
    bool contains = toolbar_container_contains(self, pointer.pos.xy);
    if (pointer.action != E_POINTER_UP && !contains)
        return false;

    for (int i = 0; i < self->tools_len; i++) {
        self->tools[i]->pointer_event(self->tools[i], pointer, refs);
    }

    return contains;
}

float toolbar_constainer_size(const ToolbarContainer *self, const Camera_s *cam) {
    if(!toolbar_container_valid(self))
        return 0;
    return camera_is_portrait_mode(cam) ? self->container.out.size.y: self->container.out.size.x;
}

static void hide_selection(Toolbar *self) {
    log_info("toolbar: hide_selection");
    toolbar_container_kill(&self->selection);
}

static void show_selection_set(Toolbar *self) {
    log_info("toolbar: show_selection_set");
    toolbar_container_kill(&self->selection);
    self->selection = toolbar_container_new(
            self->all_selection_set_tools,
            TOOLBAR_SELECTION_SET_TOOLS_LEN,
            self->L.selection_bg_a, 
            self->L.selection_bg_b);
    self->selection.align = U_CONTAINER_ALIGN_CENTER;
    
}

static void show_selection_move(Toolbar *self) {
    log_info("toolbar: show_selection_move");
    toolbar_container_kill(&self->selection);
    self->selection = toolbar_container_new(
            self->all_selection_paste_tools,
            TOOLBAR_SELECTION_PASTE_TOOLS_LEN,
            self->L.selection_bg_a, 
            self->L.selection_bg_b);
    self->selection.align = U_CONTAINER_ALIGN_CENTER;
}


//
// public
//

Toolbar *toolbar_new(Camera_s *cam, 
                     CameraCtrl *camctrl,
                     Canvas *canvas,
                     Brush *brush, 
                     Palette *palette,
                     SelectionCtrl *selectionctrl,
                     Dialog *dialog,
                     Animation *animation,
                     uColor_s active_bg_a, uColor_s active_bg_b,
                     uColor_s secondary_bg_a, uColor_s secondary_bg_b,
                     uColor_s selection_bg_a, uColor_s selection_bg_b) {
    Toolbar *self = rhc_calloc(sizeof *self);

    self->refs = (ToolRefs) {
            cam, camctrl, canvas, brush, palette, selectionctrl, dialog, animation, self
    };

    self->tools.tooltip = tool_new_tooltip();
    self->tools.import = tool_new_import();
    self->tools.clear = tool_new_clear();
    self->tools.undo = tool_new_undo();
    self->tools.redo = tool_new_redo();
    self->tools.selection = tool_new_selection();
    self->tools.kernel = tool_new_kernel();
    self->tools.secondary_color = tool_new_secondary_color();
    self->tools.shading = tool_new_shading();
    self->tools.camera = tool_new_camera();
    self->tools.grid = tool_new_grid();
    self->tools.preview = tool_new_preview();
    self->tools.layer = tool_new_layer();

    self->tools.mode_none = tool_new_mode_none();
    self->tools.mode_free = tool_new_mode_free();
    self->tools.mode_dot = tool_new_mode_dot();
    self->tools.mode_line = tool_new_mode_line();
    self->tools.mode_rect = tool_new_mode_rect();
    self->tools.mode_circle = tool_new_mode_circle();
    self->tools.mode_dither = tool_new_mode_dither();
    self->tools.mode_dither_inv = tool_new_mode_dither_inv();
    self->tools.mode_fill = tool_new_mode_fill();
    self->tools.mode_fill8 = tool_new_mode_fill8();
    self->tools.mode_replace = tool_new_mode_replace();
    self->tools.mode_pipette = tool_new_mode_pipette();


    self->selection_set_tools.move = tool_new_selection_set_move();
    self->selection_set_tools.copy = tool_new_selection_set_copy();
    self->selection_set_tools.cut = tool_new_selection_set_cut();
    
    self->selection_paste_tools.rotate_l = tool_new_selection_paste_rotate_l();
    self->selection_paste_tools.rotate_r = tool_new_selection_paste_rotate_r();
    self->selection_paste_tools.mirror_v = tool_new_selection_paste_mirror_v();
    self->selection_paste_tools.mirror_h = tool_new_selection_paste_mirror_h();
    self->selection_paste_tools.blend = tool_new_selection_paste_blend();
    self->selection_paste_tools.copy = tool_new_selection_paste_copy();
    self->selection_paste_tools.ok = tool_new_selection_paste_ok();

    self->L.active_bg_a = active_bg_a;
    self->L.active_bg_b = active_bg_b;
    self->L.secondary_bg_a = secondary_bg_a;
    self->L.secondary_bg_b = secondary_bg_b;
    self->L.selection_bg_a = selection_bg_a;
    self->L.selection_bg_b = selection_bg_b;

    self->active = toolbar_container_new(self->all_tools, TOOLBAR_TOOLS_LEN, active_bg_a, active_bg_b);
    self->active.align = U_CONTAINER_ALIGN_CENTER;
    return self;
}

void toolbar_update(Toolbar *self, float dtime) {
    enum selectionctrl_mode sc_mode = self->refs.selectionctrl->mode;
    if(sc_mode != self->L.last_selectionctrl_mode) {
        self->L.last_selectionctrl_mode = sc_mode;
        switch(sc_mode) {
        case SELECTIONCTRL_NONE:
        case SELECTIONCTRL_ACQUIRE:
            hide_selection(self);
            break;
        case SELECTIONCTRL_SET:
        case SELECTIONCTRL_COPY:
        case SELECTIONCTRL_CUT:
            show_selection_set(self);
            break;
        case SELECTIONCTRL_PASTE:
            show_selection_move(self);
            break;
        default:
            break;
        }
    }
    
    float start_pos = 0;
    toolbar_container_update(&self->active, start_pos, dtime, self->refs);
    start_pos += toolbar_constainer_size(&self->active, self->refs.cam);

    toolbar_container_update(&self->secondary, start_pos, dtime, self->refs);
    start_pos += toolbar_constainer_size(&self->secondary, self->refs.cam);

    toolbar_container_update(&self->selection, start_pos, dtime, self->refs);
}

void toolbar_render(const Toolbar *self, const mat4 *cam_mat) {
    toolbar_container_render(&self->active, cam_mat);
    toolbar_container_render(&self->secondary, cam_mat);
    toolbar_container_render(&self->selection, cam_mat);
}

// returns toolbar_contains(pointer.pos.xy)
bool toolbar_pointer_event(Toolbar *self, ePointer_s pointer) {
    bool contains = false;
    bool go = true;
    bool set_go = pointer.action==E_POINTER_UP? true : false;
    if(toolbar_container_pointer_event(&self->active, pointer, self->refs)) {
        contains = true;
        go = set_go;
    }
    if(go && toolbar_container_pointer_event(&self->secondary, pointer, self->refs)) {
        contains = true;
        go = set_go;
    }
    if(go && toolbar_container_pointer_event(&self->selection, pointer, self->refs)) {
        contains = true;
    }
    return contains;
}

float toolbar_size(const Toolbar *self) {
    return toolbar_constainer_size(&self->active, self->refs.cam)
            + toolbar_constainer_size(&self->secondary, self->refs.cam)
            + toolbar_constainer_size(&self->selection, self->refs.cam);
}

bool toolbar_contains(const Toolbar *self, vec2 pos) {
    return toolbar_container_contains(&self->active, pos)
            || toolbar_container_contains(&self->secondary, pos)
            || toolbar_container_contains(&self->selection, pos);
}

Tool *toolbar_get_tool_by_pos(const Toolbar *self, vec2 pos) {
    Tool *t;
    t = toolbar_container_get_tool_by_pos(&self->active, pos);
    if(t)
        return t;
        
    t = toolbar_container_get_tool_by_pos(&self->secondary, pos);
    if(t)
        return t;
        
    t = toolbar_container_get_tool_by_pos(&self->selection, pos);
    return t;
}

