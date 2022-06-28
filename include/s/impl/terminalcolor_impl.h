#ifndef S_TERMINALCOLOR_IMPL_H
#define S_TERMINALCOLOR_IMPL_H
#ifdef S_IMPL

#if defined(PLATFORM_MINGW) || defined(PLATFORM_MSVC)
#include <windows.h>
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif
static HANDLE s___terminalcolor_stdout_handle;
static DWORD s___terminalcolor_out_mode_init;
void s_terminalcolor_start() {
    DWORD out_mode = 0;
    s___terminalcolor_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(s___terminalcolor_stdout_handle, &out_mode);
    s___terminalcolor_out_mode_init = out_mode;

    // Enable ANSI escape codes
    out_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(s___terminalcolor_stdout_handle, out_mode);
}
void s_terminalcolor_stop() {
    // Reset console mode
    SetConsoleMode(s___terminalcolor_stdout_handle, s___terminalcolor_out_mode_init);
}

#else // Windows

void s_terminalcolor_start() {
    // noop
}

void s_terminalcolor_stop() {
    // noop
}

#endif // Windows

#endif //S_IMPL
#endif //S_TERMINALCOLOR_IMPL_H
