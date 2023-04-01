#include <SDL2/SDL_image.h>
#include "m/sca/int.h"
#include "u/image.h"



//
// public
//

uImage u_image_new_empty_a(int cols, int rows, int layers, sAllocator_i a) {
    ssize data_size = (ssize) cols * (ssize) rows * (ssize) layers * (ssize) sizeof(uColor_s);

    if (data_size <= 0) {
        s_error_set("image new failed");
        s_log_error("failed: wrong data size: %zu", data_size);
        return u_image_new_invalid();
    }

    uImage self =
            {s_a_malloc(a, data_size),
             cols, rows, layers,
             a};
    return self;
}

uImage u_image_new_zeros_a(int cols, int rows, int layers, sAllocator_i a) {
    uImage self = u_image_new_empty_a(cols, rows, layers, a);
    memset(self.data, 0, u_image_data_size(self));
    return self;
}

uImage u_image_new_clone_a(uImage from, sAllocator_i a) {
    if(!u_image_valid(from))
        return u_image_new_invalid_a(a);
    uImage self = u_image_new_empty_a(from.cols, from.rows, from.layers, a);
    memcpy(self.data, from.data, u_image_data_size(from));
    return self;
}

uImage u_image_new_clone_scaled_a(int cols, int rows, uImage from, bool filter_linear, sAllocator_i a) {
    if(!u_image_valid(from))
        return u_image_new_invalid_a(a);
    uImage self = u_image_new_empty_a(cols, rows, from.layers, a);
    for (int l = 0; l < self.layers; l++) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                float u = (float) c / cols;
                float v = (float) r / rows;
                *u_image_pixel(self, c, r, l) = u_image_get_pixel_filtered(from, u, v, l, filter_linear);
            }
        }
    }
    return self;
}

uImage u_image_new_clone_merge_down_a(uImage from, int layer_to_merge_down, sAllocator_i a) {
    if(!u_image_valid(from))
        return u_image_new_invalid_a(a);
    if (from.layers <= 1 || layer_to_merge_down <= 0 || layer_to_merge_down >= from.layers) {
        s_error_set("image new clone merge down failed");
        s_log_error("failed: wrong layer to merge: %i/%i", layer_to_merge_down, from.layers);
        return u_image_new_invalid_a(a);
    }
    uImage self = u_image_new_empty_a(from.cols, from.rows, from.layers - 1, a);
    
    // layers to clone up to layer_to_merge_down-1
    if (layer_to_merge_down > 1)
        memcpy(self.data, from.data, sizeof(uColor_s) * self.cols * self.rows * (layer_to_merge_down - 1));
    // layers to clone behind layer_to_merge_down
    if (layer_to_merge_down < from.layers - 1)
        memcpy(u_image_layer(self, layer_to_merge_down), u_image_layer(from, layer_to_merge_down + 1),
               sizeof(uColor_s) * self.cols * self.rows * (from.layers - layer_to_merge_down - 1));
    // merge the layers
    for (int r = 0; r < self.rows; r++) {
        for (int c = 0; c < self.cols; c++) {
            uColor_s col_a = *u_image_pixel(from, c, r, layer_to_merge_down - 1);
            uColor_s col_b = *u_image_pixel(from, c, r, layer_to_merge_down);
            *u_image_pixel(self, c, r, layer_to_merge_down - 1) = u_color_blend(col_a, col_b);
        }
    }
    return self;
}

uImage u_image_new_clone_merge_down_full_a(uImage from, sAllocator_i a) {
    if(!u_image_valid(from))
        return u_image_new_invalid_a(a);
    if(from.layers == 1)
        return u_image_new_clone_a(from, a);
    
    uImage self = u_image_new_clone_merge_down_a(from, 1, a);
    while(self.layers>1) {
        uImage tmp = u_image_new_clone_merge_down(self, 1);
        u_image_kill(&self);
        self = tmp;
    }
    return self;
}

