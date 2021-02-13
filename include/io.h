#ifndef PIXELC_IO_H
#define PIXELC_IO_H

#include <stdbool.h>
#include "image.h"

struct IoGlobals_s {
	const char *default_image_file;
	const char *default_import_file;
};
extern struct IoGlobals_s io;

Image *io_load_image(const char *file);

bool io_save_image(const Image *image, const char *file);

#endif //PIXELC_IO_H
