#include "utilc/alloc.h"
#include "canvas.h"
#include "layer.h"


void layer_init(Layer *self) {
    *self = (Layer) {
            New0(Color_s, canvas_rows() * canvas_cols()),
            255
    };
}

void layer_kill(Layer *self) {
    free(self->data);
    *self = (Layer) {0};
}

Color_s *layer_pixel(Layer *self, int row, int col) {
    return &self->data[col + row * canvas_cols()];
}

Color_s *layer_pixel_index(Layer *self, int index) {
    return &self->data[index];
}
