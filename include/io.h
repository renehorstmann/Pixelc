#ifndef PIXELC_IO_H
#define PIXELC_IO_H

#include "layer.h"

void io_load_layer(Layer *out_layer, const char *file);

void io_save_layer(const Layer layer, const char *file);

#endif //PIXELC_IO_H
