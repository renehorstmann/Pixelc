#ifndef S_COMMON_H
#define S_COMMON_H

//
// some default includes, types and macros to use
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//
// Definitions
//

#define s_min(a, b) ((a)<(b)?(a):(b))
#define s_max(a, b) ((a)>(b)?(a):(b))

typedef uint8_t su8;
typedef int8_t si8;
typedef uint16_t su16;
typedef int16_t si16;
typedef uint32_t su32;
typedef int32_t si32;
typedef uint64_t su64;
typedef int64_t si64;
typedef float sf32;
typedef double sf64;
typedef si64 ssize;

#define S_U8_MIN 0
#define S_U8_MAX 255
#define S_I8_MIN (-128)
#define S_I8_MAX 127
#define S_U16_MIN 0
#define S_U16_MAX 65535
#define S_I16_MIN (-32768)
#define S_I16_MAX 32767
#define S_U32_MIN 0
#define S_U32_MAX 4294967295
#define S_I32_MIN (-2147483648)
#define S_I32_MAX 2147483647
#define S_U64_MIN 0
#define S_U64_MAX 18446744073709551615UL
#define S_I64_MIN (-9223372036854775808LL)
#define S_I64_MAX 9223372036854775807LL
#define S_SIZE_MIN (-9223372036854775808LL)
#define S_SIZE_MAX 9223372036854775807LL

//
// windows stuff
//

#ifdef PLATFORM_MSVC
#define _Thread_local __declspec(thread)
#endif

#endif //S_COMMON_H
