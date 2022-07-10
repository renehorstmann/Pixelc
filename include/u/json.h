#ifndef U_JSON_H
#define U_JSON_H

// load and save json files from strings or files

#include "s/s.h"
#include "s/string.h"

typedef struct uJson uJson;


// possible json item types, see u_json_get_type
enum u_json_types {
    U_JSON_TYPE_NULL,
    U_JSON_TYPE_BOOL,
    U_JSON_TYPE_NUM,
    U_JSON_TYPE_STRING,
    U_JSON_TYPE_ARRAY,
    U_JSON_TYPE_OBJECT,
    U_JSON_NUM_TYPES
};


// some options for json saves
struct uJson_Options {
    bool array_single_line;
};


// creates a new empty root json element (object type)
// sAllocator version
uJson *u_json_new_empty_a(sAllocator_i a);

// creates a new empty root json element (object type)
static uJson *u_json_new_empty() {
    return u_json_new_empty_a(S_ALLOCATOR_DEFAULT);
}


// parses a json str into the uJson hierarchy
// returns u_json_new_empty on failure (check with u_json_empty)
// sAllocator version
uJson *u_json_new_str_a(sStr_s s_str_to_parse, sAllocator_i a);

// parses a json str into the uJson hierarchy
// returns u_json_new_empty on failure (check with u_json_empty)
static uJson *u_json_new_str(sStr_s s_str_to_parse) {
    return u_json_new_str_a(s_str_to_parse, S_ALLOCATOR_DEFAULT);
}

// loads a json file
// calls u_json_new_empty
// returns u_json_new_empty on failure (check with u_json_empty)
// sAllocator version
uJson *u_json_new_file_a(const char *file, sAllocator_i a);

// loads a json file
// calls u_json_new_empty
// returns u_json_new_empty on failure (check with u_json_empty)
static uJson *u_json_new_file(const char *file) {
    return u_json_new_file_a(file, S_ALLOCATOR_DEFAULT);
}


// kills self and recursivly all childs
void u_json_kill(uJson **self_ptr);

// returns true if self is an empty array or object (u_json_new_empty would return true)
//    also returns false if NULL is passed
bool u_json_empty(const uJson *self);


// creates a string from the uJson hierarchy (recursivly)
// custom a for the result string
sString *u_json_to_string_a(const uJson *self, sAllocator_i a, struct uJson_Options *opt_options);

// creates a string from the uJson hierarchy (recursivly)
// uses uJsons a
sString *u_json_to_string(const uJson *self, struct uJson_Options *opt_options);

// saves to a json file
// calls u_json_to_string
bool u_json_save_file(const uJson *self, const char *file, struct uJson_Options *opt_options);


// returns the type of a json item
enum u_json_types u_json_get_type(const uJson *self);

// returns the name of a json item, if available (parent is an object), NULL otherwise
const char *u_json_get_name(const uJson *self);

// returns a bool containing the json value, or NULL on missmatch
const bool *u_json_get_bool(const uJson *self);

// returns a str containing the num, or NULL on missmatch
const char *u_json_get_num(const uJson *self);

// returns a str, or NULL on missmatch
const char *u_json_get_string(const uJson *self);

// returns the array or object elements size, or 0 on a mismatch
int u_json_get_size(const uJson *self);

// returns an writeable item of the array or object element, or NULL on missmatch
uJson *u_json_get_id(const uJson *self, int id);

// returns an writeable object element by name, or NULL on missmatch
uJson *u_json_get_object(const uJson *self, const char *name);


// calls u_json_get_num an parses into out_data, returns out_data on success, otherwise NULL
int *u_json_get_int(const uJson *self, int *out_data);

// calls u_json_get_num an parses into out_data, returns out_data on success, otherwise NULL
float *u_json_get_float(const uJson *self, float *out_data);

// calls u_json_get_num an parses into out_data, returns out_data on success, otherwise NULL
double *u_json_get_double(const uJson *self, double *out_data);


// resets the name of a child (self) in an object (parent)
void u_json_set_name(uJson *self, const char *name);

// resets the value of a bool item
// returns false on type missmatch
bool u_json_set_bool(uJson *self, bool value);


// resets the value of a number item
// returns false on type missmatch
bool u_json_set_num(uJson *self, const char *value);

// resets the string of a string item
// returns false on type missmatch
bool u_json_set_string(uJson *self, const char *value);

