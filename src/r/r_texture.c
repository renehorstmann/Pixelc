#include <SDL2/SDL_image.h>
#include "mathc/uchar.h"
#include "rhc/error.h"
#include "rhc/log.h"
#include "rhc/alloc.h"
#include "r/render.h"
#include "r/texture.h"


_Static_assert(sizeof(ucvec4) == 4, "wtf");


//
// private
//

// grid to vertical
static void reorder(ucvec4 *dst, const ucvec4 *src, ivec2 sprite_size, ivec2 sprites) {
   
    for(int sr=0; sr<sprites.y; sr++) {
        for(int sc=0; sc<sprites.x; sc++) {
            for(int r=0; r<sprite_size.y; r++) {
                int src_row = sr*sprite_size.y + r;
                int src_col = sc*sprite_size.x;
                int src_idx = src_row * sprite_size.x * sprites.x + src_col;
                int dst_row = sr*sprite_size.y*sprites.x + sc*sprite_size.y + r;
                int dst_idx = dst_row * sprite_size.x;
            
                memcpy(&dst[dst_idx], &src[src_idx], sprite_size.x * sizeof(ucvec4));
            }
        }
    }   
}



//
// public
//

rTexture r_texture_new(int image_cols, int image_rows, int sprites_cols, int sprites_rows, const void *opt_buffer) {
    r_render_error_check("r_texture_newBEGIN");
    
    assume(image_cols > 0 && image_rows > 0
            && sprites_cols > 0 && sprites_rows > 0
            && image_cols % sprites_cols == 0
            && image_rows % sprites_rows == 0
            && image_cols / sprites_cols >= 1
            && image_rows / sprites_rows >= 1
            , "texture size invalid: %i, %i ; %i %i",            image_cols, image_rows,
            sprites_cols, sprites_rows
            );
    
    rTexture self = {
        0,
        {{image_cols/sprites_cols, image_rows/sprites_rows}},
        {{sprites_cols, sprites_rows}}
    };
    
    // reorder vertical
    void *tmp_buffer = NULL;
    if(opt_buffer && self.sprites.x > 1) {
        tmp_buffer = rhc_malloc(4 * image_cols * image_rows);
        
        reorder(tmp_buffer, opt_buffer, self.sprite_size, self.sprites);
        opt_buffer = tmp_buffer;
    }
    
    glGenTextures(1, &self.tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self.tex);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA,
             self.sprite_size.x, 
             self.sprite_size.y, 
             self.sprites.x * self.sprites.y,
             0, GL_RGBA, GL_UNSIGNED_BYTE, opt_buffer);


    r_texture_filter_nearest(self);
    r_texture_wrap_clamp(self);
    
    // NULL safe free
    rhc_free(tmp_buffer);
    r_render_error_check("r_texture_new");
    return self;
}

rTexture r_texture_new_sdl_surface(int sprites_cols, int sprites_rows, const SDL_Surface *img) {
    assume(img, "SDL_Surface must not be null");
    SDL_PixelFormat *f = img->format;
    if (f->BitsPerPixel != 32 || f->Amask == 0) {
        rhc_error = "load texture failed";
        log_error("r_texture_new_sdl_surface failed: 8bpp and alpha needed");
        return r_texture_new_invalid();
    }
    return r_texture_new(img->w, img->h, sprites_cols, sprites_rows, img->pixels);
}

rTexture r_texture_new_file(int sprites_cols, int sprites_rows, const char *file) {
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        rhc_error = "load texture failed";
        log_error("r_texture_new_file failed: %s (%s)", IMG_GetError(), file);
        return r_texture_new_invalid();
    }

    rTexture self = r_texture_new_sdl_surface(sprites_cols, sprites_rows, img);
    
    SDL_FreeSurface(img);
    return self;
}

rTexture r_texture_new_white_pixel() {
    return r_texture_new(1, 1, 1, 1, (uint8_t[]) {255, 255, 255, 255});
}

void r_texture_kill(rTexture *self) {
    // invalid safe
    glDeleteTextures(1, &self->tex);
    *self = r_texture_new_invalid();
}

void r_texture_set(rTexture self, const void *buffer) {
    r_render_error_check("r_texture_setBEGIN");
    if(!r_texture_valid(self) || !buffer)
        return;

    // reorder vertical
    void *tmp_buffer = NULL;
    if(self.sprites.x > 1) {
        int image_cols = self.sprite_size.x * self.sprites.x;
        int image_rows = self.sprite_size.y * self.sprites.y;
        tmp_buffer = rhc_malloc(4 * image_cols * image_rows);

        reorder(tmp_buffer, buffer, self.sprite_size, self.sprites);
        buffer = tmp_buffer;
    }

    glBindTexture(GL_TEXTURE_2D_ARRAY, self.tex);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 
            0, 0, 0, 
            self.sprite_size.x, 
            self.sprite_size.y, 
            self.sprites.x * self.sprites.y,
            GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    // NULL safe free
    rhc_free(tmp_buffer);
    r_render_error_check("r_texture_set");
}


void r_texture_filter_linear(rTexture self) {
    r_render_error_check("r_texture_filter_linearBEGIN");
    if(!r_texture_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D_ARRAY, self.tex);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    r_render_error_check("r_texture_filter_linear");
}

void r_texture_filter_nearest(rTexture self) {
    r_render_error_check("r_texture_filter_nearestBEGIN");   
    if(!r_texture_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D_ARRAY, self.tex);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    r_render_error_check("r_texture_filter_nearest");
}

void r_texture_wrap_repeat(rTexture self) {
    r_render_error_check("r_texture_wrap_repeatBEGIN");
    if(!r_texture_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D_ARRAY, self.tex);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    r_render_error_check("r_texture_wrap_repeat");
}

void r_texture_wrap_clamp(rTexture self) {
    r_render_error_check("r_texture_wrap_clampBEGIN");
    if(!r_texture_valid(self))
        return;
    glBindTexture(GL_TEXTURE_2D_ARRAY, self.tex);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    r_render_error_check("r_texture_wrap_clamp");
}
