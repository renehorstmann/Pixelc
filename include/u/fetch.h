#ifndef U_FETCH_H
#define U_FETCH_H
#ifdef OPTION_FETCH

//
// GET and POST http requests
// uses libcurl, emscripten fetch api, or the android api
//

#include "s/s.h"
#include "s/string.h"

typedef struct uFetch uFetch;


// does an asynchronous GET call and returns the uFetch class handle
// if url is not a full http url (example.com instead of https://example.com), the relative path may be used!
// sAllocator version
uFetch *u_fetch_new_get_a(const char *url, sAllocator_i a);

// does an asynchronous GET call and returns the uFetch class handle
// if url is not a full http url (example.com instead of https://example.com), the relative path may be used!
static uFetch *u_fetch_new_get(const char *url) {
    return u_fetch_new_get_a(url, S_ALLOCATOR_DEFAULT);
}

// does an asynchronous POST call and returns the uFetch class handle
// data should be key=value string with an & as seperator
// if url is not a full http url (example.com instead of https://example.com), the relative path may be used!
// sAllocator version
uFetch *u_fetch_new_post_a(const char *url, sStr_s data, sAllocator_i a);

// does an asynchronous POST call and returns the uFetch class handle
// data should be key=value string with an & as seperator
// if url is not a full http url (example.com instead of https://example.com), the relative path may be used!
static uFetch *u_fetch_new_post(const char *url, sStr_s data) {
    return u_fetch_new_post_a(url, data, S_ALLOCATOR_DEFAULT);
}

// as always, its safe to pass a killed (*self_ptr==NULL) instance
void u_fetch_kill(uFetch **self_ptr);


// checks for a completed transmission or error
// returns a non invalid sString on success, containing the data
// opt_error will be set to true on error, if the fetch is completed (if not NULL) (otherwise false)
// will call u_fetch_kill, so you dont have to
// the returned sString is allocated with the uFetch a
sString *u_fetch_check_response(uFetch **self_ptr, bool *opt_error);


#endif //OPTION_FETCH
#endif //U_FETCH_H
