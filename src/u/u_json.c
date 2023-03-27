#include "s/s_full.h"
#include "u/json.h"


#define INDENT_TAB 2

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

    sAllocator_i a;
};


static bool is_object_or_array(enum u_json_types type) {
    return type == U_JSON_TYPE_ARRAY || type == U_JSON_TYPE_OBJECT;
}

static void json_kill_r(uJson *self) {
    s_a_free(self->a, self->name);
    switch (self->type) {
        case U_JSON_TYPE_NUM:
        case U_JSON_TYPE_STRING:
            s_a_free(self->a, self->data_str);
            break;
        case U_JSON_TYPE_ARRAY:
        case U_JSON_TYPE_OBJECT:
            for (int i = 0; i < self->arr_size; i++) {
                json_kill_r(&self->data_arr[i]);
            }
            s_a_free(self->a, self->data_arr);
            break;
        default:
            break;
    }
}

static uJson *append_child(uJson *self, const char *name) {
    if (!self || !is_object_or_array(self->type))
        return NULL;

    uJson *child;
    uJson *old_child = u_json_get_object(self, name);
    if (old_child) {
        // kill and replace
        json_kill_r(old_child);
        child = old_child;
    } else {
        // append
        self->data_arr = s_a_realloc(self->a, self->data_arr, sizeof *self->data_arr * ++self->arr_size);
        child = &self->data_arr[self->arr_size - 1];
    }

    *child = (uJson) {0};
    child->a = self->a;

    // copy name if self is an object (not an array)
    if (self->type == U_JSON_TYPE_OBJECT) {
        u_json_set_name(child, name);
    }
    return child;
}

static sString *use_escapes(sStr_s str) {
    sString *s = s_string_new(str.size);

    for (ssize i = 0; i < str.size; i++) {
        if (str.data[i] != '\\') {
            s_string_push(s, str.data[i]);
            continue;
        }
        i++;
        switch (str.data[i]) {
            case 'n':
                s_string_push(s, '\n');
                break;
            case 't':
                s_string_push(s, '\t');
                break;
            case 'b':
                s_string_push(s, '\b');
                break;
            case 'f':
                s_string_push(s, '\f');
                break;
            case 'r':
                s_string_push(s, '\r');
                break;
            case '\"':
                s_string_push(s, '\"');
                break;
            case '\\':
                s_string_push(s, '\\');
                break;
        }
    }
    return s;
}

static sString *create_escapes(sStr_s str) {
    sString *s = s_string_new(str.size);

    for (ssize i = 0; i < str.size; i++) {
        switch (str.data[i]) {
            case '\n':
                s_string_append(s, s_strc("\\n"));
                break;
            case '\t':
                s_string_append(s, s_strc("\\t"));
                break;
            case '\b':
                s_string_append(s, s_strc("\\b"));
                break;
            case '\f':
                s_string_append(s, s_strc("\\f"));
                break;
            case '\r':
                s_string_append(s, s_strc("\\r"));
                break;
            case '\"':
                s_string_append(s, s_strc("\\\""));
                break;
            case '\\':
                s_string_append(s, s_strc("\\\\"));
                break;
            default:
                s_string_push(s, str.data[i]);
                break;
        }
    }
    return s;
}

