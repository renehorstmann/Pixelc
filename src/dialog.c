#include "e/window.h"
#include "e/input.h"
#include "e/io.h"
#include "r/ro_single.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "toolbar.h"
#include "palette.h"
#include "button.h"
#include "dialog.h"
#include "textinput.h"

#define BG_A "#776666"
#define BG_B "#887777"
#define TOOLTIP_BG_A "#776666"
#define TOOLTIP_BG_B "#887777"
#define CANVASSIZE_BG_A "#667766"
#define CANVASSIZE_BG_B "#778877"

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


    return self;
}


void dialog_update(Dialog *self, float dtime) {
    if (!dialog_valid(self))
        return;
    self->out.textinput_active = false;
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
    ro_text_render(&self->title_shadow, cam_mat);
    ro_text_render(&self->title, cam_mat);
    if (self->opt_on_cancel_cb)
        ro_single_render(&self->cancel, cam_mat);
    if (self->opt_on_ok_cb)
        ro_single_render(&self->ok, cam_mat);
    self->render(self, cam_mat);
}

bool dialog_pointer_event(Dialog *self, ePointer_s pointer) {
    if (!dialog_valid(self))
        return false;
    if (pointer.id==0 && self->opt_on_cancel_cb && button_clicked(&self->cancel.rect, pointer)) {
        self->opt_on_cancel_cb(self, false);
        dialog_hide(self);
        return true;
    }
    if (pointer.id==0 && self->opt_on_ok_cb && button_clicked(&self->ok.rect, pointer)) {
        self->opt_on_ok_cb(self, true);
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
    vec2 size = ro_text_set_text(&self->title, title_id);
    ro_text_set_text(&self->title_shadow, title_id);
    ro_text_set_color(&self->title, color);
    self->title.pose = u_pose_new(DIALOG_LEFT + DIALOG_WIDTH/2 - sca_ceil(size.x),
                                  DIALOG_TOP - 2, 2, 2);
    self->title_shadow.pose = self->title.pose;
    u_pose_shift_xy(&self->title_shadow.pose, 1, -1);
}

void dialog_create_delete(Dialog *self, const char *msg, dialog_on_action_cb on_action_cb, void *user_data) {
    dialog_hide(self);
}

void dialog_create_upload(Dialog *self, const char *msg, dialog_pointer_event_fun on_action_cb, void *user_data) {
    dialog_hide(self);
}


//
// dialogs
//


struct ToolTip {
    const Toolbar *toolbar_ref;
    const Palette *palette_ref;
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
    if(palette_contains_pos(impl->palette_ref, pointer.pos.xy)) {
        tooltip_set(self, "palette", "tip to select\na color\n\n"
                                     "swipe left or\nright to change\nthe palette\n\n"
                                     "swipe up for\nmultitouchmode");
        return true;
    }
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

void dialog_create_tooltip(Dialog *self, const struct Toolbar *toolbar, const struct Palette *palette) {
    dialog_hide(self);
    struct ToolTip *impl = rhc_calloc(sizeof *impl);
    self->impl = impl;
    impl->toolbar_ref = toolbar;
    impl->palette_ref = palette;

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



struct CanvasSize {
    const struct eWindow *window_ref;
    eInput *input_ref;
    Canvas *canvas_ref;

    int cols;
    RoText cols_text;
    RoText cols_num;
    mat4 cols_hitbox;
    
    int rows;
    RoText rows_text;
    RoText rows_num;
    mat4 rows_hitbox;
    
    int layers;
    RoText layers_text;
    RoText layers_num;
    mat4 layers_hitbox;
    
    int p_cols;
    RoText p_cols_text;
    RoText p_cols_num;
    mat4 p_cols_hitbox;
    
    int p_rows;
    RoText p_rows_text;
    RoText p_rows_num;
    mat4 p_rows_hitbox;
    
    int textinput_usage;
    TextInput *textinput;
};
static void canvas_size_kill(void *impl) {
    struct CanvasSize *self = impl;
    ro_text_kill(&self->cols_text);
    ro_text_kill(&self->cols_num);
    ro_text_kill(&self->rows_text);
    ro_text_kill(&self->rows_num);
    ro_text_kill(&self->layers_text);
    ro_text_kill(&self->layers_num);
    ro_text_kill(&self->p_cols_text);
    ro_text_kill(&self->p_cols_num);
    ro_text_kill(&self->p_rows_text);
    ro_text_kill(&self->p_rows_num);
    textinput_kill(&self->textinput);
    rhc_free(self);
}
static void canvas_size_update(Dialog *self, float dtime) {
    struct CanvasSize *impl = self->impl;

    if(impl->textinput) {
        self->out.textinput_active = true;
        
        textinput_update(impl->textinput, e_window_get_size(impl->window_ref), dtime);

        char *end;
        int size = strtol(impl->textinput->text, &end, 10);
        bool ok = end && end!=impl->textinput->text && size>0 && size<=CANVAS_MAX_SIZE;
        if(ok && impl->textinput_usage == 2
                && size>CANVAS_MAX_LAYERS)
                ok = false;
        impl->textinput->in.ok_active = ok;

        if(impl->textinput->state == TEXTINPUT_DONE) {
            switch(impl->textinput_usage) {
            case 0:
                impl->cols = size;
                break;
            case 1:
                impl->rows = size;
                break;
            case 2:
                impl->layers = size;
                break;
            case 3:
                impl->p_cols = size;
                break;
            case 4:
                impl->p_rows = size;
                break;
            default:
                assume(0, "wtf");
            }
        }
        if(impl->textinput->state != TEXTINPUT_IN_PROGRESS)
            textinput_kill(&impl->textinput);
    }

    char buf[16];
    snprintf(buf, sizeof buf, "%i", impl->cols);
    ro_text_set_text(&impl->cols_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->rows);
    ro_text_set_text(&impl->rows_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->layers);
    ro_text_set_text(&impl->layers_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->p_cols);
    ro_text_set_text(&impl->p_cols_num, buf);
    snprintf(buf, sizeof buf, "%i", impl->p_rows);
    ro_text_set_text(&impl->p_rows_num, buf);
}
static void canvas_size_render(Dialog *self, const mat4 *cam_mat) {
    struct CanvasSize *impl = self->impl;
    ro_text_render(&impl->cols_text, cam_mat);
    ro_text_render(&impl->cols_num, cam_mat);
    ro_text_render(&impl->rows_text, cam_mat);
    ro_text_render(&impl->rows_num, cam_mat);
    ro_text_render(&impl->layers_text, cam_mat);
    ro_text_render(&impl->layers_num, cam_mat);
    ro_text_render(&impl->p_cols_text, cam_mat);
    ro_text_render(&impl->p_cols_num, cam_mat);
    ro_text_render(&impl->p_rows_text, cam_mat);
    ro_text_render(&impl->p_rows_num, cam_mat);
    if(impl->textinput) {
        textinput_render(impl->textinput);
    }
}
static bool canvas_size_pe(Dialog *self, ePointer_s pointer) {
    struct CanvasSize *impl = self->impl;

    if(pointer.id == 0 && pointer.action == E_POINTER_DOWN) {
        if(u_pose_aa_contains(impl->cols_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new(impl->input_ref, "Set canvas cols", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->cols);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 0;
        } else if(u_pose_aa_contains(impl->rows_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new(impl->input_ref, "Set canvas rows", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->rows);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 1;
        } else if(u_pose_aa_contains(impl->layers_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new(impl->input_ref, "Set layers", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->layers);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 2;
        } else if(u_pose_aa_contains(impl->p_cols_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new(impl->input_ref, "Set pattern cols", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->p_cols);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 3;
        } else if(u_pose_aa_contains(impl->p_rows_hitbox, pointer.pos.xy)) {
            impl->textinput = textinput_new(impl->input_ref, "Set pattern rows", 8);
            snprintf(impl->textinput->text, sizeof impl->textinput->text, "%i", impl->p_rows);
            impl->textinput->shiftstate = TEXTINPUT_SHIFT_ALT;
            impl->textinput_usage = 4;
        }
    }

    return true;
}

void canvas_size_on_action(Dialog *self, bool ok) {
    struct CanvasSize *impl = self->impl;
    Canvas *canvas = impl->canvas_ref;
    uImage img = canvas->RO.image;
    int cols = impl->cols;
    int rows = impl->rows;
    int layers = impl->layers;
    int p_cols = impl->p_cols;
    int p_rows = impl->p_rows;

    dialog_hide(self);
    if(!ok) {
        log_info("dialog canvas_size aborted");
        return;
    }
    if(cols != img.cols || rows != img.rows || layers != img.layers) {
        log_info("dialog canvas_size: new size %i %i", cols, rows);

        uImage new_img = u_image_new_zeros(cols, rows, layers);
        u_image_copy_top_left(new_img, img);
        canvas_set_image(canvas, new_img, true);
    }
    if(p_cols != canvas->RO.pattern_cols 
            || p_rows != canvas->RO.pattern_rows) {
        log_info("dialog canvas_size: new pattern size %i %i", p_cols, p_rows);
        canvas_set_pattern_size(canvas, p_cols, p_rows);
    }
}
void dialog_create_canvas_size(Dialog *self, const eWindow *window, eInput *input, struct Canvas *canvas) {
    dialog_hide(self);
    dialog_hide(self);
    struct CanvasSize *impl = rhc_calloc(sizeof *impl);
    self->impl = impl;
    impl->window_ref = window;
    impl->input_ref = input;
    impl->canvas_ref = canvas;
    
    int pos;

    pos = 20;
    impl->cols = canvas->RO.image.cols;
    impl->cols_text = ro_text_new_font55(5);
    ro_text_set_text(&impl->cols_text, "cols:");
    ro_text_set_color(&impl->cols_text, (vec4){{0.9, 0.9, 0.9, 1}});
    impl->cols_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->cols_num, (vec4){{0.1, 0.1, 0.9, 1}});
    impl->cols_text.pose = u_pose_new(DIALOG_LEFT+8, DIALOG_TOP-pos, 1, 2);
    impl->cols_num.pose = u_pose_new(DIALOG_LEFT+40, DIALOG_TOP-pos, 1, 2);
    impl->cols_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP-pos+4, DIALOG_WIDTH, 10+8);

    pos = 35;
    impl->rows = canvas->RO.image.rows;
    impl->rows_text = ro_text_new_font55(5);
    ro_text_set_text(&impl->rows_text, "rows:");
    ro_text_set_color(&impl->rows_text, (vec4){{0.9, 0.9, 0.9, 1}});
    impl->rows_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->rows_num, (vec4){{0.1, 0.1, 0.9, 1}});
    impl->rows_text.pose = u_pose_new(DIALOG_LEFT+8, DIALOG_TOP-pos, 1, 2);
    impl->rows_num.pose = u_pose_new(DIALOG_LEFT+40, DIALOG_TOP-pos, 1, 2);    
    impl->rows_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP-pos+4, DIALOG_WIDTH, 10+8);

    pos = 50;
    impl->layers = canvas->RO.image.layers;
    impl->layers_text = ro_text_new_font55(7);
    ro_text_set_text(&impl->layers_text, "layers:");
    ro_text_set_color(&impl->layers_text, (vec4){{0.9, 0.9, 0.9, 1}});
    impl->layers_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->layers_num, (vec4){{0.1, 0.1, 0.9, 1}});
    impl->layers_text.pose = u_pose_new(DIALOG_LEFT+8, DIALOG_TOP-pos, 1, 2);
    impl->layers_num.pose = u_pose_new(DIALOG_LEFT+50, DIALOG_TOP-pos, 1, 2);    
    impl->layers_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP-pos+4, DIALOG_WIDTH, 10+8);


    pos = 70;
    impl->p_cols = canvas->RO.pattern_cols;
    impl->p_cols_text = ro_text_new_font55(13);
    ro_text_set_text(&impl->p_cols_text, "pattern cols:");
    ro_text_set_color(&impl->p_cols_text, (vec4){{0.9, 0.9, 0.9, 1}});
    impl->p_cols_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->p_cols_num, (vec4){{0.1, 0.1, 0.9, 1}});
    impl->p_cols_text.pose = u_pose_new(DIALOG_LEFT+8, DIALOG_TOP-pos, 1, 2);
    impl->p_cols_num.pose = u_pose_new(DIALOG_LEFT+90, DIALOG_TOP-pos, 1, 2);
    impl->p_cols_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP-pos+4, DIALOG_WIDTH, 10+8);

    pos = 85;
    impl->p_rows = canvas->RO.pattern_rows;
    impl->p_rows_text = ro_text_new_font55(13);
    ro_text_set_text(&impl->p_rows_text, "pattern rows:");
    ro_text_set_color(&impl->p_rows_text, (vec4){{0.9, 0.9, 0.9, 1}});
    impl->p_rows_num = ro_text_new_font55(8);
    ro_text_set_color(&impl->p_rows_num, (vec4){{0.1, 0.1, 0.9, 1}});
    impl->p_rows_text.pose = u_pose_new(DIALOG_LEFT+8, DIALOG_TOP-pos, 1, 2);
    impl->p_rows_num.pose = u_pose_new(DIALOG_LEFT+90, DIALOG_TOP-pos, 1, 2);    
    impl->p_rows_hitbox = u_pose_new_aa(DIALOG_LEFT, DIALOG_TOP-pos + 4, DIALOG_WIDTH, 10+8);


    dialog_set_title(self, "set size", (vec4){{0.8, 0.2, 0.2, 1}});
    dialog_set_bg_color(self, u_color_from_hex(CANVASSIZE_BG_A), u_color_from_hex(CANVASSIZE_BG_B));
    self->in.impl_height = pos;
    self->kill = canvas_size_kill;
    self->update = canvas_size_update;
    self->render = canvas_size_render;
    self->pointer_event = canvas_size_pe;
    self->opt_on_cancel_cb = canvas_size_on_action;
    self->opt_on_ok_cb = canvas_size_on_action;
}




