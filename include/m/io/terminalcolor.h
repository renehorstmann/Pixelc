#ifndef M_IO_TERMINALCOLOR_H
#define M_IO_TERMINALCOLOR_H

#define M_TERMINALCOLOR_RED     "\x1B[31m"
#define M_TERMINALCOLOR_GREEN   "\x1B[32m"
#define M_TERMINALCOLOR_YELLOW  "\x1B[33m"
#define M_TERMINALCOLOR_BLUE    "\x1B[34m"
#define M_TERMINALCOLOR_MAGENTA "\x1B[35m"
#define M_TERMINALCOLOR_CYAN    "\x1B[36m"
#define M_TERMINALCOLOR_WHITE   "\x1B[37m"
#define M_TERMINALCOLOR_RESET   "\x1B[0m"


#ifdef _WIN32
#include <windows.h>
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif
static HANDLE m___terminalcolor_stdout_handle;
static DWORD m___terminalcolor_out_mode_init;
static void m_terminalcolor_start() {
    DWORD out_mode = 0;
    m___terminalcolor_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(m___terminalcolor_stdout_handle, &out_mode);
    m___terminalcolor_out_mode_init = out_mode;

    // Enable ANSI escape codes
    out_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(m___terminalcolor_stdout_handle, out_mode);
}
static void m_terminalcolor_stop() {
    // Reset console mode
    SetConsoleMode(m___terminalcolor_stdout_handle, m___terminalcolor_out_mode_init);
}

#else //_WIN32

static void m_terminalcolor_start() {
    // noop
}

static void m_terminalcolor_stop() {
    // noop
}

#endif //_WIN32


#endif //M_IO_TERMINALCOLOR_H
