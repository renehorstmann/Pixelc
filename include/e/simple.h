#ifndef E_SIMPLE_H
#define E_SIMPLE_H

//
// a simplified way to init the some framework
// INFO: this module uses not only e/ but also parts of r/ !
//

#include "window.h"
#include "input.h"
#include "gui.h"

// parts of r/
#include "r/render.h"


typedef struct eSimple eSimple;

// will be called once for startup
typedef void (*e_simple_init_fn)(eSimple *simple, ivec2 window_size);

// will be called to update the game in updates/s
typedef void (*e_simple_update_fn)(eSimple *simple, ivec2 window_size, float delta_time);

// will be called each frame to render
typedef void (*e_simple_render_fn)(eSimple *simple, ivec2 window_size);


struct eSimple {
    eWindow *window;
    eInput *input;
    eGui *gui;
    rRender *render;
    
    e_simple_update_fn update_fn;
    e_simple_render_fn render_fn;
    
    void *user_data;
};

// call this function once in the main function
void e_simple_start(const char *title, const char *author, float updates_per_seconds, 
        e_simple_init_fn init_fn,
        e_simple_update_fn update_fn,
        e_simple_render_fn render_fn);



#endif //E_SIMPLE_H
