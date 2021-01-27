#include "e/e_input.h"
#include "brush.h"
#include "palette.h"
#include "input.h"


static void pointer_event(ePointer_s pointer, void *user_data) {
    if(!palette_pointer_event(pointer))
        brush_pointer_event(pointer);
}

void input_init() {
    e_input_register_pointer_event(pointer_event, NULL);
}
