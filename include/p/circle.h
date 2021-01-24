#ifndef P_CIRCLE_H
#define P_CIRCLE_H


#include "math.h"
#include "stdbool.h"
#include "mathc/types/float.h"
#include "core.h"


typedef struct pCircle_s {
	float x, y, r;
} pCircle_s;


static bool p_circle_oo(pCircle_s a, pCircle_s b) {
	float d_sqr = powf(b.x-a.x, 2) + powf(b.y-a.y, 2);
	return d_sqr < powf(a.r+b.r, 2);
}


pIndices_s p_circle_og(pCircle_s a, const pCircle_s *b, int n);


void p_circle_handle_elastic_collision(pCircle_s *a, pCircle_s *b, vec2 speed_a, vec2 speed_b);


#endif //P_CIRCLE_H
