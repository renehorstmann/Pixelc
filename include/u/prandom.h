#ifndef U_PRANDOM_H
#define U_PRANDOM_H

//
// Pseudo random with m_random support
//

#include "s/s.h"

static const uint32_t uPRAND_MAX = 0xefffffff;

void u_pseed(uint32_t seed);

// [0 : uPRAND_MAX)
uint32_t u_prand();


#ifdef MAHTC_UTILS_RANDOM
#error include prandom.h before m/utils/random.h (m/m.h, m/utils/float.h)!
#endif

#define M_RANDOM_FUNCTION u_prand
#define M_RANDOM_FUNCTION_MAX uPRAND_MAX

#include "m/utils/random.h"

#endif //U_PRANDOM_H