struct ImageUpload {
    RoText info;
    RoSingle upload;
    bool upload_available;
};
static void image_upload_kill(void *impl) {
    struct ImageUpload *self = impl;
    ro_text_kill(&self->info);
    ro_single_kill(&self->upload);
    rhc_free(self);
}
static void image_upload_update(Dialog *self, float dtime) {
    // noop
}
static void image_upload_render(Dialog *self, const mat4 *cam_mat) {
    struct ImageUpload *impl = self->impl;
    ro_text_render(&impl->info, cam_mat);
    if(impl->upload_available)
        ro_single_render(&impl->upload, cam_mat);
}

static void image_upload_set_info(Dialog *self, const char *file_name) {
    struct ImageUpload *impl = self->impl;
    char text[64];
    uImage img = u_image_new_file(1, "import.png");
    if(!u_image_valid(img)) {
        snprintf(text, sizeof text, "failed to load\n  image\n%s", file_name);
    } else {
        snprintf(text, sizeof text, "%s\n   cols: %i\n   rows: %i", file_name, img.cols, img.rows);
    }
    ro_text_set_text(&impl->info, text);
    u_image_kill(&img);  
}

static void image_upload_uploaded(const char *file, bool ascii, const char *user_file_name, void *user_data) {
    image_upload_set_info(user_data, user_file_name);
}

