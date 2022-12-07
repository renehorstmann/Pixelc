#include "u/billing.h"
#include "e/core.h"

#ifdef PLATFORM_ANDROID

#include <jni.h>

static struct {
    u_billing_purchased_fn callback;
    void *callback_user_data;
} L;

JNIEXPORT bool JNICALL SOME_ANDROID_INTERFACE(uBillingPurchased)(JNIEnv* env, jobject thisObject, jint idx) {
    s_log("got a purchase!");
    if(!L.callback) {
        s_log_error("callback invalid!");
        return false;
    }
    return L.callback(idx, L.callback_user_data);
}

//
// public
//

bool u_billing_loaded() {
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
                                              "u_billing_loaded",
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

void u_billing_buy(int idx, u_billing_purchased_fn callback, void *callback_user_data) {
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
                                                  "u_billing_buy",
                                                  "(I)V");

        if(!method_id) {
            s_log_error("method not found");
            goto JNI_CLEAN_UP;
        }

        (*env)->CallVoidMethod(env, activity, method_id, (jint) idx);

        JNI_CLEAN_UP:
        if(env) {
            if(activity) (*env)->DeleteLocalRef(env, activity);
            if(clazz) (*env)->DeleteLocalRef(env, clazz);
        }
    }
}

#else //PLATFORM_ANDROID

bool u_billing_loaded() {
    return false;
}

void u_billing_buy(int idx, u_billing_purchased_fn callback, void *callback_user_data) {
    s_log_warn("billing not available for this platform");
}
#endif
