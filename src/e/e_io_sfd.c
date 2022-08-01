#if defined(PLATFORM_MSVC) || defined(PLATFORM_MINGW) || defined(PLATFORM_UNIX)


#include "s/s_full.h"
#include "e/io.h"
#include "e_ext_sfd.h"

//
// private
//

static sfd_Options create_options(const char *file) {
    sfd_Options opt;

    sString *filestring = s_string_new_clone(s_strc(file));
    s_str_tolower(s_string_get_str(filestring));
    if(s_str_ends_with(s_string_get_str(filestring), s_strc(".png"))) {
        opt = (sfd_Options) {
                .title        = "Image PNG File",
                .filter_name  = "Image PNG File",
                .filter       = "*.png",
                .extension    = ".png"
        };
    } else if(s_str_ends_with(s_string_get_str(filestring), s_strc(".txt"))) {
        opt = (sfd_Options) {
                .title        = "Text File",
                .filter_name  = "Text File",
                .filter       = "*.txt",
                .extension    = ".txt"
        };
    } else if(s_str_ends_with(s_string_get_str(filestring), s_strc(".gif"))) {
        opt = (sfd_Options) {
                .title        = "GIF File",
                .filter_name  = "GIF File",
                .filter       = "*.gif",
                .extension    = ".gif"
        };
    } else if(s_str_ends_with(s_string_get_str(filestring), s_strc(".json"))) {
        opt = (sfd_Options) {
                .title        = "Json File",
                .filter_name  = "Json File",
                .filter       = "*.json",
                .extension    = ".json",
        };
    } else {
        opt = (sfd_Options) {
                .title        = "File"
        };
    }

    s_string_kill(&filestring);
    return opt;
}

static void clone_file(const char *dst, const char *src) {
    sFile *file_dst = s_file_new_write(dst, false);
    sFile *file_src = s_file_new_read(src, false);

    sStream_i stream_dst = s_file_stream(file_dst);
    sStream_i stream_src = s_file_stream(file_src);

    su8 buffer[1024];
    while(s_stream_valid(stream_dst) && s_stream_valid(stream_src)) {
        ssize read = s_stream_read_try(stream_src, buffer, sizeof buffer);
        s_stream_write(stream_dst, buffer, read);
    }

    s_file_kill(&file_dst);
    s_file_kill(&file_src);
}


//
// publix
//

void e_io_offer_file_as_download(const char *file) {
    sfd_Options opt = create_options(file);
    const char *filename = sfd_save_dialog(&opt);
    if (filename) {
        s_log("Got save destination: '%s'\n", filename);
        clone_file(filename, file);
    } else {
        s_log("Download canceled\n");
    }
}

void e_io_ask_for_file_upload(const char *file, bool ascii, eIoFileUploadCallback callback, void *user_data) {
    sfd_Options opt = create_options(file);

    const char *filename = sfd_open_dialog(&opt);

    if (filename) {
        s_log("Got load file: '%s'\n", filename);
        clone_file(file, filename);
        callback(file, ascii, filename, user_data);
    } else {
        s_log("Upload canceled\n");
    }
}

#else //defined(PLATFORM_MSVC) || defined(PLATFORM_MINGW) || defined(PLATFORM_UNIX)
typedef int avoid_iso_c_empty_translation_unit_warning_;
#endif
