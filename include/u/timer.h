#ifndef U_TIMER_H
#define U_TIMER_H

//
// A timer based on (default:) e_window.time_ms with milliseconds accuracy
// So only updated before the update function
// For a high precision timer based on monotonic time, see sTimer_s in s/time.h
//
#include "e/window.h"


//
// options
//

#ifndef U_TIMER_SRC
#define U_TIMER_SRC (e_window.time_ms)
#endif

typedef struct {
    su32 start_time_ms;
} uTimer_s;

// creates a new timer with the u_window time (updated each time before the update function)
// to reset just override with a new one
static uTimer_s u_timer_new() {
    return (uTimer_s) {U_TIMER_SRC};
}

// returns the elapsed time in ms
static uint32_t u_timer_elapsed_ms(uTimer_s self) {
    return U_TIMER_SRC - self.start_time_ms;
}

// returns the elapsed time in seconds
static float u_timer_elapsed(uTimer_s self) {
    return u_timer_elapsed_ms(self) / 1000.0f;
}

#endif //U_TIMER_H
