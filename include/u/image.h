#ifndef U_IMAGE_H
#define U_IMAGE_H

#include "rhc/allocator.h"
#include "color.h"


#define IMAGE_DEFAULT_ALLCOATOR allocator_new_raising()


typedef struct {
    uColor_s *data;
    int cols, rows;
    int layers;
    Allocator_s allocator;
} uImage;

static bool u_image_valid(uImage self) {
    return self.cols > 0 && self.rows > 0
           && self.layers > 0
           && allocator_valid(self.allocator);
}

static uImage u_image_new_invalid_a(Allocator_s a) {
    return (uImage) {.allocator = a};
}

static uImage u_image_new_invalid() {
    return u_image_new_invalid_a(IMAGE_DEFAULT_ALLCOATOR);
}

uImage u_image_new_empty_a(int cols, int rows, int layers, Allocator_s a);

static uImage u_image_new_empty(int cols, int rows, int layers) {
    return u_image_new_empty_a(cols, rows, layers,
                               IMAGE_DEFAULT_ALLCOATOR);
}

uImage u_image_new_zeros_a(int cols, int rows, int layers, Allocator_s a);

static uImage u_image_new_zeros(int cols, int rows, int layers) {
    return u_image_new_zeros_a(cols, rows, layers,
                               IMAGE_DEFAULT_ALLCOATOR);
}

uImage u_image_new_clone_a(uImage from, Allocator_s a);

static uImage u_image_new_clone(uImage from) {
    return u_image_new_clone_a(from,
                               allocator_new_raising());
}

uImage u_image_new_file_a(int layers, const char *file, Allocator_s a);

static uImage u_image_new_file(int layers, const char *file) {
    return u_image_new_file_a(layers, file,
                              allocator_new_raising());
}


void u_image_kill(uImage *self);

bool u_image_save_file(uImage self, const char *file);

bool u_image_copy(uImage self, uImage from);

bool u_image_equals(uImage self, uImage from);

void u_image_rotate(uImage *self, bool right);

void u_image_mirror(uImage self, bool vertical);

static size_t u_image_data_size(uImage self) {
    if (!u_image_valid(self))
        return 0;

    return self.cols * self.rows * self.layers * sizeof(uColor_s);
}

static uColor_s *u_image_pixel(uImage self, int c, int r, int layer) {
    if (!u_image_valid(self))
        return NULL;
    return &self.data[
            layer * self.rows * self.cols
            + r * self.cols
            + c];
}

static uColor_s *u_image_pixel_index(uImage self, int index, int layer) {
    // invalid safe
    return u_image_pixel(self, index, 0, layer);
}

static uColor_s *u_image_layer(uImage self, int layer) {
    // invalid safe
    return u_image_pixel(self, 0, 0, layer);
}

static bool u_image_contains(uImage self, int c, int r) {
    if (!u_image_valid(self))
        return false;
    return c >= 0 && c < self.cols
           && r >= 0 && r < self.rows;
}

#endif //U_IMAGE_H
