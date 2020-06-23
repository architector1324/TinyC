#include <stdio.h>
#include "vec.h"

MICRO_VECTOR(float)

int main() {
    vec_micro(float) v = vec_micro_init(float)();

    vec_push(v, 3.14f);
    vec_push(v, 2.71);
    vec_push(v, 1.0f);

    float b = vec_pop(v);
    printf("%f %f %f\nsize=%ld\n", vec_at(v, 0), vec_at(v, 1), b, v.size);

    return 0;
}