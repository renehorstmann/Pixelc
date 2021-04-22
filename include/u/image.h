#ifndef JUMPHARE_IMAGE_H
#define JUMPHARE_IMAGE_H

#include "rhc/allocator.h"
#include "color.h"


typedef struct {
    int cols, rows;
    int layers;
    Allocator_s allocator;
    uColor_s data[];
} uImage;

static bool u_image_valid(const uImage *self) {
    return self != NULL
            && self->cols > 0 && self->rows > 0
            && self->layers > 0
            && allocator_valid(self->allocator);
}

static uImage *u_image_new_invalid() {
    return NULL;
}

uImage *u_image_new_empty_a(int cols, int rows, int layers, Allocator_s a);

static uImage *u_image_new_empty(int cols, int rows, int layers) {
    return u_image_new_empty_a(cols, rows, layers,
            allocator_new_raising());
}

uImage *u_image_new_zeros_a(int cols, int rows, int layers,  Allocator_s a);

static uImage *u_image_new_zeros(int cols, int rows, int layers) {
    return u_image_new_zeros_a(cols, rows, layers,
            allocator_new_raising());
}

uImage *u_image_new_clone_a(const uImage *from, Allocator_s a);

static uImage *u_image_new_clone(const uImage *from) {
    return u_image_new_clone_a(from,
            allocator_new_raising());
}

uImage *u_image_new_file_a(int layers, const char *file, Allocator_s a);

static uImage *u_image_new_file(int layers, const char *file) {
    return u_image_new_file_a(layers, file,
            allocator_new_raising());
}



void u_image_delete(uImage *self);

bool u_image_save_file(const uImage *self, const char *file);

bool u_image_copy(uImage *self, const uImage *from);

bool u_image_equals(const uImage *self, const uImage *from);

static size_t u_image_data_size(const uImage *self) {
    if(!u_image_valid(self))
        return 0;
    
    return self->cols * self->rows * self->layers * sizeof(uColor_s);
}

static size_t u_image_full_size(const uImage *self) {
    // invalid safe
    return sizeof(uImage) + u_image_data_size(self);
}

static uColor_s *u_image_pixel(uImage *self, int c, int r, int layer) {
    if(!u_image_valid(self))
        return NULL;
    return &self->data[
            layer * self->rows * self->cols
            + r * self->cols
            + c];
}

static uColor_s *u_image_pixel_index(uImage *self, int index, int layer) {
    // invalid safe
    return u_image_pixel(self, index, 0, layer);
}

static uColor_s *u_image_layer(uImage *self, int layer) {
    // invalid safe
    return u_image_pixel(self, 0, 0, layer);
}

static bool u_image_contains(const uImage *self, int c, int r) {
    if(!u_image_valid(self))
        return false;
    return c >= 0 && c < self->cols
           && r >= 0 && r < self->rows;
}

#endif //JUMPHARE_IMAGE_H
