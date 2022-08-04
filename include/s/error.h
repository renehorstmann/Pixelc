#ifndef S_ERROR_H
#define S_ERROR_H

#include "export.h"

//
// error management
//      used for files and sockets for example.
//

// returns the current error from the calling thread, or NULL if no error occured
S_EXPORT
const char *s_error_get();

// clears the error of the calling thread
S_EXPORT
void s_error_clear();

// sets the error of the calling thread and logs it as error
// if s_error_get != NULL, the old error is logged as error before the reset
// the given error should be static data:
//      s_error_set("File not found");
S_EXPORT
void s_error_set(const char *static_data_error);

// does not overwrite an existing error
// the given error should be static data:
//      s_error_set_try("File not found");
static void s_error_set_try(const char *static_data_error) {
    if(s_error_get())
        return;
    s_error_set(static_data_error);
}

#endif //S_ERROR_H
