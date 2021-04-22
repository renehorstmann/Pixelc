#ifndef RHC_TIME_H
#define RHC_TIME_H

#include <time.h>

static double time_monotonic() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double) time.tv_sec + (double) time.tv_nsec / 1000000000.0;
}

#endif //RHC_TIME_H
