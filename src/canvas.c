#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "mathc/mat/float.h"

#include "c_camera.h"
#include "io.h"
#include "canvas.h"


typedef struct {
    Layer layer;
    rRoSingle ro;
    GLuint tex;
} RoLayer;

static struct {
    int rows, cols;

    mat4 pose;

    RoLayer *layers;
    int layers_size;
    int current_layer;

    rRoSingle bg;
    rRoSingle grid;
} L;


mat4 canvas_pose() {
    return L.pose;
}

int canvas_cols() {
    return L.cols;
}
int canvas_rows() {
    return L.rows;
}

Layer *canvas_current_layer() {
    return &L.layers[L.current_layer].layer;
}

void canvas_init(int rows, int cols) {
    L.rows = rows;
    L.cols = cols;

    L.pose = mat4_eye();

    L.layers = New0(RoLayer, 1);
    L.layers_size = 1;
    L.current_layer = 0;

    for(int i=0; i<L.layers_size; i++) {
        layer_init(&L.layers[i].layer);

        L.layers[i].tex = r_texture_init(L.cols, L.rows, L.layers[i].layer.data);
        r_texture_filter_nearest(L.layers[i].tex);

        r_ro_single_init(&L.layers[i].ro, &c_camera_vp.m00, L.layers[i].tex);
    }
    
    GLuint grid_tex = r_texture_init_file("res/canvas_grid.png", NULL);
    r_texture_filter_nearest(grid_tex);
    r_ro_single_init(&L.grid, &c_camera_p.m00, grid_tex);
    u_pose_set_size(&L.grid.rect.uv, 2*cols, 2*rows);


    Color_s buf[4];
    buf[0] = buf[3] = color_from_hex("#999999");
    buf[1] = buf[2] = color_from_hex("#777777");
    GLuint bg_tex = r_texture_init(2, 2, buf);
    r_texture_filter_nearest(bg_tex);
    r_ro_single_init(&L.bg, &c_camera_p.m00, bg_tex);
    u_pose_set_size(&L.bg.rect.uv, 4*cols, 4*rows);


    if(!io_load_layer(canvas_current_layer(), "sprite.png")) {
        for(int i=0; i<L.rows*L.cols; i++) {
            *layer_pixel_index(canvas_current_layer(), i) = COLOR_TRANSPARENT;
        }
        *layer_pixel(canvas_current_layer(), 0, 0) = COLOR_WHITE;
        *layer_pixel(canvas_current_layer(), L.rows-1, 0) = COLOR_WHITE;
        *layer_pixel(canvas_current_layer(), 0, L.cols-1) = COLOR_WHITE;
        *layer_pixel(canvas_current_layer(), L.rows-1, L.cols-1) = COLOR_WHITE;
    }
}

void canvas_update(float dtime) {
    if(c_camera_is_portrait_mode())
        u_pose_set(&L.pose, 0, c_camera_top() - 85, 160, 160, 0);
    else
        u_pose_set(&L.pose, c_camera_left() + 85, 0, 160, 160, 0);

    for(int i=0; i<L.layers_size; i++) {
        r_texture_update(L.layers[i].tex, L.cols, L.rows, L.layers[i].layer.data);

        // set alpha and pose
        L.layers[i].ro.rect.color.w = L.layers[i].layer.alpha * (1.0f/255.0f);
        L.layers[i].ro.rect.pose = L.pose;
    }
    
    L.grid.rect.pose = L.pose;
    L.bg.rect.pose = L.pose;
}

void canvas_render() {
    r_ro_single_render(&L.bg);
    
    for(int i=0; i<L.layers_size; i++) {
        r_ro_single_render(&L.layers[i].ro);
    }
    
    r_ro_single_render(&L.grid);
}
