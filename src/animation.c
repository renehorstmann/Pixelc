#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "hud_camera.h"
#include "canvas.h"
#include "animation.h"


static struct {
	rRoSingle ro;
	GLuint tex;
    int frames;
    float time;	
    float fps;
} L;

void animation_init(int frames) {
	L.frames = frames;
	L.fps = 2;
	
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

    u_pose_set(&L.ro.rect.pose, 50, -50, img->cols / L.frames, img->rows, 0);
}

void animation_render() {
	r_ro_single_render(&L.ro);
}