// resets the value of a number item
// calls u_json_set_num
// returns false on type missmatch
bool u_json_set_int(uJson *self, int value);

// resets the value of a number item
// calls u_json_set_num
// returns false on type missmatch
bool u_json_set_float(uJson *self, float value);

// resets the value of a number item
// calls u_json_set_num
// returns false on type missmatch
bool u_json_set_double(uJson *self, double value);


// append a new json "null" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// returns the appended item, or NULL on missmatch
uJson *u_json_append_null(uJson *self, const char *name);

// append a new json "bool" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// returns the appended item, or NULL on missmatch
uJson *u_json_append_bool(uJson *self, const char *name, bool value);

// append a new json "num" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// value should contain the string representation of a number (will be checked with strtod)
// returns the appended item, or NULL on missmatch
uJson *u_json_append_num(uJson *self, const char *name, const char *value);

// append a new json "bool" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// returns the appended item, or NULL on missmatch
uJson *u_json_append_string(uJson *self, const char *name, const char *value);

// append a new json "array" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// returns the appended item, or NULL on missmatch
uJson *u_json_append_array(uJson *self, const char *name);

// append a new json "object" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// returns the appended item, or NULL on missmatch
uJson *u_json_append_object(uJson *self, const char *name);

// append a new json "num" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// calls u_json_append_num
// returns the appended item, or NULL on missmatch
uJson *u_json_append_int(uJson *self, const char *name, int value);

// append a new json "num" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// calls u_json_append_num
// returns the appended item, or NULL on missmatch
uJson *u_json_append_float(uJson *self, const char *name, float value);

// append a new json "num" item to an json array or object
// if self is an array, name is ignored
// if self is an object and already contains the element name,
//     the old will be killed and replaced
// calls u_json_append_num
// returns the appended item, or NULL on missmatch
uJson *u_json_append_double(uJson *self, const char *name, double value);




// removes an element out of an array or object
// returns true on success
bool u_json_remove_id(uJson *self, int id);

// removes element by name out of an object
// returns the amount of successfully removed items
int u_json_remove_objects(uJson *self, const char *name);


//
// getter shortcuts
//

// shortcut to get a bool by name from an object
static const bool *u_json_get_object_bool(const uJson *self, const char *name) {
    return u_json_get_bool(u_json_get_object(self, name));
}

// shortcut to get a num by name from an object
static const char *u_json_get_object_num(const uJson *self, const char *name) {
    return u_json_get_num(u_json_get_object(self, name));
}

// shortcut to get a string by name from an object
static const char *u_json_get_object_string(const uJson *self, const char *name) {
    return u_json_get_string(u_json_get_object(self, name));
}

// shortcut to get an int by name from an object
static int *u_json_get_object_int(const uJson *self, const char *name, int *out_data) {
    return u_json_get_int(u_json_get_object(self, name), out_data);
}

// shortcut to get a float by name from an object
static float *u_json_get_object_float(const uJson *self, const char *name, float *out_data) {
    return u_json_get_float(u_json_get_object(self, name), out_data);
}

// shortcut to get a double by name from an object
static double *u_json_get_object_double(const uJson *self, const char *name, double *out_data) {
    return u_json_get_double(u_json_get_object(self, name), out_data);
}


// shortcut to get a bool by id from an array or object
static const bool *u_json_get_id_bool(const uJson *self, int id) {
    return u_json_get_bool(u_json_get_id(self, id));
}

// shortcut to get a num by id from an array or object
static const char *u_json_get_id_num(const uJson *self, int id) {
    return u_json_get_num(u_json_get_id(self, id));
}

// shortcut to get a string by id from an array or object
static const char *u_json_get_id_string(const uJson *self, int id) {
    return u_json_get_string(u_json_get_id(self, id));
}

// shortcut to get an int by id from an array or object
static int *u_json_get_id_int(const uJson *self, int id, int *out_data) {
    return u_json_get_int(u_json_get_id(self, id), out_data);
}

// shortcut to get a float by id from an array or object
static float *u_json_get_id_float(const uJson *self, int id, float *out_data) {
    return u_json_get_float(u_json_get_id(self, id), out_data);
}

// shortcut to get a double by id from an array or object
static double *u_json_get_id_double(const uJson *self, int id, double *out_data) {
    return u_json_get_double(u_json_get_id(self, id), out_data);
}


#endif //U_JSON_H
