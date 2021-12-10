#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "e/window.h"
#include "e/definitions.h"

// rhc implementation source file, only once in a project
#include "rhc/rhc_impl.h"


#define MAX_DELTA_TIME 5.0 // seconds


//
// protected
//

void e_window_handle_window_event_(const SDL_Event *event);


//
// private
//

typedef struct {
    e_window_pause_callback_fn cb;
    void *ud;    
} RegPause;
 
struct eWindow{
    SDL_Window *window;
    SDL_GLContext gl_context;
    ivec2 size;
    
    bool pause;
    bool running;

    e_window_main_loop_fn main_loop_fn;
    Uint32 last_time;
    
    RegPause reg_pause_e[E_WINDOW_MAX_PAUSE_EVENTS];
    int reg_pause_e_size;
};

//
// singleton
//
static eWindow singleton;
static bool singleton_created;
//
//
//

static void check_resume() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        e_window_handle_window_event_(&event);
    }
}

static void loop() {
    if(singleton.pause) {
        check_resume();
        return;
    }
                
    SDL_GetWindowSize(singleton.window, &singleton.size.x, &singleton.size.y);

    Uint32 time = SDL_GetTicks();
    float dtime = (time - singleton.last_time) / 1000.0f;
    singleton.last_time = time;

    if(dtime < MAX_DELTA_TIME)
        singleton.main_loop_fn(dtime);
}

static void pause_wnd() {
    if(singleton.pause)
        return;
    log_info("e_window: pause");
    singleton.pause = true;
    for(int i=0; i<singleton.reg_pause_e_size; i++) {
        singleton.reg_pause_e[i].cb(false, singleton.reg_pause_e[i].ud);
    }
}

static void resume_wnd() {
    if(!singleton.pause)
        return;
    log_info("e_window: resume");
    for(int i=0; i<singleton.reg_pause_e_size; i++) {
        singleton.reg_pause_e[i].cb(true, singleton.reg_pause_e[i].ud);
    }
    
    // delta_time should not be near infinity...
    singleton.last_time = SDL_GetTicks();
    singleton.pause = false;
}


static void log_window_event(const SDL_Event *event);

//
// protected
//
void e_window_handle_window_event_(const SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        eWindow *tmp = &singleton;
        e_window_kill(&tmp);
        return;
    }
    if(event->type == SDL_WINDOWEVENT) {
        log_window_event(event);
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

//
// public
//

eWindow *e_window_new(const char *title) {
    log_info("e_window_new");

    assume(!singleton_created, "e_window_new should be called only onve");
    singleton_created = true;

    
#ifdef NDEBUG
    rhc_log_set_min_level(RHC_LOG_WARN);
#else
    rhc_log_set_min_level(RHC_LOG_TRACE);
#endif

    if (SDL_Init(E_SDL_INIT_FLAGS) != 0) {
        log_error("e_window_new: SDL_Init failed: %s", SDL_GetError());
        e_exit_failure();
    }


    // initialize IMG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        log_error("e_window_new: IMG_Init failed: %s", IMG_GetError());
        e_exit_failure();
    }

#ifdef OPTION_TTF
    // initialize TTF
    if (TTF_Init() == -1) {
        log_error("e_window_new: TTF_Init failed: %s", TTF_GetError());
        e_exit_failure();
    }
#endif

#ifdef OPTION_SOCKET
    // initialize net
    if (SDLNet_Init() == -1) {
        log_error("e_window_new: SDLNet_Init failed: %s", SDLNet_GetError());
        e_exit_failure();
    }
#endif

    // setup OpenGL usage
    log_info("e_window_new: OpenGL minimal version: %d.%d", E_GL_MAJOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, E_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, E_GL_PROFILE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // create window
    singleton.window = SDL_CreateWindow(title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_OPENGL 
            | SDL_WINDOW_RESIZABLE
            );
    if (!singleton.window) {
        log_error("e_window_new: SDL_CreateWindow failed: %s", SDL_GetError());
        e_exit_failure();
    }
//    SDL_SetWindowMinimumSize(singleton.window, 480, 320);
    SDL_SetWindowMinimumSize(singleton.window, 1, 1);


    // Not necessary, but recommended to create a gl context:
    singleton.gl_context = SDL_GL_CreateContext(singleton.window);
    if (!singleton.gl_context) {
        log_error("e_window_new: SDL_GL_CreateContext failed: %s", SDL_GetError());
        e_exit_failure();
    }

#ifdef OPTION_GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        log_error( "e_window_new faled: %s", glewGetErrorString(err));
        e_exit_failure();
    }
    log_info("e_window_new: Using GLEW version: %s", glewGetString(GLEW_VERSION));
#endif

    SDL_GetWindowSize(singleton.window, &singleton.size.x, &singleton.size.y);

    return &singleton;
}

void e_window_kill(eWindow **self_ptr) {
    // safe to free NULL
    if(!self_ptr)
        return;

    assume(*self_ptr == &singleton, "singleton?");
    if(!singleton.running)
        return;

    log_info("e_window_kill: killing...");
    singleton.running = false;
    
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    EM_ASM(set_error_img(););
#endif

    // will be killed in the main loop
    *self_ptr = NULL;
}

