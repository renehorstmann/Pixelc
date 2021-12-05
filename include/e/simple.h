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
// author will be displayed at the startup screen
// the startup screen will have an additional block time of startup_block_time
// if updates_per_seconds <= 0, updates delta_time is the time between the last frame
// if updates_per_seconds > 0, updates delta_time is fixed to it (usefull for games: collisionchecks, etc.)
void e_simple_start(const char *title, const char *author, float startup_block_time, float updates_per_seconds,
                    e_simple_init_fn init_fn,
                    e_simple_update_fn update_fn,
                    e_simple_render_fn render_fn);



#endif //E_SIMPLE_H