static void stringify_r(const uJson *self, sString *string, int indent_lvl, struct uJson_Options options) {
    switch (self->type) {
        case U_JSON_TYPE_NULL:
            s_string_append(string, s_strc("null"));
            break;
        case U_JSON_TYPE_BOOL:
            s_string_append(string, s_strc(self->data_bool ? "true" : "false"));
            break;
        case U_JSON_TYPE_NUM:
            s_string_append(string, s_strc(self->data_str));
            break;
        case U_JSON_TYPE_STRING: {
            s_string_push(string, '\"');
            sString *s = create_escapes(s_strc(self->data_str));
            s_string_append(string, s_string_get_str(s));
            s_string_kill(&s);
            s_string_push(string, '\"');
        }
            break;
        case U_JSON_TYPE_ARRAY:
            if(options.array_single_line) {
                s_string_push(string, '[');
                for (int i = 0; i < self->arr_size; i++) { 
                    stringify_r(&self->data_arr[i], string, indent_lvl, options); 
                    if (i < self->arr_size - 1) 
                        s_string_append(string, s_strc(", ")); 
                } 
                s_string_push(string, ']'); 
            } else {
                // !options.array_single_line
                s_string_append(string, s_strc("[\n"));
            
                for (int i = 0; i < self->arr_size; i++) { 
                    for (int indent = 0; indent < indent_lvl + INDENT_TAB; indent++)
                        s_string_push(string, ' '); 
                    stringify_r(&self->data_arr[i], string, indent_lvl, options); 
                    if (i < self->arr_size - 1) 
                        s_string_push(string, ',');
                    s_string_push(string, '\n'); 
                } 
                for (int indent = 0; indent < indent_lvl; indent++) 
                    s_string_push(string, ' '); 
                s_string_push(string, ']'); 
            }
            
            break;
        case U_JSON_TYPE_OBJECT:
            s_string_append(string, s_strc("{\n"));
            for (int i = 0; i < self->arr_size; i++) {
                for (int indent = 0; indent < indent_lvl + INDENT_TAB; indent++)
                    s_string_push(string, ' ');
                s_string_push(string, '\"');
                s_string_append(string, s_strc(self->data_arr[i].name));
                s_string_append(string, s_strc("\": "));
                stringify_r(&self->data_arr[i], string, indent_lvl + INDENT_TAB, options);
                if (i < self->arr_size - 1)
                    s_string_push(string, ',');
                s_string_push(string, '\n');
            }
            for (int indent = 0; indent < indent_lvl; indent++)
                s_string_push(string, ' ');
            s_string_push(string, '}');
            break;
        default:
            break;
    }
}

static char *eat_string_to_heap(sStr_s *remaining, sAllocator_i a) {
    // must begin with " and end with " (not \")
    *remaining = s_str_eat(*remaining, 1);
    ssize len = 0;
    while (len < remaining->size && !(remaining->data[len] == '\"' && remaining->data[len - 1] != '\\'))
        len++;

    if (len == remaining->size && remaining->data[len - 1] != '\"') {
        s_log_error("failed to parse a string");
        return NULL;
    }

    // todo parse escape stuff

    char *str = s_a_malloc(a, len + 1);
    memcpy(str, remaining->data, len);
    str[len] = '\0';
    *remaining = s_str_eat(*remaining, len + 1);
    return str;
}

