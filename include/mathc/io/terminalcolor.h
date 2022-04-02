#ifndef MATHC_IO_TERMINALCOLOR_H
#define MATHC_IO_TERMINALCOLOR_H

#define MATHC_TERMINALCOLOR_RED     "\x1B[31m"
#define MATHC_TERMINALCOLOR_GREEN   "\x1B[32m"
#define MATHC_TERMINALCOLOR_YELLOW  "\x1B[33m"
#define MATHC_TERMINALCOLOR_BLUE    "\x1B[34m"
#define MATHC_TERMINALCOLOR_MAGENTA "\x1B[35m"
#define MATHC_TERMINALCOLOR_CYAN    "\x1B[36m"
#define MATHC_TERMINALCOLOR_WHITE   "\x1B[37m"
#define MATHC_TERMINALCOLOR_RESET   "\x1B[0m"


#ifdef _WIN32
#include <windows.h>
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif
static HANDLE mathc___terminalcolor_stdout_handle;
static DWORD mathc___terminalcolor_out_mode_init;
static void mathc_terminalcolor_start() {
    DWORD out_mode = 0;
    mathc___terminalcolor_stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(mathc___terminalcolor_stdout_handle, &out_mode);
    mathc___terminalcolor_out_mode_init = out_mode;

    // Enable ANSI escape codes
    out_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(mathc___terminalcolor_stdout_handle, out_mode);
}
static void mathc_terminalcolor_stop() {
    // Reset console mode
    SetConsoleMode(mathc___terminalcolor_stdout_handle, mathc___terminalcolor_out_mode_init);
}

#else //_WIN32
static void mathc_terminalcolor_start() {
    // noop
}
static void mathc_terminalcolor_stop() {
    // noop
}
#endif //_WIN32


#endif //MATHC_IO_TERMINALCOLOR_H
