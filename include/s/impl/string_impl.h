#ifndef S_STRING_IMPL_H
#define S_STRING_IMPL_H
#ifdef S_IMPL

static ssize s__string_stream_read(struct sStream_i *stream, void *data, ssize len);
static ssize s__string_stream_write(struct sStream_i *stream, const void *data, ssize len);
static bool s__string_stream_valid(struct sStream_i *stream);



// allocated start_capacity + 1 (null)
sString *s_string_new_a(ssize start_capacity, sAllocator_i a) {
    s_assume(s_allocator_valid(a), "a needs to be valid");
    sString *self = s_a_new0(a, sString, 1);
    // at least 8 bytes to be allocated
    start_capacity = s_max(7, start_capacity);
    self->data = s_a_malloc0(a, start_capacity + 1);
    self->capacity = start_capacity;
    self->allocator = a;
    self->stream = (sStream_i) {
            .impl = self,
            .opt_read_try = s__string_stream_read,
            .opt_write_try = s__string_stream_write,
            .valid = s__string_stream_valid
    };
    return self;
}

sString *s_string_new_clone_a(sStr_s to_clone, sAllocator_i a) {
    sString *sb = s_string_new_a(to_clone.size, a);
    if (!s_string_valid(sb))
        return sb;
    memcpy(sb->data, to_clone.data, to_clone.size);
    sb->size = to_clone.size;
    return sb;
}

sString *s_string_new_replace_a(sStr_s to_replace, sStr_s old, sStr_s replacement, sAllocator_i a) {
    if (s_str_empty(to_replace) || s_str_empty(old) || !s_str_valid(replacement)) {
        return s_string_new_invalid();
    }
    ssize cnt = s_str_count_str(to_replace, old);
    if (cnt <= 0) {
        return s_string_new_clone_a(to_replace, a);
    }
    ssize size = to_replace.size - cnt * old.size + cnt * replacement.size;
    sString *res = s_string_new_a(size, a);
    res->size = size;
    sStr_s str = s_string_get_str(res);
    str = s_str_replace_str_into(str, to_replace, old, replacement);
    res->data = str.data;
    res->size = str.size;
    return res;
}

sString *s_string_new_cat_a(sStr_s *strs, int n, sAllocator_i a) {
    ssize size = 0;
    for (int i = 0; i < n; i++) {
        size += s_str_empty(strs[i]) ? 0 : strs[i].size;
    }
    sString *res = s_string_new_a(size, a);
    if (!s_string_valid(res))
        return res;

    for (int i = 0; i < n; i++) {
        if (!s_str_empty(strs[i])) {
            s_str_cpy(strs[i], (sStr_s) {res->data + res->size, strs[i].size});
            res->size += strs[i].size;
        }
    }
    return res;
}

void s_string_kill(sString **self_ptr) {
    sString *self = *self_ptr;
    if(!s_string_valid(self))
        return;
    s_a_free(self->allocator, self->data);
    s_a_free(self->allocator, self);
    *self_ptr = NULL;
}

void s_string_set_capacity(sString *self, ssize capacity) {
    if (!s_string_valid(self))
        return;

    void *data = s_a_realloc(self->allocator, self->data, capacity + 1);
    if (!data) {
        s_string_kill(&self);
        return;
    }
    self->data = data;
    self->capacity = capacity;
    memset(&self->data[self->size], 0, self->capacity + 1 - self->size);
}

void s_string_resize(sString *self, ssize size) {
    if (size > self->capacity) {
        s_string_set_capacity(self, size * 2);
    }
    if (!s_string_valid(self))
        return;
    self->size = size;
    self->data[self->size] = '\0';  //just to be sure
}

void s_string_push(sString *self, char push) {
    if (!s_string_valid(self))
        return;
    s_string_resize(self, self->size + 1);
    self->data[self->size - 1] = push;
    self->data[self->size] = '\0';  //just to be sure
}

void s_string_append(sString *self, sStr_s append) {
    if (!s_string_valid(self))
        return;
    ssize prev_size = self->size;
    s_string_resize(self, self->size + append.size);
    memcpy(self->data + prev_size, append.data, append.size);
    self->data[self->size] = '\0';  //just to be sure
}



static ssize s__string_stream_read(struct sStream_i *stream, void *data, ssize len) {
    sString *self = stream->impl;
    if(!s_string_valid(self) || len <=0)
        return 0;
    ssize s = s_min(self->size - self->stream_pos, len);
    memcpy(data, self->data+self->stream_pos, s);
    self->stream_pos+=s;
    return s;
}
static ssize s__string_stream_write(struct sStream_i *stream, const void *data, ssize len) {
    sString *self = stream->impl;
    if(!s_string_valid(self) || len <=0)
        return 0;
    s_string_append(self, (sStr_s) {(char *) data, len});
    return len;
}
static bool s__string_stream_valid(struct sStream_i *stream) {
    sString *self = stream->impl;
    return s_string_valid(self);
}

#endif //S_IMPL
#endif //S_STRING_IMPL_H
