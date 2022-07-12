#ifndef U_ANIMATOR_H
#define U_ANIMATOR_H

//
// An a animator based on (default:) e_window.time_ms with milliseconds accuracy
// So only updated before the update function
//    see timer.h
//

#include "timer.h"
#include "m/vec/ivecn.h"

// 
// options
//

#ifndef U_ANIMATOR_MAX_FRAMES
#define U_ANIMATOR_MAX_FRAMES 32
#endif

typedef struct {
    uTimer_s timer;
    int frames;
    int frame_time_ms[U_ANIMATOR_MAX_FRAMES];
    
    // offset to the timer time
    // used by set_frame to offset to the desired frame
    // use rand()%_full_frame_time_ms() to select a random frame
    su32 time_offset_ms;
    
    // maximal time for the elapsed timer time
    su32 time_stop_ms;
} uAnimator_s;


// creates a new animator starting at frame 0
// use set_frame or reset .frame_offset_ms to select a frame
static uAnimator_s u_animator_new(int frames, int frame_time_ms) {
    uAnimator_s self;
    self.timer = u_timer_new();
    self.frames = frames;
    ivecN_set(self.frame_time_ms, frame_time_ms, U_ANIMATOR_MAX_FRAMES);
    self.time_offset_ms = 0;
    self.time_stop_ms = UINT32_MAX;
    return self;
}

// creates an animator with fps cast
static uAnimator_s u_animator_new_fps(int frames, float frames_per_second) {
    return u_animator_new(frames, 1000.0f/frames_per_second);
}

// set an individual frame time for each frame
static uAnimator_s u_animator_new_individual(int frames, const int *frame_time_ms_array) {
    uAnimator_s self;
    self.timer = u_timer_new();
    self.frames = frames;
    ivecN_copy(self.frame_time_ms, frame_time_ms_array, frames);
    self.time_offset_ms = 0;
    self.time_stop_ms = UINT32_MAX;
    return self;
}

// returns the full cycle time
static int u_animator_cycle_time_ms(uAnimator_s self) {
   return ivecN_sum(self.frame_time_ms, self.frames);
}
   
// resets the timer and sets .frame_offset_ms to match the desired frame
static void u_animator_set_frame(uAnimator_s *self, int frame) {
    self->timer = u_timer_new();
    self->time_offset_ms = 0;
    for(int i=0;i<frame;i++)
        self->time_offset_ms += self->frame_time_ms[i];
}

static void u_animator_set_stop_frame(uAnimator_s *self, int frame, int add_full_cycles) {
    self->time_stop_ms = add_full_cycles * u_animator_cycle_time_ms(*self);
    for(int i=0; i<frame; i++) 
        self->time_stop_ms += self->frame_time_ms[i];
}

// returns the current frame
static int u_animator_frame(uAnimator_s self) {
    su32 time = u_timer_elapsed_ms(self.timer);
    time += self.time_offset_ms;
    // min(time, stop_time):
    time = time < self.time_stop_ms? time : self.time_stop_ms;
    
    time %= u_animator_cycle_time_ms(self);
    int frame = 0;
    while(time >= (su32) self.frame_time_ms[frame]) {
        time -= (su32) self.frame_time_ms[frame];
        frame++;
    }
    return frame;
}

#endif //U_ANIMATOR_H
