#include "utilc/alloc.h"
#include "selection.h"

static struct {
	int x, y;
	int rows, cols;
	Color_s *opt_data;
} L;

void selection_init(int x, int y, int rows, int cols) {
	L.x = x;
	L.y = y;
	L.rows = rows;
	L.cols = cols;
	selection_kill();
}

void selection_kill() {
	L.x = L.y = L.rows = L.cols = 0;
	Free0(L.opt_data);
}

bool selection_contains(int x, int y) {
	return x>=L.x && x<L.x+L.cols
	        && y>=L.y && y<L.y+L.rows;
}

void selection_copy(Image *from, int layer) {
     Free0(L.opt_data);
}

void selection_cut(Image *from, int layer, Color_s replace) {
	selection_copy(from, layer);
	
	for(int r=0; r<L.rows; r++) {
		for(int c=0; c<L.cols; c++) {
			*image_pixel(from, layer, r+L.x, c+L.y) = replace;
		}
	}
}

void selection_paste(Image *to, int layer) {
	
}

