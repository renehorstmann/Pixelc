#include <SDL_image.h>
#include "r/texture.h"


static int tex_size[R_MAX_TEXTURES][2];

GLuint r_texture_from_img(SDL_Surface *img) {
	SDL_PixelFormat *f = img->format;
	if(f->BitsPerPixel != 32 || f->Amask == 0) {
        SDL_Log("Load texture failed, 8bpp and alpha needed");
	    return 0;
	}

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    // GL_REPEAT is already default...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
   
    tex_size[tex%R_MAX_TEXTURES][0] = img->w;
    tex_size[tex%R_MAX_TEXTURES][1] = img->h;
   
    return tex;
}


GLuint r_texture_from_file(const char *file) {
    SDL_Surface *img = IMG_Load(file);
    if (!img) {
        SDL_Log("Load image (%s) failed: %s", file, IMG_GetError());
        return 0;
    }
    
    GLuint tex = r_texture_from_img(img);
    SDL_FreeSurface(img);
    return tex;
}

GLuint r_texture_init_empty(bool filter) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    // GL_REPEAT is already default...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(filter) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    return tex;
}

void r_texture_update(GLuint tex, int width, int height, const uint8_t *buffer) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    tex_size[tex%R_MAX_TEXTURES][0] = width;
    tex_size[tex%R_MAX_TEXTURES][1] = height;
}

void r_texture_get_size(GLuint tex, int *w, int *h) {
    // not working on Galaxy Note Pro 10.1
    //glBindTexture(GL_TEXTURE_2D, tex);
    //glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, w);
    //glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, h);
    *w = tex_size[tex%R_MAX_TEXTURES][0];
    *h = tex_size[tex%R_MAX_TEXTURES][1];
}
