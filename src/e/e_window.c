// s implementation source file, only once in a project
#include "s/s_impl.h"

#include <SDL2/SDL_image.h>

#ifdef OPTION_TTF
#include <SDL2/SDL_ttf.h>
#endif

#include "e/window.h"
#include "e/definitions.h"


#define MAX_DELTA_TIME 5.0 // seconds


struct eWindow_Globals e_window;


//
// protected
//

void e_window_handle_window_event_(const SDL_Event *event);

const char *e_window_get_title();

void e_io_savestate_load();

//
// private
//

typedef struct {
    e_window_pause_callback_fn cb;
    void *ud;
} RegPause;

typedef struct {
    e_window_main_loop_fn cb;
    void *ud;
} RegRunOnce;

static struct {
    char title[32];

    bool pause;
    bool running;

    e_window_main_loop_fn main_loop_fn;
    void *main_loop_user_data;
    su32 last_time_ms;

    RegPause reg_pause_e[E_WINDOW_MAX_PAUSE_EVENTS];
    int reg_pause_e_size;

    RegRunOnce reg_run_once_e[E_WINDOW_MAX_RUN_ONCE_EVENTS];
    int reg_run_once_e_size;
    SDL_mutex *run_once_lock;
} L;

static void check_resume() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        e_window_handle_window_event_(&event);
    }
}

static void loop() {
    if (L.pause) {
        check_resume();
        return;
    }

    su32 time_ms = SDL_GetTicks();
    int deltatime_ms = time_ms - L.last_time_ms;
    L.last_time_ms = time_ms;
    float deltatime = deltatime_ms / 1000.0f;

    if (deltatime < 0 || deltatime >= MAX_DELTA_TIME)
        return;

    // only set values if the frame is not dropped
    SDL_GetWindowSize(e_window.sdl_window, &e_window.size.x, &e_window.size.y);
    e_window.frame_deltatime = deltatime;
    e_window.frame_deltatime_ms = deltatime_ms;
    e_window.frame_time_ms += deltatime_ms;
    // may be reset by e_simple:
    e_window.deltatime = e_window.frame_deltatime;
    e_window.deltatime_ms = e_window.frame_deltatime_ms;
    e_window.time_ms = e_window.frame_time_ms;

    SDL_LockMutex(L.run_once_lock);
    for(int i=0; i<L.reg_run_once_e_size; i++) {
        L.reg_run_once_e[i].cb(L.reg_run_once_e[i].ud);
    }
    L.reg_run_once_e_size = 0;
    SDL_UnlockMutex(L.run_once_lock);

    L.main_loop_fn(L.main_loop_user_data);
}

static void pause_wnd() {
    if (L.pause || !e_window.allow_pause)
        return;
    s_log("e_window: pause");
    L.pause = true;
    for (int i = 0; i < L.reg_pause_e_size; i++) {
        L.reg_pause_e[i].cb(false, L.reg_pause_e[i].ud);
    }
}

static void resume_wnd() {
    if (!L.pause || !e_window.allow_pause)
        return;
    s_log("e_window: resume");
    for (int i = 0; i < L.reg_pause_e_size; i++) {
        L.reg_pause_e[i].cb(true, L.reg_pause_e[i].ud);
    }

    // delta_time should not be near infinity...
    L.last_time_ms = SDL_GetTicks();
    L.pause = false;
}


static void log_window_event(const SDL_Event *event);

//
// protected
//
void e_window_handle_window_event_(const SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        e_window_kill();
        return;
    }
    if (event->type == SDL_WINDOWEVENT) {
//        log_window_event(event);
        switch (event->window.event) {
//        case SDL_WINDOWEVENT_SHOWN:
//        case SDL_WINDOWEVENT_RESTORED:
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                resume_wnd();
                break;
//        case SDL_WINDOWEVENT_HIDDEN:
//        case SDL_WINDOWEVENT_MINIMIZED:
            case SDL_WINDOWEVENT_FOCUS_LOST:
                pause_wnd();
                break;
        }
    }
}

const char *e_window_get_title() {
    return L.title;
}

//
// public
//

