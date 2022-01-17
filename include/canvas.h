#ifndef PIXELC_CANVAS_H
#define PIXELC_CANVAS_H

#include "mathc/types/int.h"
#include "mathc/types/float.h"
#include "u/image.h"
#include "r/ro_types.h"

#define CANVAS_MAX_LAYERS 16
#define CANVAS_MAX_SAVES 128

typedef struct {
    vec4 ro_color;
    
    int current_layer;
    bool show_grid;
    float alpha;
    const char *default_image_file;
    const char *default_import_file;
    
    
    // read only
    struct {
        mat4 pose; // = u_pose_new_aa(0, 0, cols, rows)
        uImage image;
    } RO;

    // private
    struct {
        uImage prev_image;
        RoSingle render_objects[CANVAS_MAX_LAYERS];

        RoSingle bg;
        RoSingle grid;
        
        int grid_rows;
        int grid_cols;

        int save_idx;
        int save_idx_max;
        int save_idx_min;

    } L;
} Canvas;

Canvas *canvas_new(int cols, int rows, int layers, int grid_cols, int grid_rows);

void canvas_update(Canvas *self, float dtime);

void canvas_render(Canvas *self, const mat4 *canvascam_mat);


// sets a new image for the canvas
// canvas will take the ownership of image_sink
void canvas_set_image(Canvas *self, uImage image_sink);

// saves an image (for undo and redo)
void canvas_save(Canvas *self);

// reloads the last saved image (for aborting a draw operation)
void canvas_reload(Canvas *self);

// reloads the last saved image
void canvas_undo(Canvas *self);

// redos the undo (loads the next saved image, if available)
void canvas_redo(Canvas *self);

// sets the render object color for vertex color effects
// default = R_COLOR_WHITE
void canvas_set_ro_color(Canvas *self, vec4 color);


#endif //PIXELC_CANVAS_H
