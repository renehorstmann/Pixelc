#include "utilc/alloc.h"
#include "image.h"


Image *image_new_empty(int layers, int rows, int cols) {
    Image *self = raising_malloc(1, sizeof(Image) + sizeof(Color_s) * layers * rows * cols, SIGABRT);
    self->layers = layers;
    self->rows = rows;
    self->cols = cols;
    return self;
}

Image *image_new_zeros(int layers, int rows, int cols) {
    Image *self = raising_calloc(1, sizeof(Image) + sizeof(Color_s) * layers * rows * cols, SIGABRT);
    self->layers = layers;
    self->rows = rows;
    self->cols = cols;
    return self;
}

Image *image_new_clone(const Image *from) {
    Image *self = image_new_empty(from->layers, from->rows, from->cols);
    memcpy(self->data, from->data, image_data_size(from));
    return self;
}

void image_delete(Image *self) {
    free(self);
}

bool image_copy(Image *self, const Image *from) {
    size_t self_size = image_data_size(self);
    size_t from_size = image_data_size(from);
    if(self_size == from_size) {
        memcpy(self->data, from->data, self_size);
        self->layers = from->layers;
        self->rows = from->rows;
        self->cols = from->cols;
        return true;
    }
    SDL_Log("image_copy failed: wrong size (self/from): %zu / %zu", self_size, from_size);
    return false;
}

