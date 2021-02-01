#include "c_camera.h"
#include "camera_control.h"


static struct {
	float x, y;
	float size;
	
	ePointer_s touch0;
} L;

void camera_control_init() {
	L.x = L.y = 0;
	L.size = 1;	
}

void camera_control_pointer_event(ePointer_s pointer) {
#ifdef GLES
    if(pointer.id == 0) {
    	L.touch0 = pointer;
    	return;
    }

    

#endif
}