void e_window_init(const char *title) {
    s_assume(!e_window.init, "should be called only once");
    e_window.init = true;

    s_log("init");

    e_window.allow_pause = true;

    s_assume(strlen(title) < sizeof L.title, "title to long: %i/%i",
           strlen(title), sizeof L.title);
    strcpy(L.title, title);

    if (SDL_Init(E_SDL_INIT_FLAGS) != 0) {
        s_log_error("SDL_Init failed: %s", SDL_GetError());
        e_exit_failure();
    }


    // initialize IMG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        s_log_error("IMG_Init failed: %s", IMG_GetError());
        e_exit_failure();
    }

#ifdef OPTION_TTF
        // initialize TTF
        if (TTF_Init() == -1) {
            s_log_error("TTF_Init failed: %s", TTF_GetError());
            e_exit_failure();
        }
#endif

#ifdef OPTION_SOCKET
        // initialize net
        if (SDLNet_Init() == -1) {
            s_log_error("SDLNet_Init failed: %s", SDLNet_GetError());
            e_exit_failure();
        }
#endif

    // setup OpenGL usage
    s_log("OpenGL minimal version: %d.%d", E_GL_MAJOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, E_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, E_GL_PROFILE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // create window
    e_window.sdl_window = SDL_CreateWindow(title,
           SDL_WINDOWPOS_UNDEFINED,
           SDL_WINDOWPOS_UNDEFINED,
           640, 480,
           SDL_WINDOW_OPENGL
           | SDL_WINDOW_RESIZABLE
//           | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!e_window.sdl_window) {
        s_log_error("SDL_CreateWindow failed: %s", SDL_GetError());
        e_exit_failure();
    }
    SDL_SetWindowMinimumSize(e_window.sdl_window, 1, 1);


    // Not necessary, but recommended to create a gl context:
    e_window.gl_context = SDL_GL_CreateContext(e_window.sdl_window);
    if (!e_window.gl_context) {
        s_log_error("SDL_GL_CreateContext failed: %s", SDL_GetError());
        e_exit_failure();
    }

#ifdef OPTION_GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        s_log_error("failed: %s", glewGetErrorString(err));
        e_exit_failure();
    }
    s_log("Using GLEW version: %s", glewGetString(GLEW_VERSION));
#endif

    SDL_GetWindowSize(e_window.sdl_window, &e_window.size.x, &e_window.size.y);

    // call protected function to let web load indexDB database
    e_io_savestate_load();

    L.run_once_lock = SDL_CreateMutex();
}

void e_window_kill() {
    if (!L.running)
        return;

    s_log("killing...");
    L.running = false;

#ifdef PLATFORM_EMSCRIPTEN
    emscripten_cancel_main_loop();
    EM_ASM(set_error_img(););
#endif

    SDL_DestroyMutex(L.run_once_lock);
}

void e_window_main_loop(e_window_main_loop_fn main_loop, void *user_data) {
    L.main_loop_fn = main_loop;
    L.main_loop_user_data = user_data;
    L.pause = false;
    L.running = true;
    L.last_time_ms = SDL_GetTicks();

#ifdef PLATFORM_EMSCRIPTEN
    emscripten_set_main_loop(loop, 0, true);
#else
    while (L.running)
        loop();
#endif


#ifdef OPTION_SANITIZER
    void __lsan_do_leak_check();
    int __lsan_do_recoverable_leak_check(void);

    // checks for memory leaks
    s_log("sanitizer leak check...");
    int leaks = __lsan_do_recoverable_leak_check();
    if (leaks)
        s_log_error("sanitizer leak check done, got %i leaks!", leaks);
    else
        s_log("sanitizer leak check done, without leaks", leaks);

    // this call also checks for leaks, but than it doesnt check at program end
    //      some SDL (or ports) may have some memory leaks
    //      so we call it before shutting them down to see our own mistakes
    __lsan_do_leak_check();
#endif

    SDL_DestroyWindow(e_window.sdl_window);
#ifdef OPTION_TTF
    TTF_Quit();
#endif
    IMG_Quit();
    SDL_Quit();

    e_window.init = false;
    memset(&e_window, 0, sizeof e_window);
    memset(&L, 0, sizeof L);
    s_log("killed");
}

void e_window_reset_main_loop(e_window_main_loop_fn main_loop, void *user_data) {
    s_assume(L.main_loop_fn, "main_loop not started yet?");
    s_log("reset");
    L.main_loop_fn = main_loop;
    L.main_loop_user_data = user_data;
}

