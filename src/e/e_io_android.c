#ifdef PLATFORM_ANDROID

#include <jni.h>
#include "s/s_full.h"
#include "e/io.h"
#include "e/window.h"


//
// private
//


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

//
// public
//

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

#else //PLATFORM_ANDROID
typedef int avoid_iso_c_empty_translation_unit_warning_;
#endif
