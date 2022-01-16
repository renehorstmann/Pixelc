#include <stdlib.h>
#include <locale.h>
#include "rhc/str.h"
#include "rhc/string.h"
#include "rhc/file.h"
#include "u/json.h"


#define INDENT_TAB 4

//
// private
//

struct uJson {
	char *name; // may be null
	union {
		bool data_bool;
		char *data_str; // for num and str
		struct uJson *data_arr; // for arr and obj
	};
	int arr_size; // only for arr and obj
	enum u_json_types type;
};


static void json_kill_r(uJson *self) {
	rhc_free(self->name);
	switch(self->type) {
	case U_JSON_TYPE_NUM:
	case U_JSON_TYPE_STRING:
		rhc_free(self->data_str);
		break;
	case U_JSON_TYPE_ARRAY:
	case U_JSON_TYPE_OBJECT:
		for(int i=0; i<self->arr_size; i++) {
			json_kill_r(&self->data_arr[i]);
		}
		rhc_free(self->data_arr);
		break;
	default:
		break;
	}
}

static uJson *append_child(uJson *self, const char *name) {
	if(!self || !(self->type == U_JSON_TYPE_ARRAY || self->type == U_JSON_TYPE_OBJECT))
	    return NULL;
	    
	uJson *child;
	uJson *old_child = u_json_get_object(self, name);
	if(old_child) {
	    // kill and replace
	    json_kill_r(old_child);
	    child = old_child;
	} else {
	    // append
	    self->data_arr = rhc_realloc(self->data_arr, sizeof *self->data_arr * ++self->arr_size);
	child = &self->data_arr[self->arr_size-1];    
	}
	
	*child = (uJson) {0};
	
	// copy name if self is an object (not an array)
	if(self->type == U_JSON_TYPE_OBJECT) {
		u_json_set_name(child, name);
	}
	return child;
}

static String use_escapes(Str_s str) {
    String s = string_new(str.size);
    
    for(int i=0; i<str.size; i++) {
        if(str.data[i] != '\\') {
            string_push(&s, str.data[i]);
            continue;
        }
        i++;
        switch (str.data[i]) {
        case 'n':
             string_push(&s, '\n');
             break;
        case 't':
             string_push(&s, '\t');
             break;
        case 'b':
             string_push(&s, '\b');
             break;
        case 'f':
             string_push(&s, '\f');
             break;
        case 'r':
             string_push(&s, '\r');
             break;
        case '\"':
             string_push(&s, '\"');
             break;
        case '\\':
             string_push(&s, '\\');
             break;
        }
    }
    return s;
}

static String create_escapes(Str_s str) {
    String s = string_new(str.size);
    
    for(int i=0; i<str.size; i++) {
        switch (str.data[i]) {
        case '\n':
             string_append(&s, strc("\\n"));
             break;
        case '\t':
             string_append(&s, strc("\\t"));
             break;
        case '\b':
             string_append(&s, strc("\\b"));
             break;
        case '\f':
             string_append(&s, strc("\\f"));
             break;
        case '\r':
             string_append(&s, strc("\\r"));
             break;
        case '\"':
             string_append(&s, strc("\\\""));
             break;
        case '\\':
             string_append(&s, strc("\\\\"));
             break;
        default:
            string_push(&s, str.data[i]);
            break;
        }
    }
    return s;
}

