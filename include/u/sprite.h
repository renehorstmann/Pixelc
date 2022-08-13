#ifndef U_SPRITE_H
#define U_SPRITE_H

//
// Holds an uImage 
// and expands layers into sprite cols, rows
// like an rTexture...
//

#include "m/types/int.h"
#include "image.h"

// image layer from sprite pos
static int u_sprite_pos_to_layer(int sprite_cols, int sprite_col, int sprite_row) {
    return sprite_col + sprite_row * sprite_cols;
}

// sprite pos to image layers
static ivec2 u_sprite_pos_from_layer(int sprite_cols, int layer) {
    return (ivec2) {{layer % sprite_cols, layer / sprite_cols}};
}



// A sprite adds a dimension to an uImage.
// instead of cols, rows, layers
// we get img.cols, img.rows, sprite_cols, sprite_rows
//    where img.cols .rows is the size for a single sprite
// img.layers is always == sprite_cols*sprite_rows
typedef struct {
    uImage img;
    int cols;
    int rows;
} uSprite;


static bool u_sprite_valid(uSprite self) {
    return u_image_valid(self.img)
            && self.cols > 0 && self.rows > 0
            && self.img.layers == self.cols * self.rows;
}

static uSprite u_sprite_new_invalid_a(sAllocator_i a) {
    return (uSprite) {u_image_new_invalid_a(a), 0, 0};
}

static uSprite u_sprite_new_invalid() {
    return u_sprite_new_invalid_a(S_ALLOCATOR_DEFAULT);
}

// creates a new empty sprite with a custom a
// cols, rows are the size of a single sprite
// sprite_cols, _rows are the amount of sprites
static uSprite u_sprite_new_empty_a(int cols, int rows, int sprite_cols, int sprite_rows, sAllocator_i a) {
    return (uSprite) {
                u_image_new_empty_a(cols, rows, sprite_cols*sprite_rows, a), 
                sprite_cols, 
                sprite_rows};
}

// creates a new empty sprite
// cols, rows are the size of a single sprite
// sprite_cols, _rows are the amount of sprites
static uSprite u_sprite_new_empty(int cols, int rows, int sprite_cols, int sprite_rows) {
    return u_sprite_new_empty_a(cols, rows, sprite_cols, sprite_rows, S_ALLOCATOR_DEFAULT);
}

// creates a new image with all values set to 0 with a custom a
// cols, rows are the size of a single sprite
// sprite_cols, _rows are the amount of sprites
static uSprite u_sprite_new_zeros_a(int cols, int rows, int sprite_cols, int sprite_rows, sAllocator_i a) {
    return (uSprite) {
            u_image_new_zeros_a(cols, rows, sprite_cols*sprite_rows, a), 
            sprite_cols, 
            sprite_rows};
}

// creates a new image with all values set to 0
// cols, rows are the size of a single sprite
// sprite_cols, _rows are the amount of sprites
static uSprite u_sprite_new_zeros(int cols, int rows, int sprite_cols, int sprite_rows) {
    return u_sprite_new_zeros_a(cols, rows, sprite_cols, sprite_rows, S_ALLOCATOR_DEFAULT);
}

// clones a sprite with a custom a
static uSprite u_sprite_new_clone_a(uSprite from, sAllocator_i a) {
    return (uSprite) {
            u_image_new_clone_a(from.img, a), 
            from.cols, from.rows
    };
}

// clones a sprite
static uSprite u_sprite_new_clone(uSprite from) {
    return u_sprite_new_clone_a(from, from.img.a);
}

// returns a new scaled clone, if filter_linear is FALSE, filter_nearest will be used, with a custom a
static uSprite u_sprite_new_clone_scaled_a(int cols, int rows, uSprite from, bool filter_linear, sAllocator_i a) {
    return (uSprite) {
            u_image_new_clone_scaled_a(cols, rows, from.img, filter_linear, a),
            from.cols, from.rows
    };
}

// returns a new scaled clone, if filter_linear is FALSE, filter_nearest will be used
static uSprite u_sprite_new_clone_scaled(int cols, int rows, bool filter_linear, uSprite from) {
    return u_sprite_new_clone_scaled_a(cols, rows, from, filter_linear, from.img.a);
}


