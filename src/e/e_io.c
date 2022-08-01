#include "s/s_full.h"
#include "e/io.h"



// protected function
const char *e_window_get_title();


_Thread_local char e_io_savestate_file[64 + E_IO_SAVESTATE_MAX_FILENAME_LENGTH];


bool e_io_savestate_filename_valid(const char *filename) {
    sStr_s name = s_strc(filename);
    bool valid = s_str_count(name, '/') == 0 && name.size < E_IO_SAVESTATE_MAX_FILENAME_LENGTH;
    if (!valid)
        s_log_error("failed: filename not valid: %s", filename);
    return valid;
}


#ifdef PLATFORM_CXXDROID
// does not have a file dialog

void e_io_offer_file_as_download(const char *file) {
    // noop
}

void e_io_ask_for_file_upload(const char *file, bool ascii, eIoFileUploadCallback callback, void *user_data) {
    // noop
}

#endif //PLATFORM_CXXDROID


#ifndef PLATFORM_EMSCRIPTEN
// emscripten needs its own savestate system

// protected function, called by window new
void e_io_savestate_load() {
    // noop (just for web)
}

void e_io_savestate_save() {
    // noop (just for web)
}

const char *e_io_savestate_file_path(const char *filename) {
    if (!e_io_savestate_filename_valid(filename)) {
        return NULL;
    }
    snprintf(e_io_savestate_file, sizeof e_io_savestate_file, "savestate_%s", filename);
    return e_io_savestate_file;
}

sString *e_io_savestate_read(const char *filename, bool ascii) {
    if (!e_io_savestate_filename_valid(filename))
        return s_string_new_invalid();
    return s_file_read(
            e_io_savestate_file_path(filename),
            ascii);
}


bool e_io_savestate_write(const char *filename, sStr_s content, bool ascii) {
    if (!e_io_savestate_filename_valid(filename))
        return false;
    return s_file_write(
            e_io_savestate_file_path(filename),
            content, ascii);
}


bool e_io_savestate_append(const char *filename, sStr_s content, bool ascii) {
    if (!e_io_savestate_filename_valid(filename))
        return false;
    return s_file_append(
            e_io_savestate_file_path(filename),
            content, ascii);
}

#endif //PLATFORM_EMSCRIPTEN
