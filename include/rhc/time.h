#ifndef RHC_TIME_H
#define RHC_TIME_H

#include <time.h>

static double time_monotonic() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double) time.tv_sec + (double) time.tv_nsec / 1000000000.0;
}


//
// High precision timer based on time_monotonic
//
typedef struct {
    double start_time;
} RhcTimer_s;

// creates a new timer with the current monotonic time
static RhcTimer_s rhc_timer_new() {
    return (RhcTimer_s) {time_monotonic()};
}

// returns the elapsed time in seconds
static double rhc_timer_elapsed(RhcTimer_s self) {
    return time_monotonic() - self.start_time;
}

// resets the timer and return the elapsed time in seconds
static double rhc_timer_reset(RhcTimer_s self) {
    double time = time_monotonic();
    double elapsed = time - self.start_time;
    self.start_time = time;
    return elapsed;
}


#endif //RHC_TIME_H
