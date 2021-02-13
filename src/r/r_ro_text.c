#include "float.h"
#include "mathc/float.h"
#include "r/ro_text.h"
#include "r/texture.h"

// todo remove
#include "u/pose.h"


static void hide(rRoText *self, int from) {
	for(int i=from;i<self->ro.num;i++) {
		u_pose_set_xy(&self->ro.rects[i].pose, FLT_MAX, FLT_MAX);
	}
}

static void set_pose(rRoText *self, mat4 *p, int c, int r) {
	u_pose_aa_set(p, c*self->offset.x, (-r-1)*self->offset.y, self->size.x, self->size.y);
}


void r_ro_text_init(rRoText *self, int max, r_ro_text_uv_fn uv_fn, const float *vp, GLuint tex_sink) {
	self->uv_fn = uv_fn;
	self->pose = mat4_eye();
	self->size = (vec2) {{5, 5}};
	self->offset = (vec2) {{6, 6}};
	self->vp = vp;
	self->mvp = mat4_eye();
	r_ro_batch_init(&self->ro, max, &self->mvp.m00, tex_sink);
	hide(self, 0);
	r_ro_batch_update(&self->ro);
}

void r_ro_text_kill(rRoText *self) {
	r_ro_batch_kill(&self->ro);
}

void r_ro_text_render(rRoText *self) {
	self->mvp = mat4_mul_mat(Mat4(self->vp), self->pose);
	r_ro_batch_render(&self->ro);
}

void r_ro_text_set_text(rRoText *self, const char *text) {
	int i=0;
	int col=0;
	int row=0;
	while(*text) {
		bool newline = self->uv_fn(&self->ro.rects[i].uv, *text);
		set_pose(self, &self->ro.rects[i].pose, col, row);
		
		col++;
		if(newline) {
		    col=0;
		    row++;
		}
		text++;
		i++;
	}
	hide(self, i);
	r_ro_batch_update(&self->ro);
}


static bool font55_uv_cb(mat4 *uv, char c) {
	static const int cols = 64;
	static const int rows = 64;
	static const int size_x = 5;
	static const int size_y = 5;
	
	int columns = cols / size_x;
	
	bool nl = false;
	if(c=='\n') {
		nl = true;
		c = ' ';
	}
	
	c = toupper(c);
	if(c<' ' || c>'Z')
	    c =' ';
	c-=' ';
	int col = c%columns;
	int row = c/columns;
	
	float w = (float) size_x/cols;
	float h = (float) size_y/rows;
	
	u_pose_set(uv, col*w, row*h, w, h, 0);
	
	return nl;
}

void r_ro_text_init_font55(rRoText *self, int max, const float *vp) {
	r_ro_text_init(self, max, font55_uv_cb, vp, r_texture_init_file("res/r/font55.png", NULL));
}
