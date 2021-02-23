#include "utilc/assume.h"
#include "SDL_image.h"
#include "canvas.h"
#include "io.h"

struct IoGlobals_s io = {
	"sprite.png",
	"import.png"
};


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


Image *io_load_image(const char *file, int layers) {
    assume(layers>0, "A single layer needed");
    Image *image = NULL;
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        SDL_Log("io_load_image (%s) failed: %s", file, IMG_GetError());
        goto CLEAN_UP;
    }
    SDL_PixelFormat *f = img->format;
    if (f->BitsPerPixel != 32 || f->Amask == 0) {
        SDL_Log("io_load_image failed, 8bpp and alpha needed");
        goto CLEAN_UP;
    }

    if(img->h % layers != 0) {
        SDL_Log("io_load_image failed, height %% layers != 0");
        goto CLEAN_UP;
    }

    image = image_new_empty(layers, img->w, img->h/layers);
    memcpy(image->data, img->pixels, sizeof(Color_s) * img->w * img->h);

    CLEAN_UP:
    SDL_FreeSurface(img);
    return image;
}


bool io_save_image(const char *file, const Image *image) {
    SDL_Surface *img = load_buffer((void *)image->data, image->cols, image->rows * image->layers);
    int ret = IMG_SavePNG(img, file);
    SDL_FreeSurface(img);
    if(ret) {
        SDL_Log("io_save_layer (%s) failed: %s", file, IMG_GetError());
        return false;
    }
    return true;
}
