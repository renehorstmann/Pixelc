#include "mathc/float.h"
#include "utilc/assume.h"
#include "e/window.h"
#include "e/gui.h"
#include "e/input.h"
#include "e/definitions.h"

struct eInputGloabals_s e_input;


typedef struct {
    ePointerEventFn cb;
    void *ud;
} RegPointer;

typedef struct {
    eWheelEventFn cb;
    void *ud;
} RegWheel;

static struct {
    RegPointer reg_pointer_e[E_MAX_POINTER_EVENTS];
    int reg_pointer_e_size;

    RegWheel reg_wheel_e[E_MAX_WHEEL_EVENTS];
    int reg_wheel_e_size;

#ifdef __EMSCRIPTEN__
    ePointer_s emscripten_pointer_stack[E_EMSCRIPTEN_POINTER_STACK_SIZE];
    int emscripten_pointer_stack_size;
#endif

} L;

static ePointer_s pointer_mouse(enum ePointerAction action, int btn_id) {
    ePointer_s res;
    res.action = action;
    res.id = btn_id;
    int x, y;
    SDL_GetMouseState(&x, &y);

    res.pos.x = (2.0f * x) / e_window.size.x - 1.0f;
    res.pos.y = 1.0f - (2.0f * y) / e_window.size.y;
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

#ifdef __EMSCRIPTEN__
static ePointer_s pointer_emscripten_touch(enum ePointerAction action, float x, float y, int finger_id) {
    ePointer_s res;
    res.action = action;
    res.id = finger_id;

    res.pos.x = (2.0f * x) / e_window.size.x - 1.0f;
    res.pos.y = 1.0f - (2.0f * y) / e_window.size.y;
    res.pos.z = 0;
    res.pos.w = 1;

    return res;
}
#endif

static void emit_pointer_events(ePointer_s action) {
    for (int i = 0; i < L.reg_pointer_e_size; i++)
        L.reg_pointer_e[i].cb(action, L.reg_pointer_e[i].ud);
}

static void emit_wheel_events(bool up) {
    for(int i=0; i<L.reg_wheel_e_size; i++)
        L.reg_wheel_e[i].cb(up, L.reg_wheel_e[i].ud);
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
    if(event->wheel.y == 0)
        return;
    emit_wheel_events(event->wheel.y > 0);
}

static void input_handle_keys(SDL_Event *event) {
    bool down = event->type == SDL_KEYDOWN;
    switch (event->key.keysym.sym) {
        case SDLK_UP:
            e_input.keys.up = down;
            break;
        case SDLK_LEFT:
            e_input.keys.left = down;
            break;
        case SDLK_RIGHT:
            e_input.keys.right = down;
            break;
        case SDLK_DOWN:
            e_input.keys.down = down;
            break;
        case SDLK_RETURN:
            e_input.keys.enter = down;
            break;
        case SDLK_SPACE:
            e_input.keys.space = down;
            break;
    }
}

#ifdef USING_GYRO
static void input_handle_sensors(SDL_Event *event) {
    SDL_Sensor *sensor = SDL_SensorFromInstanceID(event->sensor.which);
    if (!sensor
        || SDL_SensorGetType(sensor) != SDL_SENSOR_ACCEL) {
        SDL_Log("Couldn't get sensor for sensor event\n");
        return;
    }

    const float *data = event->sensor.data;
    memcpy(e_input.accel.v, data, sizeof(e_input.accel));

    //printf("Gyro update: %.2f, %.2f, %.2f\n", data[0], data[1], data[2]);
}
#endif

#ifdef __EMSCRIPTEN__
EM_BOOL touch_callback_func(int type, const EmscriptenTouchEvent *event, void *ud) {
    if(L.emscripten_pointer_stack_size >= E_EMSCRIPTEN_POINTER_STACK_SIZE)
        return true;

    enum ePointerAction action;
    switch(type) {
        case EMSCRIPTEN_EVENT_TOUCHSTART:
            action = E_POINTER_DOWN;
            break;
        case EMSCRIPTEN_EVENT_TOUCHMOVE:
            action = E_POINTER_MOVE;
            break;
        default:
            action = E_POINTER_UP;
    }
    for(int i=0; i<event->numTouches; i++) {
        float x = event->touches[i].targetX;
        float y = event->touches[i].targetY;
        int id = event->touches[i].identifier;
        L.emscripten_pointer_stack[L.emscripten_pointer_stack_size++] = pointer_emscripten_touch(action, x, y, id);
    }
    return true;
}
#endif

void e_input_init() {
    e_input.is_touch = SDL_GetNumTouchDevices() > 0;
    SDL_Log("Has touch input: %i", e_input.is_touch);

#ifdef USING_GYRO
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

    e_input.accel_active = accel_opened;
    if (accel_opened)
        SDL_Log("Opened acceleration sensor");
#endif

#ifdef __EMSCRIPTEN__
    emscripten_set_touchstart_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, 1, touch_callback_func);
    emscripten_set_touchend_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, 1, touch_callback_func);
    emscripten_set_touchmove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, 1, touch_callback_func);
    emscripten_set_touchcancel_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, 1, touch_callback_func);
