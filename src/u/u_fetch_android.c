#ifdef OPTION_FETCH
#ifdef PLATFORM_ANDROID

#define MAX_PARALLEL_FETCHES 128

#include <jni.h>
#include "s/str.h"
#include "u/fetch.h"
#include "s/file.h"
#include "e/window.h"

struct uFetch {
    bool succeeded;
    bool error;
    sAllocator_i a;
};

static struct {
    uFetch *fetches[MAX_PARALLEL_FETCHES];
} L;


static void succeeded_on_looped(void *user_data) {
    uFetch *self = user_data;
    self->succeeded = true;
}
static void failed_on_looped(void *user_data) {
    uFetch *self = user_data;
    self->error = true;
}

JNIEXPORT void JNICALL SOME_ANDROID_INTERFACE(uFetchFinished)(JNIEnv* env, jobject thisObject,
        jint succeeded, jint fetch_idx) {
    s_log("fetch succeeded");
    if(fetch_idx<0 || fetch_idx>=MAX_PARALLEL_FETCHES || !L.fetches[fetch_idx]) {
        s_log_error("invalid fetch?");
        return;
    }
    if(succeeded)
        e_window_run_once_on_main_looper(succeeded_on_looped, L.fetches[fetch_idx]);
    else
        e_window_run_once_on_main_looper(failed_on_looped, L.fetches[fetch_idx]);
}

uFetch *u_fetch_new_get_a(const char *url, sAllocator_i a) {
    int idx = -1;
    for(int i=0; i<MAX_PARALLEL_FETCHES; i++) {
        if(L.fetches[i] == NULL) {
            idx = i;
            break;
        }
    }
    if(idx<0) {
        s_log_error("too many parallel fetches!");
        return NULL;
    }
    
    uFetch *self = s_a_new0(a, uFetch, 1);
    self->a = a;
    L.fetches[idx] = self;


    // JNI CALL
    {
        JNIEnv* env = NULL;
        jobject activity = NULL;
        jclass clazz = NULL;
        jstring jurl = NULL;

        env = (JNIEnv*) SDL_AndroidGetJNIEnv();
        if(!env) {
            s_log_error("failed to get jni env");
            goto JNI_CLEAN_UP;
        }

        activity = (jobject) SDL_AndroidGetActivity();
        if(!activity) {
            s_log_error("failed to get activity");
            goto JNI_CLEAN_UP;
        }

        clazz = (*env)->GetObjectClass(env, activity);
        if(!clazz) {
            s_log_error("failed to get clazz");
            goto JNI_CLEAN_UP;
        }

        jmethodID method_id = (*env)->GetMethodID(env, clazz,
                                                  "u_fetch_request",
                                                  "(Ljava/lang/String;II)V");
        if(!method_id) {
            s_log_error("method not found");
            goto JNI_CLEAN_UP;
        }

        jurl = (*env)->NewStringUTF(env, url);
        (*env)->CallVoidMethod(env, activity, method_id, jurl, (jint) 0, (jint) idx);

        JNI_CLEAN_UP:
        if(env) {
            if(jurl) (*env)->DeleteLocalRef(env, jurl);
            if(activity) (*env)->DeleteLocalRef(env, activity);
            if(clazz) (*env)->DeleteLocalRef(env, clazz);
        }
    }

    return self;
}

uFetch *u_fetch_new_post_a(const char *url, sStr_s data, sAllocator_i a) {
    int idx = -1;
    for(int i=0; i<MAX_PARALLEL_FETCHES; i++) {
        if(L.fetches[i] == NULL) {
            idx = i;
            break;
        }
    }
    if(idx<0) {
        s_log_error("too many parallel fetches!");
        return NULL;
    }

    uFetch *self = s_a_new0(a, uFetch, 1);
    self->a = a;
    L.fetches[idx] = self;

    char post_file[128];
    snprintf(post_file, sizeof post_file, "u_fetch_post_%04d.bin", idx);
    s_file_write(post_file, data, false);

    // JNI CALL
    {
        JNIEnv* env = NULL;
        jobject activity = NULL;
        jclass clazz = NULL;
        jstring jurl = NULL;

        env = (JNIEnv*) SDL_AndroidGetJNIEnv();
        if(!env) {
            s_log_error("failed to get jni env");
            goto JNI_CLEAN_UP;
        }

        activity = (jobject) SDL_AndroidGetActivity();
        if(!activity) {
            s_log_error("failed to get activity");
            goto JNI_CLEAN_UP;
        }

        clazz = (*env)->GetObjectClass(env, activity);
        if(!clazz) {
            s_log_error("failed to get clazz");
            goto JNI_CLEAN_UP;
        }

        jmethodID method_id = (*env)->GetMethodID(env, clazz,
                                                  "u_fetch_request",
                                                  "(Ljava/lang/String;II)V");
        if(!method_id) {
            s_log_error("method not found");
            goto JNI_CLEAN_UP;
        }

        jurl = (*env)->NewStringUTF(env, url);
        (*env)->CallVoidMethod(env, activity, method_id, jurl, (jint) 1, (jint) idx);

        JNI_CLEAN_UP:
        if(env) {
            if(jurl) (*env)->DeleteLocalRef(env, jurl);
            if(activity) (*env)->DeleteLocalRef(env, activity);
            if(clazz) (*env)->DeleteLocalRef(env, clazz);
        }
    }

    return self;
}

void u_fetch_kill(uFetch **self_ptr) {
    uFetch *self = *self_ptr;
    if(!self)
        return;
    bool found = false;
    for(int i=0; i<MAX_PARALLEL_FETCHES; i++) {
        if(L.fetches[i] == self) {
            L.fetches[i] = NULL;
            found = true;
            break;
        }
    }
    if(!found)
        s_log_error("fetch not found?");

    s_a_free(self->a, self);
    *self_ptr = NULL;
}

sString *u_fetch_check_response(uFetch **self_ptr, bool *opt_error) {
    sString *ret = s_string_new_invalid();
    uFetch *self = *self_ptr;
    if(opt_error)
        *opt_error = false;
    if(!self)
        return ret;

    int idx = -1;
    for(int i=0; i<MAX_PARALLEL_FETCHES; i++) {
        if(self == L.fetches[i]) {
            idx = i;
            break;
        }
    }
    if(idx<0) {
        s_log_error("invalid fetch?");
        return NULL;
    }

    if(opt_error && self->error) {
        *opt_error = true;
    }
    if(self->succeeded) {
        char result_file[128];
        snprintf(result_file, sizeof result_file, "u_fetch_result_%04d.bin", idx);
        ret = s_file_read_a(result_file, false, self->a);
    }

    if(self->succeeded || self->error)
        u_fetch_kill(self_ptr);
    return ret;
}

#else //PLATFORM_ANDROID
typedef int avoid_iso_c_empty_translation_unit_warning_a_;
#endif
#else //OPTION_FETCH
typedef int avoid_iso_c_empty_translation_unit_warning_b_;
#endif
