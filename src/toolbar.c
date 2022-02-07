#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
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
    } else {
        self->container.left += start_pos;
        self->container.mode = U_CONTAINER_MODE_FREE_V;
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
    self->bg.rect.pose = u_pose_new_aa(self->container.left, self->container.top, bg_w, bg_h);
    u_pose_set_size(&self->bg.rect.uv, bg_w / 2, bg_h / 2);
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
bool toolbar_container_contains(const ToolbarContainer *self, vec2 pos) {
    if(!toolbar_container_valid(self))
        return false;
    return u_pose_aa_contains(u_pose_new_aa(
            self->container.left,
            self->container.top,
            self->container.out.size.x,
            self->container.out.size.y), pos);
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



Toolbar *toolbar_new(Camera_s *cam, Canvas *canvas,
                     Brush *brush, Palette *palette,
                     uColor_s active_bg_a, uColor_s active_bg_b,
                     uColor_s secondary_bg_a, uColor_s secondary_bg_b,
                     uColor_s selection_bg_a, uColor_s selection_bg_b) {
    Toolbar *self = rhc_calloc(sizeof *self);

    self->refs = (ToolRefs) {
            cam, canvas, brush, palette
    };


    self->tools.undo = tool_new_undo();
    self->tools.redo = tool_new_redo();
    self->tools.import = tool_new_import();

    self->L.active_bg_a = active_bg_a;
    self->L.active_bg_b = active_bg_b;
    self->L.secondary_bg_a = secondary_bg_a;
    self->L.secondary_bg_b = secondary_bg_b;
    self->L.selection_bg_a = selection_bg_a;
    self->L.selection_bg_b = selection_bg_b;

    self->active = toolbar_container_new(self->all_tools, TOOLBAR_TOOLS_LEN, active_bg_a, active_bg_b);
    toolbar_show_selection(self);

    return self;
}

void toolbar_update(Toolbar *self, float dtime) {
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

// returns true if pos is within the toolbar
bool toolbar_contains(const Toolbar *self, vec2 pos) {
    return toolbar_container_contains(&self->active, pos)
            || toolbar_container_contains(&self->secondary, pos)
            || toolbar_container_contains(&self->selection, pos);
}


void toolbar_show_selection(Toolbar *self) {
    toolbar_container_kill(&self->selection);
//    self->selection = toolbar_container_new((Tool*[]) {self->all[0]}, 1,
//                                            self->L.selection_bg_a, self->L.selection_bg_b);
}

void toolbar_hide_selection(Toolbar *self) {
    toolbar_container_kill(&self->selection);
}
