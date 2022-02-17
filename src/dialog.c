#include "r/ro_single.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "toolbar.h"
#include "button.h"
#include "dialog.h"

#define BG_A "#776666"
#define BG_B "#887777"
#define TOOLTIP_BG_A "#776666"
#define TOOLTIP_BG_B "#887777"

Dialog *dialog_new() {
    Dialog *self = rhc_calloc(sizeof *self);

    self->bg = ro_single_new(r_texture_new_invalid());
    self->bg_shadow = ro_single_new(r_texture_new_invalid());
    self->bg_shadow.owns_tex = false;
    self->bg_shadow.rect.color = (vec4) {{0.2, 0.2, 0.2, 0.5}};
    dialog_set_bg_color(self, u_color_from_hex(BG_A), u_color_from_hex(BG_B));

    self->title = ro_text_new_font55(16);
    self->title_shadow = ro_text_new_font55(16);
    ro_text_set_color(&self->title_shadow, (vec4) {{0, 0, 0, 0.33}});

    self->cancel = ro_single_new(r_texture_new_file(2, 3, "res/textinput_key_special.png"));
    self->cancel.rect.sprite.y = 1;
    self->ok = ro_single_new(self->cancel.tex);
    self->ok.owns_tex = false;

    self->cancel.rect.pose = u_pose_new_aa(DIALOG_LEFT + 10, 0,
                                           self->cancel.tex.sprite_size.x, self->cancel.tex.sprite_size.y);
    self->ok.rect.pose = u_pose_new_aa(DIALOG_LEFT + DIALOG_WIDTH - 10 - self->ok.tex.sprite_size.x, 0,
                                       self->ok.tex.sprite_size.x, self->ok.tex.sprite_size.y);

    self->title.pose = u_pose_new(DIALOG_LEFT + 19, DIALOG_TOP - 2, 2, 2);
    self->title_shadow.pose = self->title.pose;
    u_pose_shift_xy(&self->title_shadow.pose, 1, -1);

    return self;
}


void dialog_update(Dialog *self, float dtime) {
    if (!dialog_valid(self))
        return;
    self->update(self, dtime);

    float height = 16 + self->in.impl_height;
    if(self->opt_on_cancel_cb || self->opt_on_ok_cb)
        height += 20;

    self->bg.rect.pose = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP,DIALOG_WIDTH, height);
    self->bg_shadow.rect.pose = self->bg.rect.pose;
    u_pose_shift_xy(&self->bg_shadow.rect.pose, 2, -2);
    u_pose_set_size(&self->bg.rect.uv, DIALOG_WIDTH/2, height/2);
    self->bg_shadow.rect.uv = self->bg.rect.uv;

    u_pose_aa_set_bottom(&self->cancel.rect.pose, DIALOG_TOP-height+2);
    u_pose_aa_set_bottom(&self->ok.rect.pose, DIALOG_TOP-height+2);
}

void dialog_render(Dialog *self, const mat4 *cam_mat) {
    if (!dialog_valid(self))
        return;
    ro_single_render(&self->bg_shadow, cam_mat);
    ro_single_render(&self->bg, cam_mat);
    self->render(self, cam_mat);
    ro_text_render(&self->title_shadow, cam_mat);
    ro_text_render(&self->title, cam_mat);
    if (self->opt_on_cancel_cb)
        ro_single_render(&self->cancel, cam_mat);
    if (self->opt_on_ok_cb)
        ro_single_render(&self->ok, cam_mat);
}

bool dialog_pointer_event(Dialog *self, ePointer_s pointer) {
    if (!dialog_valid(self))
        return false;
    if (self->opt_on_cancel_cb && button_clicked(&self->cancel.rect, pointer)) {
        self->opt_on_cancel_cb(self, false);
        dialog_hide(self);
        return true;
    }
    if (self->opt_on_ok_cb && button_clicked(&self->ok.rect, pointer)) {
        self->opt_on_ok_cb(self, false);
        dialog_hide(self);
        return true;
    }
    return self->pointer_event(self, pointer);
}


