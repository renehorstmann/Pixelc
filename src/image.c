#include <string.h>  // memcmp
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
    if(self->layers == from->layers
       && self->rows == from->rows 
       && self->cols == from->cols) {
        size_t size = image_data_size(self);
        memcpy(self->data, from->data, size);
        return true;
    }
    SDL_Log("image_copy failed");
    return false;
}

bool image_equals(const Image *self, const Image *from) {
	if(image_data_size(self) != image_data_size(from))
	    return false;
	    
	return memcmp(self, from, image_full_size(self)) == 0;
}