// merges the given col down (left) with the previous one, with a custom a
uSprite u_sprite_new_clone_merge_col_down_a(uSprite from, int col_to_merge_down, sAllocator_i a);

// merges the given col down (left) with the previous one
static uSprite u_sprite_new_clone_merge_col_down(uSprite from, int col_to_merge_down) {
    return u_sprite_new_clone_merge_col_down_a(from, col_to_merge_down, from.img.a);
}


// merges all cols down (left), with a custom a
uSprite u_sprite_new_clone_merge_col_down_full_a(uSprite from, sAllocator_i a);

// merges all cols down (left)
static uSprite u_sprite_new_clone_merge_col_down_full(uSprite from) {
    return u_sprite_new_clone_merge_col_down_full_a(from, from.img.a);
}


// merges the given row down (to top) with the previous one, with a custom a
uSprite u_sprite_new_clone_merge_row_down_a(uSprite from, int row_to_merge_down, sAllocator_i a);

// merges the given row down (to top) with the previous one
static uSprite u_sprite_new_clone_merge_row_down(uSprite from, int row_to_merge_down) {
    return u_sprite_new_clone_merge_row_down_a(from, row_to_merge_down, from.img.a);
}


// merges all rows down (to top), with a custom a
uSprite u_sprite_new_clone_merge_row_down_full_a(uSprite from, sAllocator_i a);

// merges all rows down (to top)
static uSprite u_sprite_new_clone_merge_row_down_full(uSprite from) {
    return u_sprite_new_clone_merge_row_down_full_a(from, from.img.a);
}


// returns a clone of from, with a col removed
// with a custom a
uSprite u_sprite_new_clone_remove_col_a(uSprite from, int col_to_remove, sAllocator_i a);

// returns a clone of from, with a col removed
static uSprite u_sprite_new_clone_remove_col(uSprite from, int col_to_remove) {
    return u_sprite_new_clone_remove_col_a(from, col_to_remove, from.img.a);
}

// returns a clone of from, with a row removed
// with a custom a
uSprite u_sprite_new_clone_remove_row_a(uSprite from, int row_to_remove, sAllocator_i a);

// returns a clone of from, with a row removed
static uSprite u_sprite_new_clone_remove_row(uSprite from, int row_to_remove) {
    return u_sprite_new_clone_remove_row_a(from, row_to_remove, from.img.a);
}


// returns a clone of from, with a new zero'd col
// col_behind may be -1 to insert at the beginning
// with a custom a
uSprite u_sprite_new_clone_insert_col_a(uSprite from, int col_behind, sAllocator_i a);

// returns a clone of from, with a new zero'd col
// col_behind may be -1 to insert at the beginning
static uSprite u_sprite_new_clone_insert_col(uSprite from, int col_behind) {
    return u_sprite_new_clone_insert_col_a(from, col_behind, from.img.a);
}


// returns a clone of from, with a new zero'd row
// row_behind may be -1 to insert at the beginning
// with a custom a
uSprite u_sprite_new_clone_insert_row_a(uSprite from, int row_behind, sAllocator_i a);

// returns a clone of from, with a new zero'd row
// row_behind may be -1 to insert at the beginning
static uSprite u_sprite_new_clone_insert_row(uSprite from, int row_behind) {
    return u_sprite_new_clone_insert_row_a(from, row_behind, from.img.a);
}


// returns a new clone of from, with the cols a and b swapped
// with a custom a
uSprite u_sprite_new_clone_swap_cols_a(uSprite from, int col_a, int col_b, sAllocator_i a);

// returns a new clone of from, with the cols a and b swapped
static uSprite u_sprite_new_clone_swap_cols(uSprite from, int col_a, int col_b) {
    return u_sprite_new_clone_swap_cols_a(from, col_a, col_b, from.img.a);
}

// returns a new clone of from, with the rowd a and b swapped
// with a custom a
uSprite u_sprite_new_clone_swap_rows_a(uSprite from, int row_a, int row_b, sAllocator_i a);

