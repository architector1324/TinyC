#include <stdio.h>
#include "bvec.h"

BIG_VECTOR(float)

int main() {
    bvec(float) v = bvec_init(float)("tmp.dat");

    // 10Gb
    for(size_t i = 0; i < 2684354560; i++) {
        bvec_push(v, 3.14f);
    }
    printf("size=%ld\n", v.size);

    bvec_free(v);
    return 0;
}