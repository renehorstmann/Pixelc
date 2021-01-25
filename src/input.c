#include "e/input.h"
#include "brush.h"
#include "input.h"


static void pointer_event(ePointer_s pointer, void *user_data) {
    brush_pointer_event(pointer);
}

void input_init() {
    e_input_register_pointer_event(pointer_event, NULL);
}
