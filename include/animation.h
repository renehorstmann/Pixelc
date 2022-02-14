#ifndef PIXELC_ANIMATION_H
#define PIXELC_ANIMATION_H

#include <stdbool.h>
#include "r/ro_types.h"
#include "canvas.h"
#include "camera.h"

typedef struct {
    const Canvas *canvas_ref;
    
    bool show;
    
    struct {
        RoText horsimann;
        RoBatch ro[CANVAS_MAX_LAYERS];
        
        int mcols, mrows;
        float size;
        int frames;
        float time;
        float fps;
        
        struct {
            RoSingle ro;
            vec4 color;
            float time;
        } longpress;
        
    } L;
} Animation;

Animation *animation_new(const Canvas *canvas, int multi_cols, int multi_rows, float size, int frames, float fps);

void animation_update(Animation *self, const Camera_s *camera, float palette_hud_size, float dtime);

void animation_render(const Animation *self, const mat4 *camera_mat);

void animation_longpress(Animation *self, vec2 pos, vec4 color);

#endif //PIXELC_ANIMATION_H
