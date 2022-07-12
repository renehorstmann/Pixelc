#ifndef U_PRANDOM_H
#define U_PRANDOM_H

//
// Pseudo random with m_random support
//

#include "s/s.h"

static const su32 uPRAND_MAX = 0xefffffff;

void u_pseed(su32 seed);

// [0 : uPRAND_MAX)
su32 u_prand();


#ifdef MAHTC_UTILS_RANDOM
#error include prandom.h before m/utils/random.h (m/m.h, m/utils/float.h)!
#endif

#define M_RANDOM_FUNCTION u_prand
#define M_RANDOM_FUNCTION_MAX uPRAND_MAX

#include "m/utils/random.h"

#endif //U_PRANDOM_H
