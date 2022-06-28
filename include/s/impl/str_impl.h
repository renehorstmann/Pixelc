#ifndef S_STR_IMPL_H
#define S_STR_IMPL_H
#ifdef S_IMPL

#include "../file.h"
#include "../str.h"

ssize s_str_stream_print(sStr_s str, sStream_i stream) {
    if(!s_str_valid(str))
        return s_stream_printf(stream, "(sStr_s) {NULL, 0}\n");
    return s_stream_printf(stream, "(sStr_s) {\"%.*s\", %zu}\n", (int) str.size, str.data, str.size);
}

ssize s_str_print(sStr_s str) {
    return s_str_stream_print(str, s_file_stream_stdout());
}

#endif //S_IMPL
#endif //S_STR_IMPL_H