static void stringify_r(const uJson *self, String *string, int indent_lvl) {
	switch (self->type) {
	case U_JSON_TYPE_NULL:
		string_append(string, strc("null"));
		break;
	case U_JSON_TYPE_BOOL:
		string_append(string, strc(self->data_bool? "true" : "false"));
		break;
	case U_JSON_TYPE_NUM:
		string_append(string, strc(self->data_str));
		break;
	case U_JSON_TYPE_STRING:
	    {
		    string_push(string, '\"');
            String s = create_escapes(strc(self->data_str));
		    string_append(string, s.str);
		    string_kill(&s);
		    string_push(string, '\"');
	    }
		break;
	case U_JSON_TYPE_ARRAY:
		string_append(string, strc("[\n"));
		for(int i=0; i<self->arr_size; i++) {
			for(int indent=0; indent<indent_lvl+INDENT_TAB; indent++)
				string_push(string, ' ');
			stringify_r(&self->data_arr[i], string, indent_lvl);
			if(i < self->arr_size-1) 
				string_push(string, ',');
		    string_push(string, '\n');
		}
		for(int indent=0; indent<indent_lvl; indent++)
			string_push(string, ' ');
		string_push(string, ']');
		break;
	case U_JSON_TYPE_OBJECT:
		string_append(string, strc("{\n"));
		for(int i=0; i<self->arr_size; i++) {
			for(int indent=0; indent<indent_lvl+INDENT_TAB; indent++)
				string_push(string, ' ');
			string_push(string, '\"');
			string_append(string, strc(self->data_arr[i].name));
			string_append(string, strc("\": "));
			stringify_r(&self->data_arr[i], string, indent_lvl+INDENT_TAB);
			if(i < self->arr_size-1) 
				string_push(string, ',');
			string_push(string, '\n');
		}
		for(int indent=0; indent<indent_lvl; indent++)
			string_push(string, ' ');
		string_push(string, '}');
		break;
	default:
		break;
	}
}

static char *eat_string_to_heap(Str_s *remaining) {
	// must begin with " and end with " (not \")
	*remaining = str_eat(*remaining, 1);
	size_t len = 0;
	while(len < remaining->size && !(remaining->data[len] == '\"' && remaining->data[len-1] != '\"'))
			len++;
		
	if(len==remaining->size && remaining->data[len-1] != '\"') {
		log_error("u_json: failed to parse a string");
		return NULL;
	}
	
	// todo parse escape stuff
	
	char *str = rhc_malloc(len+1);
	memcpy(str, remaining->data, len);
	str[len] = '\0';
	*remaining = str_eat(*remaining, len+1);
	return str;
}

static bool parse_r(uJson *self, Str_s *remaining, const char *child_name) {
	*remaining = str_lstrip(*remaining, ' ');
	
	// start of a json item
	switch(remaining->data[0]) {
	case '\"':
		// string
		{
			char *str = eat_string_to_heap(remaining);
			if(!str)
				return false;
		    String s = use_escapes(strc(str));
			u_json_append_string(self, child_name, s.data);
			string_kill(&s);
			rhc_free(str);
		}
		break;
	case 'n':
		// null
		{
			*remaining = str_eat_str(*remaining, strc("null"));
			if(!str_valid(*remaining)) {
				log_error("u_json: failed to parse null");
				return false;
			}
			u_json_append_null(self, child_name);
		}
		break;
	case 't':
		// true
		{
			*remaining = str_eat_str(*remaining, strc("true"));
			if(!str_valid(*remaining)) {
				log_error("u_json: failed to parse true");
				return false;
			}
			u_json_append_bool(self, child_name, true);
			}
		break;
	case 'f':
		// false
		{
			*remaining = str_eat_str(*remaining, strc("false"));
			if(!str_valid(*remaining)) {
				log_error("u_json: failed to parse false");
				return false;
			}
			u_json_append_bool(self, child_name, false);
		}
		break;
	case '[':
		// array
		{
			*remaining = str_eat(*remaining, 1);
			uJson *arr = u_json_append_array(self, child_name);
			while(str_valid(*remaining)) {
				*remaining = str_lstrip(*remaining, ' ');
				if(remaining->data[0] == ']') {
					*remaining = str_eat(*remaining, 1);
					break;
				}
				if(!parse_r(arr, remaining, NULL))
					return false;
				*remaining = str_lstrip(*remaining, ' ');
				if(remaining->data[0] == ',') {
					*remaining = str_eat(*remaining, 1);
				}
			}
			if(!str_valid(*remaining)) {
				log_error("u_json: failed to parse array");
				return false;
			}
		}
		break;
	case '{':
		// object
		{
			*remaining = str_eat(*remaining, 1);
			uJson *obj = u_json_append_object(self, child_name);
			while(str_valid(*remaining)) {
				*remaining = str_lstrip(*remaining, ' ');
				if(remaining->data[0] == '}') {
					*remaining = str_eat(*remaining, 1);
					break;
				}
				char *name = eat_string_to_heap(remaining);
				if(!name) {
					log_error("u_json: failed to parse object");
					return false;
				}
				*remaining = str_lstrip(*remaining, ' ');
				*remaining = str_eat_str(*remaining, strc(":"));
				if(!str_valid(*remaining)) {
					rhc_free(name);
					log_error("u_json: failed to parse object");
					return false;
				}
				
				bool parse_ok = parse_r(obj, remaining, name);
				rhc_free(name);
				if(!parse_ok) {
					log_error("u_json: failed to parse object");
					return false;
				}
				
				*remaining = str_lstrip(*remaining, ' ');
				if(remaining->data[0] == ',') {
					*remaining = str_eat(*remaining, 1);
				}
			}
			if(!str_valid(*remaining)) {
				log_error("u_json: failed to parse object");
				return false;
			}
		}
		break;
	default:
		// num
		{
			setlocale(LC_ALL, "C");
			char *end;
			strtod(remaining->data, &end);
			size_t num = end - remaining->data;
			if(num == 0) {
				log_error("u_json: failed to parse num");
				return false;
			}
			char *num_str = str_as_new_c((Str_s) {remaining->data, num});
			u_json_append_num(self, child_name, num_str);
			rhc_free(num_str);
			*remaining = str_eat(*remaining, num);
		}
		break;
	}
	return true;
}


