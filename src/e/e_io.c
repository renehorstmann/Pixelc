#include "rhc/log.h"
#include "rhc/str.h"
#include "rhc/string.h"
#include "rhc/file.h"
#include "e/io.h"


// protected function
const char *e_window_get_title();

static bool savestate_filename_valid(const char *filename) {
    Str_s name = strc(filename);
    bool valid = str_count(name, '/') == 0 && name.size < E_IO_SAVESTATE_MAX_FILENAME_LENGTH;
    if(!valid)
        log_error("e_io_savestate failed: filename not valid: %s", filename);
    return valid;
}


#ifdef __EMSCRIPTEN__

#include "emscripten.h"

static struct {
    bool mounted;
    bool synced;

    struct {
        char file[128];
        bool ascii;
        eIoFileUploadCallback cb;
        void *ud;
    } file_upload;
} L;

static void idbfs_mount() {
    if(L.mounted)
        return;
    EM_ASM( 
        FS.mkdir('/savestate'); 
        FS.mount(IDBFS, {}, '/savestate');
        e_io_idbfs_synced = false;
    );
    L.mounted = true;
    log_info("e_io_idbfs: mounted");

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
    log_info("e_io_idbfs: synced");
}

// protected, JS need its name as global
void e_io_idbfs_synced() {
    log_trace("e_io_idbfs_synced");
    L.synced = true;
}

static void idbfs_save() {
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
        log_info("file upload done for: %s, ascii: %i", file, ascii);
        L.file_upload.cb(L.file_upload.file, L.file_upload.ascii, user_file_name, L.file_upload.ud);
    } else {
        log_error("file upload done for: %s, ascii: %i, but invalid configuration"
                  "(wrong file, or ascii or callback NULL)", file, ascii);
    }
}

//
// public
//

void e_io_offer_file_as_download(const char *file) {
    char script[256];
    if(strlen(file) >= sizeof script) {
        log_error("e_io_offer_file_as_download failed, file length to long");
        return;
    }
    snprintf(script, sizeof script, "offer_file_as_download(\'%s\');", file);
    emscripten_run_script(script);
}

void e_io_ask_for_file_upload(const char *file, bool ascii, eIoFileUploadCallback callback, void *user_data) {
    if(strlen(file) >= sizeof L.file_upload.file || str_count(strc(file), '/') != 0) {
        log_error("e_io_ask_for_file_upload failed, file length to long, or got some \'/\'");
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

struct eIoSavestateString e_io_savestate_file_path(const char *filename) {
    struct eIoSavestateString name;
    if(!savestate_filename_valid(filename)) {
        memset(name.s, 0, sizeof name);
        return name;
    }
    snprintf(name.s, sizeof name, "savestate/%s_%s", e_window_get_title(), filename);
    return name;
}


String e_io_savestate_read(const char *filename, bool ascii) {
    if(!savestate_filename_valid(filename))
        return string_new_invalid();
    return file_read(
            e_io_savestate_file_path(filename).s,
            ascii);
}


bool e_io_savestate_write(const char *filename, Str_s content, bool ascii) {
    if(!savestate_filename_valid(filename))
        return false;
    bool ok = file_write(
            e_io_savestate_file_path(filename).s,
            content, ascii);
    idbfs_save();
    return ok;
}


bool e_io_savestate_append(const char *filename, Str_s content, bool ascii) {
    if(!savestate_filename_valid(filename))
        return false;
    bool ok = file_append(
            e_io_savestate_file_path(filename).s,
            content, ascii);
    idbfs_save();
    return ok;
}

#else

void e_io_offer_file_as_download(const char *file) {
    // noop (just for web)
}

void e_io_ask_for_file_upload(const char *file, bool ascii, eIoFileUploadCallback callback, void *user_data) {
    // noop (just for web)
}

// protected function, called by window new
void e_io_savestate_load() {
    // noop (just for web)
}

void e_io_savestate_save() {
    // noop (just for web)
}

struct eIoSavestateString e_io_savestate_file_path(const char *filename) {
    struct eIoSavestateString name;
    if(!savestate_filename_valid(filename)) {
        memset(&name, 0, sizeof name);
        return name;
    }
    snprintf(name.s, sizeof name, "savestate_%s", filename);
    return name;
}

String e_io_savestate_read(const char *filename, bool ascii) {
    if(!savestate_filename_valid(filename))
        return string_new_invalid();
    return file_read(
            e_io_savestate_file_path(filename).s, 
            ascii);
}


bool e_io_savestate_write(const char *filename, Str_s content, bool ascii) {
    if(!savestate_filename_valid(filename))
        return false;
    return file_write(
            e_io_savestate_file_path(filename).s,
            content, ascii);
}


bool e_io_savestate_append(const char *filename, Str_s content, bool ascii) {
    if(!savestate_filename_valid(filename))
        return false;
    return file_append(
            e_io_savestate_file_path(filename).s,
            content, ascii);
}

#endif