// returns a new clone of from, with the rows a and b swapped
static uSprite u_sprite_new_clone_swap_rows(uSprite from, int row_a, int row_b) {
    return u_sprite_new_clone_swap_rows_a(from, row_a, row_b, from.img.a);
}

// creates a sprite from the image
// sprite_rows == from.layers
// the image will be reordered to fit the cols in the layers
// with a custom a
uSprite u_sprite_new_reorder_from_image_a(int sprite_cols, uImage from, sAllocator_i a);

// creates a sprite from the image
// sprite_rows == from.layers
// the image will be reordered to fit the cols in the layers
static uSprite u_sprite_new_reorder_from_image(int sprite_cols, uImage from) {
    return u_sprite_new_reorder_from_image_a(sprite_cols, from, from.a);
}


// copy a SDL_Surface into a new sprite with a costum a
uSprite u_sprite_new_sdl_surface_a(int sprite_cols, int sprite_rows, struct SDL_Surface *surface, sAllocator_i a);


// copy a SDL_Surface into a new sprite
static uSprite u_sprite_new_sdl_surface(int sprite_cols, int sprite_rows, struct SDL_Surface *surface) {
    return u_sprite_new_sdl_surface_a(sprite_cols, sprite_rows, surface, S_ALLOCATOR_DEFAULT);
}

// loads a sprite from a file (.png) 
// memory will be reordered, to use layers
//with a costum a
uSprite u_sprite_new_file_a(int sprite_cols, int sprite_rows, const char *file, sAllocator_i a);

// loads a sprite from a file (.png)
// memeory will be reordered, to use layers
static uSprite u_sprite_new_file(int sprite_cols, int sprite_rows, const char *file) {
    return u_sprite_new_file_a(sprite_cols, sprite_rows, file, S_ALLOCATOR_DEFAULT);
}

void u_sprite_kill(uSprite *self);


// creates a new image from the sprite
// from.layers will be == sprite_rows
// the image will be reordered to fit the cols
// with a custom a
uImage u_sprite_reorder_to_new_image_a(uSprite self, sAllocator_i a);

// creates a new image from the sprite
// from.layers will be == sprite_cols*sprite_rows
// the image will be reordered to fit the cols
// with a custom a
static uImage u_sprite_reorder_to_new_image(uSprite self) {
    return u_sprite_reorder_to_new_image_a(self, self.img.a);
}

// creates an SDL_Surface from the image
// will reorder cols from the layers
struct SDL_Surface *u_sprite_to_sdl_surface(uSprite self);

// saves the image to a file (.png)
// will reorder cols from the layers
bool u_sprite_save_file(uSprite self, const char *file);



// just calls u_image_layer_data_size
static ssize u_sprite_sprite_data_size(uSprite self) {
    return u_image_layer_data_size(self.img);
}

// returns the size of a sprite row
static ssize u_sprite_row_data_size(uSprite self) {
    return u_sprite_sprite_data_size(self) * self.cols;
}


// just calls u_image_data_size
static ssize u_sprite_data_size(uSprite self) {
    return u_image_data_size(self.img);
}

// gives access (read and write) to a pixel of the sprite
static uColor_s *u_sprite_pixel(uSprite self, int c, int r, int sprite_col, int sprite_row) {
    return u_image_pixel(self.img, c, r,
            sprite_col + sprite_row*self.cols);
}

// gives access (read and write) to a pixel of the sprite by index (row major order)
static uColor_s *u_sprite_pixel_index(uSprite self, int index, int sprite_col, int sprite_row) {
    // invalid safe
    return u_sprite_pixel(self, index, 0, sprite_col, sprite_row);
}

// returns the data start of a sprites sprite / its first pixel
static uColor_s *u_sprite_sprite(uSprite self, int sprite_col, int sprite_row) {
    // invalid safe
    return u_sprite_pixel(self, 0, 0, sprite_col, sprite_row);
}

// returns the data start of a sprites row / its first pixel
static uColor_s *u_sprite_row(uSprite self, int sprite_row) {
    // invalid safe
    return u_sprite_pixel(self, 0, 0, 0, sprite_row);
}

#endif //U_SPRITE_H