//
// public
//


uJson *u_json_new_empty() {
	uJson *self = rhc_calloc(sizeof *self);
	self->type = U_JSON_TYPE_OBJECT;
	return self;
}

uJson *u_json_new_str(Str_s str_to_parse) {
	if(str_empty(str_to_parse)) {
	    log_warn("u_json: load failed, str invalid, returning empty uJson");
	    return u_json_new_empty();
	}
	uJson *root = u_json_new_empty();
	if(!parse_r(root, &str_to_parse, "root")) {
		log_warn("u_json: load failed, returning empty uJson");
		u_json_kill(&root);
		return u_json_new_empty();
	}
	if(root->arr_size != 1) {
		log_warn("u_json: load failed, multiple root elements, returning empty uJson");
		u_json_kill(&root);
		return u_json_new_empty();
	}
	uJson *self = root->data_arr;
	rhc_free(root);
	return self;
}

uJson *u_json_new_file(const char *file) {
	String s = file_read(file, true);
	uJson *self = u_json_new_str(s.str);
	string_kill(&s);
	return self;
}

void u_json_kill(uJson **self_ptr) {
	uJson *self = *self_ptr;
	if(!self)
	    return;
	json_kill_r(self);
	rhc_free(self);
	*self_ptr = NULL;
}

bool u_json_empty(const uJson *self) {
    if(!self)
        return false;
    if(self->type==U_JSON_TYPE_ARRAY || self->type==U_JSON_TYPE_OBJECT)
        return self->arr_size == 0;
    return false;
}

String u_json_to_string(const uJson *self) {
	if(!self)
		return string_new_invalid();
	String s = string_new(128);
	stringify_r(self, &s, 0);
	return s;
}

bool u_json_save_file(const uJson *self, const char *file) {
	if(!self)
		return false;
	String s = u_json_to_string(self);
	bool ok = rhc_file_write(file, s.str, true);
	string_kill(&s);
	return ok;
}

enum u_json_types u_json_get_type(const uJson *self) {
	if(!self)
		return U_JSON_TYPE_NULL;
	return self->type;
}

const char *u_json_get_name(const uJson *self) {
	if(!self)
		return NULL;
	return self->name;
}

const bool *u_json_get_bool(const uJson *self) {
	if(!self || self->type != U_JSON_TYPE_BOOL)
		return NULL;
	return &self->data_bool;
}

