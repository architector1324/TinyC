#include <stdio.h>

#include "ref.h"
#include "vec.h"

REF(float)
VECTOR(ref(float))

int main() {
    vec(ref(float)) v = vec_init(ref(float))();

    float a = 3.14f;
    float b = 2.71;

    vec_push(v, &a);
    vec_push(v, &b);

    printf("%f %f\n", *v.data[0], *v.data[1]);

    vec_free(v);

    return 0;
}