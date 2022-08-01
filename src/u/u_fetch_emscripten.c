#ifdef OPTION_FETCH
#ifdef PLATFORM_EMSCRIPTEN

#include "s/str.h"
#include "u/fetch.h"
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

#endif //PLATFORM_EMSCRIPTEN
#else //OPTION_FETCH
typedef int avoid_iso_c_empty_translation_unit_warning_;
#endif
