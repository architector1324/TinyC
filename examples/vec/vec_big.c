#include <stdio.h>
#include "vec.h"

BIG_VECTOR(float)

int main() {
    vec_big(float) v = vec_big_init(float)("tmp.dat");

    vec_push(v, 3.14f);
    vec_push(v, 2.71);
    vec_push(v, 1.0f);

    float a = vec_pop(v);
    printf("%f %f %f\nsize=%ld\n", vec_at(v, 0), vec_at(v, 1), a, v.size);

    vec_free(v);
    return 0;
}
