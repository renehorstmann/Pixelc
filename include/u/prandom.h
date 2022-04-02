#ifndef U_PRANDOM_H
#define U_PRANDOM_H

//
// Pseudo random with mathc_random support
//

#include <stdint.h>

static const uint32_t uPRAND_MAX = 0xefffffff;

void u_pseed(uint32_t seed);

// [0 : uPRAND_MAX)
uint32_t u_prand();


#ifdef MAHTC_UTILS_RANDOM
#error include prandom.h before mathc/utils/random.h (mathc/mathc.h, mathc/utils/float.h)!
#endif

#define MATHC_RANDOM_FUNCTION u_prand
#define MATHC_RANDOM_FUNCTION_MAX uPRAND_MAX

#include "mathc/utils/random.h"

#endif //U_PRANDOM_H
