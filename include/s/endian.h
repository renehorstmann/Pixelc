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

static su16 s_endian_host_to_be16(su16 x) {
    su16 result;
    unsigned char *c;
    c = (unsigned char *) &result;
    c[0] = (x >> 8) & 0xFF;
    c[1] = x & 0xFF;
    return result;
}

static su16 s_endian_host_to_le16(su16 x) {
    su16 result;
    unsigned char *c;
    c = (unsigned char *) &result;
    c[1] = (x >> 8) & 0xFF;
    c[0] = x & 0xFF;
    return result;
}

static su16 s_endian_le_to_host16(su16 x) {
    su16 result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (su16) c[0];
    result |= (su16) c[1] << 8;
    return result;
}

static su16 s_endian_be_to_host16(su16 x) {
    su16 result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (su16) c[1];
    result |= (su16) c[0] << 8;
    return result;
}

static su32 s_endian_host_to_be32(su32 x) {
    su32 result;
    unsigned char *c;
    c = (unsigned char *) &result;
    c[0] = (x >> 24) & 0xFF;
    c[1] = (x >> 16) & 0xFF;
    c[2] = (x >> 8) & 0xFF;
    c[3] = x & 0xFF;
    return result;
}

static su32 s_endian_host_to_le32(su32 x) {
    su32 result;
    unsigned char *c;
    c = (unsigned char *) &result;
    c[3] = (x >> 24) & 0xFF;
    c[2] = (x >> 16) & 0xFF;
    c[1] = (x >> 8) & 0xFF;
    c[0] = x & 0xFF;
    return result;
}

static su32 s_endian_le_to_host32(su32 x) {
    su32 result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (su32) c[0];
    result |= (su32) c[1] << 8;
    result |= (su32) c[2] << 16;
    result |= (su32) c[3] << 24;
    return result;
}

static su32 s_endian_be_to_host32(su32 x) {
    su32 result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (su32) c[3];
    result |= (su32) c[2] << 8;
    result |= (su32) c[1] << 16;
    result |= (su32) c[0] << 24;
    return result;
}

static su64 s_endian_host_to_be64(su64 x) {
    su64 result;
    unsigned char *c;
    c = (unsigned char *) &result;
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

static su64 s_endian_host_to_le64(su64 x) {
    su64 result;
    unsigned char *c;
    c = (unsigned char *) &result;
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

static su64 s_endian_le_to_host64(su64 x) {
    su64 result;
    unsigned char *c;

    c = (unsigned char *) &x;
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

static su64 s_endian_be_to_host64(su64 x) {
    su64 result;
    unsigned char *c;

    c = (unsigned char *) &x;
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

#endif //S_ENDIAN_H
