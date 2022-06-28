#ifndef S_ERROR_IMPL_H
#define S_ERROR_IMPL_H
#ifdef S_IMPL


#include "../common.h"  // for _Thread_local
#include "../log.h"
#include "../error.h"


//
// data
//

static _Thread_local const char *s__error;


const char *s_error_get() {
    return s__error;
}

void s_error_clear() {
    s__error = NULL;
}

void s_error_set(const char *static_data_error) {
    if(s__error) {
        s_log_base(S_LOG_WARN, NULL, 0, __func__, "overwriting error: %s", s__error);
    }
    s__error = static_data_error;
    s_log_base(S_LOG_ERROR, NULL, 0, __func__, "%s", s__error);
}

#endif //S_IMPL
#endif //S_ERROR_IMPL_H
