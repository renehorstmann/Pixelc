#include "m/float.h"
#include "r/texture.h"
#include "r/ro_batch.h"
#include "r/ro_text.h"


// for fontXX_shadow opt color
#include "u/sprite.h"


//
// private
//

// from u/pose
static mat4 u_pose_new(float x, float y, float w, float h) {
    // mat4 has column major order
    return (mat4) {{
                           w, 0, 0, 0,
                           0, h, 0, 0,
                           0, 0, 1, 0,
                           x, y, 0, 1
                   }};
}

static mat4 u_pose_new_aa(float l, float t, float w, float h) {
    return u_pose_new(l + w / 2, t - h / 2, w, h);
}

static mat4 u_pose_new_hidden() {
    return u_pose_new(SCA_MAX, SCA_MAX, 1, 1);
}
// end of u/pose copy



static void hide(RoText *self, int from) {
    for (int i = from; i < self->ro.num; i++) {
        self->ro.rects[i].pose = u_pose_new_hidden();
    }
}

static mat4 pose(const RoText *self, int c, int r) {
    return u_pose_new_aa(c * self->offset.x, -r * self->offset.y,
                         self->ro.tex.sprite_size.x, self->ro.tex.sprite_size.y);
}



//
// public
//

RoText ro_text_new(int max, ro_text_sprite_fn sprite_fn, rTexture tex_sink) {
    RoText self;
    self.sprite_fn = sprite_fn;
    self.pose = mat4_eye();
    self.offset = (vec2) {{6, 6}};
    // batch.vp will be set each time before rendering
    self.ro = ro_batch_new(max, tex_sink);
    hide(&self, 0);
    ro_batch_update(&self.ro);
    return self;
}

void ro_text_kill(RoText *self) {
    ro_batch_kill(&self->ro);
}

void ro_text_render(const RoText *self, const mat4 *camera_mat) {
    mat4 mvp = mat4_mul_mat(*camera_mat, self->pose);
    ro_batch_render(&self->ro, &mvp, false);
}

vec2 ro_text_set_text(RoText *self, const char *text) {
    int i = 0;
    int col = 0;
    int row = 0;
    int cols = 0;
    while (*text && i < self->ro.num) {
        bool newline = self->sprite_fn(&self->ro.rects[i].sprite, *text);
        self->ro.rects[i].pose = pose(self, col, row);

        col++;
        if (newline) {
            col = 0;
            row++;
        }
        cols = sca_max(cols, col);
        text++;
        i++;
    }
    hide(self, i);
    ro_batch_update(&self->ro);

    if (cols == 0)
        return vec2_set(0);

    return (vec2) {{
                           (cols - 1) * self->offset.x + self->ro.tex.sprite_size.x,
                           row * self->offset.y + self->ro.tex.sprite_size.y
                   }};
}

vec2 ro_text_get_size(const RoText *self, const char *text) {
    int cols = 0;
    int rows = 0;
    int c = 0;
    int i = 0;
    vec2 sprite = {{0}};
    while (*text && i < self->ro.num) {
        if (self->sprite_fn(&sprite, *text++)) {
            rows++;
            c = 0;
        } else {
            c++;
            cols = sca_max(cols, c);
        }
        i++;
    }

    if (cols == 0)
        return vec2_set(0);

    return (vec2) {{
                           (cols - 1) * self->offset.x + self->ro.tex.sprite_size.x,
                           rows * self->offset.y + self->ro.tex.sprite_size.y
                   }};
}

void ro_text_set_color(RoText *self, vec4 color) {
    for (int i = 0; i < self->ro.num; i++) {
        self->ro.rects[i].color = color;
    }
    ro_batch_update(&self->ro);
}



//
// private
//

static bool font55_sprite_cb(vec2 *sprite, char c) {
    const int columns = 12;
    const int rows = 5;

    bool nl = false;
    if (c == '\n') {
        nl = true;
        c = ' ';
    }

    c = toupper(c);
    if (c < ' ' || c > 'Z')
        c = ' ';
    c -= ' ';
    int col = c % columns;
    int row = c / columns;

    sprite->x = col;
    sprite->y = row;

    return nl;
}


static bool font85_sprite_cb(vec2 *sprite, char c) {
    const int columns = 12;
    const int rows = 8;

    bool nl = false;
    if (c == '\n') {
        nl = true;
        c = ' ';
    }

    if (c < ' ' || c > '~')
        c = ' ';
    c -= ' ';
    int col = c % columns;
    int row = c / columns;

    sprite->x = col;
    sprite->y = row;

    return nl;
}


//
// public
//

RoText ro_text_new_font55(int max) {
    const int columns = 12;
    const int rows = 5;
    rTexture tex = r_texture_new_file(columns, rows, "res/r/font55.png");
    r_texture_filter_nearest(tex);
    return ro_text_new(max, font55_sprite_cb, tex);
}

RoText ro_text_new_font55_shadow(int max, ucvec4 *opt_shadow_color) {
    const int columns = 12;
    const int rows = 5;
    uSprite sprite = u_sprite_new_file(columns, rows, "res/r/font55_shadow.png");
    if(opt_shadow_color) {
        int size = sprite.img.cols*sprite.img.rows*sprite.img.layers;
        for(int i=0; i<size; i++) {
            uColor_s *col = u_image_pixel_index(sprite.img, i, 0);
            if(u_color_equals(*col, RO_TEXT_SHADOW_COLOR))
                *col = *opt_shadow_color;
        }
    }
    rTexture tex = r_texture_new_sprite_buffer(sprite.img.cols, sprite.img.rows, columns, rows, sprite.img.data);
    u_sprite_kill(&sprite);
    r_texture_filter_nearest(tex);
    return ro_text_new(max, font55_sprite_cb, tex);
}

RoText ro_text_new_font85(int max) {
    const int columns = 12;
    const int rows = 8;
    rTexture tex = r_texture_new_file(columns, rows, "res/r/font85.png");
    r_texture_filter_nearest(tex);
    RoText self = ro_text_new(max, font85_sprite_cb, tex);
    self.offset = (vec2) {{6, 9}};
    return self;
}

RoText ro_text_new_font85_shadow(int max, ucvec4 *opt_shadow_color) {
    const int columns = 12;
    const int rows = 8;
    uSprite sprite = u_sprite_new_file(columns, rows, "res/r/font85_shadow.png");
    if(opt_shadow_color) {
        int size = sprite.img.cols*sprite.img.rows*sprite.img.layers;
        for(int i=0; i<size; i++) {
            uColor_s *col = u_image_pixel_index(sprite.img, i, 0);
            if(u_color_equals(*col, RO_TEXT_SHADOW_COLOR))
                *col = *opt_shadow_color;
        }
    }
    rTexture tex = r_texture_new_sprite_buffer(sprite.img.cols, sprite.img.rows, columns, rows, sprite.img.data);
    u_sprite_kill(&sprite);
    r_texture_filter_nearest(tex);
    RoText self = ro_text_new(max, font85_sprite_cb, tex);
    self.offset = (vec2) {{6, 9}};
    return self;
}
