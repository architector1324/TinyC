#include <stdio.h>
#include "vec.h"

VECTOR(float)

int main() {
    vec(float) v = vec_init(float)();

    vec_push(v, 3.14f);
    vec_push(v, 2.71);
    vec_push(v, 1.0f);

    float b = vec_pop(v);
    printf("%f %f %f\n", v.data[0], v.data[1], b);
    printf("cap=%ld size=%ld\n", v.cap, v.size);

    vec_free(v);
}