#ifdef USING_TTF
#ifndef R_RO_TTFTEXT_H
#define R_RO_TTFTEXT_H

//
// renders text, prerendered by SDL_TTF, only available if USING_TTF is set
//

#include "SDL_ttf.h"
#include "mathc/types/float.h"
#include "ro_single.h"

struct RoTtfTextGlobals_s {
    TTF_Font *default_font;
};
extern struct RoTtfTextGlobals_s ro_ttftext;

GLuint ro_ttftext_create_texture(TTF_Font *font, vec4 color, const char *text, int *opt_out_w, int *opt_out_h);


// Renders ttf text
typedef struct {
    RoSingle ro;
    TTF_Font *font;
    float ratio;    // width / height
} RoTtfText;

void ro_ttftext_init(RoTtfText *self, const float *vp, vec4 color, const char *text);

void ro_ttftext_kill(RoTtfText *self);

void ro_ttftext_render(RoTtfText *self);

void ro_ttftext_set_size(RoTtfText *self, float h);

void ro_ttftext_set_text(RoTtfText *self, vec4 color, const char *text);

#endif //R_RO_TTFTEXT_H
#endif //USING_TTF