static bool parse_r(uJson *self, sStr_s *remaining, const char *child_name) {
    *remaining = s_str_lstrip(*remaining, ' ');

    // start of a json item
    switch (remaining->data[0]) {
        case '\"':
            // string
        {
            char *str = eat_string_to_heap(remaining, self->a);
            if (!str)
                return false;
            sString *s = use_escapes(s_strc(str));
            u_json_append_string(self, child_name, s->data);
            s_string_kill(&s);
            s_a_free(self->a, str);
        }
            break;
        case 'n':
            // null
        {
            *remaining = s_str_eat_str(*remaining, s_strc("null"));
            if (!s_str_valid(*remaining)) {
                s_log_error("failed to parse null");
                return false;
            }
            u_json_append_null(self, child_name);
        }
            break;
        case 't':
            // true
        {
            *remaining = s_str_eat_str(*remaining, s_strc("true"));
            if (!s_str_valid(*remaining)) {
                s_log_error("failed to parse true");
                return false;
            }
            u_json_append_bool(self, child_name, true);
        }
            break;
        case 'f':
            // false
        {
            *remaining = s_str_eat_str(*remaining, s_strc("false"));
            if (!s_str_valid(*remaining)) {
                s_log_error("failed to parse false");
                return false;
            }
            u_json_append_bool(self, child_name, false);
        }
            break;
        case '[':
            // array
        {
            *remaining = s_str_eat(*remaining, 1);
            uJson *arr = u_json_append_array(self, child_name);
            while (s_str_valid(*remaining)) {
                *remaining = s_str_lstrip(*remaining, ' ');
                if (remaining->data[0] == ']') {
                    *remaining = s_str_eat(*remaining, 1);
                    break;
                }
                if (!parse_r(arr, remaining, NULL))
                    return false;
                *remaining = s_str_lstrip(*remaining, ' ');
                if (remaining->data[0] == ',') {
                    *remaining = s_str_eat(*remaining, 1);
                }
            }
            if (!s_str_valid(*remaining)) {
                s_log_error("failed to parse array");
                return false;
            }
        }
            break;
        case '{':
            // object
        {
            *remaining = s_str_eat(*remaining, 1);
            uJson *obj = u_json_append_object(self, child_name);
            while (s_str_valid(*remaining)) {
                *remaining = s_str_lstrip(*remaining, ' ');
                if (remaining->data[0] == '}') {
                    *remaining = s_str_eat(*remaining, 1);
                    break;
                }
                char *name = eat_string_to_heap(remaining, self->a);
                if (!name) {
                    s_log_error("failed to parse object");
                    return false;
                }
                *remaining = s_str_lstrip(*remaining, ' ');
                *remaining = s_str_eat_str(*remaining, s_strc(":"));
                if (!s_str_valid(*remaining)) {
                    s_a_free(self->a, name);
                    s_log_error("failed to parse object");
                    return false;
                }

                bool parse_ok = parse_r(obj, remaining, name);
                s_a_free(self->a, name);
                if (!parse_ok) {
                    s_log_error("failed to parse object");
                    return false;
                }

                *remaining = s_str_lstrip(*remaining, ' ');
                if (remaining->data[0] == ',') {
                    *remaining = s_str_eat(*remaining, 1);
                }
            }
            if (!s_str_valid(*remaining)) {
                s_log_error("failed to parse object");
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
            ssize num = end - remaining->data;
            if (num == 0) {
                s_log_error("failed to parse num");
                return false;
            }
            char *num_str = s_str_as_new_c_a((sStr_s) {remaining->data, num}, self->a);
            u_json_append_num(self, child_name, num_str);
            s_a_free(self->a, num_str);
            *remaining = s_str_eat(*remaining, num);
        }
            break;
    }
    return true;
}


//
// public
//


uJson *u_json_new_empty_a(sAllocator_i a) {
    uJson *self = s_a_malloc0(a, sizeof *self);
    self->a = a;
    self->type = U_JSON_TYPE_OBJECT;
    return self;
}

uJson *u_json_new_str_a(sStr_s s_str_to_parse, sAllocator_i a) {
    if (s_str_empty(s_str_to_parse)) {
        s_log_warn("load failed, str invalid, returning empty uJson");
        return u_json_new_empty_a(a);
    }
    uJson *root = u_json_new_empty_a(a);
    if (!parse_r(root, &s_str_to_parse, "root")) {
        s_log_warn("load failed, returning empty uJson");
        u_json_kill(&root);
        return u_json_new_empty_a(a);
    }
    if (root->arr_size != 1) {
        s_log_warn("load failed, multiple root elements, returning empty uJson");
        u_json_kill(&root);
        return u_json_new_empty_a(a);
    }
    uJson *self = root->data_arr;
    s_a_free(a, root);
    return self;
}

uJson *u_json_new_file_a(const char *file, sAllocator_i a) {
    sString *s = s_file_read(file, true);
    uJson *self = u_json_new_str(s_string_get_str(s));
    s_string_kill(&s);
    return self;
}

void u_json_kill(uJson **self_ptr) {
    uJson *self = *self_ptr;
    if (!self)
        return;
    json_kill_r(self);
    s_a_free(self->a, self);
    *self_ptr = NULL;
}

bool u_json_empty(const uJson *self) {
    if (!self)
        return false;
    if (is_object_or_array(self->type))
        return self->arr_size == 0;
    return false;
}

sString *u_json_to_string_a(const uJson *self, sAllocator_i a, struct uJson_Options *opt_options) {
    if (!self)
        return s_string_new_invalid();
    struct uJson_Options options = {0};
    if(opt_options)
        options = *opt_options;
    sString *s = s_string_new_a(128, a);
    stringify_r(self, s, 0, options);
    return s;
}

sString *u_json_to_string(const uJson *self, struct uJson_Options *opt_options) {
    if (!self)
        return s_string_new_invalid();
    struct uJson_Options options = {0};
    if(opt_options)
        options = *opt_options;
    sString *s = s_string_new_a(128, self->a);
    stringify_r(self, s, 0, options);
    return s;
}

bool u_json_save_file(const uJson *self, const char *file, struct uJson_Options *opt_options) {
    if (!self)
        return false;
    sString *s = u_json_to_string(self, opt_options);
    bool ok = s_file_write(file, s_string_get_str(s), true);
    s_string_kill(&s);
    return ok;
}

enum u_json_types u_json_get_type(const uJson *self) {
    if (!self)
        return U_JSON_TYPE_NULL;
    return self->type;
}

const char *u_json_get_name(const uJson *self) {
    if (!self)
        return NULL;
    return self->name;
}

const bool *u_json_get_bool(const uJson *self) {
    if (!self || self->type != U_JSON_TYPE_BOOL)
        return NULL;
    return &self->data_bool;
}

const char *u_json_get_num(const uJson *self) {
    if (!self || self->type != U_JSON_TYPE_NUM)
        return NULL;
    return self->data_str;
}

const char *u_json_get_string(const uJson *self) {
    if (!self || self->type != U_JSON_TYPE_STRING)
        return NULL;
    return self->data_str;
}

int u_json_get_size(const uJson *self) {
    if (!self || !is_object_or_array(self->type))
        return 0;
    return self->arr_size;
}

uJson *u_json_get_id(const uJson *self, int id) {
    if (!self || !is_object_or_array(self->type))
        return NULL;
    if (id < 0 || id >= self->arr_size)
        return NULL;
    return &self->data_arr[id];
}

uJson *u_json_get_object(const uJson *self, const char *name) {
    if (!self || self->type != U_JSON_TYPE_OBJECT)
        return NULL;
    if (!name || *name == '\0')
        return NULL;
    for (int i = 0; i < self->arr_size; i++) {
        if (strcmp(self->data_arr[i].name, name) == 0) {
            return &self->data_arr[i];
        }
    }

    // not found
    return NULL;
}

int *u_json_get_int(const uJson *self, int *out_data) {
    if (!self || !out_data || self->type != U_JSON_TYPE_NUM)
        return NULL;
    char *end;
    setlocale(LC_ALL, "C");
    *out_data = strtol(self->data_str, &end, 10);
    if (end == self->data_str)
        return NULL;
    return out_data;
}

float *u_json_get_float(const uJson *self, float *out_data) {
    if (!self || !out_data || self->type != U_JSON_TYPE_NUM)
        return NULL;
    char *end;
    setlocale(LC_ALL, "C");
    *out_data = strtof(self->data_str, &end);
    if (end == self->data_str)
        return NULL;
    return out_data;
}

double *u_json_get_double(const uJson *self, double *out_data) {
    if (!self || !out_data || self->type != U_JSON_TYPE_NUM)
        return NULL;
    char *end;
    setlocale(LC_ALL, "C");
    *out_data = strtod(self->data_str, &end);
    if (end == self->data_str)
        return NULL;
    return out_data;
}


void u_json_set_name(uJson *self, const char *name) {
    if (!self)
        return;
    ssize len = strlen(name) + 1;
    self->name = s_a_realloc(self->a, self->name, len);
    memcpy(self->name, name, len);
}

bool u_json_set_bool(uJson *self, bool value) {
    if (!self || self->type != U_JSON_TYPE_BOOL) {
        s_log_error("failed to set bool, type missmatch");
        return false;
    }
    self->data_bool = value;
    return true;
}

bool u_json_set_num(uJson *self, const char *value) {
    if (!self || self->type != U_JSON_TYPE_NUM) {
        s_log_error("failed to set num, type missmatch");
        return false;
    }
    ssize len = strlen(value) + 1;
    self->data_str = s_a_realloc(self->a, self->data_str, len);
    memcpy(self->data_str, value, len);
    return true;
}

bool u_json_set_string(uJson *self, const char *value) {
    if (!self || self->type != U_JSON_TYPE_STRING) {
        s_log_error("failed to set string, type missmatch");
        return false;
    }
    ssize len = strlen(value) + 1;
    self->data_str = s_a_realloc(self->a, self->data_str, len);
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
    if (!child)
        return NULL;
    // should be null, but just to be clear
    child->type = U_JSON_TYPE_NULL;
    return child;
}

uJson *u_json_append_bool(uJson *self, const char *name, bool value) {
    uJson *child = append_child(self, name);
    if (!child)
        return NULL;
    child->type = U_JSON_TYPE_BOOL;
    child->data_bool = value;
    return child;
}

uJson *u_json_append_num(uJson *self, const char *name, const char *value) {
    if (!value) {
        s_log_warn("got NULL for appending a num, appending item null");
        return u_json_append_null(self, name);
    }
    setlocale(LC_ALL, "C");
    char *end;
    strtod(value, &end);
    ssize num = end - value;
    if (num == 0) {
        s_log_warn("failed to parse appended num, appending item null");
        return u_json_append_null(self, name);
    }
    uJson *child = append_child(self, name);
    if (!child)
        return NULL;
    child->type = U_JSON_TYPE_NUM;
    child->data_str = s_a_malloc(self->a, num + 1);
    memcpy(child->data_str, value, num);
    child->data_str[num] = '\0';
    return child;
}

uJson *u_json_append_string(uJson *self, const char *name, const char *value) {
    if (!value) {
        s_log_warn("got NULL for appending a string, appending item null");
        return u_json_append_null(self, name);
    }
    uJson *child = append_child(self, name);
    if (!child)
        return NULL;
    child->type = U_JSON_TYPE_STRING;
    ssize len = strlen(value) + 1;
    child->data_str = s_a_malloc(self->a, len);
    memcpy(child->data_str, value, len);
    return child;
}

uJson *u_json_append_array(uJson *self, const char *name) {
    uJson *child = append_child(self, name);
    if (!child)
        return NULL;
    child->type = U_JSON_TYPE_ARRAY;
    return child;
}

uJson *u_json_append_object(uJson *self, const char *name) {
    uJson *child = append_child(self, name);
    if (!child)
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
    if (!self || !(self->type == U_JSON_TYPE_ARRAY || self->type == U_JSON_TYPE_OBJECT))
        return false;
    if (id < 0 || id >= self->arr_size)
        return false;
    json_kill_r(&self->data_arr[id]);
    for (int i = id; i < self->arr_size - 1; i++)
        self->data_arr[i] = self->data_arr[i + 1];
    self->arr_size--;
    return true;
}

int u_json_remove_objects(uJson *self, const char *name) {
    if (!self || self->type != U_JSON_TYPE_OBJECT)
        return false;
    int rem = 0;
    for (int i = 0; i < self->arr_size; i++) {
        if (strcmp(self->data_arr[i].name, name) == 0) {
            if (u_json_remove_id(self, i)) {
                rem++; // should always be true
            }

            // restart loop with i==0
            i = -1;
            continue;
        }
    }
    return rem;
}
