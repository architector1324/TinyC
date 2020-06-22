#include <stdio.h>
#include "bvec.h"

BIG_VECTOR(float)

int main() {
    bvec(float) v = bvec_init(float)("tmp.dat");

    bvec_push(v, 3.14f);
    bvec_push(v, 2.71);
    bvec_push(v, 1.0f);

    float a = bvec_pop(v);
    printf("%f %f %f\nsize=%ld\n", bvec_at(v, 0), bvec_at(v, 1), a, v.size);

    bvec_free(v);
    return 0;
}
