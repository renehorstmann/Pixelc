#ifndef U_IMAGE_H
#define U_IMAGE_H

#include "rhc/alloc.h"
#include "color.h"


struct SDL_Surface;

// Image class
typedef struct {
    uColor_s *data;
    int cols, rows;
    int layers;
    Allocator_i allocator;
} uImage;

static bool u_image_valid(uImage self) {
    return self.cols > 0 && self.rows > 0
           && self.layers > 0
           && allocator_valid(self.allocator);
}

static uImage u_image_new_invalid_a(Allocator_i a) {
    return (uImage) {.allocator = a};
}

static uImage u_image_new_invalid() {
    return u_image_new_invalid_a(rhc_allocator_new());
}

// creates a new empty image with a costum allocator
uImage u_image_new_empty_a(int cols, int rows, int layers, Allocator_i a);

// creates a new empty image
static uImage u_image_new_empty(int cols, int rows, int layers) {
    return u_image_new_empty_a(cols, rows, layers,
                               rhc_allocator_new());
}

// creates a new image with all values set to 0 with a costum allocator
uImage u_image_new_zeros_a(int cols, int rows, int layers, Allocator_i a);

// creates a new image with all values set to 0
static uImage u_image_new_zeros(int cols, int rows, int layers) {
    return u_image_new_zeros_a(cols, rows, layers,
                               rhc_allocator_new());
}

// clones an image with a costum allocator
uImage u_image_new_clone_a(uImage from, Allocator_i a);

// clones an image
static uImage u_image_new_clone(uImage from) {
    return u_image_new_clone_a(from,
                               rhc_allocator_new());
}

// copy a SDL_Surface into a new image with a costum allocator
uImage u_image_new_sdl_surface_a(int layers, struct SDL_Surface *surface, Allocator_i a);


// copy a SDL_Surface into a new image
static uImage u_image_new_sdl_surface(int layers, struct SDL_Surface *surface) {
    return u_image_new_sdl_surface_a(layers, surface,
            rhc_allocator_new());
}

// loads an image from a file (.png) with a costum allocator
uImage u_image_new_file_a(int layers, const char *file, Allocator_i a);

// loads an image from a file (.png)
static uImage u_image_new_file(int layers, const char *file) {
    return u_image_new_file_a(layers, file,
                              rhc_allocator_new());
}

void u_image_kill(uImage *self);


// creates an SDL_Surface from the image
struct SDL_Surface *u_image_to_sdl_surface(uImage self);

// saves the image to a file (.png)
bool u_image_save_file(uImage self, const char *file);

// copies the image data, cols, rows and layers must be the same
bool u_image_copy(uImage self, uImage from);

// copies the image centred at top left, if the sizes are different
void u_image_copy_top_left(uImage self, uImage from);

// returns true if self == from
bool u_image_equals(uImage self, uImage from);


// rotates the image 90°
void u_image_rotate(uImage *self, bool right);

// mirrors the image
void u_image_mirror(uImage self, bool vertical);

// returns the size of the byte array
static size_t u_image_data_size(uImage self) {
    if (!u_image_valid(self))
        return 0;

    return self.cols * self.rows * self.layers * sizeof(uColor_s);
}

// gives access (read and write) to a pixel of the image
static uColor_s *u_image_pixel(uImage self, int c, int r, int layer) {
    if (!u_image_valid(self))
        return NULL;
    return &self.data[
            layer * self.rows * self.cols
            + r * self.cols
            + c];
}

// gives access (read and write) to a pixel of the image by index (row major order)
static uColor_s *u_image_pixel_index(uImage self, int index, int layer) {
    // invalid safe
    return u_image_pixel(self, index, 0, layer);
}

// returns the data start of a layer / its first pixel
static uColor_s *u_image_layer(uImage self, int layer) {
    // invalid safe
    return u_image_pixel(self, 0, 0, layer);
}

// returns true if c and r are in range 
static bool u_image_contains(uImage self, int c, int r) {
    if (!u_image_valid(self))
        return false;
    return c >= 0 && c < self.cols
           && r >= 0 && r < self.rows;
}

#endif //U_IMAGE_H
