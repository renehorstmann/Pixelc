#ifndef RHC_ENDIAN_H
#define RHC_ENDIAN_H

#include <stdint.h>

static uint16_t endian_host_to_be16(uint16_t x) {
    uint16_t result;
    unsigned char *c;
    c = (unsigned char *) &result;
    c[0] = (x >> 8) & 0xFF;
    c[1] = x & 0xFF;
    return result;
}

static uint16_t endian_host_to_le16(uint16_t x) {
    uint16_t result;
    unsigned char *c;
    c = (unsigned char *) &result;
    c[1] = (x >> 8) & 0xFF;
    c[0] = x & 0xFF;
    return result;
}

static uint16_t endian_le_to_host16(uint16_t x) {
    uint16_t result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (uint16_t) c[0];
    result |= (uint16_t) c[1] << 8;
    return result;
}

static uint16_t endian_be_to_host16(uint16_t x) {
    uint16_t result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (uint16_t) c[1];
    result |= (uint16_t) c[0] << 8;
    return result;
}

static uint32_t endian_host_to_be32(uint32_t x) {
    uint32_t result;
    unsigned char *c;
    c = (unsigned char *) &result;
    c[0] = (x >> 24) & 0xFF;
    c[1] = (x >> 16) & 0xFF;
    c[2] = (x >> 8) & 0xFF;
    c[3] = x & 0xFF;
    return result;
}

static uint32_t endian_host_to_le32(uint32_t x) {
    uint32_t result;
    unsigned char *c;
    c = (unsigned char *) &result;
    c[3] = (x >> 24) & 0xFF;
    c[2] = (x >> 16) & 0xFF;
    c[1] = (x >> 8) & 0xFF;
    c[0] = x & 0xFF;
    return result;
}

static uint32_t endian_le_to_host32(uint32_t x) {
    uint32_t result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (uint32_t) c[0];
    result |= (uint32_t) c[1] << 8;
    result |= (uint32_t) c[2] << 16;
    result |= (uint32_t) c[3] << 24;
    return result;
}

static uint32_t endian_be_to_host32(uint32_t x) {
    uint32_t result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (uint32_t) c[3];
    result |= (uint32_t) c[2] << 8;
    result |= (uint32_t) c[1] << 16;
    result |= (uint32_t) c[0] << 24;
    return result;
}

static uint64_t endian_host_to_be64(uint64_t x) {
    uint64_t result;
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

static uint64_t endian_host_to_le64(uint64_t x) {
    uint64_t result;
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

static uint64_t endian_le_to_host64(uint64_t x) {
    uint64_t result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (uint64_t) c[0];
    result |= (uint64_t) c[1] << 8;
    result |= (uint64_t) c[2] << 16;
    result |= (uint64_t) c[3] << 24;
    result |= (uint64_t) c[4] << 32;
    result |= (uint64_t) c[5] << 40;
    result |= (uint64_t) c[6] << 48;
    result |= (uint64_t) c[7] << 56;
    return result;
}

static uint64_t endian_be_to_host64(uint64_t x) {
    uint64_t result;
    unsigned char *c;

    c = (unsigned char *) &x;
    result = (uint64_t) c[7];
    result |= (uint64_t) c[6] << 8;
    result |= (uint64_t) c[5] << 16;
    result |= (uint64_t) c[4] << 24;
    result |= (uint64_t) c[3] << 32;
    result |= (uint64_t) c[2] << 40;
    result |= (uint64_t) c[1] << 48;
    result |= (uint64_t) c[0] << 56;
    return result;
}

#endif //RHC_ENDIAN_H
