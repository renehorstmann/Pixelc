#ifndef P_CORE_H
#define P_CORE_H

//
// basic types for collision objects and groupd
//

#include "s/s.h"

#define P_MAX_INDICES 256

typedef struct {
    int data[P_MAX_INDICES];
    int num;
} pIndices_s;

#endif //P_CORE_H
