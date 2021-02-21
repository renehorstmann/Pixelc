#include <string.h>  // memcmp
#include "utilc/alloc.h"
#include "image.h"


Image *image_new_empty(int layers, int cols, int rows) {
    Image *self = raising_malloc(1, sizeof(Image) + sizeof(Color_s) * layers * rows * cols, SIGABRT);
    self->layers = layers;
    self->rows = rows;
    self->cols = cols;
    return self;
}

Image *image_new_zeros(int layers, int cols, int rows) {
    Image *self = raising_calloc(1, sizeof(Image) + sizeof(Color_s) * layers * rows * cols, SIGABRT);
    self->layers = layers;
    self->rows = rows;
    self->cols = cols;
    return self;
}

Image *image_new_clone(const Image *from) {
    Image *self = image_new_empty(from->layers, from->cols, from->rows);
    memcpy(self->data, from->data, image_data_size(from));
    return self;
}

void image_delete(Image *self) {
    free(self);
}

bool image_copy(Image *self, const Image *from) {
    printf("s f %d %d\n", self->layers, from->layers);
    if(self->layers == from->layers
       && self->rows == from->rows 
       && self->cols == from->cols) {
        size_t size = image_data_size(self);
        memcpy(self->data, from->data, size);
        return true;
    }
    SDL_Log("image_copy failed");
    return false;
}

bool image_equals(const Image *self, const Image *from) {
	if(image_data_size(self) != image_data_size(from))
	    return false;
	    
	return memcmp(self, from, image_full_size(self)) == 0;
}


void image_rotate(Image *self, bool right) {
	Image *tmp = image_new_clone(self);
	self->cols = tmp->rows;
	self->rows = tmp->cols;
	for(int l=0; l<self->layers; l++) {
		for(int r=0; r<self->rows; r++) {
			for(int c=0; c<self->rows; c++) {
			    int mc = right? r : tmp->cols - 1 - r;
			    int mr = right? tmp->rows - 1 - c : c;
			    *image_pixel(self, l, c, r) = *image_pixel(tmp, l, mc, mr);
		    }
		}
	}
	
	image_delete(tmp);
}

void image_mirror(Image *self, bool vertical) {
	Image *tmp = image_new_clone(self);
	
	for(int l=0; l<self->layers; l++) {
		for(int r=0; r<self->rows; r++) {
			for(int c=0; c<self->rows; c++) {
			    int mc = vertical? self->cols - 1 - c : c;
			    int mr = vertical? r : self->rows - 1 - r;
			    *image_pixel(self, l, c, r) = *image_pixel(tmp, l, mc, mr);
		    }
		}
	}
	
	image_delete(tmp);
}

