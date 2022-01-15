#include "rhc/log.h"
#include "rhc/str.h"
#include "rhc/string.h"
#include "rhc/file.h"
#include "e/io.h"


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
    log_info("e_io_idbfs_mount");
}

// protected, JS need its name as global
void e_io_idbfs_synced() {
    log_trace("e_io_idbfs_synced");
    L.synced = true;
}

static void idbfs_load() {
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
}


static void idbfs_save() {
    L.synced = false;
    
    // false = load file system from idbfs
    EM_ASM(
        e_io_idbfs_synced = false;
        FS.syncfs(false, function (err) {
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
}

void e_io_savestate_load() {
    idbfs_mount();
    idbfs_load();
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
    snprintf(name.s, sizeof name, "savestate/%s", filename);
    return name;
}


String e_io_savestate_read(const char *filename, bool ascii) {
    if(!savestate_filename_valid(filename))
        return string_new_invalid();
    idbfs_mount();
    idbfs_load();
    return file_read(
            e_io_savestate_file_path(filename).s,
            ascii);
}


bool e_io_savestate_write(const char *filename, Str_s content, bool ascii) {
    if(!savestate_filename_valid(filename))
        return false;
    idbfs_mount();
    bool ok = file_write(
            e_io_savestate_file_path(filename).s,
            content, ascii);
    idbfs_save();
    return ok;
}


bool e_io_savestate_append(const char *filename, Str_s content, bool ascii) {
    if(!savestate_filename_valid(filename))
        return false;
    idbfs_mount();
    idbfs_load();
    bool ok = file_append(
            e_io_savestate_file_path(filename).s,
            content, ascii);
    idbfs_save();
    return ok;
}

#else

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
