#ifdef OPTION_TTF
#ifndef R_RO_TTFTEXT_H
#define R_RO_TTFTEXT_H

//
// renders text, prerendered by SDL_TTF, only available if OPTION_TTF is set
//

#include "ro_types.h"

struct RoTtfTextGlobals_s {
    TTF_Font *default_font;
};
extern struct RoTtfTextGlobals_s ro_ttftext;

rTexture ro_ttftext_create_texture(TTF_Font *font, vec4 color, const char *text, int *opt_out_w, int *opt_out_h);




RoTtfText ro_ttftext_new(vec4 color, const char *text);

void ro_ttftext_kill(RoTtfText *self);

void ro_ttftext_render(const RoTtfText *self, const mat4 *camera_mat);

void ro_ttftext_set_size(RoTtfText *self, float h);

void ro_ttftext_set_text(RoTtfText *self, vec4 color, const char *text);

#endif //R_RO_TTFTEXT_H
#endif //OPTION_TTF
