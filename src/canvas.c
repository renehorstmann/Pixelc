#include "r/ro_single.h"
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

    L.layers = New0(RoLayer, 1);
    L.layers_size = 1;
    L.current_layer = 0;

    for(int i=0; i<L.layers_size; i++) {
        layer_init(&L.layers[i].layer);

        L.layers[i].tex = r_texture_init(L.cols, L.rows, L.layers[i].layer.data);
        r_texture_filter_nearest(L.layers[i].tex);

        r_ro_single_init(&L.layers[i].ro, &c_camera_vp.m00, L.layers[i].tex);
    }

    for(int i=0; i<L.rows*L.cols; i++) {
        *layer_pixel_index(canvas_current_layer(), i) = (color) {32, 32, 32, 255};
    }
}

void canvas_update(float dtime) {
    if(c_camera_is_portrait_mode())
        u_pose_set(&L.pose, 0, c_camera_top() - 85, 80, 80, 0);
    else
        u_pose_set(&L.pose, c_camera_left() + 85, 0, 80, 80, 0);

    for(int i=0; i<L.layers_size; i++) {
        r_texture_update(L.layers[i].tex, L.cols, L.rows, L.layers[i].layer.data);

        // set alpha and pose
        L.layers[i].ro.rect.color.w = L.layers[i].layer.alpha * (1.0f/255.0f);
        L.layers[i].ro.rect.pose = L.pose;
    }
}

void canvas_render() {
    for(int i=0; i<L.layers_size; i++) {
        r_ro_single_render(&L.layers[i].ro);
    }
}
