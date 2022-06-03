#ifndef RHC_TERMINALCOLOR_IMPL_H
#define RHC_TERMINALCOLOR_IMPL_H
#ifdef RHC_IMPL

#ifdef _WIN32
#include <windows.h>
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif
static HANDLE rhc___terminalcolor_stdout_handle;
static DWORD rhc___terminalcolor_out_mode_init;
void rhc_terminalcolor_start() {
    DWORD out_mode = 0;
    rhc___terminalcolor_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(rhc___terminalcolor_stdout_handle, &out_mode);
    rhc___terminalcolor_out_mode_init = out_mode;

    // Enable ANSI escape codes
    out_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(rhc___terminalcolor_stdout_handle, out_mode);
}
void rhc_terminalcolor_stop() {
    // Reset console mode
    SetConsoleMode(rhc___terminalcolor_stdout_handle, rhc___terminalcolor_out_mode_init);
}

#else //_WIN32

void rhc_terminalcolor_start() {
    // noop
}

void rhc_terminalcolor_stop() {
    // noop
}

#endif //_WIN32

#endif //RHC_IMPL
#endif //RHC_TERMINALCOLOR_IMPL_H
