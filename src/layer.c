#include "utilc/alloc.h"
#include "layer.h"


void layer_init(Layer *self, int rows, int cols) {
    *self = (Layer) {
            New0(color, rows * cols),
            rows, cols,
            255
    };
}

void layer_kill(Layer *self) {
    free(self->data);
    *self = (Layer) {0};
}

color *layer_pixel(Layer *self, int row, int col) {
    return &self->data[col + row * self->cols];
}