static bool image_upload_pe(Dialog *self, ePointer_s pointer) {
    struct ImageUpload *impl = self->impl;
    
    if(impl->upload_available && button_clicked(&impl->upload.rect, pointer)) {
        e_io_ask_for_file_upload("import.png", false, image_upload_uploaded, self);
    }
    
    return true;
}

void image_upload_on_action(Dialog *self, bool ok) {
    dialog_hide(self);
}


void dialog_create_image_upload(Dialog *self) {
    dialog_hide(self);
    struct ImageUpload *impl = rhc_calloc(sizeof *impl);
    self->impl = impl;
    
    impl->info = ro_text_new_font55(64);
    ro_text_set_color(&impl->info, (vec4){{0.9, 0.9, 0.9, 1}});

    image_upload_set_info(self, "import.png");
    
    impl->info.pose = u_pose_new(DIALOG_LEFT+8, DIALOG_TOP-22, 1, 2);
    
    self->in.impl_height = 44;

#ifdef __EMSCRIPTEN__ 
    impl->upload = ro_single_new(r_texture_new_file(2, 1, "res/button_dialog_upload.png"));
    impl->upload_available = true;
    impl->upload.rect.pose = u_pose_new_aa(DIALOG_LEFT + 8, DIALOG_TOP-62, 64, 16);
#endif
    
    dialog_set_title(self, "import", (vec4){{0.2, 0.6, 0.2, 1}});
    dialog_set_bg_color(self, u_color_from_hex(TOOLTIP_BG_A), u_color_from_hex(TOOLTIP_BG_B));
    self->kill = image_upload_kill;
    self->update = image_upload_update;
    self->render = image_upload_render;
    self->pointer_event = image_upload_pe;
//    self->opt_on_cancel_cb = tooltip_on_action;
    self->opt_on_ok_cb = image_upload_on_action;
}

