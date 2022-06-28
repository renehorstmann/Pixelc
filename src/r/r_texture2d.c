#include <SDL2/SDL_image.h>
#include "r/render.h"
#include "r/texture2d.h"


rTexture2D r_texture2d_new(int image_cols, int image_rows, const void *opt_buffer) {
    r_render_error_check("r_texture2d_newBEGIN");

    s_assume(image_cols > 0 && image_rows > 0, "texture2d size invalid");

    rTexture2D self = {0, {{image_cols, image_rows}}};


    glGenTextures(1, &self.tex);
    glBindTexture(GL_TEXTURE_2D, self.tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 self.size.x, self.size.y,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, opt_buffer);

    r_texture2d_filter_nearest(self);
    r_texture2d_wrap_clamp(self);

    r_render_error_check("r_texture2d_new");
    return self;
}

rTexture2D r_texture2d_new_sdl_surface(const SDL_Surface *img) {
    s_assume(img, "SDL_Surface must not be null");
    SDL_PixelFormat *f = img->format;
    if (f->BitsPerPixel != 32 || f->Amask == 0) {
        s_error_set("load texture failed");
        s_log_error("failed: 8bpp and alpha needed");
        return r_texture2d_new_invalid();
    }
    return r_texture2d_new(img->w, img->h, img->pixels);
}

rTexture2D r_texture2d_new_file(const char *file) {
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        s_error_set("load texture failed");
        s_log_error("failed: %s (%s)", IMG_GetError(), file);
        return r_texture2d_new_invalid();
    }

    rTexture2D self = r_texture2d_new_sdl_surface(img);

    SDL_FreeSurface(img);
    return self;
}

rTexture2D r_texture2d_new_white_pixel() {
    return r_texture2d_new(1, 1, (uint8_t[]) {255, 255, 255, 255});
}

void r_texture2d_kill(rTexture2D *self) {
    // invalid safe
    glDeleteTextures(1, &self->tex);
    *self = r_texture2d_new_invalid();
}

void r_texture2d_set(rTexture2D self, const void *buffer) {
    r_render_error_check("r_texture2d_setBEGIN");
    if (!r_texture2d_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D, self.tex);
    glTexSubImage2D(GL_TEXTURE_2D, 0,
                    0, 0, self.size.x, self.size.y,
                    GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    r_render_error_check("r_texture2d_set");
}

void r_texture2d_get(rTexture2D self, void *buffer) {
    r_render_error_check("r_texture2d_getBEGIN");
    if (!r_texture2d_valid(self) || !buffer)
        return;
    glBindTexture(GL_TEXTURE_2D, self.tex);
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, self.tex, 0);
    glReadPixels(0, 0, self.size.x, self.size.y, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &fbo);
    r_render_error_check("r_texture2d_get");
}


void r_texture2d_filter_linear(rTexture2D self) {
    r_render_error_check("r_texture2d_filter_linearBEGIN");
    if (!r_texture2d_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D, self.tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    r_render_error_check("r_texture2d_filter_linear");
}

void r_texture2d_filter_nearest(rTexture2D self) {
    r_render_error_check("r_texture2d_filter_nearestBEGIN");
    if (!r_texture2d_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D, self.tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    r_render_error_check("r_texture2d_filter_nearest");
}

void r_texture2d_wrap_repeat(rTexture2D self) {
    r_render_error_check("r_texture2d_wrap_repeatBEGIN");
    if (!r_texture2d_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D, self.tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    r_render_error_check("r_texture2d_wrap_repeat");
}

void r_texture2d_wrap_clamp(rTexture2D self) {
    r_render_error_check("r_texture2d_wrap_clampBEGIN");
    if (!r_texture2d_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D, self.tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    r_render_error_check("r_texture2d_wrap_clamp");
}

