#include <stdio.h>
#include "thrd.h"

THREAD(float, foo_t, float, a);

float foo(float a) {
    printf("%f\n", a);
    return a / 2.0f;
}

int main() {
    thrd(foo_t) th;
    thrd_create(foo_t, th, foo, 3.14f);

    printf("%f\n", thrd_join(th));
    return 0;
}
