#include "u/admob.h"
#include "e/core.h"

#ifdef PLATFORM_ANDROID

#include <jni.h>

static struct {
    u_admob_reward_fn callback;
    void *callback_user_data;
} L;

JNIEXPORT void JNICALL SOME_ANDROID_INTERFACE(uAdmobReward)(JNIEnv* env, jobject thisObject) {
    s_log("got an ad reward");
    if(!L.callback) {
        s_log_error("callback invalid!");
        return;
    }
    L.callback(L.callback_user_data);
}

//
// public
//


bool u_admob_ump_loaded() {
    bool loaded = false;

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
                                              "u_admob_ump_loaded",
                                              "()Z");

        if(!method_id) {
            s_log_error("method not found");
            goto JNI_CLEAN_UP;
        }

        jboolean jloaded = (*env)->CallBooleanMethod(env, activity, method_id);
        loaded = jloaded;

        JNI_CLEAN_UP:
        if(env) {
            if(activity) (*env)->DeleteLocalRef(env, activity);
            if(clazz) (*env)->DeleteLocalRef(env, clazz);
        }
    }

    return loaded;
}



void u_admob_ump_show() {
    // JNI CALL
    {
        JNIEnv* env = NULL;
        jobject activity = NULL;
        jclass clazz = NULL;

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
                                                  "u_admob_ump_show",
                                                  "()V");

        if(!method_id) {
            s_log_error("method not found");
            goto JNI_CLEAN_UP;
        }

        (*env)->CallVoidMethod(env, activity, method_id);

        JNI_CLEAN_UP:
        if(env) {
            if(activity) (*env)->DeleteLocalRef(env, activity);
            if(clazz) (*env)->DeleteLocalRef(env, clazz);
        }
    }
}

bool u_admob_reward_ad_loaded() {
    bool loaded = false;

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
                                              "u_admob_reward_ad_loaded",
                                              "()Z");

        if(!method_id) {
            s_log_error("method not found");
            goto JNI_CLEAN_UP;
        }

        jboolean jloaded = (*env)->CallBooleanMethod(env, activity, method_id);
        loaded = jloaded;

        JNI_CLEAN_UP:
        if(env) {
            if(activity) (*env)->DeleteLocalRef(env, activity);
            if(clazz) (*env)->DeleteLocalRef(env, clazz);
        }
    }

    return loaded;
}

void u_admob_reward_ad_show(u_admob_reward_fn callback, void *callback_user_data) {
    L.callback = callback;
    L.callback_user_data = callback_user_data;

    // JNI CALL
    {
        JNIEnv* env = NULL;
        jobject activity = NULL;
        jclass clazz = NULL;

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
                                                  "u_admob_reward_ad_show",
                                                  "()V");

        if(!method_id) {
            s_log_error("method not found");
            goto JNI_CLEAN_UP;
        }

        (*env)->CallVoidMethod(env, activity, method_id);

        JNI_CLEAN_UP:
        if(env) {
            if(activity) (*env)->DeleteLocalRef(env, activity);
            if(clazz) (*env)->DeleteLocalRef(env, clazz);
        }
    }
}

#else //PLATFORM_ANDROID

bool u_admob_ump_loaded() {
	return false;
}

void u_admob_ump_show() {
    s_log_warn("admob not available for this platform");
}

bool u_admob_reward_ad_loaded() {
    return false;
}

void u_admob_reward_ad_show(u_admob_reward_fn callback, void *callback_user_data) {
    s_log_warn("admob not available for this platform");
}
#endif
