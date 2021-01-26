#include "SDL_image.h"
#include "canvas.h"
#include "io.h"

static SDL_Surface *load_buffer(void *data, int width, int height) {
    // Set up the pixel format color masks for RGB(A) byte arrays.
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    int depth = 32;
    int pitch = 4 * width;

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(data, width, height, depth, pitch, rmask, gmask, bmask, amask);
    return surf;
}


bool io_load_layer(Layer *out_layer, const char *file) {
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        SDL_Log("io_load_layer (%s) failed: %s", file, IMG_GetError());
        return false;
    }
    SDL_PixelFormat *f = img->format;
    if (f->BitsPerPixel != 32 || f->Amask == 0) {
        SDL_Log("io_load_layer failed, 8bpp and alpha needed");
        return false;
    }
    if (img->w != canvas_cols() || img->h != canvas_rows()) {
        SDL_Log("io_load_layer failed, wrong size");
        return false;
    }

    memcpy(out_layer->data, img->pixels, img->w * img->h * 4);
    SDL_FreeSurface(img);
    return true;
}

bool io_save_layer(const Layer layer, const char *file) {
    SDL_Surface *img = load_buffer(layer.data, canvas_cols(), canvas_rows());
    int ret = IMG_SavePNG(img, file);
    if(ret) {
        SDL_Log("io_save_layer (%s) failed: %s", file, IMG_GetError());
        return false;
    }
    return true;
}
