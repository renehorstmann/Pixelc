#ifndef S_ENDIAN_H
#define S_ENDIAN_H

//
// host to little or big endian and vice versa for 16, 32 and 64 bit types
//      to use signed or float types, just cast these as unsinged to u*
//

#include "common.h"

// returns true if the system is little endian
static bool s_endian_system_is_binary_little_endian() {
    int n = 1;
    // little endian if true
    return *(char *) &n == 1;
}

// swaps endian order of the buffer
static void s_endian_swap(void *buf, int n) {
    assert(n <= 256 && "s_swap_endian: max 256 bits");
    char tmp[256];
    char *buf_data = (char *) buf;
    for (int i = 0; i < n; i++)
        tmp[i] = buf_data[n - i - 1];
    memcpy(buf_data, tmp, n);
}

//
// Contents;
// uX host to le|be
// uX le|be to host
// iX host to le|be
// iX le|be to host
//



//
// unsigned
//

static su16 s_endian_u16_host_to_be(su16 x) {
    su16 result;
    su8 *c;
    c = (su8 *) &result;
    c[0] = (x >> 8) & 0xFF;
    c[1] = x & 0xFF;
    return result;
}

static su16 s_endian_u16_host_to_le(su16 x) {
    su16 result;
    su8 *c;
    c = (su8 *) &result;
    c[1] = (x >> 8) & 0xFF;
    c[0] = x & 0xFF;
    return result;
}

static su16 s_endian_u16_le_to_host(su16 x) {
    su16 result;
    su8 *c;

    c = (su8 *) &x;
    result = (su16) c[0];
    result |= (su16) c[1] << 8;
    return result;
}

static su16 s_endian_u16_be_to_host(su16 x) {
    su16 result;
    su8 *c;

    c = (su8 *) &x;
    result = (su16) c[1];
    result |= (su16) c[0] << 8;
    return result;
}

static su32 s_endian_u32_host_to_be(su32 x) {
    su32 result;
    su8 *c;
    c = (su8 *) &result;
    c[0] = (x >> 24) & 0xFF;
    c[1] = (x >> 16) & 0xFF;
    c[2] = (x >> 8) & 0xFF;
    c[3] = x & 0xFF;
    return result;
}

static su32 s_endian_u32_host_to_le(su32 x) {
    su32 result;
    su8 *c;
    c = (su8 *) &result;
    c[3] = (x >> 24) & 0xFF;
    c[2] = (x >> 16) & 0xFF;
    c[1] = (x >> 8) & 0xFF;
    c[0] = x & 0xFF;
    return result;
}

static su32 s_endian_u32_le_to_host(su32 x) {
    su32 result;
    su8 *c;

    c = (su8 *) &x;
    result = (su32) c[0];
    result |= (su32) c[1] << 8;
    result |= (su32) c[2] << 16;
    result |= (su32) c[3] << 24;
    return result;
}

static su32 s_endian_u32_be_to_host(su32 x) {
    su32 result;
    su8 *c;

    c = (su8 *) &x;
    result = (su32) c[3];
    result |= (su32) c[2] << 8;
    result |= (su32) c[1] << 16;
    result |= (su32) c[0] << 24;
    return result;
}

static su64 s_endian_u64_host_to_be(su64 x) {
    su64 result;
    su8 *c;
    c = (su8 *) &result;
    c[0] = x >> 56;
    c[1] = (x >> 48) & 0xFF;
    c[2] = (x >> 40) & 0xFF;
    c[3] = (x >> 32) & 0xFF;
    c[4] = (x >> 24) & 0xFF;
    c[5] = (x >> 16) & 0xFF;
    c[6] = (x >> 8) & 0xFF;
    c[7] = x & 0xFF;
    return result;
}

static su64 s_endian_u64_host_to_le(su64 x) {
    su64 result;
    su8 *c;
    c = (su8 *) &result;
    c[7] = x >> 56;
    c[6] = (x >> 48) & 0xFF;
    c[5] = (x >> 40) & 0xFF;
    c[4] = (x >> 32) & 0xFF;
    c[3] = (x >> 24) & 0xFF;
    c[2] = (x >> 16) & 0xFF;
    c[1] = (x >> 8) & 0xFF;
    c[0] = x & 0xFF;
    return result;
}

static su64 s_endian_u64_le_to_host(su64 x) {
    su64 result;
    su8 *c;

    c = (su8 *) &x;
    result = (su64) c[0];
    result |= (su64) c[1] << 8;
    result |= (su64) c[2] << 16;
    result |= (su64) c[3] << 24;
    result |= (su64) c[4] << 32;
    result |= (su64) c[5] << 40;
    result |= (su64) c[6] << 48;
    result |= (su64) c[7] << 56;
    return result;
}

static su64 s_endian_u64_be_to_host(su64 x) {
    su64 result;
    su8 *c;

    c = (su8 *) &x;
    result = (su64) c[7];
    result |= (su64) c[6] << 8;
    result |= (su64) c[5] << 16;
    result |= (su64) c[4] << 24;
    result |= (su64) c[3] << 32;
    result |= (su64) c[2] << 40;
    result |= (su64) c[1] << 48;
    result |= (su64) c[0] << 56;
    return result;
}


//
// signed wrapper
//

static si16 s_endian_i16_host_to_be(si16 x) {
    su16 ret = s_endian_u16_host_to_be(*((su16*)&x));
    return *((si16*)&ret);
}

static si16 s_endian_i16_host_to_le(si16 x) {
    su16 ret = s_endian_u16_host_to_le(*((su16*)&x));
    return *((si16*)&ret);
}

static si16 s_endian_i16_le_to_host(si16 x) {
    su16 ret = s_endian_u16_le_to_host(*((su16*)&x));
    return *((si16*)&ret);
}

static si16 s_endian_i16_be_to_host(si16 x) {
    su16 ret = s_endian_u16_be_to_host(*((su16*)&x));
    return *((si16*)&ret);
}


static si32 s_endian_i32_host_to_be(si32 x) {
    su32 ret = s_endian_u32_host_to_be(*((su32*)&x));
    return *((si32*)&ret);
}

static si32 s_endian_i32_host_to_le(si32 x) {
    su32 ret = s_endian_u32_host_to_le(*((su32*)&x));
    return *((si32*)&ret);
}

static si32 s_endian_i32_le_to_host(si32 x) {
    su32 ret = s_endian_u32_le_to_host(*((su32*)&x));
    return *((si32*)&ret);
}

static si32 s_endian_i32_be_to_host(si32 x) {
    su32 ret = s_endian_u32_be_to_host(*((su32*)&x));
    return *((si32*)&ret);
}


static si64 s_endian_i64_host_to_be(si64 x) {
    su64 ret = s_endian_u64_host_to_be(*((su64*)&x));
    return *((si64*)&ret);
}

static si64 s_endian_i64_host_to_le(si64 x) {
    su64 ret = s_endian_u64_host_to_le(*((su64*)&x));
    return *((si64*)&ret);
}

static si64 s_endian_i64_le_to_host(si64 x) {
    su64 ret = s_endian_u64_le_to_host(*((su64*)&x));
    return *((si64*)&ret);
}

static si64 s_endian_i64_be_to_host(si64 x) {
    su64 ret = s_endian_u64_be_to_host(*((su64*)&x));
    return *((si64*)&ret);
}

#endif //S_ENDIAN_H