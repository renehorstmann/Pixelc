#include "s/error.h"
#include "s/log.h"
#include "selection.h"


//
// private
//

static bool valid_to_copy(const Selection *self, uImage img, int layer) {
    return self
           && self->left >= 0 && self->top >= 0
           && self->cols > 0 && self->rows > 0
           && self->left + self->cols <= img.cols
           && self->top + self->rows <= img.rows;
}


//
// public
//

Selection *selection_new(int left, int top, int cols, int rows) {
    s_log("new");
    Selection *self = s_malloc0(sizeof *self);

    self->left = left;
    self->top = top;
    self->cols = cols;
    self->rows = rows;

    return self;
}

void selection_kill(Selection **self_ptr) {
    if (!*self_ptr)
        return;
    s_log("kill");
    Selection *self = *self_ptr;
    u_image_kill(&self->opt_img);
    s_free(*self_ptr);
    *self_ptr = NULL;
}


bool selection_contains(const Selection *self, int c, int r) {
    if (!self) return false;
    return (c >= self->left && c < self->left + self->cols
            && r >= self->top && r < self->top + self->rows);
}

void selection_copy(Selection *self, uImage from, int layer) {
    s_log("copy");
    if (!valid_to_copy(self, from, layer)) {
        s_log_error("selection_copy failed");
        return;
    }

    // invalid safe
    u_image_kill(&self->opt_img);

    self->opt_img = u_image_new_empty(self->cols, self->rows, 1);

    for (int r = 0; r < self->rows; r++) {
        for (int c = 0; c < self->cols; c++) {
            *u_image_pixel(self->opt_img, c, r, 0) =
                    *u_image_pixel(from, c + self->left, r + self->top, layer);
        }
    }
}

void selection_cut(Selection *self, uImage from, int layer, uColor_s replace) {
    s_log("cut");
    if (!valid_to_copy(self, from, layer)) {
        s_log_error("failed");
        return;
    }
    selection_copy(self, from, layer);

    for (int r = 0; r < self->rows; r++) {
        for (int c = 0; c < self->cols; c++) {
            *u_image_pixel(from, c + self->left, r + self->top, layer) = replace;
        }
    }
}

void selection_paste(Selection *self, uImage to, int layer) {
    s_log("paste");
    if (!self || !u_image_valid(self->opt_img)) {
        s_log_error("failed");
        return;
    }
    for (int r = 0; r < self->rows; r++) {
        int to_r = r + self->top;
        if (to_r < 0 || to_r >= to.rows)
            continue;
        for (int c = 0; c < self->cols; c++) {
            int to_c = c + self->left;
            if (to_c < 0 || to_c >= to.cols)
                continue;

            uColor_s *pixel_to = u_image_pixel(to, to_c, to_r, layer);
            const uColor_s *pixel_from = u_image_pixel(self->opt_img, c, r, 0);

            if (self->blend) {
                *pixel_to = ucvec4_mix(*pixel_to, *pixel_from, (float) pixel_from->a / 255);
            } else {
                *pixel_to = *pixel_from;
            }
        }
    }
}

void selection_rotate(Selection *self, bool right) {
    s_log("rotate (r=%i)", right);
    if (!self || !u_image_valid(self->opt_img)) {
        s_log_error("failed");
        return;
    }

    u_image_rotate(&self->opt_img, right);
    self->cols = self->opt_img.cols;
    self->rows = self->opt_img.rows;
}

void selection_mirror(Selection *self, bool vertical) {
    s_log("mirror (v=%i)", vertical);
    if (!self || !u_image_valid(self->opt_img)) {
        s_log_error("failed");
        return;
    }

    u_image_mirror(self->opt_img, vertical);
}
