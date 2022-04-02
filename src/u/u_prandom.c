#include "u/prandom.h"


//
// private
//

static _Thread_local uint32_t x;
static const uint32_t a = 1103515245;
static const uint32_t c = 12345;


//
// public
//

void u_pseed(uint32_t seed) {
    x = seed % uPRAND_MAX;
}

uint32_t u_prand() {
    x = (a * x + c) % uPRAND_MAX;
    return x;
}

