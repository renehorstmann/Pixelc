#ifdef OPTION_FETCH

#include "s/str.h"
#include "u/fetch.h"


#ifdef PLATFORM_EMSCRIPTEN

#include <emscripten/fetch.h>

struct uFetch {
    emscripten_fetch_t *fetch;
    
    sString *data;
    bool error;
    
    bool fetch_completed;

    sAllocator_i a;
};

static void ems_fetch_success(emscripten_fetch_t *fetch) {
    s_log_trace("succeded with http code: %i", fetch->status);
    uFetch *self = fetch->userData;
    s_assume(self->fetch == fetch, "wtf");

    self->data->size = 0;
    s_string_append(self->data, (sStr_s) {(char*) fetch->data, fetch->numBytes});
    self->error = false;

    s_log("fetched: %i %s", (int) fetch->numBytes, fetch->data);
    
    emscripten_fetch_close(self->fetch);
    self->fetch = NULL;
    
    if(self->fetch_completed)
        s_log_warn("was completed, but overridden");
    self->fetch_completed = true;
}

static void ems_fetch_error(emscripten_fetch_t *fetch) {
    s_log_warn("failed with http code: %i", fetch->status);
    uFetch *self = fetch->userData;
    s_assume(self->fetch == fetch, "wtf");
    
    s_string_kill(&self->data);
    self->error = true;
    
    emscripten_fetch_close(self->fetch);
    self->fetch = NULL;
    
    if(self->fetch_completed)
        s_log_warn("was completed, but overridden");
    self->fetch_completed = true;
}


uFetch *u_fetch_new_get_a(const char *url, sAllocator_i a) {
    s_log_trace("get: %s", url);
    
    uFetch *self = s_a_malloc0(a, sizeof *self);
    self->a = a;
    self->data = s_string_new_a(128, a);
    
    emscripten_fetch_attr_t attr;
    
    emscripten_fetch_attr_init(&attr); 
    attr.userData = self;
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY; 
    attr.onsuccess = ems_fetch_success; 
    attr.onerror = ems_fetch_error; 
    strcpy(attr.requestMethod, "GET"); 
    
    self->fetch = emscripten_fetch(&attr, url);
    s_assume(self->fetch->userData == self, "should include user_data");
    
    return self;
}

uFetch *u_fetch_new_post_a(const char *url, sStr_s data, sAllocator_i a) {
    s_log_trace("post: %s", url);
    
    uFetch *self = s_a_malloc0(a, sizeof *self);
    self->a = a;
    self->data = s_string_new_clone_a(data, a);
   
    emscripten_fetch_attr_t attr;
    
    emscripten_fetch_attr_init(&attr); 
    attr.userData = self;
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY; 
    attr.onsuccess = ems_fetch_success; 
    attr.onerror = ems_fetch_error; 
    strcpy(attr.requestMethod, "POST"); 
    attr.requestData = self->data->data;
    attr.requestDataSize = self->data->size;
    attr.requestHeaders = (const char *[]) {"Content-Type", "text/plain", NULL};
    self->fetch = emscripten_fetch(&attr, url);
    s_assume(self->fetch->userData == self, "should include user_data");
    
    return self;
}

void u_fetch_kill(uFetch **self_ptr) {
    uFetch *self = *self_ptr;
    if(!self)
        return;
    if(self->fetch) {
        s_log_warn("kill called before fetch was finished?");
        emscripten_fetch_close(self->fetch);
    }
    s_string_kill(&self->data);
    s_a_free(self->a, self);
    *self_ptr = NULL;
}


sString *u_fetch_check_response(uFetch **self_ptr, bool *opt_error) {
    uFetch *self = *self_ptr;
    if(opt_error)
        *opt_error = false;
    if(!self)
        return s_string_new_invalid();
    
    if(!self->fetch_completed)
        return s_string_new_invalid();
    
    if(opt_error)
        *opt_error = self->error;
    // move and kill
    sString *ret = self->data;
    self->data = s_string_new_invalid();

    u_fetch_kill(self_ptr);
    return ret;
}

