#ifndef U_PRANDOM_H
#define U_PRANDOM_H

#include <stdint.h>

static const uint32_t uPRAND_MAX = 0xefffffff;

void u_pseed(uint32_t seed);

uint32_t u_prand();

static float u_prandf() {
    return (float) u_prand() / uPRAND_MAX;	
}

static float u_prange(float begin, float end) {
	return begin + u_prandf() * (end - begin);
}

static float u_pnoise(float mean, float amplitude) {
	return mean - amplitude + 2 * amplitude * u_prandf();
}

#endif //U_PRANDOM_H
