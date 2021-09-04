#include "mathc/float.h"
#include "rhc/error.h"
#include "rhc/log.h"
#include "e/window.h"
#include "e/gui_nk.h"
#include "e/gui.h"
#include "e/input.h"

//
// protected
//
extern eGui *e_gui_singleton_;
void e_window_handle_window_event_(const SDL_Event *event);
void e_gui_input_begin_(const eGui *self);
void e_gui_handle_sdl_event_(const eGui *self, SDL_Event *event);
void e_gui_input_end_(const eGui *self);

typedef struct {
    ePointerEventFn cb;
    void *ud;
} RegPointer;

typedef struct {
    eWheelEventFn cb;
    void *ud;
} RegWheel;

struct eInput{
    const struct eWindow *window;

    eInputKeys keys;

    bool is_touch;
    // acceleration sensor (mobile)
    bool accel_active;
    vec3 accel;
    
    RegPointer reg_pointer_e[E_MAX_POINTER_EVENTS];
    int reg_pointer_e_size;

    RegWheel reg_wheel_e[E_MAX_WHEEL_EVENTS];
    int reg_wheel_e_size;
};


//
// singleton
//
static eInput singleton;
static bool singleton_created;
//
//
//

static ePointer_s pointer_mouse(enum ePointerAction action, int btn_id) {
    ePointer_s res;
    res.action = action;
    res.id = btn_id;
    int x, y;
    SDL_GetMouseState(&x, &y);

    ivec2 window_size = e_window_get_size(singleton.window);
    res.pos.x = (2.0f * x) / window_size.x - 1.0f;
    res.pos.y = 1.0f - (2.0f * y) / window_size.y;
    res.pos.z = 0;
    res.pos.w = 1;

    return res;
}

static ePointer_s pointer_finger(enum ePointerAction action, float x, float y, int finger_id) {
    ePointer_s res;
    res.action = action;
    res.id = finger_id;

    res.pos.x = 2.0f * x - 1.0f;
    res.pos.y = 1.0f - 2.0f * y;
    res.pos.z = 0;
    res.pos.w = 1;

    return res;
}

static void emit_pointer_events(ePointer_s action) {
    for (int i = 0; i < singleton.reg_pointer_e_size; i++)
        singleton.reg_pointer_e[i].cb(action, singleton.reg_pointer_e[i].ud);
}

static void emit_wheel_events(bool up) {
    for (int i = 0; i < singleton.reg_wheel_e_size; i++)
        singleton.reg_wheel_e[i].cb(up, singleton.reg_wheel_e[i].ud);
}

static void input_handle_pointer_touch(SDL_Event *event) {
    switch (event->type) {
    case SDL_FINGERDOWN:
        emit_pointer_events(pointer_finger(E_POINTER_DOWN,
                                           event->tfinger.x, event->tfinger.y, event->tfinger.fingerId));
        break;
    case SDL_FINGERMOTION:
        emit_pointer_events(pointer_finger(E_POINTER_MOVE,
                                           event->tfinger.x, event->tfinger.y, event->tfinger.fingerId));
        break;
    case SDL_FINGERUP:
        emit_pointer_events(pointer_finger(E_POINTER_UP,
                                           event->tfinger.x, event->tfinger.y, event->tfinger.fingerId));
        break;
    }
}

static void input_handle_pointer_mouse(SDL_Event *event) {
    switch (event->type) {
    case SDL_MOUSEBUTTONDOWN:
        if (event->button.button <= 0 || event->button.button > 3)
            break;
        emit_pointer_events(pointer_mouse(
            E_POINTER_DOWN,
            1 - event->button.button));
        break;
    case SDL_MOUSEMOTION:
        emit_pointer_events(pointer_mouse(E_POINTER_MOVE, 0));
        break;
    case SDL_MOUSEBUTTONUP:
        if (event->button.button <= 0 || event->button.button > 3)
            break;
        emit_pointer_events(pointer_mouse(
            E_POINTER_UP,
            1 - event->button.button));
        break;
    }
}

static void input_handle_wheel(SDL_Event *event) {
    // it could be possible that y==0, (e. g. x!=0)
    if (event->wheel.y == 0)
        return;
    emit_wheel_events(event->wheel.y > 0);
}

static void input_handle_keys(SDL_Event *event) {
    bool down = event->type == SDL_KEYDOWN;
    switch (event->key.keysym.sym) {
    case SDLK_UP:
        singleton.keys.up = down;
        break;
    case SDLK_LEFT:
        singleton.keys.left = down;
        break;
    case SDLK_RIGHT:
        singleton.keys.right = down;
        break;
    case SDLK_DOWN:
        singleton.keys.down = down;
        break;
    case SDLK_RETURN:
        singleton.keys.enter = down;
        break;
    case SDLK_SPACE:
        singleton.keys.space = down;
        break;
    }
}

#ifdef OPTION_GYRO
static void input_handle_sensors(SDL_Event *event) {
    SDL_Sensor *sensor = SDL_SensorFromInstanceID(event->sensor.which);
    if (!sensor || SDL_SensorGetType(sensor) != SDL_SENSOR_ACCEL) {
        log_warn("e_input_update: Couldn't get sensor for sensor event\n");
        return;
    }

    const float *data = event->sensor.data;
    memcpy(singleton.accel.v, data, sizeof(singleton.accel));

    // log_trace("e_input_update: Gyro update: %.2f, %.2f, %.2f", data[0], data[1], data[2]);
}
#endif