#elif defined(PLATFORM_ANDROID)

#include <jni.h>
#include "s/file.h"
#include "e/window.h"

struct uFetch {
    bool succeeded;
    bool error;
    sAllocator_i a;
};

static struct {
    bool running;
} L;


static void succeeded_on_looped(void *user_data) {
    uFetch *self = user_data;
    self->succeeded = true;
}

JNIEXPORT void JNICALL SOME_ANDROID_INTERFACE(uFetchSucceeded)(JNIEnv* env, jobject thisObject, jlong fetch_ptr) {
    s_log("fetch succeeded");
    e_window_run_once_on_main_looper(succeeded_on_looped, (void*) fetch_ptr);
}

static void failed_on_looped(void *user_data) {
    uFetch *self = user_data;
    self->error = true;
}

JNIEXPORT void JNICALL SOME_ANDROID_INTERFACE(uFetchFailed)(JNIEnv* env, jobject thisObject, jlong fetch_ptr) {
    s_log("fetch failed");
    e_window_run_once_on_main_looper(failed_on_looped, (void*) fetch_ptr);
}

uFetch *u_fetch_new_get_a(const char *url, sAllocator_i a) {
    if(L.running) {
        s_log_warn("multi fetch not yet supported");
    }
    L.running = true;
    
    uFetch *self = s_a_new0(a, uFetch, 1);
    self->a = a;

    // retrieve the JNI environment.
    JNIEnv* env = (JNIEnv*) SDL_AndroidGetJNIEnv();
    // retrieve the Java instance of the SDLActivity
    jobject activity = (jobject) SDL_AndroidGetActivity();
    // find the Java class of the activity. It should be SDLActivity or a subclass of it.
    jclass clazz = (*env)->GetObjectClass(env, activity);
    // find the identifier of the method to call
    jmethodID method_id = (*env)->GetMethodID(env, clazz, "u_fetch_request", "(Ljava/lang/String;IJ)V");
    // effectively call the Java method
    jstring jurl = (*env)->NewStringUTF(env, url);
    (*env)->CallVoidMethod(env, activity, method_id, jurl, (jint) 0, (jlong) self);
    // clean up the local references.
    (*env)->DeleteLocalRef(env, jurl);
    (*env)->DeleteLocalRef(env, activity);
    (*env)->DeleteLocalRef(env, clazz);

    return self;
}

uFetch *u_fetch_new_post_a(const char *url, sStr_s data, sAllocator_i a) {
    if(L.running) {
        s_log_warn("multi fetch not yet supported");
    }
    L.running = true;
    
    uFetch *self = s_a_new0(a, uFetch, 1);
    self->a = a;

    s_file_write("u_fetch_post.bin", data, false);

    // retrieve the JNI environment.
    JNIEnv* env = (JNIEnv*) SDL_AndroidGetJNIEnv();
    // retrieve the Java instance of the SDLActivity
    jobject activity = (jobject) SDL_AndroidGetActivity();
    // find the Java class of the activity. It should be SDLActivity or a subclass of it.
    jclass clazz = (*env)->GetObjectClass(env, activity);
    // find the identifier of the method to call
    jmethodID method_id = (*env)->GetMethodID(env, clazz, "u_fetch_request", "(Ljava/lang/String;IJ)V");
    // effectively call the Java method
    jstring jurl = (*env)->NewStringUTF(env, url);
    (*env)->CallVoidMethod(env, activity, method_id, jurl, (jint) 1, (jlong) self);
    // clean up the local references.
    (*env)->DeleteLocalRef(env, jurl);
    (*env)->DeleteLocalRef(env, activity);
    (*env)->DeleteLocalRef(env, clazz);

    return self;
}

void u_fetch_kill(uFetch **self_ptr) {
    uFetch *self = *self_ptr;
    if(!self)
        return;
    s_a_free(self->a, self);
    *self_ptr = NULL;
    L.running = false;
}