void dialog_hide(Dialog *self) {
    if (!dialog_valid(self))
        return;
    self->kill(self->impl);
    self->impl = NULL;
    self->id[0] = '\0';
    self->opt_on_ok_cb = NULL;
    self->opt_on_cancel_cb = NULL;
    self->kill = NULL;
    self->update = NULL;
    self->render = NULL;
    self->pointer_event = NULL;
}

void dialog_set_bg_color(Dialog *self, uColor_s a, uColor_s b) {
    uColor_s buf[4];
    buf[0] = buf[3] = a;
    buf[1] = buf[2] = b;
    rTexture tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(tex);
    ro_single_set_texture(&self->bg, tex);
    ro_single_set_texture(&self->bg_shadow, tex);
}

void dialog_set_title(Dialog *self, const char *title_id, vec4 color) {
    assume(strlen(title_id) < DIALOG_MAX_TITLE_LEN, "title to long");
    strcpy(self->id, title_id);
    ro_text_set_text(&self->title, title_id);
    ro_text_set_text(&self->title_shadow, title_id);
    ro_text_set_color(&self->title, color);
}

void dialog_create_delete(Dialog *self, const char *msg, dialog_on_action_cb on_action_cb) {
    dialog_hide(self);
}

void dialog_create_upload(Dialog *self, const char *msg, dialog_pointer_event_fun on_action_cb) {
    dialog_hide(self);
}


struct ToolTip {
    Toolbar *toolbar_ref;
    RoText name;
    RoText tip;
};
static void tooltip_kill(void *impl) {
    struct ToolTip *self = impl;
    ro_text_kill(&self->name);
    ro_text_kill(&self->tip);
    rhc_free(self);
}
static void tooltip_update(Dialog *self, float dtime) {
    // noop
}
static void tooltip_render(Dialog *self, const mat4 *cam_mat) {
    struct ToolTip *impl = self->impl;
    ro_text_render(&impl->name, cam_mat);
    ro_text_render(&impl->tip, cam_mat);
}
static void tooltip_set(Dialog *self, const char *name, const char *tip) {
    struct ToolTip *impl = self->impl;
    ro_text_set_text(&impl->name, name);
    vec2 size = ro_text_set_text(&impl->tip, tip);
    self->in.impl_height = size.y + 24;
}
static bool tooltip_pe(Dialog *self, ePointer_s pointer) {
    struct ToolTip *impl = self->impl;
    Tool *tool = toolbar_get_tool_by_pos(impl->toolbar_ref, pointer.pos.xy);
    if(!tool)
        return true;
    if(strcmp(tool->name, "tooltip")==0)
        return false;
    tooltip_set(self, tool->name, tool->tip);
    return true;
}

void tooltip_on_action(Dialog *self, bool ok) {
    log_info("tooltip closed, ok=%i", ok);
    dialog_hide(self);
}

void dialog_create_tooltip(Dialog *self, struct Toolbar *toolbar) {
    dialog_hide(self);
    struct ToolTip *impl = rhc_calloc(sizeof *impl);
    self->impl = impl;
    impl->toolbar_ref = toolbar;

    impl->name = ro_text_new_font55(TOOL_NAME_LEN);
    ro_text_set_color(&impl->name, (vec4){{0.9, 0.9, 0.9, 1}});

    impl->tip = ro_text_new_font55(TOOL_TIP_LEN);

    impl->name.pose = u_pose_new(DIALOG_LEFT+6, DIALOG_TOP-18, 1, 2);
    impl->tip.pose = u_pose_new(DIALOG_LEFT+2, DIALOG_TOP-36, 1, 1);
    tooltip_set(self, "tooltip", "click on a tool\nto get its tip");

    dialog_set_title(self, "tooltip", (vec4){{0.2, 0.6, 0.2, 1}});
    dialog_set_bg_color(self, u_color_from_hex(TOOLTIP_BG_A), u_color_from_hex(TOOLTIP_BG_B));
    self->kill = tooltip_kill;
    self->update = tooltip_update;
    self->render = tooltip_render;
    self->pointer_event = tooltip_pe;
//    self->opt_on_cancel_cb = tooltip_on_action;
//    self->opt_on_ok_cb = tooltip_on_action;
}

void dialog_create_canvas_size(Dialog *self, struct Canvas *canvas) {
    dialog_hide(self);
}
