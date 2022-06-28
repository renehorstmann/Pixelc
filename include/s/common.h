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

#define s_min(a, b) ((a)<(b)?(a):(b))
#define s_max(a, b) ((a)>(b)?(a):(b))


//
// windows stuff
//

#ifdef PLATFORM_MSVC
#define _Thread_local __declspec(thread)
#endif

#endif //S_COMMON_H