sString *u_fetch_check_response(uFetch **self_ptr, bool *opt_error) {
    sString *ret = s_string_new_invalid();
    uFetch *self = *self_ptr;
    if(opt_error)
        *opt_error = false;
    if(!self)
        return ret;

    if(opt_error && self->error) {
        *opt_error = true;
    }
    if(self->succeeded) {
        ret = s_file_read("u_fetch_result.bin", false);
    }

    if(self->succeeded || self->error)
        u_fetch_kill(self_ptr);
    return ret;
}


#else

#include <SDL2/SDL.h>
#include <curl/curl.h>

struct uFetch {
    SDL_mutex *lock;
    
    sString *url;
    sString *data;
    bool error;
    
    bool fetch_completed;

    sAllocator_i a;
};

static ssize response_writer(void *ptr, ssize size, ssize nmemb, void *ud) {
    uFetch *self = ud;
    ssize full_size = size * nmemb;
    s_string_append(self->data, (sStr_s) {ptr, full_size});
    return full_size;
}

static int request_thread(void *ud) {
    uFetch *self = ud;

    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, self->url->data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_writer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, self);

    sString *post_data = s_string_new_invalid();
    if(!s_str_empty(s_string_get_str(self->data))) {
        // POST
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: text/plain");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // move data
        post_data = self->data;
        self->data = s_string_new_invalid();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data->data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_data->size);

    }
    self->data = s_string_new_a(128, self->a);

    CURLcode perform_res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    SDL_LockMutex(self->lock);
    {
        self->error = perform_res != CURLE_OK || http_code != 200;
        self->fetch_completed = true;
        if (self->data->size == 0 || self->error)
            s_string_kill(&self->data);
    }
    SDL_UnlockMutex(self->lock);

    s_log_trace("succeded, error: %i", self->error);
    curl_easy_cleanup(curl);
    s_string_kill(&post_data);

    return 0;
}

uFetch *u_fetch_new_get_a(const char *url, sAllocator_i a) {
    s_log_trace("get: %s", url);
    
    uFetch *self = s_a_malloc0(a, sizeof *self);
    self->a = a;
    
    self->url = s_string_new_clone_a(s_strc(url), a);
    self->data = s_string_new_invalid();
    
    self->lock = SDL_CreateMutex();
    SDL_CreateThread(request_thread, "u_fetch_request", self);
    
    return self;
}

uFetch *u_fetch_new_post_a(const char *url, sStr_s data, sAllocator_i a) {
    s_log_trace("post: %s", url);
    
    uFetch *self = s_a_malloc0(a, sizeof *self);
    self->a = a;
    
    self->url = s_string_new_clone_a(s_strc(url), a);
    self->data = s_string_new_clone_a(data, a);
    
    self->lock = SDL_CreateMutex();
    SDL_CreateThread(request_thread, "u_fetch_request", self);
    
    return self;
}


void u_fetch_kill(uFetch **self_ptr) {
    uFetch *self = *self_ptr;
    if(!self)
        return;
    s_string_kill(&self->url);
    SDL_DestroyMutex(self->lock);
    s_a_free(self->a,self);
    *self_ptr = NULL;
}


sString *u_fetch_check_response(uFetch **self_ptr, bool *opt_error) {
    sString *ret = s_string_new_invalid();
    uFetch *self = *self_ptr;
    if(opt_error)
        *opt_error = false;
    if(!self)
        return ret;
        
    SDL_LockMutex(self->lock);
    {
        if (self->fetch_completed) {
            // move
            ret = self->data;
            self->data = s_string_new_invalid();
            if (opt_error)
                *opt_error = self->error;
        }
    }
    SDL_UnlockMutex(self->lock);
    // kill on success
    if(self->fetch_completed)
        u_fetch_kill(self_ptr);
    return ret;
}


#endif
#else //OPTION_FETCH
typedef int avoid_iso_c_empty_translation_unit_warning_;
#endif
