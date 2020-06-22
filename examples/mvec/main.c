#include <stdio.h>
#include "mvec.h"

MICRO_VECTOR(float)

int main() {
    mvec(float) v = mvec_init(float)();

    mvec_push(v, 3.14f);
    mvec_push(v, 2.71);
    mvec_push(v, 1.0f);

    float b = mvec_pop(v);
    printf("%f %f %f\nsize=%ld\n", v.data[0], v.data[1], b, v.size);

    return 0;
}