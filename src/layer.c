#include "utilc/alloc.h"
#include "canvas.h"
#include "layer.h"


void layer_init(Layer *self) {
    *self = (Layer) {
            New0(color, canvas_rows() * canvas_cols()),
            255
    };
}

void layer_kill(Layer *self) {
    free(self->data);
    *self = (Layer) {0};
}

color *layer_pixel(Layer *self, int row, int col) {
    return &self->data[col + row * canvas_cols()];
}
