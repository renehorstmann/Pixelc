#ifndef S_TIME_H
#define S_TIME_H

//
// functions for high precision time and a timer
//

#include "export.h"

// returns the time in seconds from the monotonic clock
S_EXPORT
double s_time_monotonic();

//
// High precision timer based on s_time_monotonic
//
typedef struct {
    double start_time;
} sTimer_s;

// creates a new timer with the current monotonic time
static sTimer_s s_timer_new() {
    return (sTimer_s) {s_time_monotonic()};
}

// returns the elapsed time in seconds
static double s_timer_elapsed(sTimer_s self) {
    return s_time_monotonic() - self.start_time;
}

// resets the timer and return the elapsed time in seconds
static double s_timer_reset(sTimer_s *self) {
    double time = s_time_monotonic();
    double elapsed = time - self->start_time;
    self->start_time = time;
    return elapsed;
}


#endif //S_TIME_H
