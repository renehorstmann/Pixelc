#ifndef S_TIME_IMPL_H
#define S_TIME_IMPL_H
#ifdef S_IMPL

#include "../time.h"

#ifdef PLATFORM_MSVC

#include <windows.h>
double s_time_monotonic() {
    LARGE_INTEGER time, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&time);
    return (double) time.QuadPart / (double) freq.QuadPart;
}

#else
#include <time.h>

double s_time_monotonic() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double) time.tv_sec + (double) time.tv_nsec / 1000000000.0;
}

#endif

#endif //S_IMPL
#endif //S_TIME_IMPL_H
