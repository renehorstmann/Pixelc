#include <assert.h>
#include <float.h>
#include "r/ro_single.h"
#include "r/ro_batch.h"
#include "r/texture.h"
#include "u/pose.h"
#include "utilc/alloc.h"
#include "mathc/mat/float.h"

#include "image.h"
#include "canvas_camera.h"
#include "io.h"
#include "palette.h"
#include "toolbar.h"
#include "savestate.h"
#include "canvas.h"


int canvas_current_layer;
bool canvas_show_grid;

static struct {
    mat4 pose;

    Image *image;
    Image *last_image;
    rRoSingle *render_objects;
    int layers;
    
    rRoSingle bg;
    rRoSingle grid;
    
    bool show_selection;
    rRoBatch selection_border;
    
    int save_id;
} L;


static void init_render_objects() {
    for(int i=0; i<L.layers; i++) {
        GLuint tex = r_texture_init(L.image->cols, L.image->rows, image_layer(L.image, i));
        r_ro_single_init(&L.render_objects[i], canvas_camera_gl, tex);
    }
}

static mat4 pixel_pose(int x, int y) {
	float w = u_pose_get_w(L.pose);
	float size = w/L.image->cols;
	
	
	float pos_x = u_pose_aa_get_left(L.pose) + (x + 0.5) * size;    
	float pos_y = u_pose_aa_get_top(L.pose) - (y + 0.5) * size;
	
	mat4 pose = mat4_eye();
	u_pose_set(&pose, pos_x, pos_y, size, size, 0);
	return pose;
}

static void setup_selection() {
	int x = 2;
	int y = -1;
	int rows = 6;
	int cols = 10;
	
	int idx = 0;
	for(int i=0;i<rows;i++) {
		L.selection_border.rects[idx].pose = pixel_pose(x-1, y+i);
		u_pose_set(&L.selection_border.rects[idx].uv, 0, 0, 0.5, 0.5, 0);
		idx++;
		
		L.selection_border.rects[idx].pose = pixel_pose(x+cols, y+i);
		u_pose_set(&L.selection_border.rects[idx].uv, 0, 0.5, 0.5, 0.5, 0);
		idx++;
	}
	for(int i=0;i<cols;i++) {
		L.selection_border.rects[idx].pose = pixel_pose(x+i, y-1);
		u_pose_set(&L.selection_border.rects[idx].uv, 0.5, 0, 0.5, 0.5, 0);
		idx++;
		
		L.selection_border.rects[idx].pose = pixel_pose(x+i, y+rows);
		u_pose_set(&L.selection_border.rects[idx].uv, 0.5, 0.5, 0.5, 0.5, 0);
		idx++;
	}
	
	for(;idx < L.selection_border.num; idx++) {
		u_pose_set(&L.selection_border.rects[idx].pose, FLT_MAX, FLT_MAX, 0, 0, 0);
	}
	
	r_ro_batch_update(&L.selection_border, 0, L.selection_border.num);
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
    
    r_ro_single_init(&L.grid, canvas_camera_gl, 
            r_texture_init_file("res/canvas_grid.png", NULL));
    u_pose_set_size(&L.grid.rect.uv, cols, rows);


    r_ro_batch_init(&L.selection_border, 2*(rows+cols), canvas_camera_gl,
            r_texture_init_file("res/selection_border.png", NULL));
    for(int i=0; i<L.selection_border.num; i++) {
        L.selection_border.rects[i].color = (vec4) {{1, 0.25, 0.25, 0.75}};       
    }
            

    Color_s buf[4];
    buf[0] = buf[3] = color_from_hex("#999999");
    buf[1] = buf[2] = color_from_hex("#777777");
    GLuint bg_tex = r_texture_init(2, 2, buf);
    r_texture_filter_nearest(bg_tex);
    r_ro_single_init(&L.bg, canvas_camera_gl, bg_tex);
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
    
    float x = 0, y = 0;
    if(canvas_camera_is_portrait_mode()) {
        y = 20;
    }
    
    u_pose_set(&L.pose, x, y, w, h, 0);

    for(int i=0; i<L.layers; i++) {
        r_texture_update(L.render_objects[i].tex, L.image->cols, L.image->rows, image_layer(L.image, i));

        // set pose
        L.render_objects[i].rect.pose = L.pose;
    }

    L.grid.rect.pose = L.pose;
    L.bg.rect.pose = L.pose;
    
    setup_selection();
    L.show_selection = true;
}

void canvas_render() {
    r_ro_single_render(&L.bg);

    for(int i=0; i<=canvas_current_layer; i++) {
        r_ro_single_render(&L.render_objects[i]);
    }

    if(canvas_show_grid)
        r_ro_single_render(&L.grid);
        
    if(L.show_selection)
        r_ro_batch_render(&L.selection_border);
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

ivec2 canvas_get_uv(vec4 pointer_pos) {
    mat4 pose_inv = mat4_inv(L.pose);
    vec4 pose_pos = mat4_mul_vec(pose_inv, pointer_pos);

    ivec2 uv;
    uv.x = (pose_pos.x + 0.5) * canvas_image()->cols;    
    uv.y = (0.5 - pose_pos.y) * canvas_image()->rows;
    return uv;
}

void canvas_clear() {
    for(int i=0; i<L.image->rows*L.image->cols; i++) {
        *image_pixel_index(L.image, canvas_current_layer, i) = COLOR_TRANSPARENT;
    }
    canvas_save();
}

void canvas_save() {
	if(!image_equals(L.image, L.last_image)) {
	    image_copy(L.last_image, L.image);
	    savestate_save();
        io_save_image(canvas_image(), "sprite.png");
	}
}

void canvas_redo_image() {
	image_copy(L.image, L.last_image);
}


static void save_state(void **data, size_t *size) {
	*data = L.image;
	*size = image_full_size(L.image);
}
static void load_state(const void *data, size_t size) {
	// todo: check new layers, rows, cols
	image_delete(L.image);
	L.image = image_new_clone(data);
	image_copy(L.last_image, L.image);
	assert(image_full_size(L.image) == size);
	io_save_image(canvas_image(), "sprite.png");
}

