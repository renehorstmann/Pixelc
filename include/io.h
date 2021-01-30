#ifndef PIXELC_IO_H
#define PIXELC_IO_H

#include <stdbool.h>
#include "layer.h"

bool io_load_layer(Layer *out_layer, const char *file);

bool io_save_layer(Layer layer, const char *file);

#endif //PIXELC_IO_H