uImage u_image_new_clone_remove_layer_a(uImage from, int layer_to_remove, sAllocator_i a) {
    if(!u_image_valid(from) || layer_to_remove<0 || layer_to_remove>=from.layers)
        return u_image_new_invalid_a(a);
    
    uImage self = u_image_new_empty_a(from.cols, from.rows, from.layers-1, a);
    int layer = 0;
    for(int i=0; i<from.layers; i++) {
        if(i == layer_to_remove)
            continue;
        memcpy(u_image_layer(self, layer), u_image_layer(from, i), u_image_layer_data_size(self));
        layer++;
    }
    return self;
}

uImage u_image_new_clone_insert_layer_a(uImage from, int layer_behind, sAllocator_i a) {
    if(!u_image_valid(from) || layer_behind<-1 || layer_behind>=from.layers) 
        return u_image_new_invalid_a(a);
    uImage self = u_image_new_empty_a(from.cols, from.rows, from.layers+1, a);
    if(layer_behind>=0)
        memcpy(self.data, from.data,
                u_image_layer_data_size(from) * (layer_behind+1));
    memset(u_image_layer(self, layer_behind+1), 0, 
            u_image_layer_data_size(from));
    if(layer_behind<from.layers-1) 
        memcpy(u_image_layer(self, layer_behind+2),
                u_image_layer(from,layer_behind+1),
                u_image_layer_data_size(from) * (from.layers-layer_behind-1));
    return self;
}

uImage u_image_new_clone_swap_layers_a(uImage from, int layer_a, int layer_b, sAllocator_i a) {
    if(!u_image_valid(from))
        return u_image_new_invalid_a(a);
    uImage swap = u_image_new_clone_a(from, a);
    memcpy(u_image_layer(swap, layer_a), 
            u_image_layer(from, layer_b),    
            u_image_layer_data_size(swap));
    memcpy(u_image_layer(swap, layer_b), 
            u_image_layer(from, layer_a),    
            u_image_layer_data_size(swap));
    return swap;
}

uImage u_image_new_sdl_surface_a(int layers, struct SDL_Surface *surface, sAllocator_i a) {
    s_assume(layers > 0, "A single layer needed");
    if (surface->h % layers != 0) {
        s_error_set("load image from sdl surface failed");
        s_log_warn("failed: rows %% layers != 0");
        return u_image_new_invalid();
    }

    int cols = surface->w;
    int rows = surface->h / layers;
    uImage self = u_image_new_invalid();

    SDL_PixelFormat *sf = surface->format;
    SDL_PixelFormat *df = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);

    SDL_Surface *cast = NULL;

    // check if the format equals the needed
    //    and convert it otherwise
    if (sf->BitsPerPixel != df->BitsPerPixel
        || sf->Rmask != df->Rmask
        || sf->Gmask != df->Gmask
        || sf->Bmask != df->Bmask
        || sf->Amask != df->Amask) {
        cast = SDL_ConvertSurface(surface, df, 0);
        surface = cast;
    }

    if (surface->pitch != cols * 4) {
        s_log_error("failed: pitch must be == cols*4");
        goto CLEANUP;
    }

    // create image with the surface data
    self = u_image_new_empty_a(cols, rows, layers, a);
    memcpy(self.data, surface->pixels, u_image_data_size(self));

    CLEANUP:
    SDL_FreeFormat(df);
    SDL_FreeSurface(cast);
    return self;
}

uImage u_image_new_file_a(int layers, const char *file, sAllocator_i a) {
    uImage self = u_image_new_invalid_a(a);
    SDL_Surface *surface = IMG_Load(file);
    if (!surface) {
        s_error_set("load image file failed");
        s_log_warn("failed: failed: %s (%s)", IMG_GetError(), file);
    } else {
        self = u_image_new_sdl_surface_a(layers, surface, a);
    }

    SDL_FreeSurface(surface);
    return self;
}

