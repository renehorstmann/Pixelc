#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "hud_camera.h"
#include "canvas.h"
#include "palette.h"
#include "animation.h"


#define SIZE 1


static struct {
	rRoSingle ro;
	GLuint tex;
    int frames;
    float time;	
    float fps;
} L;

void animation_init(int frames, float fps) {
	L.frames = frames;
	L.fps = fps;
	
	Image *img = canvas_image();
	L.tex = r_texture_init(img->cols, img->rows, image_layer(img, canvas_current_layer));
	r_texture_filter_nearest(L.tex);
	
	r_ro_single_init(&L.ro, hud_camera_gl, L.tex);
	u_pose_set_w(&L.ro.rect.uv, 1.0/frames);
}

void animation_update(float dtime) {
	L.time = fmodf(L.time + dtime, L.frames / L.fps);
	float u = floorf(L.time * L.fps) / L.frames;
	u_pose_set_x(&L.ro.rect.uv, u);
	
	Image *img = canvas_image();
	r_texture_update(L.tex, img->cols, img->rows, image_layer(img, canvas_current_layer));

    float w = SIZE * img->cols / L.frames;
    float h = SIZE * img->rows;
    
    float x, y;
    if(hud_camera_is_portrait_mode()) {
    	x = hud_camera_right() - w/2 - 2; 
        y = hud_camera_bottom() + palette_get_hud_size() + h/2 + 2;	
    } else {
    	x = hud_camera_right() - palette_get_hud_size() - w/2 - 2;
    	y = hud_camera_top() - h/2 - 2;
    }
    
    u_pose_set(&L.ro.rect.pose, 
        floorf(x), floorf(y), w, h, 0);
}

void animation_render() {
	r_ro_single_render(&L.ro);
}

