#ifndef E_TIMER_H
#define E_TIMER_H

//
// A timer based on e_window.time_ms with milliseconds accuracy
// So only updated on a not dropped frame
// For a high precision timer based on monotonic time, see RhcTimer_s in rhc/time.h
//

#include "window.h"

typedef struct {
    uint32_t start_time;
} eTimer_s;

// creates a new timer with the e_window time (updated each not dropped frame)
// to reset just override with a new one
static eTimer_s e_timer_new() {
    return (eTimer_s) {e_window.time_ms};
}

// returns the elapsed time in ms
static uint32_t e_timer_elapsed_ms(eTimer_s self) {
    return e_window.time_ms - self.start_time;
}

// returns the elapsed time in seconds
static float e_timer_elapsed(eTimer_s self) {
    return e_timer_elapsed_ms(self) / 1000.0f;
}

#endif //E_TIMER_H
