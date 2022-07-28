#include "s/s_full.h"
#include "e/io.h"


//
// private
//

static _Thread_local char L_savestate_file[64 + E_IO_SAVESTATE_MAX_FILENAME_LENGTH];

// protected function
const char *e_window_get_title();

static bool savestate_filename_valid(const char *filename) {
    sStr_s name = s_strc(filename);
    bool valid = s_str_count(name, '/') == 0 && name.size < E_IO_SAVESTATE_MAX_FILENAME_LENGTH;
    if (!valid)
        s_log_error("failed: filename not valid: %s", filename);
    return valid;
}


#ifdef PLATFORM_EMSCRIPTEN

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
}

// protected, JS need its name as global
void e_io_idbfs_synced() {
    s_log_trace("e_io_idbfs_synced");
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
    if(!savestate_filename_valid(filename)) {
        return NULL;
    }
    snprintf(L_savestate_file, sizeof L_savestate_file, "savestate/%s_%s", e_window_get_title(), filename);
    return L_savestate_file;
}


sString *e_io_savestate_read(const char *filename, bool ascii) {
    if(!savestate_filename_valid(filename))
        return s_string_new_invalid();
    return s_file_read(
            e_io_savestate_file_path(filename),
            ascii);
}


bool e_io_savestate_write(const char *filename, sStr_s content, bool ascii) {
    if(!savestate_filename_valid(filename))
        return false;
    bool ok = s_file_write(
            e_io_savestate_file_path(filename),
            content, ascii);
    idbfs_save();
    return ok;
}


bool e_io_savestate_append(const char *filename, sStr_s content, bool ascii) {
    if(!savestate_filename_valid(filename))
        return false;
    bool ok = s_file_append(
            e_io_savestate_file_path(filename),
            content, ascii);
    idbfs_save();
    return ok;
}

#else


#ifdef PLATFORM_ANDROID

#include <jni.h>
#include "e/window.h"

static struct {
    struct {
        char file[128];
        bool ascii;
        eIoFileUploadCallback cb;
        void *ud;
    } file_upload;
} L;

static void run_on_main_looper(void *user_data) {
    s_log("calling file uploaded callback...");
    if(L.file_upload.cb)
        L.file_upload.cb(L.file_upload.file, L.file_upload.ascii, L.file_upload.file, L.file_upload.ud);
}

JNIEXPORT void JNICALL SOME_ANDROID_INTERFACE(eIoOnFileUploaded)(JNIEnv* env, jobject thisObject) {
    s_log("file uploaded...");
    e_window_run_once_on_main_looper(run_on_main_looper, NULL);
}

void e_io_offer_file_as_download(const char *file) {
    s_log("download file: %s", file);

     // retrieve the JNI environment.
    JNIEnv* env = (JNIEnv*) SDL_AndroidGetJNIEnv();
    // retrieve the Java instance of the SDLActivity
    jobject activity = (jobject) SDL_AndroidGetActivity();
    // find the Java class of the activity. It should be SDLActivity or a subclass of it.
    jclass clazz = (*env)->GetObjectClass(env, activity);
    // find the identifier of the method to call
    jmethodID method_id = (*env)->GetMethodID(env, clazz, "e_io_offer_file_as_download", "(Ljava/lang/String;)V");
    // effectively call the Java method
    jstring jfile = (*env)->NewStringUTF(env, file);
    (*env)->CallVoidMethod(env, activity, method_id, jfile);
    // clean up the local references.
    (*env)->DeleteLocalRef(env, jfile);
    (*env)->DeleteLocalRef(env, activity);
    (*env)->DeleteLocalRef(env, clazz);
}

void e_io_ask_for_file_upload(const char *file, bool ascii, eIoFileUploadCallback callback, void *user_data) {
    s_log("select file: %s", file);

    if(strlen(file) >= sizeof L.file_upload.file || s_str_count(s_strc(file), '/') != 0) {
        s_log_error("e_io_ask_for_file_upload failed, file length to long, or got some \'/\'");
        return;
    }
    snprintf(L.file_upload.file, sizeof L.file_upload.file, "%s", file);
    L.file_upload.ascii = ascii;
    L.file_upload.cb = callback;
    L.file_upload.ud = user_data;

     // retrieve the JNI environment.
    JNIEnv* env = (JNIEnv*) SDL_AndroidGetJNIEnv();
    // retrieve the Java instance of the SDLActivity
    jobject activity = (jobject) SDL_AndroidGetActivity();
    // find the Java class of the activity. It should be SDLActivity or a subclass of it.
    jclass clazz = (*env)->GetObjectClass(env, activity);
    // find the identifier of the method to call
    jmethodID method_id = (*env)->GetMethodID(env, clazz, "e_io_ask_for_file_upload", "(Ljava/lang/String;)V");
    // effectively call the Java method
    jstring jfile = (*env)->NewStringUTF(env, file);
    (*env)->CallVoidMethod(env, activity, method_id, jfile);
    // clean up the local references.
    (*env)->DeleteLocalRef(env, jfile);
    (*env)->DeleteLocalRef(env, activity);
    (*env)->DeleteLocalRef(env, clazz);
}

#else

void e_io_offer_file_as_download(const char *file) {
    // noop
}

void e_io_ask_for_file_upload(const char *file, bool ascii, eIoFileUploadCallback callback, void *user_data) {
    // noop
}

#endif

// protected function, called by window new
void e_io_savestate_load() {
    // noop (just for web)
}

void e_io_savestate_save() {
    // noop (just for web)
}

const char *e_io_savestate_file_path(const char *filename) {
    if (!savestate_filename_valid(filename)) {
        return NULL;
    }
    snprintf(L_savestate_file, sizeof L_savestate_file, "savestate_%s", filename);
    return L_savestate_file;
}

sString *e_io_savestate_read(const char *filename, bool ascii) {
    if (!savestate_filename_valid(filename))
        return s_string_new_invalid();
    return s_file_read(
            e_io_savestate_file_path(filename),
            ascii);
}


bool e_io_savestate_write(const char *filename, sStr_s content, bool ascii) {
    if (!savestate_filename_valid(filename))
        return false;
    return s_file_write(
            e_io_savestate_file_path(filename),
            content, ascii);
}


bool e_io_savestate_append(const char *filename, sStr_s content, bool ascii) {
    if (!savestate_filename_valid(filename))
        return false;
    return s_file_append(
            e_io_savestate_file_path(filename),
            content, ascii);
}

#endif
