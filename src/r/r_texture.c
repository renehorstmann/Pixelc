#include <SDL_image.h>
#include "r/texture.h"

GLuint r_texture_new(int cols, int rows, const void *buffer) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cols, rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    // GL_REPEAT is already default...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    r_texture_filter_nearest(tex);
    return tex;
}

GLuint r_texture_new_img(SDL_Surface *img) {
    SDL_PixelFormat *f = img->format;
    if (f->BitsPerPixel != 32 || f->Amask == 0) {
        SDL_Log("Load texture failed, 8bpp and alpha needed");
        return 0;
    }
    return r_texture_new(img->w, img->h, img->pixels);
}

GLuint r_texture_new_file(const char *file, ivec2 *opt_out_size) {
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        SDL_Log("Load image (%s) failed: %s", file, IMG_GetError());
        return 0;
    }

    GLuint tex = r_texture_new_img(img);
    if (opt_out_size)
        *opt_out_size = (ivec2) {{img->w, img->h}};

    SDL_FreeSurface(img);
    return tex;
}

GLuint r_texture_new_empty(int cols, int rows) {
    return r_texture_new(cols, rows, NULL);
}

GLuint r_texture_new_white_pixel() {
    return r_texture_new(1, 1, (uint8_t[]) {255, 255, 255, 255});
}

void r_texture_update(GLuint tex, int cols, int rows, const void *buffer) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, cols, rows, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
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
