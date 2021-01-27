#include <SDL_image.h>
#include "r/texture.h"

GLuint r_texture_init(int width, int height, const void *buffer) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    // GL_REPEAT is already default...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    r_texture_filter_linear(tex);
    return tex;
}

GLuint r_texture_init_img(SDL_Surface *img) {
    SDL_PixelFormat *f = img->format;
    if (f->BitsPerPixel != 32 || f->Amask == 0) {
        SDL_Log("Load texture failed, 8bpp and alpha needed");
        return 0;
    }
    return r_texture_init(img->w, img->h, img->pixels);
}

GLuint r_texture_init_file(const char *file, int *opt_out_w, int *opt_out_h) {
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        SDL_Log("Load image (%s) failed: %s", file, IMG_GetError());
        return 0;
    }

    GLuint tex = r_texture_init_img(img);
    if(opt_out_w)
        *opt_out_w = img->w;
    if(opt_out_h)
        *opt_out_h = img->h;

    SDL_FreeSurface(img);
    return tex;
}

void r_texture_update(GLuint tex, int width, int height, const void *buffer) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
}

void r_texture_filter_linear(GLuint tex) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void r_texture_filter_nearest(GLuint tex) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
