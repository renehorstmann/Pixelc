#ifndef E_INPUT_H
#define E_INPUT_H

#include <stdbool.h>
#include "mathc/types/float.h"
#include "core.h"


#define E_MAX_POINTER_EVENTS 32
#define E_MAX_WHEEL_EVENTS 32
#define E_EMSCRIPTEN_POINTER_STACK_SIZE 1024

// ePointer_s::id for middle and right button clicks
#define E_POINTER_BUTTON_MIDDLE -1
#define E_POINTER_BUTTON_RIGHT -2

// Keyboard state
typedef struct {
    bool up, left, right, down;
    bool enter, space;
} eInputKeys;

struct eInputGloabals_s {
    eInputKeys keys;

    bool is_touch;
    // acceleration sensor (mobile)
    bool accel_active;
    vec3 accel;
};
extern struct eInputGloabals_s e_input;



enum ePointerAction {
    E_POINTER_DOWN, E_POINTER_MOVE, E_POINTER_UP,
    E_POINTER_NUM_ACTIONS
};

typedef struct {
    vec4 pos; // x, y, 0, 1
    enum ePointerAction action;
    int id;   // 0 = default; >0 multitouch; <0 m+r click
} ePointer_s;

typedef void (*ePointerEventFn)(ePointer_s, void *user_data);

typedef void (*eWheelEventFn)(bool up, void *user_data);


void e_input_init();

// runs the sdl event loop
void e_input_update();

// registers a callback for mouse and touch
void e_input_register_pointer_event(ePointerEventFn event, void *user_data);

// unregisters a callback
void e_input_unregister_pointer_event(ePointerEventFn event_to_unregister);

// registers a callback for mouse wheel
void e_input_register_wheel_event(eWheelEventFn event, void *user_data);

// unregisters a callback
void e_input_unregister_wheel_event(eWheelEventFn event_to_unregister);

#endif //E_INPUT_H