const char *u_json_get_num(const uJson *self) {
	if(!self || self->type != U_JSON_TYPE_NUM)
		return NULL;
	return self->data_str;
}

const char *u_json_get_string(const uJson *self) {
	if(!self || self->type != U_JSON_TYPE_STRING)
		return NULL;
	return self->data_str;
}

int u_json_get_size(const uJson *self) {
	if(!self || (self->type != U_JSON_TYPE_ARRAY && self->type != U_JSON_TYPE_OBJECT))
		return 0;
	return self->arr_size;
}

uJson *u_json_get_id(const uJson *self, int id) {
	if(!self || (self->type != U_JSON_TYPE_ARRAY && self->type != U_JSON_TYPE_OBJECT))
		return NULL;
	if(id < 0 || id >= self->arr_size)
		return NULL;
	return &self->data_arr[id];
}

uJson *u_json_get_object(const uJson *self, const char *name) {
	if(!self || self->type != U_JSON_TYPE_OBJECT)
		return NULL;
	if(!name || *name == '\0')
		return NULL;
	for(int i=0; i<self->arr_size; i++) {
		if(strcmp(self->data_arr[i].name, name) == 0) {
			return &self->data_arr[i];
		}
	}
	
	// not found
	return NULL;
}

int *u_json_get_int(const uJson *self, int *out_data) {
	if(!self || !out_data || self->type != U_JSON_TYPE_NUM)
		return NULL;
	char *end;
	setlocale(LC_ALL, "C");
	*out_data = strtol(self->data_str, &end, 10);
	if(end == self->data_str)
		return NULL;
	return out_data;
}

float *u_json_get_float(const uJson *self, float *out_data) {
	if(!self || !out_data || self->type != U_JSON_TYPE_NUM)
		return NULL;
	char *end;
	setlocale(LC_ALL, "C");
	*out_data = strtof(self->data_str, &end);
	if(end == self->data_str)
		return NULL;
	return out_data;
}

double *u_json_get_double(const uJson *self, double *out_data) {
	if(!self || !out_data || self->type != U_JSON_TYPE_NUM)
		return NULL;
	char *end;
	setlocale(LC_ALL, "C");
	*out_data = strtod(self->data_str, &end);
	if(end == self->data_str)
		return NULL;
	return out_data;
}


void u_json_set_name(uJson *self, const char *name) {
    if(!self)
        return;
    size_t len = strlen(name) +1;
	self->name = rhc_realloc(self->name, len);
    memcpy(self->name, name, len);
}

bool u_json_set_bool(uJson *self, bool value) {
    if(!self || self->type != U_JSON_TYPE_BOOL) {
        log_error("u_json: failed to set bool, type missmatch");
        return false;
    }
    self->data_bool = value;
    return true;
}

bool u_json_set_num(uJson *self, const char *value) {
    if(!self || self->type != U_JSON_TYPE_NUM) {
        log_error("u_json: failed to set num, type missmatch");
        return false;
    }
    size_t len = strlen(value) +1;
	self->data_str = rhc_realloc(self->data_str, len);
    memcpy(self->data_str, value, len);
    return true;
}

bool u_json_set_string(uJson *self, const char *value) {
    if(!self || self->type != U_JSON_TYPE_STRING) {
        log_error("u_json: failed to set string, type missmatch");
        return false;
    }
    size_t len = strlen(value) +1;
	self->data_str = rhc_realloc(self->data_str, len);
    memcpy(self->data_str, value, len);
    return true;
}

bool u_json_set_int(uJson *self, int value) {
    char tmp[128];
    snprintf(tmp, sizeof tmp, "%i", value);
    return u_json_set_num(self, tmp);
}

bool u_json_set_float(uJson *self, float value) {
    char tmp[128];
    snprintf(tmp, sizeof tmp, "%f", value);
    return u_json_set_num(self, tmp);
}

