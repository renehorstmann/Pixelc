#include "r/single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "mathc/mat/float.h"

#include "c_camera.h"
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

void canvas_init() {
    L.cols = 16;
    L.rows = 16;

    L.pose = mat4_eye();
    u_pose_set(&L.pose, -20, 20, 80, 80, 0);

    L.layers = New0(RoLayer, 1);
    L.layers_size = 1;
    L.current_layer = 0;

    for(int i=0; i<L.layers_size; i++) {
        layer_init(&L.layers[i].layer);

        L.layers[i].tex = r_texture_init(L.cols, L.rows, L.layers[i].layer.data);
        r_texture_filter_nearest(L.layers[i].tex);

        r_ro_single_init(&L.layers[i].ro, &c_camera_vp.m00, L.layers[i].tex);
        L.layers[i].ro.rect.pose = L.pose;
    }

    for(int i=0; i<L.rows*L.cols; i++) {
        *layer_pixel_index(canvas_current_layer(), i) = (color) {64, 0, 0, 255};
    }
}

void canvas_update(float dtime) {
    for(int i=0; i<L.layers_size; i++) {
        r_texture_update(L.layers[i].tex, L.cols, L.rows, L.layers[i].layer.data);

        // set alpha
        L.layers[i].ro.rect.color.w = L.layers[i].layer.alpha * (1.0f/255.0f);
    }
}

void canvas_render() {
    for(int i=0; i<L.layers_size; i++) {
        r_ro_single_render(&L.layers[i].ro);
    }
}
