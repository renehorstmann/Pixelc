#ifdef OPTION_FETCH
#if !defined(PLATFORM_EMSCRIPTEN) && !defined(PLATFORM_ANDROID)

#include <SDL2/SDL.h>
#include <curl/curl.h>
#include "s/str.h"
#include "u/fetch.h"

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


#endif //!defined(PLATFORM_EMSCRIPTEN) && !defined(PLATFORM_ANDROID)
#else //OPTION_FETCH
typedef int avoid_iso_c_empty_translation_unit_warning_;
#endif
