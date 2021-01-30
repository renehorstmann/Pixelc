#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "mathc/mat/float.h"

#include "c_camera.h"
#include "io.h"
#include "canvas.h"

static struct {
    int rows, cols;

    mat4 pose;

    Layer *layers;
    rRoSingle *ros;
    GLuint *texs;
    int size;
    int current;

    rRoSingle bg;
    rRoSingle grid;
} L;


static void init_layer_n_ros() {
    for(int i=0; i<L.size; i++) {
        layer_init(&L.layers[i]);

        GLuint tex = r_texture_init(L.cols, L.rows, L.layers[i].data);
        r_texture_filter_nearest(tex);

        r_ro_single_init(&L.ros[i], c_camera_gl, tex);
    }
}


void canvas_init(int rows, int cols) {
    L.rows = rows;
    L.cols = cols;

    L.pose = mat4_eye();

    L.layers = New0(Layer, 1);
    L.ros = New0(rRoSingle , 1);
    L.size = 1;
    L.current = 0;

    init_layer_n_ros();
    
    GLuint grid_tex = r_texture_init_file("res/canvas_grid.png", NULL);
    r_texture_filter_nearest(grid_tex);
    r_ro_single_init(&L.grid, c_camera_gl, grid_tex);
    u_pose_set_size(&L.grid.rect.uv, cols, rows);


    Color_s buf[4];
    buf[0] = buf[3] = color_from_hex("#999999");
    buf[1] = buf[2] = color_from_hex("#777777");
    GLuint bg_tex = r_texture_init(2, 2, buf);
    r_texture_filter_nearest(bg_tex);
    r_ro_single_init(&L.bg, c_camera_gl, bg_tex);
    {    
        float w = cols <= 8 ? 1 : cols/16.0f;
        float h = rows <= 8 ? 1 : rows/16.0f;
        u_pose_set_size(&L.bg.rect.uv, w, h);
    }


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



mat4 canvas_pose() {
    return L.pose;
}

int canvas_cols() {
    return L.cols;
}
int canvas_rows() {
    return L.rows;
}


Layer *canvas_layers() {
    return L.layers;
}
int canvas_size() {
    return L.size;
}
int canvas_current() {
    return L.current;
}
Layer *canvas_current_layer() {
    return &L.layers[L.current];
}

void canvas_set_layer(Layer layer, int index) {
    layer_copy(&L.layers[index], layer);
}
void canvas_set_layers(const Layer *layer, int size) {
    if(size != L.size) {
        for(int i=0; i<L.size; i++) {
            layer_kill(&L.layers[i]);
            r_ro_single_kill(&L.ros[i]);
        }
        L.layers = ReNew(Layer, L.layers, size);
        L.ros = ReNew(rRoSingle, L.ros, size);
        L.size = size;
        init_layer_n_ros();
    }

    for(int i=0; i<size; i++) {
        layer_copy(&L.layers[i], layer[i]);
    }
}
void canvas_set_current(int current) {
    L.current = current;
}

void canvas_update(float dtime) {
    float w = 160;
    float h = 160.0f * L.rows / L.cols;
    if(c_camera_is_portrait_mode())
        u_pose_set(&L.pose, 0, c_camera_top() - 85, w, h, 0);
    else
        u_pose_set(&L.pose, c_camera_left() + 85, 0, w, h, 0);

    for(int i=0; i<L.size; i++) {
        r_texture_update(L.ros[i].tex, L.cols, L.rows, L.layers[i].data);

        // set alpha and pose
        L.ros[i].rect.color.w = L.layers[i].alpha * (1.0f / 255.0f);
        L.ros[i].rect.pose = L.pose;
    }
    
    L.grid.rect.pose = L.pose;
    L.bg.rect.pose = L.pose;
}

void canvas_render() {
    r_ro_single_render(&L.bg);
    
    for(int i=0; i<=L.current; i++) {
        r_ro_single_render(&L.ros[i]);
    }
    
    r_ro_single_render(&L.grid);
}
