#ifndef E_INPUT_H
#define E_INPUT_H

//
// handles input like keys, mouse, touchscreen, gyro
//

#include <stdbool.h>
#include "mathc/types/float.h"
#include "core.h"

#define E_MAX_TOUCH_IDS 12

#define E_MAX_POINTER_EVENTS 32
#define E_MAX_WHEEL_EVENTS 32
#define E_MAX_KEY_RAW_EVENTS 32

// ePointer_s::id for middle and right button clicks
#define E_POINTER_BUTTON_MIDDLE -1
#define E_POINTER_BUTTON_RIGHT -2

// Keyboard state
typedef struct {
    bool up, left, right, down;
    bool enter, space;
} eInputKeys;


enum ePointerAction {
    E_POINTER_DOWN, E_POINTER_MOVE, E_POINTER_UP,
    E_POINTER_NUM_ACTIONS
};

typedef struct {
    vec4 pos; // x, y, 0, 1
    enum ePointerAction action;
    int id;   // 0 = default; >0 multitouch; <0 m+r click
} ePointer_s;


// mouse and touch callback
typedef void (*ePointerEventFn)(ePointer_s, void *user_data);

// mouse wheel callback
typedef void (*eWheelEventFn)(bool up, void *user_data);

// keyboard key event
typedef void (*eKeyRawEventFn)(const SDL_Event *event, void *user_data);


struct eWindow;
struct eGui;
typedef struct eInput eInput;


// creates the input interface
eInput *e_input_new(const struct eWindow *window);

void e_input_kill(eInput **self_ptr);

// runs the sdl event loop
void e_input_update(const eInput *self);

// returns pressed main keys
eInputKeys e_input_get_keys(const eInput *self);

// returns true, if its a touch input, instead of mouse
bool e_input_is_touch(const eInput *self);

// returns true, if an accelerometer is available
bool e_input_accel_active(const eInput *self);

// returns the xyz accelerometer values
vec3 e_input_get_accel(const eInput *self);

// registers a callback for mouse and touch
void e_input_register_pointer_event(const eInput *self, ePointerEventFn event, void *user_data);

// unregisters a callback
void e_input_unregister_pointer_event(const eInput *self, ePointerEventFn event_to_unregister);

// sets a pointer event to a vip call, pass event=NULL to reset
// a vip event will block all other events
void e_input_set_vip_pointer_event(const eInput *self, ePointerEventFn event, void *user_data);

// registers a callback for mouse wheel
void e_input_register_wheel_event(const eInput *self, eWheelEventFn event, void *user_data);

// unregisters a callback
void e_input_unregister_wheel_event(const eInput *self, eWheelEventFn event_to_unregister);

// sets a wheel event to a vip call, pass event=NULL to reset
// a vip event will block all other events
void e_input_set_vip_wheel_event(const eInput *self, eWheelEventFn event, void *user_data);

// registers a callback for sdl key events
void e_input_register_key_raw_event(const eInput *self, eKeyRawEventFn event, void *user_data);

// unregisters a callback
void e_input_unregister_key_raw_event(const eInput *self, eKeyRawEventFn event_to_unregister);

// sets a key raw event to a vip call, pass event=NULL to reset
// a vip event will block all other events
void e_input_set_vip_key_raw_event(const eInput *self, eKeyRawEventFn event, void *user_data);

#endif //E_INPUT_H
