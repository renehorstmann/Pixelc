#include "utilc/alloc.h"
#include "image.h"


Image *image_new(int rows, int cols, int layers){
    Image *self = raising_calloc(1, sizeof(Image) + sizeof(Color_s) * layers * rows * cols, SIGABRT);
    self->rows = rows;
    self->cols = cols;
    self->layers = layers;
    return self;
}

void image_delete(Image *self) {
    free(self);
}

Image *image_clone(const Image *from) {
    size_t size = from->layers * from->rows * from->cols;
    Image *self = raising_malloc(1, sizeof(Image) + sizeof(Color_s) * size, SIGABRT);
    self->rows = from->rows;
    self->cols = from->cols;
    self->layers = from->layers;
    memcpy(self->data, from->data, sizeof(Color_s) * size);
    return self;
}

void image_copy(Image *self, const Image *from) {
    size_t self_size = self->layers * self->rows * self->cols;
    size_t from_size = from->layers * from->rows * from->cols;
    if(self_size != from_size) {
        fprintf(stderr, "image_copy failed, wrong size: %zu / %zu\n", self_size, from_size);
        raise(SIGABRT);
    }
    memcpy(self->data, from->data, sizeof(Color_s) * self_size);
}

