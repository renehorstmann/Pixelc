#ifndef U_IMAGE_H
#define U_IMAGE_H

#include "rhc/alloc.h"
#include "mathc/sca/float.h"
#include "color.h"


struct SDL_Surface;

// Image class
typedef struct {
    uColor_s *data;
    int cols, rows;
    int layers;
    Allocator_i a;
} uImage;

static bool u_image_valid(uImage self) {
    return self.cols > 0 && self.rows > 0
           && self.layers > 0
           && allocator_valid(self.a);
}

static uImage u_image_new_invalid_a(Allocator_i a) {
    return (uImage) {.a = a};
}

static uImage u_image_new_invalid() {
    return u_image_new_invalid_a(RHC_DEFAULT_ALLOCATOR);
}

// creates a new empty image with a custom a
uImage u_image_new_empty_a(int cols, int rows, int layers, Allocator_i a);

// creates a new empty image
static uImage u_image_new_empty(int cols, int rows, int layers) {
    return u_image_new_empty_a(cols, rows, layers, RHC_DEFAULT_ALLOCATOR);
}

// creates a new image with all values set to 0 with a custom a
uImage u_image_new_zeros_a(int cols, int rows, int layers, Allocator_i a);

// creates a new image with all values set to 0
static uImage u_image_new_zeros(int cols, int rows, int layers) {
    return u_image_new_zeros_a(cols, rows, layers, RHC_DEFAULT_ALLOCATOR);
}

// clones an image with a custom a
uImage u_image_new_clone_a(uImage from, Allocator_i a);

// clones an image
static uImage u_image_new_clone(uImage from) {
    return u_image_new_clone_a(from, from.a);
}

// returns a new scaled clone, if filter_linear is FALSE, filter_nearest will be used, with a custom a
uImage u_image_new_clone_scaled_a(int cols, int rows, uImage from, bool filter_linear, Allocator_i a);

// returns a new scaled clone, if filter_linear is FALSE, filter_nearest will be used
static uImage u_image_new_clone_scaled(int cols, int rows, bool filter_linear, uImage from) {
    return u_image_new_clone_scaled_a(cols, rows, from, filter_linear, from.a);
}

// merges the given layer down with the previous one, with a custom a
uImage u_image_new_clone_merge_down_a(uImage from, int layer_to_merge_down, Allocator_i a);

// merges the given layer down with the previous one
static uImage u_image_new_clone_merge_down(uImage from, int layer_to_merge_down) {
    return u_image_new_clone_merge_down_a(from, layer_to_merge_down, from.a);
}

// copy a SDL_Surface into a new image with a costum a
uImage u_image_new_sdl_surface_a(int layers, struct SDL_Surface *surface, Allocator_i a);


// copy a SDL_Surface into a new image
static uImage u_image_new_sdl_surface(int layers, struct SDL_Surface *surface) {
    return u_image_new_sdl_surface_a(layers, surface,
                                     allocator_new());
}

// loads an image from a file (.png) with a costum a
uImage u_image_new_file_a(int layers, const char *file, Allocator_i a);

// loads an image from a file (.png)
static uImage u_image_new_file(int layers, const char *file) {
    return u_image_new_file_a(layers, file,
                              allocator_new());
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

// returns the filtered color at the % position uv of image self (at the given layer)
// if filter_linear is false, filter_nearest is used
// u and v in % [0-1] for row and col
static uColor_s u_image_get_pixel_filtered(uImage self, float u, float v, int layer, bool filter_linear) {
    float col = u * self.cols;
    float row = v * self.rows;
    int fcol = (int)(sca_floor(col)) % self.cols;
    int ccol = (int)(sca_ceil(col)) % self.cols;
    int frow = (int)(sca_floor(row)) % self.rows;
    int crow = (int)(sca_ceil(row)) % self.rows;
    float x = col - sca_floor(col);
    float y = row - sca_floor(row);
    if(filter_linear) {
        uColor_s a = *u_image_pixel(self, fcol, frow, layer);
        uColor_s b = *u_image_pixel(self, ccol, frow, layer);
        uColor_s c = *u_image_pixel(self, fcol, crow, layer);
        uColor_s d = *u_image_pixel(self, ccol, crow, layer);
        uColor_s ab = ucvec4_mix(a, b, x);
        uColor_s cd = ucvec4_mix(c, d, x);
        return ucvec4_mix(ab, cd, y);
    }
    // filter_nearest
    return *u_image_pixel(self, fcol, frow, layer);
}

#endif //U_IMAGE_H
