#include "r/single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "mathc/mat/float.h"

#include "c_camera.h"
#include "canvas.h"


static struct {
    Layer *layers;
    rRoSingle *layer_ros;
    GLuint *layer_texs;

    int layers_size;
    int current_layer;

    int rows, cols;
} L;


mat4 canvas_get_pose() {
    return L.layer_ros[0].rect.pose;
}

int canvas_cols() {
    return L.cols;
}
int canvas_rows() {
    return L.rows;
}

Layer *canvas_current_layer() {
    return &L.layers[L.current_layer];
}

void canvas_init() {
    L.cols = 32;
    L.rows = 32;

    L.layers = New0(Layer, 1);
    L.layer_ros = New0(rRoSingle, 1);
    L.layer_texs = New0(GLuint, 1);
    L.layers_size = 1;
    L.current_layer = 0;

    for(int i=0; i<L.layers_size; i++) {
        layer_init(&L.layers[i], L.rows, L.cols);

        L.layer_texs[i] = r_texture_init(L.cols, L.rows, L.layers[i].data);
        r_texture_filter_nearest(L.layer_texs[i]);

        r_ro_single_init(&L.layer_ros[i], &c_camera_vp.m00, L.layer_texs[i]);
        u_pose_set(&L.layer_ros[i].rect.pose, 0, 0, 80, 80, 0);
    }
}

void canvas_update(float dtime) {
    for(int i=0; i<L.layers_size; i++) {
        r_texture_update(L.layer_texs[i], L.cols, L.rows, L.layers[i].data);
        // todo alpha...
    }
}

void canvas_render() {
    for(int i=0; i<L.layers_size; i++) {
        r_ro_single_render(&L.layer_ros[i]);
    }
}
