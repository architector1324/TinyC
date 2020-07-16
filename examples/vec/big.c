#include <stdio.h>
#include "vec.h"

BIG_VECTOR(float)

int main() {
    vec_big(float) v = vec_big_init(float)("v.bin");

    // 10Gb
    for(size_t i = 0; i < 2684354560; i++) {
        vec_push(v, 3.14f);
    }
    printf("size=%ld\n", v.size);

    vec_free(v);
    return 0;
}