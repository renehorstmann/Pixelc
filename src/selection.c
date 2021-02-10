#include "utilc/alloc.h"
#include "selection.h"

static struct {
	int left, top;
	int width, height;
	Color_s *opt_data;
} L;

void selection_init(int left, int top, int width, int height) {
	selection_kill();
}

void selection_kill() {
	L.left = L.top = L.width = L.height = 0;
	Free0(L.opt_data);
}

bool selection_contains(int x, int y) {
	return x>=L.left && x<L.left+L.width
	        && y>=L.top && y<L.top+L.height;
}

void selection_copy(Image *from, int layer) {
	
}

void selection_cut(Image *from, int layer, Color_s replace) {
	
}

void selection_paste(Image *to, int layer) {
	
}