bool u_json_set_double(uJson *self, double value) {
    char tmp[128];
    snprintf(tmp, sizeof tmp, "%f", value);
    return u_json_set_num(self, tmp);
}



uJson *u_json_append_null(uJson *self, const char *name) {
	uJson *child = append_child(self, name);
	if(!child)
	    return NULL;
	// should be null, but just to be clear
	child->type = U_JSON_TYPE_NULL;
	return child;
}

uJson *u_json_append_bool(uJson *self, const char *name, bool value) {
	uJson *child = append_child(self, name);
	if(!child)
	    return NULL;
	child->type = U_JSON_TYPE_BOOL;
	child->data_bool = value;
	return child;
}

uJson *u_json_append_num(uJson *self, const char *name, const char *value) {
	if(!value) {
		log_warn("u_json: got NULL for appending a num, appending item null");
		return u_json_append_null(self, name);
	}
    setlocale(LC_ALL, "C");
    char *end;
	strtod(value, &end);
	size_t num = end - value;
	if(num == 0) {
		log_warn("u_json: failed to parse appended num, appending item null");
		return u_json_append_null(self, name);
	}
	uJson *child = append_child(self, name);
	if(!child)
	    return NULL;
	child->type = U_JSON_TYPE_NUM;
	child->data_str = rhc_malloc(num+1);
	memcpy(child->data_str, value, num);
    child->data_str[num] = '\0';	
	return child;
}

uJson *u_json_append_string(uJson *self, const char *name, const char *value) {
	if(!value) {
		log_warn("u_json: got NULL for appending a string, appending item null");
		return u_json_append_null(self, name);
	}
	uJson *child = append_child(self, name);
	if(!child)
	    return NULL;
	child->type = U_JSON_TYPE_STRING;
	size_t len = strlen(value) +1;
	child->data_str = rhc_malloc(len);
	memcpy(child->data_str, value, len);
	return child;
}

uJson *u_json_append_array(uJson *self, const char *name) {
	uJson *child = append_child(self, name);
	if(!child)
	    return NULL;
	child->type = U_JSON_TYPE_ARRAY;
	return child;
}

uJson *u_json_append_object(uJson *self, const char *name) {
	uJson *child = append_child(self, name);
	if(!child)
	    return NULL;
	child->type = U_JSON_TYPE_OBJECT;
	return child;
}


uJson *u_json_append_int(uJson *self, const char *name, int value) {
	char tmp[64];
	setlocale(LC_ALL, "C");
	snprintf(tmp, sizeof tmp, "%i", value);
	return u_json_append_num(self, name, tmp);
}

uJson *u_json_append_float(uJson *self, const char *name, float value) {
	char tmp[64];
	setlocale(LC_ALL, "C");
	snprintf(tmp, sizeof tmp, "%g", value);
	return u_json_append_num(self, name, tmp);
}

uJson *u_json_append_double(uJson *self, const char *name, double value) {
	char tmp[64];
	setlocale(LC_ALL, "C");
	snprintf(tmp, sizeof tmp, "%g", value);
	return u_json_append_num(self, name, tmp);
}


bool u_json_remove_id(uJson *self, int id) {
    if(!self || !(self->type == U_JSON_TYPE_ARRAY || self->type == U_JSON_TYPE_OBJECT))
        return false;
    if(id<0 || id >= self->arr_size)
        return false;
    json_kill_r(&self->data_arr[id]);
    for(int i=id; i<self->arr_size-1; i++)
        self->data_arr[i] = self->data_arr[i+1];
    self->arr_size--;
    return true;
}

int u_json_remove_objects(uJson *self, const char *name) {
    if(!self || self->type != U_JSON_TYPE_OBJECT)
        return false;
    int rem = 0;
    for(int i=0; i<self->arr_size; i++) {
        if(strcmp(self->data_arr[i].name, name) == 0) {
            if(u_json_remove_id(self, i)) {
                rem++; // should always be true
            }
            
            // restart loop with i==0
            i = -1;
            continue;
        }
    }
    return rem;
}