void e_window_set_vsync(bool activate) {
    int ret;
    if (!activate) {
        ret = SDL_GL_SetSwapInterval(0);
        if (ret == 0) {
            s_log("turned off", activate);
            return;
        }
        s_log_error("failed to turn off vsync");
        return;
    }
    // try adaptive vsync
    ret = SDL_GL_SetSwapInterval(-1);
    if (ret == 0) {
        s_log("applied adaptive-vsync");
        return;
    }
    ret = SDL_GL_SetSwapInterval(1);
    if (ret == 0) {
        s_log("applied vsync");
        return;
    }
    s_log("failed to turn on vsync");
}

void e_window_set_screen_mode(enum e_window_screen_modes mode) {
    Uint32 sdl_mode = 0;

    // emscripten is always fullscreen
#ifndef PLATFORM_EMSCRIPTEN
    s_log("mode: %i", mode);
    if (mode == E_WINDOW_MODE_MAXIMIZED) {
        sdl_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else if (mode == E_WINDOW_MODE_FULLSCREEN) {
        sdl_mode = SDL_WINDOW_FULLSCREEN;
    }
#endif
    SDL_SetWindowFullscreen(e_window.sdl_window, sdl_mode);
}


void e_window_register_pause_callback(e_window_pause_callback_fn event, void *user_data) {
    s_assume(L.reg_pause_e_size < E_WINDOW_MAX_PAUSE_EVENTS, "too many registered pause events");
    L.reg_pause_e[L.reg_pause_e_size++] = (RegPause) {event, user_data};
}

void e_window_unregister_pause_callback(e_window_pause_callback_fn event_to_unregister) {
    bool found = false;
    for (int i = 0; i < L.reg_pause_e_size; i++) {
        if (L.reg_pause_e[i].cb == event_to_unregister) {
            found = true;
            // move to close hole
            for (int j = i; j < L.reg_pause_e_size - 1; j++) {
                L.reg_pause_e[j] = L.reg_pause_e[j + 1];
            }
            L.reg_pause_e_size--;
            i--; // check moved
        }
    }
    if (!found) {
        s_log_warn("failed: event not registered");
    }
}

void e_window_run_once_on_main_looper(e_window_main_loop_fn runnable, void *user_data) {
    SDL_LockMutex(L.run_once_lock);
    s_assume(L.reg_run_once_e_size < E_WINDOW_MAX_RUN_ONCE_EVENTS, "too many registered run once runables");
    L.reg_run_once_e[L.reg_run_once_e_size++] = (RegRunOnce) {runnable, user_data};
    SDL_UnlockMutex(L.run_once_lock);
}

static void log_window_event(const SDL_Event *event) {
    if (event->type == SDL_WINDOWEVENT) {
        switch (event->window.event) {
            case SDL_WINDOWEVENT_SHOWN:
                s_log_trace("eWindow %d shown", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                s_log_trace("eWindow %d hidden", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                s_log_trace("eWindow %d exposed", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_MOVED:
                s_log_trace("eWindow %d moved to %d,%d", event->window.windowID, event->window.data1,
                          event->window.data2);
                break;
            case SDL_WINDOWEVENT_RESIZED:
                s_log_trace("eWindow %d resized to %dx%d", event->window.windowID, event->window.data1,
                          event->window.data2);
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                s_log_trace("eWindow %d size changed to %dx%d", event->window.windowID, event->window.data1,
                          event->window.data2);
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                s_log_trace("eWindow %d minimized", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                s_log_trace("eWindow %d maximized", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_RESTORED:
                s_log_trace("eWindow %d restored", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_ENTER:
                s_log_trace("Mouse entered window %d", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_LEAVE:
                s_log_trace("Mouse left window %d", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                s_log_trace("eWindow %d gained keyboard focus", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                s_log_trace("eWindow %d lost keyboard focus", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_CLOSE:
                s_log_trace("eWindow %d closed", event->window.windowID);
                break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
            case SDL_WINDOWEVENT_TAKE_FOCUS :
                s_log_trace("eWindow %d is offered a focus", event->window.windowID);
                break;
            case SDL_WINDOWEVENT_HIT_TEST:
                s_log_trace("eWindow %d has a special hit test", event->window.windowID);
                break;
#endif
            default :
                s_log_trace("eWindow %d got unknown event %d", event->window.windowID, event->window.event);
                break;
        }
    }
}