void u_image_kill(uImage *self) {
    if (u_image_valid(*self))
        s_a_free(self->a, self->data);
    *self = u_image_new_invalid_a(self->a);
}

// creates an SDL_Surface from the image
struct SDL_Surface *u_image_to_sdl_surface(uImage self) {
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void *) self.data,
                                                    self.cols,
                                                    self.rows * self.layers,
                                                    32, self.cols * 4,
                                                    format->Rmask,
                                                    format->Gmask,
                                                    format->Bmask,
                                                    format->Amask);
    SDL_FreeFormat(format);
    return surface;
}

bool u_image_save_file(uImage self, const char *file) {
    if (!u_image_valid(self)) {
        s_error_set("image save file failed");
        s_log_error("failed: invalid (%s)", file);
        return false;
    }
    SDL_Surface *surface = u_image_to_sdl_surface(self);
    if (!surface) {
        s_error_set("image save file failed");
        s_log_error("failed: sdl buffer failed: %s", SDL_GetError());
        return false;
    }
    int ret = IMG_SavePNG(surface, file);
    SDL_FreeSurface(surface);
    if (ret) {
        s_error_set("image save file failed");
        s_log_error("failed: %s (%s)", IMG_GetError(), file);
        return false;
    }
    return true;
}

bool u_image_copy(uImage self, uImage from) {
    if (!u_image_valid(self) || !u_image_valid(from)
        || self.cols != from.cols
        || self.rows != from.rows
        || self.layers != from.layers
            ) {
        s_error_set("image copy failed");
        s_log_error("failed: invalid or different size");
        return false;
    }

    ssize size = u_image_data_size(self);
    memcpy(self.data, from.data, size);
    return true;
}

void u_image_copy_top_left(uImage self, uImage from) {
    if (!u_image_valid(self) || !u_image_valid(from)) {
        s_log_warn("failed");
        return;
    }
    int layers = isca_min(self.layers, from.layers);
    int rows = isca_min(self.rows, from.rows);
    int cols = isca_min(self.cols, from.cols);

    for (int l = 0; l < layers; l++) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                *u_image_pixel(self, c, r, l) =
                        *u_image_pixel(from, c, r, l);
            }
        }
    }
}

bool u_image_equals(uImage self, uImage from) {
    if (!u_image_valid(self) || !u_image_valid(from)
        || self.cols != from.cols
        || self.rows != from.rows
        || self.layers != from.layers)
        return false;

    return memcmp(self.data, from.data, u_image_data_size(self)) == 0;
}


void u_image_rotate(uImage *self, bool right) {
    if (!u_image_valid(*self))
        return;

    uImage tmp = u_image_new_clone_a(*self, self->a);
    if (!u_image_valid(tmp))
        return;

    self->cols = tmp.rows;
    self->rows = tmp.cols;
    for (int l = 0; l < self->layers; l++) {
        for (int r = 0; r < self->rows; r++) {
            for (int c = 0; c < self->cols; c++) {
                int mc = right ? r : tmp.cols - 1 - r;
                int mr = right ? tmp.rows - 1 - c : c;
                *u_image_pixel(*self, c, r, l) = *u_image_pixel(tmp, mc, mr, l);
            }
        }
    }

    u_image_kill(&tmp);
}

void u_image_mirror(uImage self, bool vertical) {
    if (!u_image_valid(self))
        return;

    uImage tmp = u_image_new_clone(self);
    if (!u_image_valid(tmp))
        return;

    for (int l = 0; l < self.layers; l++) {
        for (int r = 0; r < self.rows; r++) {
            for (int c = 0; c < self.cols; c++) {
                int mc = vertical ? self.cols - 1 - c : c;
                int mr = vertical ? r : self.rows - 1 - r;
                *u_image_pixel(self, c, r, l) = *u_image_pixel(tmp, mc, mr, l);
            }
        }
    }

    u_image_kill(&tmp);
}
