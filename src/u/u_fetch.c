#ifdef OPTION_FETCH

#include "rhc/error.h"
#include "rhc/log.h"
#include "rhc/alloc.h"
#include "rhc/string.h"
#include "u/fetch.h"


#ifdef __EMSCRIPTEN__

#include <emscripten/fetch.h>

struct uFetch {
    emscripten_fetch_t *fetch;
    
    String data;
    bool error;
    
    bool fetch_completed;
};

static void ems_fetch_success(emscripten_fetch_t *fetch) {
    log_trace("u_fetch succeded with http code: %i", fetch->status);
    uFetch *self = fetch->userData;
    assume(self->fetch == fetch, "wtf");

    self->data.size = 0;
    string_append(&self->data, (Str_s) {(char*) fetch->data, fetch->numBytes});
    self->error = false;
    
    emscripten_fetch_close(self->fetch);
    self->fetch = NULL;
    
    if(self->fetch_completed)
        log_warn("u_fetch was completed, but overridden");
    self->fetch_completed = true;
}

static void ems_fetch_error(emscripten_fetch_t *fetch) {
    log_warn("u_fetch failed with http code: %i", fetch->status);
    uFetch *self = fetch->userData;
    assume(self->fetch == fetch, "wtf");
    
    string_kill(&self->data);
    self->error = true;
    
    emscripten_fetch_close(self->fetch);
    self->fetch = NULL;
    
    if(self->fetch_completed)
        log_warn("u_fetch was completed, but overridden");
    self->fetch_completed = true;
}


uFetch *u_fetch_new_get(const char *url) {
    log_trace("u_fetch_new_get: %s", url);
    
    uFetch *self = rhc_calloc(sizeof *self);
    self->data = string_new(128);
    
    emscripten_fetch_attr_t attr;
    
    emscripten_fetch_attr_init(&attr); 
    attr.userData = self;
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY; 
    attr.onsuccess = ems_fetch_success; 
    attr.onerror = ems_fetch_error; 
    strcpy(attr.requestMethod, "GET"); 
    
    self->fetch = emscripten_fetch(&attr, url);
    assume(self->fetch->userData == self, "should include user_data");
    
    return self;
}

uFetch *u_fetch_new_post(const char *url, Str_s data) {
    log_trace("u_fetch_new_post: %s", url);
    
    uFetch *self = rhc_calloc(sizeof *self);
    self->data = string_new_clone(data);
   
    emscripten_fetch_attr_t attr;
    
    emscripten_fetch_attr_init(&attr); 
    attr.userData = self;
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY; 
    attr.onsuccess = ems_fetch_success; 
    attr.onerror = ems_fetch_error; 
    strcpy(attr.requestMethod, "POST"); 
    attr.requestData = self->data.data;
    attr.requestDataSize = self->data.size;
    attr.requestHeaders = (const char *[]) {"Content-Type", "text/plain", NULL};
    self->fetch = emscripten_fetch(&attr, url);
    assume(self->fetch->userData == self, "should include user_data");
    
    return self;
}

void u_fetch_kill(uFetch **self_ptr) {
    uFetch *self = *self_ptr;
    if(!self)
        return;
    if(self->fetch) {
        log_warn("u_fetch_kill called before fetch was finished?");
        emscripten_fetch_close(self->fetch);
    }
    string_kill(&self->data);
    rhc_free(self);
    *self_ptr = NULL;
}


String u_fetch_check_response(uFetch **self_ptr, bool *opt_error) {
    uFetch *self = *self_ptr;
    if(opt_error)
        *opt_error = false;
    if(!self)
        return string_new_invalid();
    
    if(!self->fetch_completed)
        return string_new_invalid();
    
    if(opt_error)
        *opt_error = self->error;
    // move and kill
    String ret = self->data;
    self->data = string_new_invalid();

    u_fetch_kill(self_ptr);
    return ret;
}

#else

#include <SDL2/SDL.h>
#include <curl/curl.h>

struct uFetch {
    SDL_mutex *lock;
    
    String url;
    String data;
    bool error;
    
    bool fetch_completed;
};

static size_t response_writer(void *ptr, size_t size, size_t nmemb, void *ud) {
	uFetch *self = ud;
	size_t full_size = size * nmemb;
	string_append(&self->data, (Str_s) {ptr, full_size});
	return full_size;
}

static int request_thread(void *ud) {
    uFetch *self = ud;
    
    CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, self->url.data);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, self);
	
	String post_data = string_new_invalid();
	if(!str_empty(self->data.str)) {
	    // POST
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: text/plain");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	    // move data
	    post_data = self->data;
	    self->data = string_new_invalid();
	    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_data.size);
	    
	}
	self->data = string_new(128);

    CURLcode perform_res = curl_easy_perform(curl);

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    SDL_LockMutex(self->lock);
    {
        self->error = perform_res != CURLE_OK || http_code != 200;
        self->fetch_completed = true;
        if (self->data.size == 0 || self->error)
            string_kill(&self->data);
    }
	SDL_UnlockMutex(self->lock);
	
	log_trace("u_fetch succeded, error: %i", self->error);
	curl_easy_cleanup(curl);
	string_kill(&post_data);
	
	return 0;
}

uFetch *u_fetch_new_get(const char *url) {
    log_trace("u_fetch_new_get: %s", url);
    
    uFetch *self = rhc_calloc(sizeof *self);
    
    self->url = string_new_clone(strc(url));
    self->data = string_new_invalid();
    
    self->lock = SDL_CreateMutex();
    SDL_CreateThread(request_thread, "u_fetch_request", self);
    
    return self;
}

uFetch *u_fetch_new_post(const char *url, Str_s data) {
    log_trace("u_fetch_new_post: %s", url);
    
    uFetch *self = rhc_calloc(sizeof *self);
    
    self->url = string_new_clone(strc(url));
    self->data = string_new_clone(data);
    
    self->lock = SDL_CreateMutex();
    SDL_CreateThread(request_thread, "u_fetch_request", self);
    
    return self;
}


void u_fetch_kill(uFetch **self_ptr) {
    uFetch *self = *self_ptr;
    if(!self)
        return;
    string_kill(&self->url);
    SDL_DestroyMutex(self->lock);
    rhc_free(self);
    *self_ptr = NULL;
}


String u_fetch_check_response(uFetch **self_ptr, bool *opt_error) {
    String ret = string_new_invalid();
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
            self->data = string_new_invalid();
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
