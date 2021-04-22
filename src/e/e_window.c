#include <stdbool.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "e/window.h"
#include "e/definitions.h"

// rhc implementation source file, only once in a project
#include "rhc/rhc_impl.h"


struct eWindowGlobals_s e_window;

static struct {
    bool running;

    eWindowMainLoopFn main_loop_fn;
    Uint32 last_time;
} L;

static void loop() {
    SDL_GetWindowSize(e_window.window, &e_window.size.x, &e_window.size.y);

    Uint32 time = SDL_GetTicks();
    float dtime = (time - L.last_time) / 1000.0f;
    L.last_time = time;

    L.main_loop_fn(dtime);
}


void e_window_init(const char *name) {
#ifdef NDEBUG
    rhc_log_set_min_level(RHC_LOG_WARN);
#else
    rhc_log_set_min_level(RHC_LOG_TRACE);
#endif

    if (SDL_Init(E_SDL_INIT_FLAGS) != 0) {
        log_error("e_window_init: SDL_Init failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    // initialize IMG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        log_error("e_window_init: IMG_Init failed: %s", IMG_GetError());
        exit(EXIT_FAILURE);
    }

#ifdef OPTION_TTF
    // initialize TTF
    if (TTF_Init() == -1) {
        log_error("e_window_init: TTF_Init failed: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
#endif

    // setup OpenGL usage
    log_info("e_window_init: OpenGL minimal version: %d.%d", E_GL_MAJOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, E_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, E_GL_PROFILE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // create window
    e_window.window = SDL_CreateWindow(name,
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       640, 480,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_SetWindowMinimumSize(e_window.window, 480, 320);
    if (!e_window.window) {
        log_error("e_window_init: SDL_CreateWindow failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Not necessary, but recommended to create a gl context:
    e_window.gl_context = SDL_GL_CreateContext(e_window.window);
    if (!e_window.gl_context) {
        log_error("e_window_init: SDL_GL_CreateContext failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_GL_SetSwapInterval(1);  // (0=off, 1=V-Sync, -1=addaptive V-Sync)

#ifdef OPTION_GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        log_error( "e_window_init faled: %s", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    log_info("e_window_init: Using GLEW version: %s", glewGetString(GLEW_VERSION));
#endif

    SDL_GetWindowSize(e_window.window, &e_window.size.x, &e_window.size.y);
}

void e_window_kill() {
    log_info("e_window_kill: Window killed");
    L.running = false;
}

void e_window_main_loop(eWindowMainLoopFn main_loop) {
    L.main_loop_fn = main_loop;
    L.running = true;
    L.last_time = SDL_GetTicks();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, true);
#else
    while (L.running)
        loop();
#endif


// ?
#ifndef __EMSCRIPTEN__
    SDL_DestroyWindow(e_window.window);
    SDL_Quit();
#endif
}

