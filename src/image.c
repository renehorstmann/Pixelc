#include "utilc/alloc.h"
#include "image.h"


void image_init(Image *self, int rows, int cols, int layers) {
	*self = (Image) {
	    New0(Color_s, layers*rows*cols),
	    rows, cols, layers
	};
}

void image_kill(Image *self) {
    free(self->data);
    *self = (Image) {0};	
}

void image_clone(Image *self, Image from) {
	size_t size = from.layers * from.rows * from.cols;
	if(self->layers * self->rows * self->cols != size) {
	   
	   self->data = ReNew(Color_s, self->data, size);
    }
    self->rows = from.rows;
    self->cols = from.cols;
    self->layers = from.layers;
    
    memcpy(self->data, from.data, sizeof(Color_s) * size);
}

