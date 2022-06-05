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


// will be called once for startup
typedef void (*e_simple_init_fn)();

// will be called to update the game in updates/s
// dtime is set to 1/updates_pes_second if available,
// otherwise to the time between frames, as with the render_fn
typedef void (*e_simple_update_fn)(float dtime);

// will be called each frame to render
// dtime is set to the time between frames (not to 1/updates_per_second !)
typedef void (*e_simple_render_fn)(float dtime);


struct eSimple_Globals {
    e_simple_update_fn update_fn;
    e_simple_render_fn render_fn;

    // the following values are smoothed:
    // current frames per second (1/render_dtime)
    float fps;
    // current load in % for the update call per frame
    float load_update;
    // current load in % for the render call per frame
    float load_render;
    // current load in % per frame
    float load;
};
extern struct eSimple_Globals e_simple;


// call this function once in the main function
// author will be displayed at the startup screen
// the startup screen will have an additional block time of startup_block_time
// if update_deltatime_ms <= 0, updates deltatime is the time between the last frame
// if updates_per_seconds > 0, updates delta_time is fixed to it (usefull for games: collisionchecks, etc.)
//    and e_window.time will be a multitude of that time
void e_simple_start(const char *title, 
                    const char *author, 
                    float startup_block_time, 
                    int update_deltatime_ms,
                    e_simple_init_fn init_fn,
                    e_simple_update_fn update_fn,
                    e_simple_render_fn render_fn);


#endif //E_SIMPLE_H
