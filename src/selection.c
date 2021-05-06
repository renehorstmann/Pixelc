#include "rhc/error.h"
#include "rhc/log.h"
#include "selection.h"


//
// private
//

static struct {
    int left, top;
    int cols, rows;
    uImage opt_img;
} L;

static bool valid_to_copy(uImage img, int layer) {
    return L.left >= 0 && L.top >= 0
           && L.cols > 0 && L.rows > 0
           && L.left + L.cols <= img.cols
           && L.top + L.rows <= img.rows;
}


//
// public
//

void selection_init(int left, int top, int cols, int rows) {
    log_info("selection: init");
    u_image_kill(&L.opt_img);
    L.left = left;
    L.top = top;
    L.cols = cols;
    L.rows = rows;
}

void selection_kill() {
    log_info("selection: kill");
    L.left = L.top = L.rows = L.cols = 0;
    u_image_kill(&L.opt_img);
}

bool selection_active() {
    return L.cols > 0 && L.rows > 0;
}

ivec2 selection_pos() {
    return (ivec2) {{L.left, L.top}};
}

ivec2 selection_size() {
    return (ivec2) {{L.cols, L.rows}};
}


void selection_move(int left, int top) {
    L.left = left;
    L.top = top;
}

bool selection_contains(int c, int r) {
    return !selection_active()
           || (c >= L.left && c < L.left + L.cols
               && r >= L.top && r < L.top + L.rows);
}

void selection_copy(uImage from, int layer) {
    log_info("selection: copy");
    if (!valid_to_copy(from, layer)) {
        log_error("selection_copy failed");
        return;
    }

    // invalid safe
    u_image_kill(&L.opt_img);

    L.opt_img = u_image_new_empty(L.cols, L.rows, 1);

    for (int r = 0; r < L.rows; r++) {
        for (int c = 0; c < L.cols; c++) {
            *u_image_pixel(L.opt_img, c, r, 0) =
                    *u_image_pixel(from,c + L.left, r + L.top, layer);
        }
    }
}

void selection_cut(uImage from, int layer, uColor_s replace) {
    log_info("selection: cut");
    if (!valid_to_copy(from, layer)) {
        log_error("selection_cut failed");
        return;
    }
    selection_copy(from, layer);

    for (int r = 0; r < L.rows; r++) {
        for (int c = 0; c < L.cols; c++) {
            *u_image_pixel(from, c + L.left, r + L.top, layer) = replace;
        }
    }
}

void selection_paste(uImage to, int layer) {
    log_info("selection: paste");
    if (!u_image_valid(L.opt_img)) {
        log_error("selection_paste failed");
        return;
    }
    for (int r = 0; r < L.rows; r++) {
        int to_r = r + L.top;
        if (to_r < 0 || to_r >= to.rows)
            continue;
        for (int c = 0; c < L.cols; c++) {
            int to_c = c + L.left;
            if (to_c < 0 || to_c >= to.cols)
                continue;

            *u_image_pixel(to, to_c, to_r, layer) =
                    *u_image_pixel(L.opt_img, c, r, 0);
        }
    }
}

void selection_rotate(bool right) {
    log_info("selection: right (r=%i)", right);
    if (!u_image_valid(L.opt_img)) {
        log_error("selection_rotate failed");
        return;
    }

    u_image_rotate(&L.opt_img, right);
    L.cols = L.opt_img.cols;
    L.rows = L.opt_img.rows;
}

void selection_mirror(bool vertical) {
    log_info("selection: mirror (v=%i)", vertical);
    if (!u_image_valid(L.opt_img)) {
        log_error("selection_mirror failed");
        return;
    }

    u_image_mirror(L.opt_img, vertical);
}
