#ifndef PIXELC_PALETTE_H
#define PIXELC_PALETTE_H

#include "r/ro_types.h"
#include "e/input.h"
#include "u/color.h"
#include "camera.h"
#include "brush.h"

#define PALETTE_MAX 80


typedef struct {
    const Camera_s *camera_ref;
    Brush *brush_ref;

    struct {
        uColor_s palette[PALETTE_MAX];
        int palette_size;
        RoBatch palette_ro;
        RoSingle select_ro;
        RoBatch background_ro;
        int last_selected;
        float last_camera_width, last_camera_height;
    } L;
} Palette;

Palette *palette_new(const Camera_s *camera, Brush *brush);

void palette_update(Palette *self, float dtime);

void palette_render(Palette *self, const mat4 *camera_mat);

// return true if the pointer was used (indicate event done)
bool palette_pointer_event(Palette *self, ePointer_s pointer);

float palette_get_hud_size(const Palette *self);

int palette_get_color(const Palette *self);

void palette_set_color(Palette *self, int index);

void palette_set_colors(Palette *self, const uColor_s *palette, int size);

#endif //PIXELC_PALETTE_H
