#include "p/circle.h"

pIndices_s p_circle_og(pCircle_s a, const pCircle_s *b, int n) {
    pIndices_s res = {0};
    for (int i = 0; i < n; i++) {
        if (p_circle_oo(a, b[i]))
            res.data[res.num++] = i;
    }
    return res;
}


void p_circle_handle_elastic_collision(pCircle_s *a, pCircle_s *b, vec2 speed_a, vec2 speed_b) {

    // move a out of b
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float rr = a->r + b->r;

    float dist = sqrtf(dx * dx + dy * dy);

    // assumtion is wrong if collision is detected by a group and a was already moved...
    //s_assume(dist < rr, "not colliding");
    float shift = (rr - dist) / dist;
    shift *= 1.2f; // 20% behind b

    a->x += dx * shift;
    a->y += dy * shift;


    // elastic collision:
    // todo
    for (int i = 0; i < 2; i++) {
        float tmp = speed_a.v[i];
        speed_a.v[i] = speed_b.v[i];
        speed_b.v[i] = tmp;
    }

    float m_a = powf(a->r, 2);
    float m_b = powf(b->r, 2);
}