//
// public
//

eInput *e_input_new(const struct eWindow *window) {
    assume(!singleton_created, "e_input_new should be called only onve");
    singleton_created = true;
    
    assume(window, "needs an sdl window to get its size");
    singleton.window = window;
    
#ifdef OPTION_GYRO
    int num_sensors = SDL_NumSensors();
    bool accel_opened = false;
    for (int i = 0; i < num_sensors; i++) {
        if (SDL_SensorGetDeviceType(i) == SDL_SENSOR_ACCEL) {
            SDL_Sensor *sensor = SDL_SensorOpen(i);
            if (sensor) {
                accel_opened = true;
                break;
            }
        }
    }

    singleton.accel_active = accel_opened;
    if (accel_opened)
        log_info("e_input_new: Opened acceleration sensor");
#endif
    
    return &singleton;
}

void e_input_kill(eInput **self_ptr) {
    // safe to free NULL
    if(!self_ptr)
        return;
    
    assume(*self_ptr == &singleton, "singleton?");
    memset(&singleton, 0, sizeof(singleton));
    *self_ptr = NULL;
}


void e_input_update(const eInput *self) {
    assume(self == &singleton, "singleton?");
    singleton.is_touch = SDL_GetNumTouchDevices() > 0;


    e_gui_input_begin_(e_gui_singleton_);    // NULL safe

    void (*input_handle_pointer)(SDL_Event * event) = singleton.is_touch ? input_handle_pointer_touch : input_handle_pointer_mouse;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        e_window_handle_window_event_(&event);

        e_gui_handle_sdl_event_(e_gui_singleton_, &event);   // NULL safe

        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONUP:
        case SDL_FINGERDOWN:
        case SDL_FINGERMOTION:
        case SDL_FINGERUP:
            input_handle_pointer(&event);
            break;
        case SDL_MOUSEWHEEL:
            input_handle_wheel(&event);
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            input_handle_keys(&event);
            break;
#ifdef OPTION_GYRO
        case SDL_SENSORUPDATE:
            input_handle_sensors(&event);
            break;
#endif
        }
    }

    e_gui_input_end_(e_gui_singleton_);    // NULL safe
}


eInputKeys e_input_get_keys(const eInput *self) {
    assume(self == &singleton, "singleton?");
    return singleton.keys;
}

bool e_input_is_touch(const eInput *self) {
    assume(self == &singleton, "singleton?");
    return singleton.is_touch;
}

bool e_input_accel_active(const eInput *self) {
    assume(self == &singleton, "singleton?");
    return singleton.accel_active;
}

vec3 e_input_get_accel(const eInput *self) {
    assume(self == &singleton, "singleton?");
    return singleton.accel;
}


void e_input_register_pointer_event(const eInput *self, ePointerEventFn event, void *user_data) {
    assume(self == &singleton, "singleton?");
    assume(singleton.reg_pointer_e_size < E_MAX_POINTER_EVENTS, "too many registered pointer events");
    singleton.reg_pointer_e[singleton.reg_pointer_e_size++] = (RegPointer){event, user_data};
}

void e_input_unregister_pointer_event(const eInput *self, ePointerEventFn event_to_unregister) {
    assume(self == &singleton, "singleton?");
    bool found = false;
    for (int i = 0; i < singleton.reg_pointer_e_size; i++) {
        if (singleton.reg_pointer_e[i].cb == event_to_unregister) {
            found = true;
            // move to close hole
            for (int j = i; j < singleton.reg_pointer_e_size - 1; j++) {
                singleton.reg_pointer_e[j] = singleton.reg_pointer_e[j + 1];
            }
            singleton.reg_pointer_e_size--;
            i--; // check moved
        }
    }
    if (!found) {
        log_warn("e_input_unregister_pointer_event failed: event not registered");
    }
}

void e_input_register_wheel_event(const eInput *self, eWheelEventFn event, void *user_data) {
    assume(self == &singleton, "singleton?");
    assume(singleton.reg_wheel_e_size < E_MAX_WHEEL_EVENTS, "too many registered wheel events");
    singleton.reg_wheel_e[singleton.reg_wheel_e_size++] = (RegWheel){event, user_data};
}

void e_input_unregister_wheel_event(const eInput *self, eWheelEventFn event_to_unregister) {
    assume(self == &singleton, "singleton?");
    bool found = false;
    for (int i = 0; i < singleton.reg_wheel_e_size; i++) {
        if (singleton.reg_wheel_e[i].cb == event_to_unregister) {
            found = true;
            // move to close hole
            for (int j = i; j < singleton.reg_wheel_e_size - 1; j++) {
                singleton.reg_wheel_e[j] = singleton.reg_wheel_e[j + 1];
            }
            singleton.reg_wheel_e_size--;
            i--; // check moved
        }
    }
    if (!found) {
        log_warn("e_input_unregister_wheel_event failed: event not registered");
    }
}