SDL_Window *e_window_get_sdl_window(const eWindow *self) {
    assume(self == &singleton, "singleton?");
    return singleton.window;
}

SDL_GLContext e_window_get_sdl_gl_context(const eWindow *self) {
    assume(self == &singleton, "singleton?");
    return singleton.gl_context;
}

void e_window_main_loop(eWindow *self, e_window_main_loop_fn main_loop) {
    assume(self == &singleton, "singleton?");
    singleton.main_loop_fn = main_loop;
    singleton.pause = false;
    singleton.running = true;
    singleton.last_time = SDL_GetTicks();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, true);
#else
    while (singleton.running)
        loop();
#endif


    SDL_DestroyWindow(singleton.window);
#ifdef OPTION_TTF
    TTF_Quit();
#endif 
    IMG_Quit();
    SDL_Quit();

    memset(&singleton, 0, sizeof(singleton));
    singleton_created = false;
    log_info("e_window_kill: killed");
}

void e_window_reset_main_loop(eWindow *self, e_window_main_loop_fn main_loop) {
    assume(self == &singleton, "singleton?");
    assume(singleton.main_loop_fn, "main_loop not started yet?");
    log_info("e_window_reset_main_loop");
    singleton.main_loop_fn = main_loop;
}

ivec2 e_window_get_size(const eWindow *self) {
    assume(self == &singleton, "singleton?");
    return singleton.size;
}

void e_window_set_vsync(const eWindow *self, bool activate) {
    int ret;
    if(!activate) {
        ret = SDL_GL_SetSwapInterval(0);
        if(ret == 0) {
            log_info("e_window_set_vsync: turned off", activate);
            return;
        }
        log_error("e_window_set_vsync: failed to turn off vsync");
        return;
    }
    // try adaptive vsync
    ret = SDL_GL_SetSwapInterval(-1);
    if(ret == 0) {
        log_info("e_window_set_vsync: applied adaptive-vsync");
        return;
    }
    ret = SDL_GL_SetSwapInterval(1);
    if(ret == 0) {
        log_info("e_window_set_vsync: applied vsync");
        return;
    }
    log_error("e_window_set_vsync: failed to turn on vsync");
}

void e_window_set_screen_mode(const eWindow *self, enum e_window_screen_modes mode) {
    assume(self == &singleton, "singleton?");
    Uint32 sdl_mode = 0;
    
    // emscripten is always fullscreen
#ifndef __EMSCRIPTEN__
    log_info("e_window_set_screen_mode: %i", mode);
    if(mode == E_WINDOW_MODE_MAXIMIZED) {
        sdl_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else if(mode == E_WINDOW_MODE_FULLSCREEN) {
        sdl_mode = SDL_WINDOW_FULLSCREEN;
    }
#endif
    SDL_SetWindowFullscreen(singleton.window, sdl_mode);
}


void e_window_register_pause_callback(eWindow *self, e_window_pause_callback_fn event, void *user_data) {
    assume(self == &singleton, "singleton?");
    assume(singleton.reg_pause_e_size < E_WINDOW_MAX_PAUSE_EVENTS, "too many registered pause events");
    singleton.reg_pause_e[singleton.reg_pause_e_size++] = (RegPause){event, user_data};
}

void e_window_unregister_pause_callback(eWindow *self, e_window_pause_callback_fn event_to_unregister) {
    assume(self == &singleton, "singleton?");
    bool found = false;
    for (int i = 0; i < singleton.reg_pause_e_size; i++) {
        if (singleton.reg_pause_e[i].cb == event_to_unregister) {
            found = true;
            // move to close hole
            for (int j = i; j < singleton.reg_pause_e_size - 1; j++) {
                singleton.reg_pause_e[j] = singleton.reg_pause_e[j + 1];
            }
            singleton.reg_pause_e_size--;
            i--; // check moved
        }
    }
    if (!found) {
        log_warn("e_window_unregister_pause_callback failed: event not registered");
    }
}




static void log_window_event(const SDL_Event *event) {
    if (event->type == SDL_WINDOWEVENT){
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            log_info("eWindow %d shown", event->window.windowID);
            break;       
        case SDL_WINDOWEVENT_HIDDEN:
            log_info("eWindow %d hidden", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            log_info("eWindow %d exposed", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            log_info("eWindow %d moved to %d,%d", event->window.windowID, event->window.data1, event->window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            log_info("eWindow %d resized to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            log_info("eWindow %d size changed to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            log_info("eWindow %d minimized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            log_info("eWindow %d maximized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            log_info("eWindow %d restored", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            log_info("Mouse entered window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            log_info("Mouse left window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            log_info("eWindow %d gained keyboard focus", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            log_info("eWindow %d lost keyboard focus", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            log_info("eWindow %d closed", event->window.windowID);
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5) 
            case SDL_WINDOWEVENT_TAKE_FOCUS : log_info("eWindow %d is offered a focus", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            log_info("eWindow %d has a special hit test", event->window.windowID);
            break;
#endif 
            default : log_info("eWindow %d got unknown event %d", event->window.windowID, event->window.event);
            break;
        }
    }
}

