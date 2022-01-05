#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "u/image.h"
#include "r/ro_types.h"
#include "savestate.h"

#define CANVAS_MAX_LAYERS 16


typedef struct {
    SaveState *savestate_ref;

    int current_layer;
    bool show_grid;
    float alpha;
    const char *default_image_file;
    const char *default_import_file;

    // read only
    struct {
        mat4 pose;
        uImage image;
    } RO;

    // private
    struct {
        uImage prev_image;
        RoSingle render_objects[CANVAS_MAX_LAYERS];

        RoSingle bg;
        RoSingle grid;

        int save_id;
    } L;
} Canvas;

Canvas *canvas_new(SaveState *savestate, int cols, int rows, int layers, int grid_cols, int grid_rows);

void canvas_update(Canvas *self, float dtime);

void canvas_render(Canvas *self, const mat4 *canvascam_mat);

void canvas_save(Canvas *self);

void canvas_redo_image(Canvas *self);


#endif //PIXELC_CANVAS_H