#endif
}


void ignore_pointer(SDL_Event *event) {}

void e_input_update() {
    if (e_gui.ctx) nk_input_begin(e_gui.ctx);

    void (*input_handle_pointer)(SDL_Event *event) = e_input.is_touch?
            input_handle_pointer_touch : input_handle_pointer_mouse;


#ifdef __EMSCRIPTEN__
    // ignore mouse / finger events, if touches are available
    if(L.emscripten_pointer_stack_size > 0) {
        e_input.is_touch = true;
        input_handle_pointer = ignore_pointer;
    }
#endif

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (e_gui.ctx) nk_sdl_handle_event(&event);

        switch (event.type) {
            case SDL_QUIT:
                e_window_kill();
                return;
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
#ifdef USING_GYRO
            case SDL_SENSORUPDATE:
                input_handle_sensors(&event);
                break;
#endif
        }
    }

    if (e_gui.ctx) nk_input_end(e_gui.ctx);

#ifdef __EMSCRIPTEN__
    for(int i=0; i<L.emscripten_pointer_stack_size; i++) {
        emit_pointer_events(L.emscripten_pointer_stack[i]);
    }
    L.emscripten_pointer_stack_size = 0;
#endif
}


void e_input_register_pointer_event(ePointerEventFn event, void *user_data) {
    assume(L.reg_pointer_e_size < E_MAX_POINTER_EVENTS, "too many registered pointer events");
    L.reg_pointer_e[L.reg_pointer_e_size++] = (RegPointer) {event, user_data};
}

void e_input_unregister_pointer_event(ePointerEventFn event_to_unregister) {
    int idx = -1;
    for (int i = 0; i < L.reg_pointer_e_size; i++) {
        if (L.reg_pointer_e[i].cb == event_to_unregister) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        SDL_Log("e_input_unregister_pointer_event failed, event not registered");
        return;
    }

    // move to close hole
    for (int i = idx; i < L.reg_pointer_e_size - 1; i++) {
        L.reg_pointer_e[i] = L.reg_pointer_e[i + 1];
    }
    L.reg_pointer_e_size--;
}

void e_input_register_wheel_event(eWheelEventFn event, void *user_data) {
    assume(L.reg_wheel_e_size < E_MAX_WHEEL_EVENTS, "too many registered wheel events");
    L.reg_wheel_e[L.reg_wheel_e_size++] = (RegWheel) {event, user_data};
}

void e_input_unregister_wheel_event(eWheelEventFn event_to_unregister) {
    int idx = -1;
    for (int i = 0; i < L.reg_wheel_e_size; i++) {
        if (L.reg_wheel_e[i].cb == event_to_unregister) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        SDL_Log("e_input_unregister_wheel_event failed, event not registered");
        return;
    }

    // move to close hole
    for (int i = idx; i < L.reg_wheel_e_size - 1; i++) {
        L.reg_wheel_e[i] = L.reg_wheel_e[i + 1];
    }
    L.reg_wheel_e_size--;
}
