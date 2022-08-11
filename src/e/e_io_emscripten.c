#ifdef PLATFORM_EMSCRIPTEN

#include "s/s_full.h"
#include "e/window.h"
#include "e/io.h"
#include "emscripten.h"


#define SYNC_TIMEOUT_MS 200

// protected function
const char *e_window_get_title();

//
// private
//


static struct {
    bool mounted;
    bool synced;
    su32 synced_timeout;

    struct {
        char file[128];
        bool ascii;
        eIoFileUploadCallback cb;
        void *ud;
    } file_upload;
} L;

static void idbfs_mount() {
    s_log_info("idbfs_mount");

    if(L.mounted)
        return;
    EM_ASM( 
        FS.mkdir('/savestate'); 
        FS.mount(IDBFS, {}, '/savestate');
        e_io_idbfs_synced = false;
    );
    L.mounted = true;
    s_log("e_io_idbfs: mounted");

    L.synced = false;

    // true = load file system from idbfs
    EM_ASM(
        e_io_idbfs_synced = false;
        FS.syncfs(true, function (err) {
            assert(!err);
            e_io_idbfs_synced = true;
        });
    );
    // sleep a ms until synced to get a synchronous call
    while(!L.synced) {
        EM_ASM(
            if(e_io_idbfs_synced) { ccall('e_io_idbfs_synced', 'v'); }
        );
        emscripten_sleep(1);
    }
    s_log("e_io_idbfs: synced");

    L.synced_timeout = e_window.time_ms + SYNC_TIMEOUT_MS;
}

// protected, JS need its name as global
void e_io_idbfs_synced() {
    s_log_trace("e_io_idbfs_synced");
    L.synced = true;
}

static void idbfs_save() {
    if(L.synced_timeout > e_window.time_ms) {
        s_log_info("ignoring e_io save sync (timeout: %i ms)", L.synced_timeout - e_window.time_ms);
        return;
    }
    L.synced_timeout = e_window.time_ms + SYNC_TIMEOUT_MS;

    s_log_info("idbfs_save");
    // false = save file system from idbfs
    EM_ASM(
        e_io_idbfs_synced = false;
        FS.syncfs(false, function (err) {
            assert(!err);
        });
    );
}


// protected function
void e_io_file_upload_done(const char *file, bool ascii, const char *user_file_name) {
    if(strcmp(file, L.file_upload.file) == 0 && ascii == L.file_upload.ascii && L.file_upload.cb) {
        s_log("file upload done for: %s, ascii: %i", file, ascii);
        L.file_upload.cb(L.file_upload.file, L.file_upload.ascii, user_file_name, L.file_upload.ud);
    } else {
        s_log_error("file upload done for: %s, ascii: %i, but invalid configuration"
                  "(wrong file, or ascii or callback NULL)", file, ascii);
    }
}

//
// public
//

void e_io_offer_file_as_download(const char *file) {
    char script[256];
    if(strlen(file) >= sizeof script) {
        s_log_error("e_io_offer_file_as_download failed, file length to long");
        return;
    }
    snprintf(script, sizeof script, "offer_file_as_download(\'%s\');", file);
    emscripten_run_script(script);
}

void e_io_ask_for_file_upload(const char *file, bool ascii, eIoFileUploadCallback callback, void *user_data) {
    if(strlen(file) >= sizeof L.file_upload.file || s_str_count(s_strc(file), '/') != 0) {
        s_log_error("e_io_ask_for_file_upload failed, file length to long, or got some \'/\'");
        return;
    }
    snprintf(L.file_upload.file, sizeof L.file_upload.file, "%s", file);
    L.file_upload.ascii = ascii;
    L.file_upload.cb = callback;
    L.file_upload.ud = user_data;

    char script[256];
    if(ascii)
        snprintf(script, sizeof script, "ask_for_file_upload(\'%s\', true);", file);
    else
        snprintf(script, sizeof script, "ask_for_file_upload(\'%s\', false);", file);
    emscripten_run_script(script);
}


// protected function, called by window new
void e_io_savestate_load() {
    idbfs_mount();
}

void e_io_savestate_save() {
    idbfs_save();
}

const char *e_io_savestate_file_path(const char *filename) {
    if(!e_io_savestate_filename_valid(filename)) {
        return NULL;
    }
    snprintf(e_io_savestate_file, sizeof e_io_savestate_file, "savestate/%s_%s", e_window_get_title(), filename);
    return e_io_savestate_file;
}


sString *e_io_savestate_read(const char *filename, bool ascii) {
    if(!e_io_savestate_filename_valid(filename))
        return s_string_new_invalid();
    return s_file_read(
            e_io_savestate_file_path(filename),
            ascii);
}


bool e_io_savestate_write(const char *filename, sStr_s content, bool ascii) {
    if(!e_io_savestate_filename_valid(filename))
        return false;
    bool ok = s_file_write(
            e_io_savestate_file_path(filename),
            content, ascii);
    idbfs_save();
    return ok;
}


bool e_io_savestate_append(const char *filename, sStr_s content, bool ascii) {
    if(!e_io_savestate_filename_valid(filename))
        return false;
    bool ok = s_file_append(
            e_io_savestate_file_path(filename),
            content, ascii);
    idbfs_save();
    return ok;
}

#else //PLATFORM_EMSCRPITEN
typedef int avoid_iso_c_empty_translation_unit_warning_;
#endif
