#include <assert.h>
#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "mathc/mat/float.h"

#include "image.h"
#include "c_camera.h"
#include "io.h"
#include "savestate.h"
#include "canvas.h"


int canvas_current_layer;

static struct {
    mat4 pose;

    Image *image;
    Image *last_image;
    rRoSingle *render_objects;
    int layers;
    
    rRoSingle bg;
    rRoSingle grid;
    
    int save_id;
} L;


static void init_render_objects() {
    for(int i=0; i<L.layers; i++) {
        GLuint tex = r_texture_init(L.image->cols, L.image->rows, image_layer(L.image, i));
        r_texture_filter_nearest(tex);

        r_ro_single_init(&L.render_objects[i], c_camera_gl, tex);
    }
}

static void save_state(void **data, size_t *size);
static void load_state(const void *data, size_t size);


void canvas_init(int rows, int cols) {
    int layers = 1;
    
    L.save_id = savestate_register(save_state, load_state);
     
    L.pose = mat4_eye();

    L.image = image_new_zeros(layers, rows, cols);
    L.render_objects = New0(rRoSingle , layers);
    L.layers = layers;
    canvas_current_layer = 0;

    init_render_objects();
    
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

    Image *img = io_load_image("sprite.png");
    if(img) {
        image_copy(L.image, img);
        image_delete(img);
    }
    
    L.last_image = image_new_clone(L.image);
}

void canvas_update(float dtime) {
    float w, h;
    if(L.image->rows < L.image->cols) {
        w = 160;
        h = 160.0f * L.image->rows / L.image->cols;      } else {
        h = 160;
        w = 160.0f * L.image->cols / L.image->rows;
    }
    
    if(c_camera_is_portrait_mode())
        u_pose_set(&L.pose, 0, c_camera_top() - 110, w, h, 0);
    else
        u_pose_set(&L.pose, c_camera_left() + 85, 0, w, h, 0);

    for(int i=0; i<L.layers; i++) {
        r_texture_update(L.render_objects[i].tex, L.image->cols, L.image->rows, image_layer(L.image, i));

        // set pose
        L.render_objects[i].rect.pose = L.pose;
    }

    L.grid.rect.pose = L.pose;
    L.bg.rect.pose = L.pose;
}

void canvas_render() {
    r_ro_single_render(&L.bg);

    for(int i=0; i<=canvas_current_layer; i++) {
        r_ro_single_render(&L.render_objects[i]);
    }

    r_ro_single_render(&L.grid);
}


mat4 canvas_pose() {
    return L.pose;
}

Image *canvas_image() {
    return L.image;
}

int canvas_layers() {
    return L.layers;
}

void canvas_save() {
	if(!image_equals(L.image, L.last_image)) {
	    image_copy(L.last_image, L.image);
	    savestate_save();
        io_save_image(canvas_image(), "sprite.png");
	}
}

void canvas_redo_image() {
	savestate_redo_id(L.save_id);
}


static void save_state(void **data, size_t *size) {
	*data = L.image;
	*size = image_full_size(L.image);
}
static void load_state(const void *data, size_t size) {
	// todo: check new layers, rows, cols
	image_delete(L.image);
	L.image = image_new_clone(data);
	assert(image_full_size(L.image) == size);
}

