#include <SDL2/SDL_image.h>
#include "rhc/error.h"
#include "rhc/log.h"
#include "mathc/sca/int.h"
#include "u/image.h"

//
// private
//

static SDL_Surface *load_buffer(void *data, int cols, int rows) {
    // Set up the pixel format color masks for RGB(A) byte arrays.
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    int depth = 32;
    int pitch = 4 * cols;

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(data, cols, rows, depth, pitch, rmask, gmask, bmask, amask);
    return surf;
}


//
// public
//

uImage u_image_new_empty_a(int cols, int rows, int layers, Allocator_i a) {
    size_t data_size = cols * rows * layers * sizeof(uColor_s);

    if (data_size <= 0) {
        rhc_error = "image new failed";
        log_error("u_image_new_empty_a failed: wrong data size: %zu", data_size);
        return u_image_new_invalid();
    }

    uImage self =
            {a.malloc(a, data_size),
             cols, rows, layers,
             a};
    if (!u_image_valid(self))
        return u_image_new_invalid_a(a);
    return self;
}

uImage u_image_new_zeros_a(int cols, int rows, int layers, Allocator_i a) {
    uImage self = u_image_new_empty_a(cols, rows, layers, a);
    if (!u_image_valid(self))
        return self;
    memset(self.data, 0, u_image_data_size(self));
    return self;
}

uImage u_image_new_clone_a(uImage from, Allocator_i a) {
    uImage self = u_image_new_empty_a(from.cols, from.rows, from.layers, a);
    if (!u_image_valid(self))
        return u_image_new_invalid();
    memcpy(self.data, from.data, u_image_data_size(from));
    return self;
}

uImage u_image_new_file_a(int layers, const char *file, Allocator_i a) {
    assume(layers > 0, "A single layer needed");
    uImage self = u_image_new_invalid_a(a);
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        rhc_error = "load image file failed";
        log_warn("u_image_new_file_a failed: failed: %s (%s)", IMG_GetError(), file);
        goto CLEAN_UP;
    }
    SDL_PixelFormat *f = img->format;
    if (f->BitsPerPixel != 32 || f->Amask == 0) {
        rhc_error = "load image file failed";
        log_warn("u_image_new_file_a failed: 8bpp and alpha needed (%s)", file);
        goto CLEAN_UP;
    }

    if (img->h % layers != 0) {
        rhc_error = "load image file failed";
        log_warn("u_image_new_file_a failed: rows %% layers != 0 (%s)", file);
        goto CLEAN_UP;
    }

    self = u_image_new_empty_a(img->w, img->h / layers, layers, a);
    if (u_image_valid(self))
        memcpy(self.data, img->pixels, u_image_data_size(self));

    CLEAN_UP:
    SDL_FreeSurface(img);
    return self;
}

void u_image_kill(uImage *self) {
    if (u_image_valid(*self))
        self->allocator.free(self->allocator, self->data);
    *self = u_image_new_invalid_a(self->allocator);
}

bool u_image_save_file(uImage self, const char *file) {
    if (!u_image_valid(self)) {
        rhc_error = "image save file failed";
        log_error("u_image_save_file failed: invalid (%s)", file);
        return false;
    }
    SDL_Surface *img = load_buffer((void *) self.data, self.cols, self.rows * self.layers);
    if (!img) {
        rhc_error = "image save file failed";
        log_error("u_image_save_file failed: sdl buffer failed: %s", SDL_GetError());
        return false;
    }
    int ret = IMG_SavePNG(img, file);
    SDL_FreeSurface(img);
    if (ret) {
        rhc_error = "image save file failed";
        log_error("u_image_save_file: failed: %s (%s)", IMG_GetError(), file);
        return false;
    }
    return true;
}

bool u_image_copy(uImage self, uImage from) {
    if (!u_image_valid(self) || !u_image_valid(from)
        || self.cols != from.cols
        || self.rows != from.rows
        || self.layers != from.layers
            ) {
        rhc_error = "image copy failed";
        log_error("u_image_copy failed: invalid or different size");
        return false;
    }

    size_t size = u_image_data_size(self);
    memcpy(self.data, from.data, size);
    return true;
}

void u_image_copy_top_left(uImage self, uImage from) {
    if(!u_image_valid(self) || !u_image_valid(from)) {
        log_warn("u_image_copy_top_left failed");
        return;
    }
    int layers = isca_min(self.layers, from.layers);
    int rows = isca_min(self.rows, from.rows);
    int cols = isca_min(self.cols, from.cols);
    
    for(int l=0; l<layers; l++) {
        for(int r=0; r<rows; r++) {
            for(int c=0; c<cols; c++) {
                *u_image_pixel(self, c, r, l) = 
                        *u_image_pixel(from, c, r, l);
            }
        }
    }
}

bool u_image_equals(uImage self, uImage from) {
    if (!u_image_valid(self) || !u_image_valid(from)
        || self.cols != from.cols
        || self.rows != from.rows
        || self.layers != from.layers)
        return false;

    return memcmp(self.data, from.data, u_image_data_size(self)) == 0;
}


void u_image_rotate(uImage *self, bool right) {
    if (!u_image_valid(*self))
        return;

    uImage tmp = u_image_new_clone_a(*self, self->allocator);
    if (!u_image_valid(tmp))
        return;

    self->cols = tmp.rows;
    self->rows = tmp.cols;
    for (int l = 0; l < self->layers; l++) {
        for (int r = 0; r < self->rows; r++) {
            for (int c = 0; c < self->cols; c++) {
                int mc = right ? r : tmp.cols - 1 - r;
                int mr = right ? tmp.rows - 1 - c : c;
                *u_image_pixel(*self, c, r, l) = *u_image_pixel(tmp, mc, mr, l);
            }
        }
    }

    u_image_kill(&tmp);
}

void u_image_mirror(uImage self, bool vertical) {
    if (!u_image_valid(self))
        return;

    uImage tmp = u_image_new_clone(self);
    if (!u_image_valid(tmp))
        return;

    for (int l = 0; l < self.layers; l++) {
        for (int r = 0; r < self.rows; r++) {
            for (int c = 0; c < self.cols; c++) {
                int mc = vertical ? self.cols - 1 - c : c;
                int mr = vertical ? r : self.rows - 1 - r;
                *u_image_pixel(self, c, r, l) = *u_image_pixel(tmp, mc, mr, l);
            }
        }
    }

    u_image_kill(&tmp);
}
